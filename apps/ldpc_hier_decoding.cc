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

#include <gnuradio/top_block.h>
#include <gnuradio/blocks/file_sink.h>
#include <gnuradio/blocks/file_source.h>
#include <gnuradio/blocks/unpacked_to_packed_bb.h>
#include <gnuradio/blocks/packed_to_unpacked_bb.h>
#include <gnuradio/digital/chunks_to_symbols_bf.h>
#include <router/throughput.h>
#include "ldpc_hier_decoder_fb.h"

using namespace gr;

 // Imports
 int main(int argc, char **argv){

    float noise_ampl;
    std::string in_file_name = "/home/tjt7a/src/gr-ldpc/apps/inputs/";
    std::string out_file_name = "/home/tjt7a/src/gr-ldpc/apps/inputs/";
     
     if(argc < 2){
        std::cout << "Useage: ldpc_hier_decoding <input file name> < output file name>" << std::endl;
     }
     else{
        in_file_name += argv[1];
        out_file_name += argv[2];
    }
     
     
 	const char* fname = "/home/tjt7a/src/gr-ldpc/apps/inputs/96.3.963";
 	float sigma = 0.5;
 	int max_iterations = 100;

 	gr::top_block_sptr tb = gr::make_top_block("ldpc_hier_decoding");
 	
 	ldpc_hier_decoder_fb_sptr decoder = ldpc_hier_decoder_fb_make(fname, sigma, max_iterations);
 	
 	gr::blocks::unpacked_to_packed_bb::sptr unpack2pack = gr::blocks::unpacked_to_packed_bb::make(1, gr::GR_MSB_FIRST);

 	gr::blocks::file_source::sptr source = gr::blocks::file_source::make(sizeof(float), in_file_name.c_str(), true);
 	gr::blocks::file_sink::sptr sink = gr::blocks::file_sink::make(sizeof(char), out_file_name.c_str());

	gr::router::throughput::sptr throughput = gr::router::throughput::make(sizeof(char), 2, 0);

 	// Connect source -> decoder -> unpackedtopacked -> sink
 	tb->connect(source, 0, decoder, 0);
 	tb->connect(decoder, 0, unpack2pack, 0);
	tb->connect(unpack2pack, 0, throughput, 0);
	tb->connect(throughput, 0, sink, 0);

 	tb->run();

 	return 0;
 }
