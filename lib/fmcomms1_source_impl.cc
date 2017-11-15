/* -*- c++ -*- */
/* 
 * Copyright 2017 CIDTE.
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
#include "fmcomms1_source_impl.h"

#include <cstdio>
#include <fstream>
#include <string>

namespace gr {
  namespace fmcomms1 {

    /* Constructor */
    fmcomms1_source::sptr
    fmcomms1_source::make(const std::string &uri, unsigned long frequency, 
              unsigned long samplerate, unsigned long bandwidth, 
              const std::vector<std::string> &channels, 
              unsigned int buffer_size, unsigned int decimation)
    {
      return gnuradio::get_initial_sptr
        (new fmcomms1_source_impl(fmcomms1_source_impl::get_context(uri), true,
                  frequency, samplerate, bandwidth, 
                  channels, buffer_size, decimation));
    }

    fmcomms1_source::sptr
    fmcomms1_source::make_from(struct iio_context *ctx,
              unsigned long frequency, unsigned long samplerate,
              unsigned long bandwidth,
              const std::vector<std::string> &channels,
              unsigned int buffer_size, unsigned int decimation)
    {
      return gnuradio::get_initial_sptr
        (new fmcomms1_source_impl(ctx, false, frequency, samplerate,
                  bandwidth, channels,
                  buffer_size, decimation));
    }

    /* Función recursiva para establecer los parámetros de la tarjeta */
    void fmcomms1_source_impl::set_parameters(struct iio_device *phy,
                  const std::vector<std::string> &params)
    {
      for (std::vector<std::string>::const_iterator it = params.begin(); it != params.end(); ++it)
      {
        struct iio_channel *chn = NULL;
        const char *attr = NULL;

        size_t pos;
        int ret;

        pos = it->find('=');
        if (pos == std::string::npos)
        {
          std::cerr << "Misformed line: " << *it << std::endl;
          continue;
        }

        std::string key = it->substr(0, pos);
        std::string val = it->substr(pos + 1, std::string::npos);

        ret = iio_device_identify_filename(phy, key.c_str(), &chn, &attr);

        if (ret)
        {
          std::cerr << "Parameter not recognized: " << key << std::endl;
          continue;
        }

        if (chn)
          ret = iio_channel_attr_write(chn, attr, val.c_str());
        else if (iio_device_find_attr(phy, attr))
          ret = iio_device_attr_write(phy, attr, val.c_str());
        else
          ret = iio_device_debug_attr_write(phy, attr, val.c_str());

        if (ret < 0)
        {
          std::cerr << "Unable to write attribute" << key << ": " << ret << std::endl;
        }
      }
    }

    
    /* Función para establecer los parámetros de los dispositivos */
    void fmcomms1_source_impl::set_params(unsigned long frequency,
            unsigned long samplerate, unsigned long bandwidth)
    {
      std::vector<std::string> params_dev, params_phy, params_vga;

      // Parámetros del dispositivo
      params_dev.push_back("in_voltage_sampling_frequency="+
              boost::to_string(samplerate));
      params_dev.push_back("in_voltage0_calibbias="+
              boost::to_string(bandwidth));
      params_dev.push_back("in_voltage1_calibbias="+
              boost::to_string(bandwidth));
      
      // Parámetros del dispositivo phy
      params_dev.push_back("out_altvoltage0_frequency="+
              boost::to_string(frequency));


      // Parámetros del dispositivo vga
      params_dev.push_back("out_voltage0_hardwaregain="+
        boost::to_string(20.0));
      params_dev.push_back("out_voltage1_hardwaregain="+
        boost::to_string(20.0));

      set_parameters(this->vga, params_vga);
      set_parameters(this->phy, params_phy);
      set_parameters(this->dev, params_dev);
    }

    /* Función para establecer el tamaño del búfer */
    void fmcomms1_source_impl::set_buffer_size(unsigned int _buffer_size)
    {
      iio_mutex.lock();

      bool started = !!buf;

      if (started)
      {
        iio_buffer_destroy(buf);

        buf = iio_device_create_buffer(dev, _buffer_size, false);

        if (!buf)
        {
          iio_mutex.unlock();
          throw std::runtime_error("Unable to create buffer");
        }
      }

      this -> buffer_size = _buffer_size;
      iio_mutex.unlock();
    }

    /* Función para obtener el contexto IIO */
    struct iio_context * fmcomms1_source_impl::get_context(const std::string &uri)
    {
      struct iio_context *ctx;

      if (uri.empty())
      {
        ctx = iio_create_default_context();

        if(!ctx)
          ctx = iio_create_network_context(NULL);
      } else {
        ctx = iio_create_context_from_uri(uri.c_str());

        if(!ctx)
          ctx = iio_create_network_context(uri.c_str());
      }

      return ctx;
    }

    /*
     * The private constructor
     */
    fmcomms1_source_impl::fmcomms1_source_impl(struct iio_context *ctx, 
              bool destroy_ctx, 
              unsigned long frequency, unsigned long samplerate, 
              unsigned long bandwidth,
              const std::vector<std::string> &channels,
              unsigned int buffer_size, unsigned int decimation)
      : gr::sync_block("fmcomms1_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, -1, sizeof(short))),
        ctx(ctx), buf(NULL),
        buffer_size(buffer_size),
        decimation(decimation),
        destroy_ctx(destroy_ctx)
    {
      unsigned int nb_channels, i;

      if(!ctx)
        throw std::runtime_error("Unable to create context.");

      dev = iio_context_find_device(ctx, "adf4351-rx-lpc");
      phy = iio_context_find_device(ctx, "cf-ad9643-core-lpc");
      vga = iio_context_find_device(ctx, "ad8366-lpc");

      if(!dev || !phy || !vga)
      {
        if (destroy_ctx)
          iio_context_destroy(ctx);
        throw std::runtime_error("Device not found");
      }

      //** Opcional, puede ir en la interfaz del bloque **//
      
      // Canal del dispositivo phy de la tarjeta-
      struct iio_channel *chn0 = iio_device_find_channel(phy, "altvoltage0", true);

      // Canal 0 del vga
      struct iio_channel *chn1 = iio_device_find_channel(vga, "voltage0", true);

      // Canal 1 del vga
      struct iio_channel *chn2 = iio_device_find_channel(vga, "voltage1", true);

      //Activación de los canales
      iio_channel_enable(chn0);
      iio_channel_enable(chn1);
      iio_channel_enable(chn2);

      //** Activación de los canales del dispositivo de recepción **//
      // Primero se desactivan todos, si están activados
      nb_channels = iio_device_get_channels_count(dev);
      for (i = 0; i < nb_channels; i++)
        iio_channel_disable(iio_device_get_channel(dev, i));

      if (channels.empty())
      {
        for (i = 0; i < nb_channels; i++)
        {
          struct iio_channel *chn = iio_device_get_channel(dev, i);

          iio_channel_enable(chn);
          channel_list.push_back(chn);
        }
      } else {
        for (std::vector<std::string>::const_iterator it =
             channels.begin(); it != channels.end(); ++it)
        {
          struct iio_channel *chn = 
              iio_device_find_channel(dev, it->c_str(), false);

          if (!chn)
          {
            if (destroy_ctx)
              iio_context_destroy(ctx);

            throw std::runtime_error("Channel not found");
          }

          iio_channel_enable(chn);
          channel_list.push_back(chn);
        }
      }

      set_params(frequency, samplerate, bandwidth);
      set_output_multiple(0x400);
    }

    /*
     * Our virtual destructor.
     */
    fmcomms1_source_impl::~fmcomms1_source_impl()
    {
      if (destroy_ctx)
        iio_context_destroy(ctx);
    }

    /* Lectura de los datos recibidos por el canal dado */
    void
    fmcomms1_source_impl::channel_read(const struct iio_channel *chn,
              void *dst, size_t len)
    {
      uintptr_t src_ptr, dst_ptr = (uintptr_t) dst, end = dst_ptr + len;
      unsigned int length = iio_channel_get_data_format(chn)->length / 8;
      uintptr_t buf_end = (uintptr_t) iio_buffer_end(buf);
      ptrdiff_t buf_step = iio_buffer_step(buf) * (decimation + 1);

      for (src_ptr = (uintptr_t) iio_buffer_first(buf, chn) + byte_offset;
      src_ptr < buf_end && dst_ptr + length <= end;
      src_ptr += buf_step, dst_ptr += length)
      {
        iio_channel_convert(chn, (void *) dst_ptr, (const void *) src_ptr);
      }
    }


    /* Donde se realiza el trabajo */
    int
    fmcomms1_source_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {

      iio_mutex.lock();

      // Do <+signal processing+>

      if (!items_in_buffer)
      {
        int ret = iio_buffer_refill(buf);
        if (ret < 0)
        {
          iio_mutex.unlock();

          char buf[256];
          iio_strerror(-ret, buf, sizeof(buf));
          std::string error(buf);

          throw std::runtime_error("Unable to refill buffer: " + error);
        }

        items_in_buffer = (unsigned long) ret / iio_buffer_step(buf);
        byte_offset = 0;
      }

      unsigned long items = std::min(items_in_buffer, (unsigned long) noutput_items);

      for (unsigned int i = 0; i < output_items.size(); i++)
      {
        channel_read(channel_list[i], output_items[i], items * sizeof(short));

        if (!byte_offset)
        {
          tag_t tag;
          tag.value = pmt::from_long(items_in_buffer);
          tag.offset = sample_counter;
          tag.key = pmt::intern("buffer_start");
          tag.srcid = alias_pmt();
          add_item_tag(i, tag);
        }
      }

      sample_counter += items;
      items_in_buffer -= items;
      byte_offset += items * iio_buffer_step(buf);

      iio_mutex.unlock();

      // Tell runtime system how many output items we produced
      return (int) items;
    }

    /* Funciones de inicio y finalización */
    bool fmcomms1_source_impl::start()
    {
      sample_counter = 0;
      items_in_buffer = 0;

      buf = iio_device_create_buffer(dev, buffer_size, false);
      return !!buf;
    }

    bool fmcomms1_source_impl::stop()
    {
      if (buf)
      {
        iio_buffer_destroy(buf);
        buf = NULL;
      }

      return true;
    }
  } /* namespace fmcomms1 */
} /* namespace gr */

