#include <string>
#include <vector>
#include <iostream>
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "numero.h"
#include "entity.h"

/*
 * Collection of entities to work with
 */
std::vector<Entity> numero::entities;

/*
 * Constructs entity from a CSV string
 */
Entity::Entity(const std::string& s) {
    std::string::size_type p1, p2{s.find(',')};
    name = s.substr(0, p2);

    p2 = s.find(',', p1 = ++p2);
    int month{std::stoi(s.substr(p1, p2-p1))};
    p2 = s.find(',', p1 = ++p2);
    int day{std::stoi(s.substr(p1, p2-p1))};

    p2 = s.find(',', p1 = ++p2);
    int year{std::stoi(s.substr(p1, p2-p1))};
    if (year < 1900) {
        std::cerr << "(WARNING) Input file contains a year that is far in the past: " << year << '.' << std::endl;
    }

    p2 = s.find(',', p1 = ++p2);
    int hour{std::stoi(s.substr(p1, p2-p1))};
    if (hour < 0 || hour > 23) {
        std::cerr << "(ERROR) Input file contains invalid hour: " << hour << ". Should be between 0 and 23. Exiting." << std::endl;
        exit(1);
    }

    p2 = s.find(',', p1 = ++p2);
    int minute{std::stoi(s.substr(p1, p2-p1))};
    if (minute < 0 || minute > 59) {
        std::cerr << "(ERROR) Input file contains invalid minute: " << minute << ". Should be between 0 and 59. Exiting." << std::endl;
        exit(1);
    }

    try {
        boost::gregorian::date date{static_cast<boost::gregorian::greg_year>(year), static_cast<boost::gregorian::greg_month>(month), static_cast<boost::gregorian::greg_day>(day)};
        boost::posix_time::time_duration td{hour, minute, 0};
        age = boost::posix_time::time_period{{date, td}, CURRENT_TIME}.length();
    } catch (boost::gregorian::bad_month&) {
        std::cerr << "(ERROR) Input file contains invalid month: " << month << ". Should be between 1 and 12. Exiting." << std::endl;
        exit(1);
    } catch (boost::gregorian::bad_year&) {
        std::cerr << "(ERROR) Input file contains invalid year: " << year << ". Should be between 1400 and 9999. Exiting." << std::endl;
        exit(1);
    } catch (boost::gregorian::bad_day_of_month&) {
        std::cerr << "(ERROR) Input file contains invalid date: " << month << '/' << day << '/' << year << ". Exiting." << std::endl;
        exit(1);
    }
}