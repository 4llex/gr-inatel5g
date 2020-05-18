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

#ifndef INCLUDED_INATEL5G_MQAM_MAP_BC_IMPL_H
#define INCLUDED_INATEL5G_MQAM_MAP_BC_IMPL_H

#include <inatel5g/mqam_map_bc.h>

namespace gr {
  namespace inatel5g {

    class mqam_map_bc_impl : public mqam_map_bc
    {
     private:
     int d_map_order; // Mapping Order

     public:
      mqam_map_bc_impl(int map_order);
      ~mqam_map_bc_impl();

      
      gr_complex get_complex_symbol(const char &sample);


      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
 
     
    };

  } // namespace inatel5g
} // namespace gr

#endif /* INCLUDED_INATEL5G_MQAM_MAP_BC_IMPL_H */

