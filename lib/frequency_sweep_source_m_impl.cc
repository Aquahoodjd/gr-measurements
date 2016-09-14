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
#include "frequency_sweep_source_m_impl.h"

namespace gr {
  namespace measurements {

    frequency_sweep_source_m::sptr
    frequency_sweep_source_m::make(double start_freq, double stop_freq,
				   size_t duration_ms, int step_method)
    {
      return gnuradio::get_initial_sptr
        (new frequency_sweep_source_m_impl(start_freq, stop_freq,
					   duration_ms, step_method));
    }

    /*
     * The private constructor
     */
    frequency_sweep_source_m_impl::frequency_sweep_source_m_impl (
	double start_freq, double stop_freq, size_t duration_ms,
	int step_method) :
	    gr::block ("frequency_sweep_source_m",
		       gr::io_signature::make (0, 0, 0),
		       gr::io_signature::make (0, 0, 0)),
		       d_start_freq(start_freq),
		       d_stop_freq(stop_freq),
		       d_duration_ms(duration_ms),
		       d_step_method(step_method),
		       d_running(true)
    {

      message_port_register_out (pmt::mp ("freq"));
      message_port_register_out (pmt::mp ("trigger"));
      d_thread = boost::shared_ptr<boost::thread> (
	  new boost::thread (
	      boost::bind (&frequency_sweep_source_m_impl::run, this)));
    }

    /*
     * Our virtual destructor.
     */
    frequency_sweep_source_m_impl::~frequency_sweep_source_m_impl()
    {
      d_running = false;
      d_thread->join();
    }

    void
    frequency_sweep_source_m_impl::run()
    {
      while(d_running) {
      }
    }

  } /* namespace measurements */
} /* namespace gr */

