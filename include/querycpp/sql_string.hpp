#ifndef QUERYCPP_SQL_STRING_HPP
#define QUERYCPP_SQL_STRING_HPP

#include <querycpp/common.hpp>

#include <fmt/core.h>

#include <string>

namespace querycpp
{
class sql_string
{
public:
    sql_string() = default;
    
    sql_string(std::string str) : m_str(str)
    {}
    
    /// Produce an SQL safe escaped string
    std::string str() const
    {
        return fmt::format("{}{}{}", common::symbols::QUOTE, m_str, common::symbols::QUOTE);
    }

    std::string raw_str() const
    {
        return m_str; 
    }
    
    size_t size() const {
        return m_str.size() + (common::symbols::QUOTE.size() * 2);
    }

    
    

private:
    std::string m_str;
};
}
#endif /* QUERYCPP_SQL_STRING_HPP */
