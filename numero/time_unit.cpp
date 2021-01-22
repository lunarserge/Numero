#include "time_unit.h"

/*
 * Time unit constants
 */
constexpr i_duration_t SECONDS_IN_MINUTE    {60};
constexpr i_duration_t SECONDS_IN_HOUR      {SECONDS_IN_MINUTE * 60};
constexpr i_duration_t SECONDS_IN_DAY       {SECONDS_IN_HOUR * 24};
constexpr i_duration_t SECONDS_IN_YEAR      {static_cast<i_duration_t>(SECONDS_IN_DAY * 365.2425)};
constexpr i_duration_t SECONDS_IN_MONTH     {SECONDS_IN_YEAR / 12};
constexpr i_duration_t SECONDS_IN_WEEK      {SECONDS_IN_DAY * 7};
constexpr i_duration_t SECONDS_IN_QUATER    {SECONDS_IN_MONTH * 3};
constexpr i_duration_t SECONDS_IN_FORTNIGHT {SECONDS_IN_WEEK * 2};
constexpr i_duration_t SECONDS_IN_LUSTRUM   {SECONDS_IN_YEAR * 5};
constexpr i_duration_t SECONDS_IN_OLYMPIAD  {SECONDS_IN_YEAR * 4};

/*
 * Time units info
 */
const TimeUnit numero::time_units[] = {
	{"second(s)", 1},
	{"minute(s)", SECONDS_IN_MINUTE},
	{"hour(s)", SECONDS_IN_HOUR},
	{"day(s)", SECONDS_IN_DAY},
	{"month(s)", SECONDS_IN_MONTH},
	{"year(s)", SECONDS_IN_YEAR},
	{"week(s)", SECONDS_IN_WEEK},
	{"quater(s)", SECONDS_IN_QUATER},
	{"fortnight(s)", SECONDS_IN_FORTNIGHT},
	{"lustrum(s)", SECONDS_IN_LUSTRUM},
	{"olympiad(s)", SECONDS_IN_OLYMPIAD}
};

/*
 * Total number of time units
 */
const std::size_t numero::time_unit_count{sizeof(numero::time_units) / sizeof(TimeUnit)};