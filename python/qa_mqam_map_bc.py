#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2019 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
#import inatel5g_swig as inatel5g
from inatel5g import mqam_map_bc


class qa_mqam_map_bc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_BPSK (self):
        src_data = [0,1]
        # "Number of symbols"
        map_order = 0
        # "Determine the expected result"www.franciscosouza.com.br/aprendacompy/capitulo_09.ht
        expected_result = (-1+0j,1+0j)
        # "Create a complex vector source"
        src = blocks.vector_source_b(src_data)
        # "Instantiate the test module"
        qam_map = mqam_map_bc(map_order)
        # "Instantiate the binary sink"
        dst = blocks.vector_sink_c()
        # "Construct the flowgraph"
        self.tb.connect(src,qam_map)
        self.tb.connect(qam_map,dst)
        # "Create the flow graph"
        self.tb.run ()
        # check data
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data)
        self.assertEqual(len(expected_result), len(result_data))
        print("test BPSK")

    def test_002_QAM (self):
        src_data = [0,1,2,3]
        # "Number of symbols"
        map_order = 1
        # "Determine the expected result"
        expected_result = (-1-1j, -1+1j, 1-1j, 1+1j)  
        # "Create a complex vector source"
        src = blocks.vector_source_b(src_data)
        # "Instantiate the test module"
        qam_map = mqam_map_bc(map_order)
        # "Instantiate the binary sink"
        dst = blocks.vector_sink_c()
        # "Construct the flowgraph"
        self.tb.connect(src,qam_map)
        self.tb.connect(qam_map,dst)
        # "Create the flow graph"
        self.tb.run ()
        # check data
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data)
        self.assertEqual(len(expected_result), len(result_data))
        print("test QAM")


    def test_003_16QAM (self):
        src_data = []
        for i in range(0, 16):
            src_data.append(i)    
        #print("test lista --->", src_data)    
        # "Number of symbols"
        map_order = 2
        # "Determine the expected result"
        expected_result = (-3 -3j, -3 -1j, -3 +3j, -3 +1j, #   0, 1, 2, 3
                           -1 -3j, -1 -1j, -1 +3j, -1 +1j, #   4, 5, 6, 7
                           +3 -3j, +3 -1j, +3 +3j, +3 +1j, #   8, 9, 10, 11
                           +1 -3j, +1 -1j, +1 +3j, +1 +1j) #   12, 13, 14, 15

        # "Create a complex vector source"
        src = blocks.vector_source_b(src_data)
        # "Instantiate the test module"
        qam_map = mqam_map_bc(map_order)
        # "Instantiate the binary sink"
        dst = blocks.vector_sink_c()
        # "Construct the flowgraph"
        self.tb.connect(src,qam_map)
        self.tb.connect(qam_map,dst)
        # "Create the flow graph"
        self.tb.run ()
        # check data
        result_data = dst.data()
        #print("result data", result_data)
        self.assertTupleEqual(expected_result, result_data)
        self.assertEqual(len(expected_result), len(result_data))
        print("test 16QAM")

    def test_004_32QAM (self):
        src_data = []
        for i in range(0, 32):
            src_data.append(i)    
        #print("test lista --->", src_data)    
        # "Number of symbols"
        map_order = 3
        # "Determine the expected result"
        expected_result =  (-3+5j, -1+5j, -3-5j, -1-5j,   #0,1,2,3
                            -5+3j, -5+1j, -5-3j, -5-1j,   #4,5,6,7
                            -1+3j, -1+1j, -1-3j, -1-1j,   #8,9,10,11
                            -3+3j, -3+1j, -3-3j, -3-1j,   #12,13,14,15
                            +3+5j, 1+5j, 3-5j, 1-5j,      #16,17,18,19
                            +5+3j, 5+1j, 5-3j, 5-1j,      #20,21,22,23
                            +1+3j, 1+1j, 1-3j, 1-1j,      #24,25,26,27
                            +3+3j, 3+1j, 3-3j, 3-1j)      #28,29,30,31

        # "Create a complex vector source"
        src = blocks.vector_source_b(src_data)
        # "Instantiate the test module"
        qam_map = mqam_map_bc(map_order)
        # "Instantiate the binary sink"
        dst = blocks.vector_sink_c()
        # "Construct the flowgraph"
        self.tb.connect(src,qam_map)
        self.tb.connect(qam_map,dst)
        # "Create the flow graph"
        self.tb.run ()
        # check data
        result_data = dst.data()
        #print("result data", result_data)
        self.assertTupleEqual(expected_result, result_data)
        self.assertEqual(len(expected_result), len(result_data))
        print("test 32QAM")
    
    def test_005_64QAM (self):
        src_data = []
        for i in range(0, 64):
            src_data.append(i)    
        #print("test lista --->", src_data)    
        # "Number of symbols"
        map_order = 4
        # "Determine the expected result"
        expected_result =  (-7 -7j, -7 -5j, -7 -1j, -7 -3j,  #0, 1, 2, 3
                            -7 +7j, -7 +5j, -7 +1j, -7+ 3j,  #4, 5, 6, 7
                            -5 -7j, -5 -5j, -5 -1j, -5 -3j,  #8, 9, 10, 11
                            -5 +7j, -5 +5j, -5 +1j, -5 +3j,  #12, 13, 14, 15
                            -1 -7j, -1 -5j, -1 -1j, -1 -3j,  #16, 17, 18, 19
                            -1 +7j, -1 +5j, -1 +1j, -1 +3j,  #20, 21, 22, 23
                            -3 -7j, -3 -5j, -3 -1j, -3 -3j,  #24, 25, 26, 27
                            -3 +7j, -3 +5j, -3 +1j, -3 +3j,  #28, 29, 30, 31
                            7 -7j,  7 -5j,  7 -1j,  7 -3j,  #32, 33, 34, 35
                            7 +7j,  7 +5j,  7 +1j,  7 +3j,  #36, 37, 38, 39
                            5 -7j,  5 -5j,  5 -1j,  5 -3j,  #40, 41, 42, 43
                            5 +7j,  5 +5j,  5 +1j,  5 +3j,  #44, 45, 46, 47
                            1 -7j,  1 -5j,  1 -1j,  1 -3j,  #48, 49, 50, 51
                            1 +7j,  1 +5j,  1 +1j,  1 +3j,  #52, 53, 54, 55
                            3 -7j,  3 -5j,  3 -1j,  3 -3j,  #56, 57, 58, 59
                            3 +7j,  3 +5j,  3 +1j,  3 +3j)  #60, 61, 62, 63

        # "Create a complex vector source"
        src = blocks.vector_source_b(src_data)
        # "Instantiate the test module"
        qam_map = mqam_map_bc(map_order)
        # "Instantiate the binary sink"
        dst = blocks.vector_sink_c()
        # "Construct the flowgraph"
        self.tb.connect(src,qam_map)
        self.tb.connect(qam_map,dst)
        # "Create the flow graph"
        self.tb.run ()
        # check data
        result_data = dst.data()
        #print("result data", result_data)
        self.assertTupleEqual(expected_result, result_data)
        self.assertEqual(len(expected_result), len(result_data))
        print("test 64QAM")

    def test_006_128QAM (self):
        src_data = []
        for i in range(0, 128):
            src_data.append(i)    
        #print("test lista --->", src_data)    
        # "Number of symbols"
        map_order = 5
        # "Determine the expected result"
        expected_result =  (-7+9j, -7+11j, -1+9j, -1+11j,     #0, 1, 2, 3
                            -7-9j, -7-11j, -1-9j, -1-11j,     #4, 5, 6, 7
                            -5+9j, -5+11j, -3+9j, -3+11j,     #8, 9, 10, 11
                            -5-9j, -5-11j, -3-9j, -3-11j,     #12, 13, 14, 15
                            -9+7j, -9+5j, -9+1j, -9+3j,       #16, 17, 18, 19
                            -9-7j, -9-5j, -9-1j, -9-3j,       #20, 21, 22, 23
                            -11+7j, -11+5j, -11+1j, -11+3j,   #24, 25, 26, 27
                            -11-7j, -11-5j, -11-1j, -11-3j,   #28, 29, 30, 31
                            -1+7j, -1+5j, -1+1j, -1+3j,       #32, 33, 34, 35
                            -1-7j, -1-5j, -1-1j, -1-3j,       #36, 37, 38, 39
                            -3+7j, -3+5j, -3+1j, -3+3j,       #40, 41, 42, 43
                            -3-7j, -3-5j, -3-1j, -3-3j,       #44, 45, 46, 47
                            -7+7j, -7+5j, -7+1j, -7+3j,       #48, 49, 50, 51
                            -7-7j, -7-5j, -7-1j, -7-3j,       #52, 53, 54, 55
                            -5+7j, -5+5j, -5+1j, -5+3j,       #56, 57, 58, 59
                            -5-7j, -5-5j, -5-1j, -5-3j,       #60, 61, 62, 63
                            +7+9j, 7+11j, 1+9j, 1+11j,        #64, 65, 66, 67
                            +7-9j, 7-11j, 1-9j, 1-11j,        #68, 69, 70, 71
                            +5+9j, 5+11j, 3+9j, 3+11j,        #72, 73, 74, 75
                            +5-9j, 5-11j, 3-9j, 3-11j,        #76, 77, 78, 79
                            +9+7j, 9+5j, 9+1j, 9+3j,          #80, 81, 82, 83
                            +9-7j, 9-5j, 9-1j, 9-3j,          #84, 85, 86, 87
                            +11+7j, 11+5j, 11+1j, 11+3j,      #88, 89, 90, 91
                            +11-7j, 11-5j, 11-1j, 11-3j,      #92, 93, 94, 95
                            +1+7j, 1+5j, 1+1j, 1+3j,          #96, 97, 98, 99
                            +1-7j, 1-5j, 1-1j, 1-3j,          #100, 101, 102, 103
                            +3+7j, 3+5j, 3+1j, 3+3j,          #104, 105, 106, 107
                            +3-7j, 3-5j, 3-1j, 3-3j,          #108, 109, 110, 111
                            +7+7j, 7+5j, 7+1j, 7+3j,          #112, 113, 114, 115
                            +7-7j, 7-5j, 7-1j, 7-3j,          #116, 117, 118, 119
                            +5+7j, 5+5j, 5+1j, 5+3j,          #120, 121, 122, 123
                            +5-7j, 5-5j, 5-1j, 5-3j)          #124, 125, 126, 127

        # "Create a complex vector source"
        src = blocks.vector_source_b(src_data)
        # "Instantiate the test module"
        qam_map = mqam_map_bc(map_order)
        # "Instantiate the binary sink"
        dst = blocks.vector_sink_c()
        # "Construct the flowgraph"
        self.tb.connect(src,qam_map)
        self.tb.connect(qam_map,dst)
        # "Create the flow graph"
        self.tb.run ()
        # check data
        result_data = dst.data()
        #print("result data", result_data)
        self.assertTupleEqual(expected_result, result_data)
        self.assertEqual(len(expected_result), len(result_data))
        print("test 128QAM")

    def test_007_256QAM (self):
        src_data = []
        for i in range(0, 256):
            src_data.append(i)    
        #print("test lista --->", src_data)    
        # "Number of symbols"
        map_order = 6
        # "Determine the expected result"
        expected_result =  (-15 -15j, -15 -13j, -15 -9j, -15 -11j,      #0, 1, 2, 3
	                        -15 -1j,  -15 -3j,  -15 -7j, -15 -5j,       #4, 5, 6, 7
		                    -15 +15j, -15 +13j, -15 +9j, -15 +11j,      #8, 9, 10, 11
			                -15 +1j,  -15 +3j,  -15 +7j, -15 +5j,       #12, 13, 14, 15
			                -13 -15j, -13 -13j, -13 -9j, -13 -11j,      #16, 17, 18, 19
                            -13 -1j,  -13 -3j,  -13 -7j, -13 -5j,       #20, 21, 22, 23
                            -13 +15j, -13 +13j, -13 +9j, -13 +11j,      #24, 25, 26, 27
                            -13 +1j,  -13 +3j,  -13 +7j, -13 +5j,       #28, 29, 30, 31
                            -9 -15j,  -9 -13j,  -9 -9j,  -9 -11j,       #32, 33, 34, 35
                            -9 -1j,   -9 -3j,   -9 -7j,  -9 -5j,        #36, 37, 38, 39
                            -9 +15j,  -9 +13j,  -9 +9j,  -9 +11j,       #40, 41, 42, 43
                            -9 +1j,   -9 +3j,   -9 +7j,  -9 +5j,        #44, 45, 46, 47
                            -11 -15j, -11 -13j, -11 -9j, -11 -11j,      #48, 49, 50, 51
                            -11 -1j,  -11 -3j,  -11 -7j, -11 -5j,       #52, 53, 54, 55
                            -11 +15j, -11 +13j, -11 +9j, -11 +11j,      #56, 57, 58, 59
                            -11 +1j,  -11 +3j,  -11 +7j, -11 +5j,       #60, 61, 62, 63
                            -1 -15j,  -1 -13j,  -1 -9j,  -1 -11j,       #64, 65, 66, 67
                            -1 -1j,   -1 -3j,   -1 -7j,  -1 -5j,        #68, 69, 70, 71
                            -1 +15j,  -1 +13j,  -1 +9j,  -1 +11j,       #72, 73, 74, 75
                            -1 +1j,   -1 +3j,   -1 +7j,  -1 +5j,        #76, 77, 78, 79
                            -3 -15j,  -3 -13j,  -3 -9j,  -3 -11j,       #80, 81, 82, 83
                            -3 -1j,   -3 -3j,   -3 -7j,  -3 -5j,        #84, 85, 86, 87
                            -3 +15j,  -3 +13j,  -3 +9j,  -3 +11j,       #88, 89, 90, 91
                            -3 +1j,   -3 +3j,   -3 +7j,  -3 +5j,        #92, 93, 94, 95
                            -7 -15j,  -7 -13j,  -7 -9j,  -7 -11j,       #96, 97, 98, 99
                            -7 -1j,   -7 -3j,   -7 -7j,  -7 -5j,        #100, 101, 102, 103
                            -7 +15j,  -7 +13j,  -7 +9j,  -7 +11j,       #104, 105, 106, 107
                            -7 +1j,   -7 +3j,   -7 +7j,  -7 +5j,        #108, 109, 110, 111
                            -5 -15j,  -5 -13j,  -5 -9j,  -5 -11j,       #112, 113, 114, 115
                            -5 -1j,   -5 -3j,   -5 -7j,  -5 -5j,        #116, 117, 118, 119
                            -5 +15j,  -5 +13j,  -5 +9j,  -5 +11j,       #120, 121, 122, 123
                            -5 +1j,   -5 +3j,   -5 +7j,  -5 +5j,        #124, 125, 126, 127
                            15 -15j,  15 -13j,  15 -9j,  15 -11j,       #128, 129, 130, 131
                            15 -1j,   15 -3j,   15 -7j,  15 -5j,        #132, 133, 134, 135
                            15 +15j,  15 +13j,  15 +9j,  15 +11j,       #136, 137, 138, 139
                            15 +1j,   15 +3j,   15 +7j,  15 +5j,        #140, 141, 142, 143
                            13 -15j,  13 -13j,  13 -9j,  13 -11j,       #144, 145, 146, 147
                            13 -1j,   13 -3j,   13 -7j,  13 -5j,        #148, 149, 150, 151
                            13 +15j,  13 +13j,  13 +9j,  13 +11j,       #152, 153, 154, 155
                            13 +1j,   13 +3j,   13 +7j,  13 +5j,        #156, 157, 158, 159
                            9 -15j,   9 -13j,   9 -9j,   9 -11j,        #160, 161, 162, 163
                            9 -1j,    9 -3j,    9 -7j,   9 -5j,         #164, 165, 166, 167
                            9 +15j,   9 +13j,   9 +9j,   9 +11j,        #168, 169, 170, 171
                            9 +1j,    9 +3j,    9 +7j,   9 +5j,         #172, 173, 174, 175
                            11 -15j,  11 -13j,  11 -9j,  11 -11j,       #176, 177, 178, 179
                            11 -1j,   11 -3j,   11 -7j,  11 -5j,        #180, 181, 182, 183
                            11 +15j,  11 +13j,  11 +9j,  11 +11j,       #184, 185, 186, 187
                            11 +1j,   11 +3j,   11 +7j,  11 +5j,        #188, 189, 190, 191
                            1 -15j,   1 -13j,   1 -9j,   1 -11j,        #192, 193, 194, 195
                            1 -1j,    1 -3j,    1 -7j,   1 -5j,         #196, 197, 198, 199
                            1 +15j,   1 +13j,   1 +9j,   1 +11j,        #200, 201, 202, 203
                            1 +1j,    1 +3j,    1 +7j,   1 +5j,         #204, 205, 206, 207
                            3 -15j,   3 -13j,   3 -9j,   3 -11j,        #208, 209, 210, 211
                            3 -1j,    3 -3j,    3 -7j,   3 -5j,         #212, 213, 214, 215
                            3 +15j,   3 +13j,   3 +9j,   3 +11j,        #216, 217, 218, 219
                            3 +1j,    3 +3j,    3 +7j,   3 +5j,         #220, 221, 222, 223
                            7 -15j,   7 -13j,   7 -9j,   7 -11j,        #224, 225, 226, 227
                            7 -1j,    7 -3j,    7 -7j,   7 -5j,         #228, 229, 230, 231
                            7 +15j,   7 +13j,   7 +9j,   7 +11j,        #232, 233, 234, 235
                            7 +1j,    7 +3j,    7 +7j,   7 +5j,         #236, 237, 238, 239
                            5 -15j,   5 -13j,   5 -9j,   5 -11j,        #240, 241, 242, 243
                            5 -1j,    5 -3j,    5 -7j,   5 -5j,         #244, 245, 246, 247
                            5 +15j,   5 +13j,   5 +9j,   5 +11j,        #248, 249, 250, 251
                            5 +1j,    5 +3j,    5 +7j,   5 +5j)         #252, 253, 254, 255

        # "Create a complex vector source"
        src = blocks.vector_source_b(src_data)
        # "Instantiate the test module"
        qam_map = mqam_map_bc(map_order)
        # "Instantiate the binary sink"
        dst = blocks.vector_sink_c()
        # "Construct the flowgraph"
        self.tb.connect(src,qam_map)
        self.tb.connect(qam_map,dst)
        # "Create the flow graph"
        self.tb.run ()
        # check data
        result_data = dst.data()
        #print("result data", result_data)
        self.assertTupleEqual(expected_result, result_data)
        self.assertEqual(len(expected_result), len(result_data))
        print("test 256QAM")

    def test_008_my_test (self):
        src_data = [3,2,1,0]
        # "Number of symbols"
        map_order = 1
        # "Determine the expected result"
        expected_result = (+1+1j, 1-1j, -1+1j, -1-1j)
        # "Create a complex vector source"
        src = blocks.vector_source_b(src_data)
        # "Instantiate the test module"
        qam_map = mqam_map_bc(map_order)
        # "Instantiate the binary sink"
        dst = blocks.vector_sink_c()
        # "Construct the flowgraph"
        self.tb.connect(src,qam_map)
        self.tb.connect(qam_map,dst)
        # "Create the flow graph"
        self.tb.run ()
        # check data
        result_data = dst.data()
        self.assertTupleEqual(expected_result, result_data)
        self.assertEqual(len(expected_result), len(result_data))
        print("test QAM")
        print("bits de entrada:", src_data)

if __name__ == '__main__':
    gr_unittest.run(qa_mqam_map_bc, "qa_mqam_map_bc.xml")

   