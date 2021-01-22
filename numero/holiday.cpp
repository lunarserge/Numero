#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/c_local_time_adjustor.hpp"
#include "time_unit.h"
#include "numero.h"
#include "group.h"
#include "holiday.h"

/*
 * Creates a descriptor of the nearest holiday for a particular group / time unit combination
 */
Holiday::Holiday(const Group& g, const time_unit_id_t u): group{g.get_id()}, tu{u}, zeros{0} {
	const i_duration_t seconds{numero::time_units[u].seconds};
	boost::posix_time::time_duration age{g.get_age()};
	i_duration_t n{age.total_seconds() / seconds}, power{1};
	
	while (n > 0) {
		n /= 10;
		power *= 10;
		++zeros;
	}
	ptime = CURRENT_TIME + ((boost::posix_time::time_duration{0, 0, power*seconds} - age) / g.get_count());
}

/*
 * Standard output overload for the holiday
 */
std::ostream& operator<<(std::ostream& o, const Holiday& h) {
	o << ((numero::options::time_zone == 0) ? boost::date_time::c_local_adjustor<boost::posix_time::ptime>::utc_to_local(h.ptime) : boost::local_time::local_date_time(h.ptime, numero::options::time_zone).local_time()) << ": ";

	Group g(h.group);
	g.print_names(o);

	o << " / 1";
	for (power_t i{h.zeros}; i > 0; --i) {
		o << "0";
	}
	o << ' ' << numero::time_units[h.tu].description;
	return o;
}