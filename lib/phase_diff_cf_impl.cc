/* -*- c++ -*- */
/*
 * gr-measurements: A GNU Radio Out-Of-Tree Module with several signal
 * processing measurements tools
 *
 *  Copyright (C) 2016, Manolis Surligas <surligas@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "phase_diff_cf_impl.h"

namespace gr
{
  namespace measurements
  {

    phase_diff_cf::sptr
    phase_diff_cf::make (double samp_rate)
    {
      return gnuradio::get_initial_sptr (new phase_diff_cf_impl (samp_rate));
    }

    /*
     * The private constructor
     */
    phase_diff_cf_impl::phase_diff_cf_impl (double samp_rate) :
	    gr::block ("phase_diff_cf",
		       gr::io_signature::make (2, 2, sizeof(gr_complex)),
		       gr::io_signature::make (1, 1, sizeof(float))),
	    d_samp_duration (1.0/samp_rate),
	    d_trigger_on (false),
	    d_start(true),
	    d_in0_above_zero(false),
	    d_in1_above_zero(false),
	    d_in0_mark (0),
	    d_in1_mark (0)
    {
      message_port_register_in (pmt::mp ("reset"));
      set_msg_handler (
	  pmt::mp ("reset"),
	  boost::bind (&phase_diff_cf_impl::reset, this, _1));
    }

    /*
     * Our virtual destructor.
     */
    phase_diff_cf_impl::~phase_diff_cf_impl ()
    {
    }

    int
    phase_diff_cf_impl::general_work (int noutput_items,
				      gr_vector_int &ninput_items,
				      gr_vector_const_void_star &input_items,
				      gr_vector_void_star &output_items)
    {
      int i;
      int produced = 0;
      int n_avail = std::min(ninput_items[0], noutput_items);
      const gr_complex *in0 = (const gr_complex *) input_items[0];
      const gr_complex *in1 = (const gr_complex *) input_items[1];
      float *out = (float *) output_items[0];

      /*
       * In order to reduce the logic inside the loop, we ensure that the
       * initialization will always be performed at the start of the
       * general_work() invocation.
       */
      if(d_start) {
	d_in0_above_zero = in0[0].real() > 0.0 ? true : false;
	d_start = false;
      }

      for(i = 0; i < n_avail; i++) {
	if(d_trigger_on) {
	  if(d_in1_above_zero) {
	    if(in1[i].real() < 0.0) {
	      d_in1_mark = nitems_read(1) + i + 1;
	      d_trigger_on = false;
	      out[produced] = (d_in1_mark - d_in0_mark);
	      produced++;
	      d_in0_above_zero = in0[i].real() > 0.0 ? true : false;
	    }
	  }
	  else {
	    if(in1[i].real() > 0.0) {
	      d_in1_mark = nitems_read(1) + i + 1;
	      d_trigger_on = false;
	      out[produced] = (d_in1_mark - d_in0_mark);
	      produced++;
	      d_in0_above_zero = in0[i].real() > 0.0 ? true : false;
	    }
	  }
	}
	/* Search for a zero crossing at the in0 */
	else {
	  if(d_in0_above_zero) {
	    if(in0[i].real() < 0.0) {
	      d_in0_mark = nitems_read(0) + i + 1;
	      d_in1_above_zero = in1[i].real() > 0.0 ? true : false;
	      d_trigger_on = true;
	    }
	  }
	  else{
	    if(in0[i].real() > 0.0) {
	      d_in0_mark = nitems_read(0) + i + 1;
	      d_in1_above_zero = in1[i].real() > 0.0 ? true : false;
	      d_trigger_on = true;
	    }
	  }
	}
      }

      consume_each (n_avail);
      return produced;
    }

    void
    phase_diff_cf_impl::reset (pmt::pmt_t msg)
    {
      d_start = true;
    }

  } /* namespace measurements */
} /* namespace gr */

