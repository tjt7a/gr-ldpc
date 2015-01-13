# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

include_directories(
        ${GR_DIGITAL_INCLUDE_DIRS}
	${GR_AUDIO_INCLUDE_DIRS}
        ${GR_ANALOG_INCLUDE_DIRS}
        ${GNURADIO_RUNTIME_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        ${GR_BLOCKS_INCLUDE_DIRS}
	${GR_LDPC_INCLUDE_DIRS}
)

#add_executable(dial_tone ${CMAKE_CURRENT_SOURCE_DIR}/dial_tone.cc)
add_executable(ldpc_hier_test ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_test.cc ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_decoder_fb.cc ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_encoder_bb.cc)
add_executable(ldpc_hier_decoding ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_decoding.cc ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_decoder_fb.cc)
add_executable(ldpc_hier_encoding ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_encoding.cc ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_encoder_bb.cc)
add_executable(ldpc_parent ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_parent.cc ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_decoder_fb.cc)
add_executable(ldpc_child ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_child.cc ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_decoder_fb.cc)
add_executable(ldpc_decoder_with_queues ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_decoder_with_queues.cc ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_decoder_fb.cc ${CMAKE_CURRENT_SOURCE_DIR}/ldpc_hier_encoder_bb.cc)

#include(GrPython)

#target_link_libraries(dial_tone
#  ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES} ${GNURADIO_ANALOG_LIBRARIES} ${GNURADIO_AUDIO_LIBRARIES} ${GNURADIO_BLOCKS_LIBRARIES})

target_link_libraries(ldpc_hier_test
  ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES} ${GNURADIO_ANALOG_LIBRARIES} ${GNURADIO_AUDIO_LIBRARIES} ${GNURADIO_BLOCKS_LIBRARIES} ${GNURADIO_LDPC_LIBRARIES} ${GNURADIO_DIGITAL_LIBRARIES})

target_link_libraries(ldpc_hier_decoding
  ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES} ${GNURADIO_ANALOG_LIBRARIES} ${GNURADIO_AUDIO_LIBRARIES} ${GNURADIO_BLOCKS_LIBRARIES} ${GNURADIO_LDPC_LIBRARIES} ${GNURADIO_DIGITAL_LIBRARIES})

target_link_libraries(ldpc_hier_encoding
  ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES} ${GNURADIO_ANALOG_LIBRARIES} ${GNURADIO_AUDIO_LIBRARIES} ${GNURADIO_BLOCKS_LIBRARIES} ${GNURADIO_LDPC_LIBRARIES} ${GNURADIO_DIGITAL_LIBRARIES})

target_link_libraries(ldpc_parent
  ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES} ${GNURADIO_ANALOG_LIBRARIES} ${GNURADIO_AUDIO_LIBRARIES} ${GNURADIO_BLOCKS_LIBRARIES} ${GNURADIO_LDPC_LIBRARIES} ${GNURADIO_DIGITAL_LIBRARIES})

target_link_libraries(ldpc_child
  ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES} ${GNURADIO_ANALOG_LIBRARIES} ${GNURADIO_AUDIO_LIBRARIES} ${GNURADIO_BLOCKS_LIBRARIES} ${GNURADIO_LDPC_LIBRARIES} ${GNURADIO_DIGITAL_LIBRARIES})

target_link_libraries(ldpc_decoder_with_queues
  ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES} ${GNURADIO_ANALOG_LIBRARIES} ${GNURADIO_AUDIO_LIBRARIES} ${GNURADIO_BLOCKS_LIBRARIES} ${GNURADIO_LDPC_LIBRARIES} ${GNURADIO_DIGITAL_LIBRARIES})

#GR_PYTHON_INSTALL(
#    PROGRAMS
#    DESTINATION bin
#)

INSTALL(TARGETS
#	dial_tone
	ldpc_hier_test
	ldpc_hier_decoding
	ldpc_hier_encoding
	ldpc_parent
	ldpc_child
	ldpc_decoder_with_queues
	DESTINATION bin
)
