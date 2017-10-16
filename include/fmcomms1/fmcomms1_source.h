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


#ifndef INCLUDED_FMCOMMS1_FMCOMMS1_SOURCE_H
#define INCLUDED_FMCOMMS1_FMCOMMS1_SOURCE_H

#include <fmcomms1/api.h>
#include <gnuradio/sync_block.h>

#define DEFAULT_BUFFER_SIZE 0x8000

/* Declaración de la estructura externa de libiio */
extern "C"{
  struct iio_context;
};

namespace gr {
  namespace fmcomms1 {

     /*!
     * \brief <+description of block+>
     * \ingroup fmcomms1
     *
     */
    class FMCOMMS1_API fmcomms1_source : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<fmcomms1_source> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of fmcomms1::fmcomms1_source.
       *
       * To avoid accidental use of raw pointers, fmcomms1::fmcomms1_source's
       * constructor is in a private implementation
       * class. fmcomms1::fmcomms1_source::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string &uri, unsigned long frequency, 
          unsigned long samplerate, unsigned long bandwidth, 
          const std::string &device, 
          const std::vector<std::string> &channels, 
          const std::string &device_phy, 
          unsigned int buffer_size = DEFAULT_BUFFER_SIZE, 
          unsigned int decimation = 0);

      static sptr make_from(struct iio_context *ctx, 
          unsigned long frequency, unsigned long samplerate, 
          unsigned long bandwidth, 
          const std::string &device, 
          const std::vector<std::string> &channels, 
          const std::string &device_phy, 
          unsigned int buffer_size = DEFAULT_BUFFER_SIZE, 
          unsigned int decimation = 0);

      virtual void set_buffer_size(unsigned int buffer_size) = 0;
    };

  } // namespace fmcomms1
} // namespace gr

#endif /* INCLUDED_FMCOMMS1_FMCOMMS1_SOURCE_H */

