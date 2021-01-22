#ifndef GROUP_H_
#define GROUP_H_

#include <iostream>
#include "boost/integer.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "numero.h"

/*
 * Type to hold a group size
 */
using group_size_t = boost::uint_value_t<MAX_ENTITIES>::least;

/*
 * Group of entities
 */
class Group {

private:

	/*
	 * Group ID
	 */
	group_id_t id;

	/*
	 * Number of entities in the group. Could be easily derived from the group ID if memory is a concern - for now I optimize for performance.
	 */
	group_size_t count;

	/*
     * Total age of the entities in the group
     */
	boost::posix_time::time_duration age;

public:

	/*
	 * Creates a group given a group ID
	 */
	Group(group_id_t g_id) : id{g_id}, count{0} {}

	/*
	 * Resolves the group info like its total age
	 */
	void resolve();

	/*
	 * Gets group ID
	 */
	group_id_t get_id() const noexcept { return id; }

	/*
	 * Gets number of entities in the group. The group should be resolved
	 */
	group_size_t get_count() const noexcept { return count; }

	/*
	 * Gets total age of entities in the group. The group should be resolved
	 */
	boost::posix_time::time_duration get_age() const noexcept { return age;  }

	/*
	 * Outputs the names in the group
	 */
	void print_names(std::ostream& o) const;

	/*
	 * Standard output overload for the group
	 */
	friend std::ostream& operator<<(std::ostream& o, const Group& g);
};

#endif // GROUP_H_