/* -*- c++ -*- */

#define MEASUREMENTS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "measurements_swig_doc.i"

%{
#include "measurements/phase_diff_cf.h"
#include "measurements/frequency_sweep_source_m.h"
%}


%include "measurements/phase_diff_cf.h"
GR_SWIG_BLOCK_MAGIC2(measurements, phase_diff_cf);
%include "measurements/frequency_sweep_source_m.h"
GR_SWIG_BLOCK_MAGIC2(measurements, frequency_sweep_source_m);
