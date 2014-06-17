/* -*- c++ -*- */
/* 
 * Copyright 2013 IIT Bombay.
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

#ifndef INCLUDED_LDPC_LDPC_DECODER_FB_IMPL_H
#define INCLUDED_LDPC_LDPC_DECODER_FB_IMPL_H

#include <ldpc/ldpc_decoder_fb.h>
#include "alist.h"
#include "cldpc.h"
#include "awgn_bp.h"

namespace gr {
  namespace ldpc {

    class ldpc_decoder_fb_impl : public ldpc_decoder_fb
    {
     private:
      alist d_list;
      cldpc d_code;
      awgn_bp d_spa;
      int N;
      int K;
      int n_iterations;

     public:
      ldpc_decoder_fb_impl(const char * alist_file, float sigma, int max_iterations);
      ~ldpc_decoder_fb_impl();
      int get_K();
      int get_N();
      int get_niterations();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace ldpc
} // namespace gr

#endif /* INCLUDED_LDPC_LDPC_DECODER_FB_IMPL_H */