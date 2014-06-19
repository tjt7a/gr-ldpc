/*
 * Copyright 2014 Tommy Tracy II (University of Virginia) 
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

// Include header files for each block used in flowgraph

#include <gnuradio/top_block.h>

#include <gnuradio/blocks/file_source.h>
#include <gnuradio/blocks/file_sink.h>
#include <gnuradio/blocks/throttle.h>

#include <gnuradio/blocks/unpacked_to_packed_bb.h>
#include <gnuradio/blocks/packed_to_unpacked_bb.h>
#include <gnuradio/digital/chunks_to_symbols_bf.h>
#include "ldpc_hier_decoder_fb.h"

#include <boost/lockfree/queue.hpp>

// For input queue
#include <router/queue_sink.h>
#include <router/queue_source.h>

// Throughput measuring
#include <router/throughput.h>
#include <router/throughput_sink.h>

// For output queue
#include <router/queue_sink_byte.h>
#include <router/queue_source_byte.h>

#include <boost/thread.hpp>
#include <router/root.h>
#include <vector>
#include <cstdio>

using namespace gr;

int main(int argc, char **argv){

	/*
		LDPC Decoder Blocks
	*/

	const char* fname = "/home/tjt7a/src/git/gr-ldpc/apps/inputs/96.3.963";
	float sigma = 0.0;
	int max_iterations = 100;

	// Create symbol table
	std::vector<float> symbol_table;
	symbol_table.push_back(1);
	symbol_table.push_back(-1);


	const int D = 1; // Set dimmension to 1


	gr::top_block_sptr tb = gr::make_top_block("LDPC Parent");

	ldpc_hier_decoder_fb_sptr decoder = ldpc_hier_decoder_fb_make(fname, sigma, max_iterations);
	gr::digital::chunks_to_symbols_bf::sptr chunks_to_symbols = gr::digital::chunks_to_symbols_bf::make(symbol_table, D);
	gr::blocks::unpacked_to_packed_bb::sptr unpacked2packed = gr::blocks::unpacked_to_packed_bb::make(1, gr::GR_MSB_FIRST);

	const char* in_file = "/home/tjt7a/src/git/gr-ldpc/apps/inputs/out_encoded";
	const char* out_file = "/home/tjt7a/src/git/gr-ldpc/apps/inputs/out_decoded";
	int number_of_children = 1;
	double throughput_value = 0.11e6;


	if(argc > 1)
		throughput_value = atof(argv[1]);
		//number_of_children = atoi(argv[1]);

	gr::blocks::file_source::sptr src = gr::blocks::file_source::make(sizeof(float), in_file, true);
	gr::blocks::file_sink::sptr sink = gr::blocks::file_sink::make(sizeof(char), out_file);

	// Input and Output Queue
	boost::lockfree::queue< std::vector<float>*, boost::lockfree::fixed_sized<true> > input_queue(1000);
	boost::lockfree::queue< std::vector<char>*, boost::lockfree::fixed_sized<true> > output_queue(1000);

	//gr::router::root::sptr root_router = gr::router::root::make(number_of_children, input_queue, output_queue, throughput_value);

	gr::router::queue_sink::sptr input_queue_sink = gr::router::queue_sink::make(sizeof(float), input_queue, false);
	gr::router::queue_source::sptr input_queue_source = gr::router::queue_source::make(sizeof(float), input_queue, false, false);

	gr::router::queue_sink_byte::sptr output_queue_sink = gr::router::queue_sink_byte::make(sizeof(char), output_queue, false);
	gr::router::queue_source_byte::sptr output_queue_source = gr::router::queue_source_byte::make(sizeof(char), output_queue, false, false);

	/* Throttles */
	gr::blocks::throttle::sptr throttle_0 = gr::blocks::throttle::make(sizeof(float), /*(768/50)**/throughput_value);
	//gr::blocks::throttle::sptr throttle_1 = gr::blocks::throttle::make(sizeof(char), 1e6);
	//gr::blocks::throttle::sptr throttle_2 = gr::blocks::throttle::make(sizeof(char), 1e6);

	/* Throughput */
	//gr::router::throughput_sink::sptr throughput_sink = gr::router::throughput_sink::make(sizeof(char), 10, 0);
	gr::router::throughput::sptr throughput = gr::router::throughput::make(sizeof(char), 1, 0);


	/*
		Input Queue Population
	*/

	tb->connect(src, 0, throttle_0, 0);
	tb->connect(throttle_0, 0, input_queue_sink, 0);
	//tb->connect(src, 0, input_queue_sink, 0);

	/*
		Handler Code
	*/

	tb->connect(input_queue_source, 0, decoder, 0);
	tb->connect(decoder, 0, unpacked2packed, 0);
	//tb->connect(unpacked2packed, 0, throttle_2, 0);
	//tb->connect(throttle_2, 0, output_queue_sink, 0);
	tb->connect(unpacked2packed, 0, output_queue_sink, 0);

	/*
		Order and sink results
	*/

	tb->connect(output_queue_source, 0, throughput, 0); // Print the throughputwo
	//tb->connect(output_queue_source, 0, throttle_1, 0);
	//tb->connect(throttle_1, 0, sink, 0);
	tb->connect(throughput, 0, sink, 0);


	tb->run();

	return 0;
}
