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

#ifndef INCLUDED_FMCOMMS1_FMCOMMS1_SINK_IMPL_H
#define INCLUDED_FMCOMMS1_FMCOMMS1_SINK_IMPL_H

#include <string>
#include <vector>

#include <iio.h>
#include <boost/thread.hpp>
#include <fmcomms1/fmcomms1_sink.h>

namespace gr {
  namespace fmcomms1 {

    class fmcomms1_sink_impl : public fmcomms1_sink
    {
     private:
      void channel_write(const struct iio_channel *chn,
           const void *src, size_t len);
      bool cyclic;

     protected:
      struct iio_context *ctx;
      struct iio_device *dev, *phy, *vga;
      struct iio_buffer *buf;
      std::vector <struct iio_channel *> channel_list;
      unsigned int buffer_size;
      unsigned int interpolation;
      bool destroy_ctx;

     public:
      fmcomms1_sink_impl(struct iio_context *ctx, 
          bool destroy_ctx, unsigned long frequency, 
          unsigned long samplerate, unsigned long bandwidth,
          const std::vector<std::string> &channels, 
          unsigned int buffer_size = DEFAULT_BUFFER_SIZE, 
          unsigned int interpolation = 0,
          bool cyclic = false);
      ~fmcomms1_sink_impl();

      void set_params(unsigned long frequency,
            unsigned long samplerate, unsigned long bandwidth);

      int work_from(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
      
      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);

      void forecast(int noutput_items, gr_vector_int &ninput_items_required);
    };

  } // namespace fmcomms1
} // namespace gr

#endif /* INCLUDED_FMCOMMS1_FMCOMMS1_SINK_IMPL_H */

