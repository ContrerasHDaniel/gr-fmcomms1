/* -*- c++ -*- */

#define FMCOMMS1_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "fmcomms1_swig_doc.i"

%{
#include "fmcomms1/fmcomms1_source.h"
%}


%include "fmcomms1/fmcomms1_source.h"
GR_SWIG_BLOCK_MAGIC2(fmcomms1, fmcomms1_source);
