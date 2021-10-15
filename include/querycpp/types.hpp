#ifndef QUERYCPP_DATABASE_DATA_TYPES_HPP
#define QUERYCPP_DATABASE_DATA_TYPES_HPP

#include <string>
#include <vector>

namespace querycpp::type::common
{
    const std::string BOOLEAN = "BOOLEAN";

namespace numerical
{
    const std::string NUMBER = "NUMBER";
    const std::string BIG_INT = "BIGINT";
    const std::string SMALL_INT = "SMALLINT";
}

namespace string
{
    const std::string VARCHAR = "VARCHAR";
    const std::string UUID = "UUID";
}

    
}

namespace querycpp::type::postgres
{
namespace numerical
{
    const std::string SMALL_SERIAL = "SMALLSERIAL";
    const std::string SERIAL = "SERIAL";
    const std::string BIG_SERIAL = "BIGSERIAL";
    const std::string NUMERIC = "NUMERIC";
    const std::string INTEGER = "INTEGER";
    const std::string DECIMAL = "DECIMAL";
    const std::string REAL = "REAL";
    const std::string DOUBLE_PRECISION = "DOUBLE PRECISION";
}

namespace binary
{
    const std::string BYTEA = "BYTEA";
    const std::string BIT = "BIT";
    const std::string BIT_VARYING = "BIT VARYING";
}
}

#endif /*QUERYCPP_DATABASE_DATA_TYPES_HPP*/
