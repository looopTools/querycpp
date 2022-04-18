#include "querycpp/column.hpp"

#include <sstream>
#include <iostream>
namespace querycpp
{

    column::column(std::string name, const std::string& type, std::vector<std::string> constraints) : _name(name), _type(type), _constraints(constraints)
    {
    }


    column::column(std::string name, const std::string& type, std::pair<std::string_view, std::shared_ptr<column>> reference, std::vector<std::string> constraints) : _name(name), _type(type), _constraints(constraints), _reference(reference) 
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

    std::optional<std::pair<std::string_view, column>> column::reference() const
    {
        column col = *(_reference.second.get());
        auto pair = std::make_pair(_reference.first, col);
        return _reference.first.empty() ? std::nullopt : std::optional<std::pair<std::string_view, column>>(pair);
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

    bool column::operator==(const column& other) const
    {
        return str() == other.str(); 
    }

    bool column::is_length_type(const std::string& type) const
    {
        return type == (type::common::string::VARCHAR);
    }

    column& column::operator=(const column& other)
    {
        _name = other._name;
        _type = other._type;
        _constraints = other._constraints;
        return *this; 
    }
}
