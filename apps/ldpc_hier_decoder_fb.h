/* -*- c++ -*- */
/*
 * Copyright 2014 Tommy James Tracy II (University of Virginia)
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_LDPC_HIER_DECODER_FB_H
#define INCLUDED_LDPC_HIER_DECODER_FB_H

#include <gnuradio/hier_block2.h>

class ldpc_hier_decoder_fb;

typedef boost::shared_ptr<ldpc_hier_decoder_fb> ldpc_hier_decoder_fb_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of LDPC_HIER_DECODER_FB
 *
 * This is effectively the public constructor. To avoid accidental use
 * of raw pointers, fcd_source_c's constructor is private.
 */

ldpc_hier_decoder_fb_sptr ldpc_hier_decoder_fb_make(const char * alist_file, float sigma, int max_iterations);

// Hier2 block for LDPC_HIER_DECODER block
class ldpc_hier_decoder_fb : public gr::hier_block2
{

public:
   ldpc_hier_decoder_fb(const char * alist_file, float sigma, int max_iterations); 
   ~ldpc_hier_decoder_fb();
};

#endif /* INCLUDED_LDPC_HIER_DECODER_FB_H */