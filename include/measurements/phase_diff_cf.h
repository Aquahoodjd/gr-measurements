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

#ifndef INCLUDED_MEASUREMENTS_PHASE_DIFF_CF_H
#define INCLUDED_MEASUREMENTS_PHASE_DIFF_CF_H

#include <measurements/api.h>
#include <gnuradio/block.h>

namespace gr
{
  namespace measurements
  {

  /*!
   * \brief This block measures the phase difference between two
   * signals by finding the zero crossing of each one.
   *
   * \ingroup measurements
   *
   */
  class MEASUREMENTS_API phase_diff_cf : virtual public gr::block
  {
  public:
    typedef boost::shared_ptr<phase_diff_cf> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of measurements::phase_diff_cf.
     *
     * To avoid accidental use of raw pointers, measurements::phase_diff_cf's
     * constructor is in a private implementation
     * class. measurements::phase_diff_cf::make is the public interface for
     * creating new instances.
     */
    static sptr make(double samp_rate);
  };

}
 // namespace measurements
}// namespace gr

#endif /* INCLUDED_MEASUREMENTS_PHASE_DIFF_CF_H */

