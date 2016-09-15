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
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include "frequency_sweep_source_m_impl.h"

namespace gr
{
  namespace measurements
  {

    frequency_sweep_source_m::sptr
    frequency_sweep_source_m::make (double start_freq, double stop_freq,
				    size_t duration_ms, int step_method,
				    size_t n_steps)
    {
      return gnuradio::get_initial_sptr (
	  new frequency_sweep_source_m_impl (start_freq, stop_freq, duration_ms,
					     step_method, n_steps));
    }

    /*
     * The private constructor
     */
    frequency_sweep_source_m_impl::frequency_sweep_source_m_impl (
	double start_freq, double stop_freq, size_t duration_ms,
	int step_method, size_t n_steps) :
	    gr::block ("frequency_sweep_source_m",
		       gr::io_signature::make (0, 0, 0),
		       gr::io_signature::make (0, 0, 0)),
	    d_start_freq (start_freq),
	    d_stop_freq (stop_freq),
	    d_duration_ms (duration_ms),
	    d_step_method ((step_method_t)step_method),
	    d_n_steps(n_steps),
	    d_running (true),
	    d_start(false)
    {

      /* This input port starts the sweeping */
      message_port_register_in (pmt::mp ("start"));

      /* Frequency producer */
      message_port_register_out (pmt::mp ("freq"));

      /* Trigger indicating the start of a new frequency */
      message_port_register_out (pmt::mp ("trigger"));

      set_msg_handler (
	  pmt::mp ("start"),
	  boost::bind (&frequency_sweep_source_m_impl::start_msg_handler,
		       this, _1));

      switch (d_step_method)
	{
	case LINEAR:
	  d_thread = boost::shared_ptr<boost::thread> (
	      new boost::thread (
		  boost::bind (&frequency_sweep_source_m_impl::run_linear,
			       this)));
	  break;
	case LOGARITHMIC:
	  d_thread = boost::shared_ptr<boost::thread> (
	      new boost::thread (
		  boost::bind (&frequency_sweep_source_m_impl::run_log,
			       this)));
	  break;
	case EXPONENTIAL:
	  d_thread = boost::shared_ptr<boost::thread> (
	      new boost::thread (
		  boost::bind (&frequency_sweep_source_m_impl::run_exp,
			       this)));
	  break;
	default:
	  throw std::invalid_argument ("Uknown step method");
	}
    }

    void
    frequency_sweep_source_m_impl::start_msg_handler (pmt::pmt_t msg)
    {
      boost::lock_guard<boost::mutex> lock(d_mutex);
      if(pmt::to_long(msg)) {
	d_start = true;
	d_cv.notify_all();
      }
    }

    void
    frequency_sweep_source_m_impl::run_log ()
    {
      size_t i;
      /* the maximum logarithm value should be at the last iteration */
      double max_log = std::log10(d_n_steps);
      double freq = d_start_freq;

      while(d_running) {
	boost::unique_lock<boost::mutex> lock(d_mutex);
	while(!d_start){
	  d_cv.wait(lock);
	}

	if(!d_running){
	  return;
	}

	for(i = 1; i <= d_n_steps; i++) {
	  freq = d_start_freq + std::log10(i) * d_stop_freq;
	  message_port_pub(pmt::mp("freq"), pmt::from_double(freq));
	  message_port_pub(pmt::mp("trigger"), pmt::from_bool(true));
	  boost::this_thread::sleep(boost::posix_time::milliseconds(d_duration_ms));
	}
	d_start = false;
      }
    }


    void
    frequency_sweep_source_m_impl::run_linear ()
    {
      size_t i;
      double inc = (d_stop_freq - d_start_freq) / d_n_steps;
      double freq = d_start_freq;

      while(d_running) {
	boost::unique_lock<boost::mutex> lock(d_mutex);
	while(!d_start){
	  d_cv.wait(lock);
	}

	if(!d_running){
	  return;
	}

	freq = d_start_freq;
	for(i = 0; i < d_n_steps; i++) {
	  message_port_pub(pmt::mp("freq"), pmt::from_double(freq));
	  message_port_pub(pmt::mp("trigger"), pmt::from_bool(true));
	  boost::this_thread::sleep(boost::posix_time::milliseconds(d_duration_ms));
	  freq += inc;
	}
	d_start = false;
      }
    }

    void
    frequency_sweep_source_m_impl::run_exp ()
    {
      /* TODO */
    }

    /*
     * Our virtual destructor.
     */
    frequency_sweep_source_m_impl::~frequency_sweep_source_m_impl ()
    {
      d_running = false;
      d_start = true;
      d_thread->join ();
    }

  } /* namespace measurements */
} /* namespace gr */

