#ifndef QUERRYCPP_COMMON_HPP
#define QUERRYCPP_COMMON_HPP

#include <string>

namespace querrycpp
{

    // CUD
    const std::string CREATE = "CREATE";
    const std::string UPDATE = "UPDATE";
    const std::string DROP = "DELETE";
    const std::string DELETE = "DELETE";

    // Keys
    const std::string PRIMARY = "PRIMARY KEY";
    
    // General
    const std::string WHERE = "WHERE"; 

    /// SELECT 
    const std::string SELECT = "SELECT";

    // TODO: Check speeling
    const std::string ORDER_BY = "ORDER BY";
    const std::string ASCENDING = "ASC";
    const std::string DESCENDING = "DSC"; 
    
}


#endif /*QUERRYCPP_COMMON_HPP*/ 
