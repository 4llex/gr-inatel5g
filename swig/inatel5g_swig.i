/* -*- c++ -*- */

#define INATEL5G_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "inatel5g_swig_doc.i"

%{
#include "inatel5g/mqam_map_bc.h"
%}


%include "inatel5g/mqam_map_bc.h"
GR_SWIG_BLOCK_MAGIC2(inatel5g, mqam_map_bc);
