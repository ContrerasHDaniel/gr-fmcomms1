/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "fmcomms1_sink_impl.h"
#include "fmcomms1_source_impl.h"

#include <cstdio>

namespace gr {
  namespace fmcomms1 {

    fmcomms1_sink::sptr
    fmcomms1_sink::make(const std::string &uri, unsigned long frequency, 
          unsigned long samplerate, unsigned long bandwidth, 
          const std::vector<std::string> &channels, 
          unsigned int buffer_size, 
          unsigned int interpolation,
          bool cyclic)
    {
      return gnuradio::get_initial_sptr
        (new fmcomms1_sink_impl(fmcomms1_source_impl::get_context(uri), true,
                      frequency, samplerate, bandwidth,
                      channels, buffer_size, interpolation, cyclic));
    }

    fmcomms1_sink::sptr
    fmcomms1_sink::make_from(struct iio_context *ctx, 
          unsigned long frequency, unsigned long samplerate, 
          unsigned long bandwidth,
          const std::vector<std::string> &channels, 
          unsigned int buffer_size, 
          unsigned int interpolation,
          bool cyclic)
    {
      return gnuradio::get_initial_sptr
        (new fmcomms1_sink_impl(ctx, false, frequency, samplerate,
                      bandwidth, channels, buffer_size, interpolation, cyclic));
    }

    /* Función para establecer los parámetros de los dispositivos de transmisión */
    void
    fmcomms1_sink_impl::set_params(unsigned long frequency,
              unsigned long samplerate, unsigned long bandwidth)
    {
      std::vector<std::string> params_dev, params_phy;

      // Parámetros del dispositivo de transmisión
      params_dev.push_back("out_altvoltage_sampling_frequency="+
              boost::to_string(frequency));
      params_dev.push_back("out_voltage0_calibbias="+
              boost::to_string(bandwidth/1000000));
      params_dev.push_back("out_voltage1_calibbias="+
              boost::to_string(bandwidth/1000000));

      // Parámetros del dispositivo DAC
      params_phy.push_back("out_altvoltage0_frequency="+
              boost::to_string(frequency));

      fmcomms1_source_impl::set_parameters(this->dev, params_dev);
      fmcomms1_source_impl::set_parameters(this->phy, params_phy);

    }

    /*
     * The private constructor
     */
    fmcomms1_sink_impl::fmcomms1_sink_impl(struct iio_context *ctx, 
          bool destroy_ctx, unsigned long frequency, 
          unsigned long samplerate, unsigned long bandwidth,
          const std::vector<std::string> &channels, 
          unsigned int buffer_size, 
          unsigned int interpolation, bool cyclic)
      : gr::sync_block("fmcomms1_sink",
              gr::io_signature::make(1, -1, sizeof(short)),
              gr::io_signature::make(0, 0, 0)),
      ctx(ctx),
      interpolation(interpolation),
      buffer_size(buffer_size),
      destroy_ctx(destroy_ctx)
    {
      unsigned int nb_channels, i;

      /* Set minimum input size*/
      set_output_multiple(buffer_size /(interpolation + 1));

      if (!ctx)
        throw std::runtime_error("Unable to create context");

      dev = iio_context_find_device(ctx, "cf-ad9122-core-lpc");
      phy = iio_context_find_device(ctx, "adf4351-tx-lpc");

      if(!dev || !phy)
      {
        if (destroy_ctx)
          iio_context_destroy(ctx);
        throw std::runtime_error("Device not found");
      }


      //** Opcional, puede ir en la interfaz del bloque **//
      
      // Canal del dispositivo phy de la tarjeta-
      struct iio_channel *chn0 = iio_device_find_channel(phy, "altvoltage0", true);


      // Canal 1 del vga
      //struct iio_channel *chn2 = iio_device_find_channel(vga, "voltage1", true);

      struct iio_channel *chn1 = iio_device_find_channel(dev, "voltage0", true);
      struct iio_channel *chn2 = iio_device_find_channel(dev, "voltage1", true);

      //Activación de los canales
      iio_channel_enable(chn0);

      //** Activación de los canales del dispositivo de transmisión **//
      // Primero se desactivan todos, si están activados
      nb_channels = iio_device_get_channels_count(dev);
      for (i = 0; i < nb_channels; i++)
        iio_channel_disable(iio_device_get_channel(dev, i));

      if (channels.empty()) {
        for (i = 0; i < nb_channels; i++) {
          struct iio_channel *chn =
            iio_device_get_channel(dev, i);

          iio_channel_enable(chn);
          channel_list.push_back(chn);
        }
      } else {
        for (std::vector<std::string>::const_iterator it =
            channels.begin();
            it != channels.end(); ++it) {
          struct iio_channel *chn =
            iio_device_find_channel(dev,
                it->c_str(), true);
          if (!chn) {
            if (destroy_ctx)
              iio_context_destroy(ctx);
            throw std::runtime_error(
                "Channel not found");
          }

          iio_channel_enable(chn);
          if (!iio_channel_is_enabled(chn))
            throw std::runtime_error(
                "Channel not enabled");
          channel_list.push_back(chn);
        }
      }


      set_params(frequency, samplerate, bandwidth);

      buf = iio_device_create_buffer(dev, buffer_size, cyclic);

      if(!buf)
        throw std::runtime_error("Unable to create buffer: " + boost::to_string(-errno));

    }

    /*
     * Our virtual destructor.
     */
    fmcomms1_sink_impl::~fmcomms1_sink_impl()
    {
      iio_buffer_destroy(buf);
      if (destroy_ctx)
        iio_context_destroy(ctx);
    }

    void
    fmcomms1_sink_impl::channel_write(const struct iio_channel *chn,
        const void *src, size_t len)
    {
      uintptr_t dst_ptr, src_ptr = (uintptr_t) src, end = src_ptr + len;
      unsigned int length = iio_channel_get_data_format(chn)->length / 8;
      uintptr_t buf_end = (uintptr_t) iio_buffer_end(buf);
      ptrdiff_t buf_step = iio_buffer_step(buf) * (interpolation + 1);

      for (dst_ptr = (uintptr_t) iio_buffer_first(buf, chn);
          dst_ptr < buf_end && src_ptr + length <= end;
          dst_ptr += buf_step, src_ptr += length)
            iio_channel_convert_inverse(chn,
            (void *) dst_ptr, (const void *) src_ptr);

    }

    int
    fmcomms1_sink_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      int ret;

      if (interpolation >= 1) {
        ptrdiff_t len = (intptr_t) iio_buffer_end(buf)
        - (intptr_t) iio_buffer_start(buf);
        memset(iio_buffer_start(buf), 0, len);
      }

      for (unsigned int i = 0; i < input_items.size(); i++)
            channel_write(channel_list[i], input_items[i],
            noutput_items * sizeof(short));

      ret = iio_buffer_push(buf);
      if (ret < 0) {
        char buf[256];
        iio_strerror(-ret, buf, sizeof(buf));
        std::string error(buf);

        throw std::runtime_error("Unable to push buffer: " + error);
      }

      consume_each(buffer_size / (interpolation + 1));
      return 0;
    }

    void
    fmcomms1_sink_impl::forecast(int noutput_items,
              gr_vector_int &ninput_items_required)
    {
      for (unsigned int i = 0; i < ninput_items_required.size(); i++)
        ninput_items_required[i] = noutput_items;
    }

  } /* namespace fmcomms1 */
} /* namespace gr */

