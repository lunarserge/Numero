#include <cassert>
#include <limits>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "boost/program_options.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "boost/date_time/local_time/local_time.hpp"
#include "numero.h"
#include "time_unit.h"
#include "entity.h"
#include "group.h"
#include "holiday.h"

/*
 * Current time that is read once for all entities
 */
const boost::posix_time::ptime CURRENT_TIME = boost::posix_time::second_clock::universal_time();

/*
 * Maximum number of holiday lines in the output
 */
numero::options::output_lines_number_t numero::options::output_lines_number;

/*
 * Target time zone for the output correction
 */
boost::local_time::time_zone_ptr numero::options::time_zone;

/*
 * Target time zone name as per the Time Zone Database
 */
static std::string time_zone_string;

/*
 * Prints usage info
 */
void print_help(std::filesystem::path& exe, const boost::program_options::options_description& options) {
	std::cerr << "Usage: " << exe.filename() << " [options] Dates.csv" << std::endl << std::endl;
	std::cerr << options << std::endl;
	std::cerr << "Dates.csv: input dates in CSV (Comma Delimited) format as per README" << std::endl << std::endl;
}

/*
 * Prints dagnostics if the options were not used correctly, followed by usage info and exiting
 */
[[noreturn]] void print_diagnostics_and_exit(const std::string& s, std::filesystem::path& exe, const boost::program_options::options_description& options) {
	std::cerr << s << ". Exiting."<< std::endl << std::endl;
	print_help(exe, options);
	exit(1);
}

/*
 * Loads the target time zone info from the database
 */
void load_time_zone(std::filesystem::path& exe) {
	const char* TIME_ZONE_SPEC = "date_time_zonespec.csv";
	boost::local_time::tz_database db;

	try {
		db.load_from_file(exe.replace_filename(TIME_ZONE_SPEC).string());
	} catch (boost::local_time::data_not_accessible&) {
		std::cerr << "Time zone spec file " << TIME_ZONE_SPEC << " can not be read. Make sure it is in the " << exe.parent_path() << " folder. Exiting." << std::endl;
		exit(1);
	}

	numero::options::time_zone = db.time_zone_from_region(time_zone_string);
	if (numero::options::time_zone == 0) {
		std::cerr << "Time zone spec file doesn't contain " << time_zone_string << " ID. Refer to the README. Exiting.";
		exit(1);
	}
}

/*
 *  Prepares for the computation by parsing the options and doing initial setup
 */
std::ifstream prepare(int argc, char** argv) {
	const char *OPT_HELP = "h", *OPT_OUTPUT_LINES = "n", *OPT_TIME_ZONE_ID = "tz", *OPT_INPUT_FILE = "input-file";
	std::string input_file;

	boost::program_options::options_description options{"Options"};
	options.add_options()
		(OPT_HELP, "produce help message")
		(OPT_OUTPUT_LINES, boost::program_options::value<numero::options::output_lines_number_t>(&numero::options::output_lines_number)->default_value(100), "limit number of holidays in the output to n lines")
		(OPT_TIME_ZONE_ID, boost::program_options::value<std::string>(&time_zone_string)->default_value(""), "specify output time zone (see README for details)")
	;
	boost::program_options::options_description all_options{"All"};
	all_options.add_options()
		(OPT_INPUT_FILE, boost::program_options::value<std::string>(&input_file), "input dates")
	;
	all_options.add(options);
	boost::program_options::positional_options_description p_options;
	p_options.add(OPT_INPUT_FILE, -1);

	std::filesystem::path exe{argv[0]};
	boost::program_options::variables_map vm;
	try {
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(all_options).positional(p_options).run(), vm);
	} catch (boost::program_options::unknown_option& e) {
		std::string s = e.get_option_name();
		if (s.substr(0, 2) != "--") {
			s += ". Notice that options start with '--'";
		}
		print_diagnostics_and_exit(std::string{"Unknown option: "} + s, exe, options);
	} catch (boost::program_options::invalid_option_value&) {
		print_diagnostics_and_exit(std::string{"--"} + OPT_OUTPUT_LINES + " option requires a number", exe, options);
	} catch (boost::program_options::multiple_occurrences&) {
		print_diagnostics_and_exit("Something is wrong with the specified options", exe, options);
	}
	boost::program_options::notify(vm);

	if (vm.count(OPT_HELP)) {
		print_help(exe, options);
	}

	if (!time_zone_string.empty()) {
		load_time_zone(exe);
	}

	std::ifstream in{input_file};
	if (in.fail()) {
		print_diagnostics_and_exit("No input file is selected. Exiting.", exe, options);
	}

	boost::posix_time::time_facet *output_facet = new boost::posix_time::time_facet();
	output_facet->format("%c");
	std::cout.imbue(std::locale(std::cout.getloc(), output_facet));

	return in;
}

int main(int argc, char** argv) {
	assert(numero::time_unit_count <= std::numeric_limits<time_unit_id_t>::max()+1u);

	std::ifstream in = prepare(argc, argv);
	std::string s;
	in >> s;
	if (s != "Name,Month,Day,Year,Hour,Minute") {
		std::cerr << "Header row of the input file has wrong format. Refer to the README. Exiting." << std::endl;
		return 1;
	}

	while (in >> s) {
		numero::entities.push_back(Entity{s});
	}
	in.close();

	numero::entities_t::size_type entities_size{numero::entities.size()};
	if (entities_size > MAX_ENTITIES) {
		std::cerr << "Input file has too many entities: " << entities_size << ". Maximum " << MAX_ENTITIES << " allowed. See README for how to increase this maximum. Exiting." << std::endl;
		return 1;
	} else if (entities_size == 0) {
		std::cerr << "Input file has no entities. See README for the input file structure. Exiting." << std::endl;
		return 1;
	}
	group_id_t last_group = (1 << entities_size) - 1; // This will work even in case of the shift operation overflow
	std::vector<Holiday> holidays;
	holidays.reserve(numero::time_unit_count * last_group);

	// Below I collect all the holidays and sort once in the end.
	// The alternative would be to keep number of holidays in memory under reporting limit all the time - by discarding those holidays that don't make a cut and re-sorting when another holiday making a cut is encountered.
	// I'll explore the alternative if I ever hit memory or performance problem with what I have thus far.
	// Also - using 'do' loop instead of 'for' to avoid the loop variable overflow.
	group_id_t i{0};
	do {
		Group g(++i);
		g.resolve();

		for (std::size_t j = 0; j < numero::time_unit_count; ++j) {
			holidays.push_back(Holiday(g, static_cast<time_unit_id_t>(j)));
		}
	} while (i < last_group);

	std::partial_sort(holidays.begin(), holidays.begin() + numero::options::output_lines_number, holidays.end());
	std::cout << "Results listed in " << ((numero::options::time_zone == 0) ? "local" : time_zone_string) << " time zone:" << std::endl;
	for (numero::options::output_lines_number_t i = 0; i < numero::options::output_lines_number; ++i) {
		std::cout << holidays[i] << std::endl;
	}
	return 0;
}