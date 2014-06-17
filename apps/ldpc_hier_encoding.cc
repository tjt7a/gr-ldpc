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
#include "ldpc_hier_encoder_bb.h"

using namespace gr;

 // Imports
 int main(int argc, char **argv){

 	const char* fname = "/home/tjt7a/src/gr-ldpc/apps/inputs/96.3.963";
 	std::vector<float> symbol_table;
 	symbol_table.push_back(1);
 	symbol_table.push_back(-1);
 	const int D = 1; // Set dimmension to 1

 	gr::top_block_sptr tb = gr::make_top_block("ldpc_hier_encoding");
 	ldpc_hier_encoder_bb_sptr encoder = ldpc_hier_encoder_bb_make(fname);
 	gr::digital::chunks_to_symbols_bf::sptr chunks_to_symbols = gr::digital::chunks_to_symbols_bf::make(symbol_table, D);
 	gr::blocks::packed_to_unpacked_bb::sptr pack2unpack = gr::blocks::packed_to_unpacked_bb::make(1, gr::GR_MSB_FIRST);

 	const char* in_file = "/home/tjt7a/src/gr-ldpc/apps/inputs/BonkEnc_test15_level8_5s_VBR_280kbps_Mono_32000Hz_16bit.flac";
 	const char* out_file = "/home/tjt7a/src/gr-ldpc/apps/inputs/out_encoded";

 	gr::blocks::file_source::sptr source = gr::blocks::file_source::make(sizeof(char), in_file, false);
 	gr::blocks::file_sink::sptr sink = gr::blocks::file_sink::make(sizeof(float), out_file);

 	// Connect source -> packedtounpacked -> encoder -> chunkstosymbols -> sink
 	tb->connect(source, 0, pack2unpack, 0);
 	tb->connect(pack2unpack, 0, encoder, 0);
 	tb->connect(encoder, 0, chunks_to_symbols, 0);
 	tb->connect(chunks_to_symbols, 0, sink, 0);

 	// Run the encoder
 	tb->run();

 	return 0;
 }