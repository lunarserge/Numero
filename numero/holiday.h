#ifndef HOLIDAY_H_
#define HOLIDAY_H_

#include <cstdint>
#include <iostream>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "numero.h"
#include "group.h"

/*
  * Type to hold number of zeros in the holiday.
  * Unsigned byte should be well enough for storing number of zeros - even for holidays using Planck time units (which is theoretically the smallest time measurement that will ever be possible).
  */
using power_t = uint8_t;

/*
 * Holiday descriptor used for sorting holidays across time, groups and time units.
 * The size of the descriptor is 16 bytes and they are directly stored in the array for sorting. The alternative would be to keep the descriptors in a separate array and sort indexes.
 * I have desided that performance implications of that are not obvious, so will experiment on a later date (if I ever see this as a performance bottleneck).
 */
class Holiday {

private:
    
    /*
     * Group ID of the group celebrating
     */
    group_id_t group;

    /*
     * ID of the time unit used for the holiday
     */
    time_unit_id_t tu;

    /*
     * Number of zeros in the holiday
     */
    power_t zeros;

    /*
     * Point of time when the holiday occurs
     */
    boost::posix_time::ptime ptime;

public:

    /*
     * Creates a descriptor of the nearest holiday for a particular group / time unit combination
     */
    Holiday(const Group& g, const time_unit_id_t u);

    /*
     * "Less than" operator overload for sorting in time
     */
    bool operator<(const Holiday& h) const noexcept {
        return ptime < h.ptime;
    }

    /*
     * Standard output overload for the holiday
     */
    friend std::ostream& operator<<(std::ostream& o, const Holiday& h);
 };

#endif // HOLIDAY_H_