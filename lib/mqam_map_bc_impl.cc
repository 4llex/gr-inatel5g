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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "mqam_map_bc_impl.h"
extern "C" {
  #include "do_map.h"
}

namespace gr {
  namespace inatel5g {

    mqam_map_bc::sptr
    mqam_map_bc::make(int map_order)
    {
      return gnuradio::get_initial_sptr
        (new mqam_map_bc_impl(map_order));
    }

    /*
     * The private constructor
     */
    mqam_map_bc_impl::mqam_map_bc_impl(int map_order)
      : gr::sync_block("mqam_map_bc",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
	      d_map_order(map_order)
    {}

    /*
     * Our virtual destructor.
     */
    mqam_map_bc_impl::~mqam_map_bc_impl()
    {
    }
     
    int
    mqam_map_bc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      //gr_complex origin = gr_complex(0,0);
      

      // Do <+signal processing+> 
      do_map((modname_t)d_map_order, (uint8_t*)in, out, noutput_items); //(uint8_t*)in -> cast to convert CHAR to INT    
 
 
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }
    

  } /* namespace inatel5g */
} /* namespace gr */

