#ifndef QUERYCPP_HELPERS_HPP
#define QUERYCPP_HELPERS_HPP

#include <querycpp/common.hpp>
#include <querycpp/column.hpp>

#include <fmt/core.h>

#include <string>
#include <cstdint>

#include <type_traits>

#include <stdexcept>

namespace querycpp::helpers
{

    template<typename T> bool is_numerical(T val)
    {

        (void) val; 
        // int
        if constexpr (std::is_same<T, int>::value || std::is_same<T, signed>::value || std::is_same<T, signed int>::value ||
                      std::is_same<T, unsigned>::value || std::is_same<T, unsigned int>::value)
        {
            return true; 
        }

        // Long
        if constexpr (std::is_same<T, long>::value || std::is_same<T, long int>::value || std::is_same<T, signed long>::value ||
            std::is_same<T, signed long int>::value || std::is_same<T, unsigned long>::value || std::is_same<T, unsigned long int>::value ||
            std::is_same<T, long long>::value || std::is_same<T, long long int>::value || std::is_same<T, signed long long>::value ||
            std::is_same<T, signed long long int>::value || std::is_same<T, unsigned long long>::value || std::is_same<T, unsigned long long int>::value)
        {
            return true;
        }                 
                         
        // Short
        if constexpr (std::is_same<T, short>::value || std::is_same<T, short int>::value || std::is_same<T, signed short>::value ||
                      std::is_same<T, signed short int>::value || std::is_same<T, unsigned short>::value || std::is_same<T, unsigned short int>::value)
        {
            return true;
        }

        // Floating point

        if constexpr (std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, long double>::value)
        {
            return true; 
        }

        // Usigned integers from <cstdint>
        // We include size_t here 
        if constexpr (std::is_same<T, uint8_t>::value || std::is_same<T, uint16_t>::value || std::is_same<T, uint32_t>::value ||
                      std::is_same<T, uint64_t>::value || std::is_same<T, uint_fast8_t>::value || std::is_same<T, uint_fast16_t>::value ||
                      std::is_same<T, uint_fast32_t>::value || std::is_same<T, uint_fast64_t>::value || std::is_same<T, uint_least8_t>::value ||
                      std::is_same<T, uint_least16_t>::value || std::is_same<T, uint_least32_t>::value ||
                      std::is_same<T, uint_least64_t>::value || std::is_same<T, uintmax_t>::value || std::is_same<T, uintptr_t>::value ||
                      std::is_same<T, size_t>::value)
        {
            return true; 
        }

        // Signed integers from <cstdint>
        if constexpr (std::is_same<T, int8_t>::value || std::is_same<T, int16_t>::value || std::is_same<T, int32_t>::value ||
                      std::is_same<T, int64_t>::value || std::is_same<T, int_fast8_t>::value || std::is_same<T, int_fast16_t>::value ||
                      std::is_same<T, int_fast32_t>::value || std::is_same<T, int_fast64_t>::value || std::is_same<T, int_least8_t>::value ||
                      std::is_same<T, int_least16_t>::value || std::is_same<T, int_least32_t>::value || std::is_same<T, int_least64_t>::value ||
                      std::is_same<T, intmax_t>::value || std::is_same<T, intptr_t>::value)
        {
            return true; 
        }

        return false;         
    }

    /// If the type of val is std::string or char it will be escaped using quote 
    template<typename T> std::string type_to_sql_str(T val)
    {
        if constexpr (std::is_same<T, char>::value || std::is_same<T, std::string>::value)
        {
            return fmt::format("{}{}{}", common::symbols::QUOTE, val, common::symbols::QUOTE); 
        }
        else if constexpr (std::is_same<T, column>::value)
        {
            return val.name();
        }
        else if (is_numerical(val))
        {
            return std::to_string(val); 
        }

        throw std::runtime_error("Cannot convert type to SQL safe str unsupported type");
    }    
}

#endif /* QUERYCPP_HELPERS_HPP */
