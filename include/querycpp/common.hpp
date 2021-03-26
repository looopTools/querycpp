#ifndef QUERYCPP_COMMON_HPP
#define QUERYCPP_COMMON_HPP

#include <string>

namespace querycpp
{
    const std::string TABLE = "TABLE"; 

    // CUD
    const std::string CREATE = "CREATE";
    const std::string UPDATE = "UPDATE";
    const std::string DROP = "DELETE";
    const std::string DELETE = "DELETE";

    // CREATE CONSTRAITNS
    const std::string IF_NOT_EXISTS = "IF NOT EXISTS"; 
    
    // Keys
    const std::string PRIMARY = "PRIMARY KEY";
    
    // General
    const std::string WHERE = "WHERE"; 

    /// SELECT 
    const std::string SELECT = "SELECT";

    /// LIST Operators
    const std::string IN = "IN"; 

    /// ORDER
    const std::string ORDER_BY = "ORDER BY";
    const std::string ASCENDING = "ASC";
    const std::string DESCENDING = "DSC"; 
    
}


#endif /*QUERYCPP_COMMON_HPP*/ 
