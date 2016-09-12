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

#ifndef INCLUDED_MEASUREMENTS_PHASE_DIFF_CF_IMPL_H
#define INCLUDED_MEASUREMENTS_PHASE_DIFF_CF_IMPL_H

#include <measurements/phase_diff_cf.h>

namespace gr
{
  namespace measurements
  {

    class phase_diff_cf_impl : public phase_diff_cf
    {
    private:
      const double d_samp_duration;
      bool d_trigger_on;
      bool d_start;
      bool d_in0_above_zero;
      bool d_in1_above_zero;
      uint64_t d_in0_mark;
      uint64_t d_in1_mark;

    public:
      phase_diff_cf_impl (double samp_rate);
      ~phase_diff_cf_impl ();

      int
      general_work (int noutput_items, gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);

      void
      reset (pmt::pmt_t msg);
    };

  } // namespace measurements
} // namespace gr

#endif /* INCLUDED_MEASUREMENTS_PHASE_DIFF_CF_IMPL_H */

