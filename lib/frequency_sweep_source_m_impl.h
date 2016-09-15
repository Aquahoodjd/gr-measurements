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

#ifndef INCLUDED_MEASUREMENTS_FREQUENCY_SWEEP_SOURCE_M_IMPL_H
#define INCLUDED_MEASUREMENTS_FREQUENCY_SWEEP_SOURCE_M_IMPL_H

#include <measurements/frequency_sweep_source_m.h>
#include <boost/thread.hpp>

namespace gr
{
  namespace measurements
  {

    class frequency_sweep_source_m_impl : public frequency_sweep_source_m
    {
    private:
      typedef enum
      {
	LINEAR = 0, LOGARITHMIC = 1, EXPONENTIAL = 2
      } step_method_t;


      const double d_start_freq;
      const double d_stop_freq;
      const size_t d_duration_ms;
      const step_method_t d_step_method;
      const size_t d_n_steps;
      bool d_running;
      bool d_start;
      boost::shared_ptr<boost::thread> d_thread;
      boost::mutex d_mutex;
      boost::condition_variable d_cv;

      void
      start_msg_handler(pmt::pmt_t msg);
      void
      run_linear ();
      void
      run_log ();
      void
      run_exp ();

    public:
      frequency_sweep_source_m_impl (double start_freq, double stop_freq,
				     size_t duartion_ms,
				     int step_method, size_t n_steps);
      ~frequency_sweep_source_m_impl ();
    };

  } // namespace measurements
} // namespace gr

#endif /* INCLUDED_MEASUREMENTS_FREQUENCY_SWEEP_SOURCE_M_IMPL_H */

