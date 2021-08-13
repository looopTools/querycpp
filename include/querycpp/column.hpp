#ifndef QUERY_COLUMN_HPP
#define QUERY_COLUMN_HPP

#include "database_data_type.hpp"

#include <string>
#include <vector>

namespace querycpp
{
/// The column class represents the column concept of SQL
class column
{
public:

    /// column constructor
    /// Currently if type = VARCHAR then first contraint is the length
    /// @param name is the name of the column
    /// @param type is the data type used the column in the database
    /// @param constratins is a collection of the constraints for the column
    /// For detailed describtion of constraints see the QueryC++ manual
    column(std::string name, const std::string& type, std::vector<std::string> constraints = std::vector<std::string>());
    
    column(const column& old); 

    /// get the name of the column 
    std::string name() const;

    /// set the name of the column
    /// @param name is the string representation for the name
    void name(const std::string& name);

    /// get the data type of the column
    std::string type() const;

    /// set the type of the column
    /// @param type is the data type used for the column in the database 
    void type(const std::string& type);

    /// get the constraints 
    std::vector<std::string> constraints() const;

    /// set new constraints
    /// This function overrides already set constraints
    /// @param list of new constraints 
    void constraints(const std::vector<std::string>& new_constraints);

    /// creates a string representation of the column
    std::string str() const;

    bool operator==(const column& other);
    
    column& operator=(const column& other);

private:

    bool is_length_type(const std::string& type) const;


private:

    std::string _name;
    std::string _type; 
    std::vector<std::string> _constraints;

}; 
}

#endif /*QUERY_COLUMN_HPP*/
