/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_INATEL5G_MQAM_MAP_BC_H
#define INCLUDED_INATEL5G_MQAM_MAP_BC_H

#include <inatel5g/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace inatel5g {

    /*!
     * \brief <+description of block+>
     * \ingroup inatel5g
     *
     */
    class INATEL5G_API mqam_map_bc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<mqam_map_bc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of inatel5g::mqam_map_bc.
       *
       * To avoid accidental use of raw pointers, inatel5g::mqam_map_bc's
       * constructor is in a private implementation
       * class. inatel5g::mqam_map_bc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int map_order);
    };

  } // namespace inatel5g
} // namespace gr

#endif /* INCLUDED_INATEL5G_MQAM_MAP_BC_H */

