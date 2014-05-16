#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Example1
# Author: Manu T S
# Generated: Fri May 16 10:23:04 2014
##################################################

from gnuradio import analog
from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import ldpc
import wx

class example1(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Example1")

        ##################################################
        # Variables
        ##################################################
        self.sigma = sigma = 0.5
        self.samp_rate = samp_rate = 32000
        self.max_iterations = max_iterations = 50
        self.alist_file = alist_file = "/home/manu/repos/ldpc/gr-ldpc/python/alist-files"

        ##################################################
        # Blocks
        ##################################################
        self.ldpc_ldpc_hier_encoder_bb_0 = ldpc.ldpc_hier_encoder_bb("/home/manu/1920.1280.3.303/H1920.1280.3.303")
        self.ldpc_ldpc_hier_decoder_fb_0 = ldpc.ldpc_hier_decoder_fb("/home/manu/1920.1280.3.303/H1920.1280.3.303", sigma, max_iterations)
        self.digital_chunks_to_symbols_xx_0 = digital.chunks_to_symbols_bf(([1.0, -1.0]), 1)
        self.blocks_unpacked_to_packed_xx_0 = blocks.unpacked_to_packed_bb(1, gr.GR_LSB_FIRST)
        self.blocks_packed_to_unpacked_xx_0 = blocks.packed_to_unpacked_bb(1, gr.GR_LSB_FIRST)
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, "/home/manu/Downloads/06 - Coming Back To Life.flac", False)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, "/home/manu/Downloads/out", False)
        self.blocks_file_sink_0.set_unbuffered(False)
        self.blocks_add_xx_0 = blocks.add_vff(1)
        self.analog_noise_source_x_0 = analog.noise_source_f(analog.GR_GAUSSIAN, sigma, 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_file_source_0, 0), (self.blocks_packed_to_unpacked_xx_0, 0))
        self.connect((self.ldpc_ldpc_hier_decoder_fb_0, 0), (self.blocks_unpacked_to_packed_xx_0, 0))
        self.connect((self.blocks_unpacked_to_packed_xx_0, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.blocks_packed_to_unpacked_xx_0, 0), (self.ldpc_ldpc_hier_encoder_bb_0, 0))
        self.connect((self.ldpc_ldpc_hier_encoder_bb_0, 0), (self.digital_chunks_to_symbols_xx_0, 0))
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.analog_noise_source_x_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.blocks_add_xx_0, 0), (self.ldpc_ldpc_hier_decoder_fb_0, 0))


# QT sink close method reimplementation

    def get_sigma(self):
        return self.sigma

    def set_sigma(self, sigma):
        self.sigma = sigma
        self.analog_noise_source_x_0.set_amplitude(self.sigma)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_max_iterations(self):
        return self.max_iterations

    def set_max_iterations(self, max_iterations):
        self.max_iterations = max_iterations

    def get_alist_file(self):
        return self.alist_file

    def set_alist_file(self, alist_file):
        self.alist_file = alist_file

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = example1()
    tb.Start(True)
    tb.Wait()

