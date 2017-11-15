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


#ifndef INCLUDED_FMCOMMS1_FMCOMMS1_SINK_H
#define INCLUDED_FMCOMMS1_FMCOMMS1_SINK_H

#include <fmcomms1/api.h>
#include <gnuradio/sync_block.h>

#define DEFAULT_BUFFER_SIZE 0x8000

extern "C" {
  struct iio_context;
};

namespace gr {
  namespace fmcomms1 {

    /*!
     * \brief <+description of block+>
     * \ingroup fmcomms1
     *
     */
    class FMCOMMS1_API fmcomms1_sink : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<fmcomms1_sink> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of fmcomms1::fmcomms1_sink.
       *
       * To avoid accidental use of raw pointers, fmcomms1::fmcomms1_sink's
       * constructor is in a private implementation
       * class. fmcomms1::fmcomms1_sink::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string &uri, unsigned long frequency, 
          unsigned long samplerate, unsigned long bandwidth, 
          const std::vector<std::string> &channels, 
          unsigned int buffer_size = DEFAULT_BUFFER_SIZE, 
          unsigned int interpolation = 0,
          bool cyclic = false);

      static sptr make_from(struct iio_context *ctx, 
          unsigned long frequency, unsigned long samplerate, 
          unsigned long bandwidth,
          const std::vector<std::string> &channels, 
          unsigned int buffer_size = DEFAULT_BUFFER_SIZE, 
          unsigned int interpolation = 0,
          bool cyclic = false);
    };

  } // namespace fmcomms1
} // namespace gr

#endif /* INCLUDED_FMCOMMS1_FMCOMMS1_SINK_H */

