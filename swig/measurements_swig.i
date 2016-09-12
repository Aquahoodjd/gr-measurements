/* -*- c++ -*- */

#define MEASUREMENTS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "measurements_swig_doc.i"

%{
#include "measurements/phase_diff_cf.h"
%}


%include "measurements/phase_diff_cf.h"
GR_SWIG_BLOCK_MAGIC2(measurements, phase_diff_cf);
