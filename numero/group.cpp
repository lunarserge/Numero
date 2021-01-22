#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "numero.h"
#include "entity.h"
#include "group.h"

/*
 * Resolves the group info like its total age
 */
void Group::resolve()  {
	group_size_t index{0};
	group_id_t g_id{id};
	do {
		if (g_id & 1) {
			++count;
			age += numero::entities[index].get_age();
		}
		++index;
	} while (g_id >>= 1);
}

/*
 * Outputs the names in the group
 */
void Group::print_names(std::ostream& o) const {
	group_size_t index{0};
	group_id_t bit{id};

	while (!(bit & 1)) {
		++index;
		bit >>= 1;
	}
	o << numero::entities[index++].get_name();
	bit >>= 1;

	while (bit) {
		if (bit & 1) {
			o << ',' << numero::entities[index].get_name();
		}
		++index;
		bit >>= 1;
	}
}

/*
 * Standard output overload for the group
 */
std::ostream& operator<<(std::ostream& o, const Group& g) {
	g.print_names(o);
	o << ": " << g.age;
	return o;
}