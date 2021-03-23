#ifndef QUERRY_COLUMN_HPP
#define QUERRY_COLUMN_HPP

#include "database_data_type.hpp"

#include <string>
#include <vector>

namespace querrycpp
{
class column
{
public:
    /// Currently if type = VARCHAR then first contraint is the length
    column(std::string name, database::data_type type, std::vector<std::string> constraints = std::vector<std::string>());

    std::string name() const;
    void name(const std::string& name);

    database::data_type type() const;
    void type(const database::data_type type);

    std::vector<std::string> constraints() const;
    void constraints(const std::vector<std::string>& new_constraints);

    std::string str() const; 


private:

    std::string _name;
    database::data_type _type; 
    std::vector<std::string> _constraints;

}; 
}

#endif /*QUERRY_COLUMN_HPP*/
