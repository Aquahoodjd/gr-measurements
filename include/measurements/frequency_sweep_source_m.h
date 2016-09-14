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

#ifndef INCLUDED_MEASUREMENTS_FREQUENCY_SWEEP_SOURCE_M_H
#define INCLUDED_MEASUREMENTS_FREQUENCY_SWEEP_SOURCE_M_H

#include <measurements/api.h>
#include <gnuradio/block.h>

namespace gr
{
  namespace measurements
  {

    /*!
     * \brief Generates PMT messages with frequency values performing sweeping.
     * The sweeping steps may be linear, logarithmic or exponential
     * \ingroup measurements
     *
     */
    class MEASUREMENTS_API frequency_sweep_source_m : virtual public gr::block
    {
    public:
      typedef boost::shared_ptr<frequency_sweep_source_m> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of measurements::frequency_sweep_source_m.
       *
       * To avoid accidental use of raw pointers, measurements::frequency_sweep_source_m's
       * constructor is in a private implementation
       * class. measurements::frequency_sweep_source_m::make is the public interface for
       * creating new instances.
       */
      static sptr
      make (double start_freq = 10, double stop_freq = 1e6,
	    size_t duartion_ms = 1000,
	    int step_method = 0);
    };

  } // namespace measurements
} // namespace gr

#endif /* INCLUDED_MEASUREMENTS_FREQUENCY_SWEEP_SOURCE_M_H */

