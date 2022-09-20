#ifndef NUMERO_H_
#define NUMERO_H_

#include <cstdint>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "boost/date_time/local_time/local_time.hpp"

/*
 * Several configurable type declarations below.
 * Those could be defined in corresponding header files, but I've chosen to keep them in one place so that all the compile-time configuration could be done from here.
 */

/*
 * Type to hold a group ID.
 * Each entity is either present or not in a particular group, so we can think about a group ID as a binary integer where each bit corresonds to one of the entities.
 * An entity belongs to the group if corresponding bit is set.
 * Thus, a group is completely defined by such an integer and integer values from 1 towards a value where all entity bits are set define all possible groups.
 */
using group_id_t = uint16_t;

/*
 * Type to hold a time unit ID to refer from holiday descriptors.
 * Unsigned byte should be more than enough (as it is hard to imagine more than 256 types of time units), but you never know.
 */
using time_unit_id_t = uint8_t;

/*
 * Integral type capable of holding a total group age in short time units (like seconds).
 * Unsigned 32 bits are typically fine to hold a single entity age in seconds.
 * However a 100 year person's age in seconds (60x60x24x365.2425x100) will utilize most significant bit of 32 bit unsigned integer.
 * Thus, a total group age of several entities has a good chance to overflow and we need a guaranteed bigger integral type.
 * Also, it is easier if this type is signed (as opposed to unsigned) to avoid narrowing conversion error because of the Boost time_duration processing (which can work with negative durations).
 */
using i_duration_t = int_fast64_t;

/*
 * Maximum number of entities that can be processed with specified group ID type
 */
constexpr unsigned MAX_ENTITIES = sizeof(group_id_t) * 8;

/*
 * Current time that is read once for all entities
 */
extern const boost::posix_time::ptime CURRENT_TIME;

/*
 * Namespace for global objects so that it is clear in the code that those are global
 */
namespace numero {

	/*
	 * Type for holding the number of holiday lines in the output
	 */
	using output_lines_number_t = unsigned;

	/*
	 * Namespace to group run options together
	 */
	namespace options {

		/*
		 * Maximum number of holiday lines in the output
		 */
		extern output_lines_number_t output_lines_number;

		/*
		 * Target time zone for the output
		 */
		extern boost::local_time::time_zone_ptr time_zone;
	}
}

#endif // NUMERO_H_