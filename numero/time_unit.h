#ifndef TIME_UNIT_H_
#define TIME_UNIT_H_

#include "numero.h"

/*
 * Single time unit info
 */
struct TimeUnit {

	/*
	 * Time unit description
	 */
	const char* description;

	/*
	 * Number of seconds in the time unit
	 */
	i_duration_t seconds;
};

/*
 * Namespace for global objects so that it is clear in the code that those are global
 */
namespace numero {

	/*
	 * Time units info
	 */
	extern const TimeUnit time_units[];

	/*
	 * Total number of time units
	 */
	extern const std::size_t time_unit_count;
}

#endif // TIME_UNIT_H_