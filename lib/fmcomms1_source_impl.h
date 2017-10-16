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

#ifndef INCLUDED_FMCOMMS1_FMCOMMS1_SOURCE_IMPL_H
#define INCLUDED_FMCOMMS1_FMCOMMS1_SOURCE_IMPL_H

#include <string>
#include <vector>

#include <iio.h>
#include <boost/thread.hpp>
#include <fmcomms1/fmcomms1_source.h>

namespace gr {
  namespace fmcomms1 {

  /*
    ***
    *** Declaración de las variables y funciones utilizadas en el script fmcomms1_source_impl.cc
    *** Obligatorio en el estándar de GNU Radio
    */

    class fmcomms1_source_impl : public fmcomms1_source
    {
     private:
      void channel_read(const struct iio_channel *chn, void *dst, size_t len);

      boost::mutex iio_mutex;
      unsigned long items_in_buffer;
      off_t byte_offset;
      unsigned long sample_counter;

     protected:
      struct iio_context *ctx;
      struct iio_device *dev, *phy, *vga;
      struct iio_buffer *buf;
      std::vector<struct iio_channel*> channel_list;
      unsigned int buffer_size;
      unsigned int decimation;
      bool destroy_ctx;

     public:
      fmcomms1_source_impl(struct iio_context *ctx, 
        bool destroy_ctx,
        unsigned long frequency, unsigned long samplerate,
        unsigned long bandwidth,
        const std::string &device,
        const std::vector<std::string> &channels,
        const std::string &device_phy,
        unsigned int buffer_size = DEFAULT_BUFFER_SIZE,
        unsigned int decimation = 0);
      ~fmcomms1_source_impl();

      void set_params(unsigned long frequency,
            unsigned long samplerate, unsigned long bandwidth);

      void set_parameters(struct iio_device *phy,
            const std::vector<std::string> &params);

      void set_buffer_size(unsigned int buffer_size);
      
      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      bool start();
      bool stop();

      static struct iio_context * get_context(const std::string &uri);
    };

  } // namespace fmcomms1
} // namespace gr

#endif /* INCLUDED_FMCOMMS1_FMCOMMS1_SOURCE_IMPL_H */

