#include "column.hpp"

#include <sstream>
#include <iostream>
namespace querycpp
{

    column::column(std::string name, database::data_type type, std::vector<std::string> constraints) : _name(name), _type(type), _constraints(constraints)
    {
    }

    std::string column::name() const
    {
        return _name; 
    }

    void column::name(const std::string& name)
    {
        _name = name; 
    }

    database::data_type column::type() const
    {
        return _type; 
    }

    void column::type(const database::data_type type)
    {
        _type = type; 
    }

    std::vector<std::string> column::constraints() const
    {
        return _constraints;
    }

    void column::constraints(const std::vector<std::string>& new_constraints)
    {
        _constraints = new_constraints; 
    }

    std::string column::str() const
    {

        std::stringstream ss;
        
        ss << _name << " ";
        ss << database::type_to_string(_type) << " ";

        bool first = true; 
        for (const auto& constraint : _constraints)
        {
            if (_type == database::data_type::VARCHAR && first)
            {
                ss << "(" << constraint << ") ";
                first = false; 
            }
            else
            {    
                ss << constraint << " ";
            }
        }

        auto result = ss.str();
        return result.substr(0, result.size() - 1);         
    }
}
