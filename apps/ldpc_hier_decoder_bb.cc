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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ldpc_hier_decoder_bb.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/hier_block2.h>
#include <gnuradio/blocks/vector_to_stream.h>
#include <gnuradio/blocks/stream_to_vector.h>
#include <ldpc/ldpc_decoder_bb.h>

/*
 * The public constructor.
 */
ldpc_hier_decoder_bb_sptr ldpc_hier_decoder_bb_make(const char * alist_file, float sigma, int max_iterations)
{
    return gnuradio::get_initial_sptr(new ldpc_hier_decoder_bb(alist_file, sigma, max_iterations));
}

/*
	LDPC Hierarchical Decoder (BB) Block
*/
 ldpc_hier_decoder_bb::ldpc_hier_decoder_bb(const char * alist_file, float sigma, int max_iterations)
        :hier_block2("ldpc_hier_decoder_bb", 
                            gr::io_signature::make(1, 1, sizeof(char)),
                            gr::io_signature::make(1, 1, sizeof(char)))
 {

	gr::ldpc::ldpc_decoder_bb::sptr decoder = gr::ldpc::ldpc_decoder_bb::make(alist_file, sigma, max_iterations);

	int K = decoder->get_K();
	int N = decoder->get_N();

	gr::blocks::stream_to_vector::sptr str2Nvec = gr::blocks::stream_to_vector::make(4, N);
	gr::blocks::vector_to_stream::sptr Kvec2str = gr::blocks::vector_to_stream::make(1, K);

	/*
 	*	Connect input to strNvec to decoder to Kvec2str, and to output
 	*/
	
	// Connect the blocks in the hierarchical block
    connect(self(), 0, str2Nvec, 0);
    connect(str2Nvec, 0, decoder, 0);
	connect(decoder, 0, Kvec2str, 0);
	connect(Kvec2str, 0, self(), 0);
 }

// Destructor
ldpc_hier_decoder_bb::~ldpc_hier_decoder_bb ()
{

}