#include "column.hpp"

#include <sstream>
#include <iostream>
namespace querycpp
{

    column::column(std::string name, const std::string& type, std::vector<std::string> constraints) : _name(name), _type(type), _constraints(constraints)
    {
    }

    column::column(const column& old)
    {
        _name = old._name;
        _type = old._type;
        _constraints = old._constraints; 
    }

    std::string column::name() const
    {
        return _name; 
    }

    void column::name(const std::string& name)
    {
        _name = name; 
    }

    std::string column::type() const
    {
        return _type; 
    }

    void column::type(const std::string& type)
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
        ss << _type; 

        
        bool first = true; 
        for (const auto& constraint : _constraints)
        {
            if (is_length_type(_type) && first)
            {
                ss << "(" << constraint << ")";
                first = false; 
            }
            else
            {    
                ss << " " << constraint;
            }
        }
        return ss.str(); 
    }

    bool column::operator==(const column& other)
    {
        return str() == other.str(); 
    }

    bool column::is_length_type(const std::string& type) const
    {
        return type == (database::type::common::string::VARCHAR);
    }
}
