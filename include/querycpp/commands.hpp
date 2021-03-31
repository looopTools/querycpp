#ifndef QUERYCPP_COMMANDS_HPP
#define QUERYCPP_COMMANDS_HPP

#include <string>

namespace querycpp::commands
{
    
    const std::string TABLE = "TABLE"; 

    // CUD
    const std::string CREATE = "CREATE";
    const std::string UPDATE = "UPDATE";
    const std::string DROP = "DROP";
    const std::string DELETE = "DELETE";

    const std::string FROM = "FROM"; 

    // CREATE CONSTRAITNS
    const std::string IF_NOT_EXISTS = "IF NOT EXISTS"; 
    
    // General
    const std::string WHERE = "WHERE";

    const std::string AND = "AND";
    const std::string OR = "OR"; 

    /// SELECT 
    const std::string SELECT = "SELECT";

    /// LIST Operators
    const std::string IN = "IN"; 

    /// ORDER
    const std::string ORDER_BY = "ORDER BY";
    const std::string ASCENDING = "ASC";
    const std::string DESCENDING = "DSC"; 
    
}

#endif /* QUERYCPP_COMMANDS_HPP */
