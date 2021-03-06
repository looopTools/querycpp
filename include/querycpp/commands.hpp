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

    /// SET
    const std::string SET = "SET";

    /// ORDER
    const std::string ORDER_BY = "ORDER BY";
    const std::string GROUP_BY = "GROUP BY";
    const std::string ASCENDING = "ASC";
    const std::string DESCENDING = "DSC";

    /// COUNT and EXISTS
    const std::string COUNT = "COUNT";
    const std::string EXISTS = "EXISTS";

    /// INSERT RELEVANT
    const std::string INSERT = "INSERT";
    const std::string INTO = "INTO";
    const std::string VALUES = "VALUES";
    const std::string RETURNING = "RETURNING";

    const std::string REFERENCES = "REFERENCES";
        
    
}

#endif /* QUERYCPP_COMMANDS_HPP */
