#ifndef QUERY_COLUMN_HPP
#define QUERY_COLUMN_HPP

#include "database_data_type.hpp"

#include <string>
#include <vector>

namespace querycpp
{
class column
{
public:
    /// Currently if type = VARCHAR then first contraint is the length
    column(std::string name, const std::string& type, std::vector<std::string> constraints = std::vector<std::string>());

    std::string name() const;
    void name(const std::string& name);

    std::string type() const;
    void type(const std::string& type);

    std::vector<std::string> constraints() const;
    void constraints(const std::vector<std::string>& new_constraints);

    std::string str() const;

    bool operator==(const column& other);


private:

    std::string _name;
    std::string _type; 
    std::vector<std::string> _constraints;

}; 
}

#endif /*QUERY_COLUMN_HPP*/
