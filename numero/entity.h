#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <vector>
#include "boost/date_time/posix_time/posix_time_types.hpp"

/*
 * Something having an age (typically a person)
 */
class Entity {

private:

    /*
     * Entity name
     */
    std::string name;

    /*
     * Entity age
     */
    boost::posix_time::time_duration age;

public:

    /*
     * Constructs entity from a CSV string
     */
    Entity(const std::string& s);

    /*
     * Gets entity name
     */
    const std::string& get_name() const noexcept {
        return name;
    }

    /*
     * Gets entity age
     */
    const boost::posix_time::time_duration& get_age() const noexcept {
        return age;
    }
 };

/*
 * Namespace for global objects so that it is clear in the code that those are global
 */
namespace numero {

    /*
     * Definition type for the collection of entities to work with
     */
    using entities_t = std::vector<Entity>;

    /*
     * Collection of entities to work with
     */
    extern entities_t entities;
}

#endif // ENTITY_H_