#include <gtest/gtest.h>

#include <querycpp/helpers.hpp>

// NOTE: All values are intialised to silence a warning 

TEST(test_querycpp_helpers, is_numerical_int)
{
    int a = 10;
    EXPECT_TRUE(querycpp::helpers::is_numerical(a));

    signed b = 1337;
    EXPECT_TRUE(querycpp::helpers::is_numerical(b));
    
    unsigned c = 42;
    EXPECT_TRUE(querycpp::helpers::is_numerical(c));

    signed int d = 16;
    EXPECT_TRUE(querycpp::helpers::is_numerical(d));

    unsigned int e = 74;
    EXPECT_TRUE(querycpp::helpers::is_numerical(e));
}

TEST(test_querycpp_helpers, is_numerical_long)
{

    long a = 1992;
    EXPECT_TRUE(querycpp::helpers::is_numerical(a));

    long int b = 890;
    EXPECT_TRUE(querycpp::helpers::is_numerical(b));

    signed long c = 420; 
    EXPECT_TRUE(querycpp::helpers::is_numerical(c));

    signed long int d = 1337;
    EXPECT_TRUE(querycpp::helpers::is_numerical(d));

    unsigned long e = 42;
    EXPECT_TRUE(querycpp::helpers::is_numerical(e));

    unsigned long int f = 42000;
    EXPECT_TRUE(querycpp::helpers::is_numerical(f));

    signed long long g = 8;
    EXPECT_TRUE(querycpp::helpers::is_numerical(g));

    unsigned long long h = 9000;
    EXPECT_TRUE(querycpp::helpers::is_numerical(h));

    unsigned long long int i = 8200;
    EXPECT_TRUE(querycpp::helpers::is_numerical(i));    
}

TEST(test_querycpp_helpers, is_numerical_short)
{
    short a = 32;
    EXPECT_TRUE(querycpp::helpers::is_numerical(a));

    short int b = 42;
    EXPECT_TRUE(querycpp::helpers::is_numerical(b));

    signed short c = 19;
    EXPECT_TRUE(querycpp::helpers::is_numerical(c));

    signed short int d = 20;
    EXPECT_TRUE(querycpp::helpers::is_numerical(d));

    unsigned short e = 10;
    EXPECT_TRUE(querycpp::helpers::is_numerical(e));

    unsigned short int f = 5;
    EXPECT_TRUE(querycpp::helpers::is_numerical(f));    
}

TEST(test_querycpp_helpers, is_numerical_floating_point)
{
    float a = 5.0;
    EXPECT_TRUE(querycpp::helpers::is_numerical(a));

    double b = 137.85;
    EXPECT_TRUE(querycpp::helpers::is_numerical(b));

    long double c = 1337.666;
    EXPECT_TRUE(querycpp::helpers::is_numerical(c));       
}

TEST(test_querycpp_helpers, is_numerical_uint_N)
{
    uint8_t a = 16;
    EXPECT_TRUE(querycpp::helpers::is_numerical(a));
    
    uint16_t b = 32;
    EXPECT_TRUE(querycpp::helpers::is_numerical(b));
    
    uint32_t c = 64;
    EXPECT_TRUE(querycpp::helpers::is_numerical(c));
    
    uint64_t d = 128;
    EXPECT_TRUE(querycpp::helpers::is_numerical(d));
    
    uint_fast8_t e = 16;
    EXPECT_TRUE(querycpp::helpers::is_numerical(e));
    
    uint_fast16_t f = 32;
    EXPECT_TRUE(querycpp::helpers::is_numerical(f));
    
    uint_fast32_t g = 64;
    EXPECT_TRUE(querycpp::helpers::is_numerical(g));
    
    uint_fast64_t h = 128;
    EXPECT_TRUE(querycpp::helpers::is_numerical(h));
    
    uint_least8_t i = 16;
    EXPECT_TRUE(querycpp::helpers::is_numerical(i));
    
    uint_least16_t j = 32;
    EXPECT_TRUE(querycpp::helpers::is_numerical(j));
    
    uint_least32_t k = 64;
    EXPECT_TRUE(querycpp::helpers::is_numerical(k));
    
    uint_least64_t l = 128;
    EXPECT_TRUE(querycpp::helpers::is_numerical(l));

    uintmax_t m = 666;
    EXPECT_TRUE(querycpp::helpers::is_numerical(m));

    uintptr_t n = m;
    EXPECT_TRUE(querycpp::helpers::is_numerical(n));

    size_t o = 1337;
    EXPECT_TRUE(querycpp::helpers::is_numerical(o));    
}

TEST(test_querycpp_helpers, is_numerical_int_N)
{
    int8_t a = 16;
    EXPECT_TRUE(querycpp::helpers::is_numerical(a));
    
    int16_t b = 32;
    EXPECT_TRUE(querycpp::helpers::is_numerical(b));
    
    int32_t c = 64;
    EXPECT_TRUE(querycpp::helpers::is_numerical(c));
    
    int64_t d = 128;
    EXPECT_TRUE(querycpp::helpers::is_numerical(d));
    
    int_fast8_t e = 16;
    EXPECT_TRUE(querycpp::helpers::is_numerical(e));
    
    int_fast16_t f = 32;
    EXPECT_TRUE(querycpp::helpers::is_numerical(f));
    
    int_fast32_t g = 64;
    EXPECT_TRUE(querycpp::helpers::is_numerical(g));
    
    int_fast64_t h = 128;
    EXPECT_TRUE(querycpp::helpers::is_numerical(h));
    
    int_least8_t i = 16;
    EXPECT_TRUE(querycpp::helpers::is_numerical(i));
    
    int_least16_t j = 32;
    EXPECT_TRUE(querycpp::helpers::is_numerical(j));
    
    int_least32_t k = 64;
    EXPECT_TRUE(querycpp::helpers::is_numerical(k));
    
    int_least64_t l = 128;
    EXPECT_TRUE(querycpp::helpers::is_numerical(l));

    intmax_t m = 666;
    EXPECT_TRUE(querycpp::helpers::is_numerical(m));

    intptr_t n = m;
    EXPECT_TRUE(querycpp::helpers::is_numerical(n));
}

TEST(test_helpers, test_is_numerical_str)
{
    char a = 'a';
    EXPECT_FALSE(querycpp::helpers::is_numerical(a));

    std::string b = "ab";
    EXPECT_FALSE(querycpp::helpers::is_numerical(b));    
}

TEST(test_helpers, test_type_to_sql_str_int)
{
    std::string EXPECTED;
    
    int a = 10;
    EXPECTED = "10";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(a), EXPECTED);

    signed b = 1337;
    EXPECTED = "1337";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(b), EXPECTED);        
    
    unsigned c = 42;
    EXPECTED = "42";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(c), EXPECTED);            


    signed int d = 16;
    EXPECTED = "16";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(d), EXPECTED);            

    unsigned int e = 74;
    EXPECTED = "74";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(e), EXPECTED);            
}

TEST(test_querycpp_helpers, test_type_to_sql_str_long)
{
    std::string EXPECTED;
    
    long a = 1992;
    EXPECTED = "1992";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(a), EXPECTED);

    long int b = 890;
    EXPECTED = "890";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(b), EXPECTED);
    
    signed long c = 420; 
    EXPECTED = "420";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(c), EXPECTED);

    signed long int d = 1337;
    EXPECTED = "1337";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(d), EXPECTED);

    unsigned long e = 42;
    EXPECTED = "42";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(e), EXPECTED);    

    unsigned long int f = 42000;
    EXPECTED = "42000";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(f), EXPECTED);

    signed long long g = 8;
    EXPECTED = "8";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(g), EXPECTED);    

    unsigned long long h = 9000;
    EXPECTED = "9000";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(h), EXPECTED);

    unsigned long long int i = 8200;
    EXPECTED = "8200";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(i), EXPECTED);    
}

TEST(test_querycpp_helpers, test_type_to_sql_str_short)
{
    std::string EXPECTED;
    
    short a = 32;
    EXPECTED = "32";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(a), EXPECTED);

    short int b = 42;
    EXPECTED = "42";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(b), EXPECTED);

    signed short c = 19;
    EXPECTED = "19";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(c), EXPECTED);    

    signed short int d = 20;
    EXPECTED = "20";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(d), EXPECTED);

    unsigned short e = 10;
    EXPECTED = "10";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(e), EXPECTED);    

    unsigned short int f = 5;
    EXPECTED = "5";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(f), EXPECTED);
}

TEST(test_querycpp_helpers, test_type_to_sql_str_floating_point)
{
    std::string EXPECTED;
    
    float a = 5.0;
    EXPECTED = std::to_string(a);
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(a), EXPECTED);

    double b = 137.85;
    EXPECTED = std::to_string(b);
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(b), EXPECTED);

    long double c = 1337.666;
    EXPECTED = std::to_string(c);
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(c), EXPECTED);    
}

TEST(test_querycpp_helpers, test_type_to_sql_str_uint_N)
{
    std::string EXPECTED;

    uint8_t a = 16;
    EXPECTED = "16";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(a), EXPECTED);

    
    uint16_t b = 32;
    EXPECTED = "32";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(b), EXPECTED);
    
    uint32_t c = 64;
    EXPECTED = "64";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(c), EXPECTED);
    
    uint64_t d = 128;
    EXPECTED = "128";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(d), EXPECTED);
    
    uint_fast8_t e = 16;
    EXPECTED = "16";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(e), EXPECTED);
    
    uint_fast16_t f = 32;
    EXPECTED = "32";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(f), EXPECTED);
    
    uint_fast32_t g = 64;
    EXPECTED = "64";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(g), EXPECTED);
    
    uint_fast64_t h = 128;
    EXPECTED = "128";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(h), EXPECTED);
    
    uint_least8_t i = 16;
    EXPECTED = "16";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(i), EXPECTED);
    
    uint_least16_t j = 32;
    EXPECTED = "32";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(j), EXPECTED);
    
    uint_least32_t k = 64;
    EXPECTED = "64";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(k), EXPECTED);
    
    uint_least64_t l = 128;
    EXPECTED = "128";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(l), EXPECTED);

    uintmax_t m = 666;
    EXPECTED = "666";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(m), EXPECTED);

    uintptr_t n = m;
    EXPECTED = "666";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(n), EXPECTED);

    size_t o = 1337;
    EXPECTED = "1337";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(o), EXPECTED);
}
    
TEST(test_querycpp_helpers, test_type_to_sql_str_int_N)
{
    std::string EXPECTED;
    int8_t a = 16;
    EXPECTED = "16";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(a), EXPECTED);

    
    int16_t b = 32;
    EXPECTED = "32";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(b), EXPECTED);
    
    int32_t c = 64;
    EXPECTED = "64";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(c), EXPECTED);
    
    int64_t d = 128;
    EXPECTED = "128";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(d), EXPECTED);
    
    int_fast8_t e = 16;
    EXPECTED = "16";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(e), EXPECTED);
    
    int_fast16_t f = 32;
    EXPECTED = "32";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(f), EXPECTED);
    
    int_fast32_t g = 64;
    EXPECTED = "64";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(g), EXPECTED);
    
    int_fast64_t h = 128;
    EXPECTED = "128";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(h), EXPECTED);
    
    int_least8_t i = 16;
    EXPECTED = "16";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(i), EXPECTED);
    
    int_least16_t j = 32;
    EXPECTED = "32";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(j), EXPECTED);
    
    int_least32_t k = 64;
    EXPECTED = "64";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(k), EXPECTED);
    
    int_least64_t l = 128;
    EXPECTED = "128";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(l), EXPECTED);

    intmax_t m = 666;
    EXPECTED = "666";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(m), EXPECTED);

    intptr_t n = m;
    EXPECTED = "666";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(n), EXPECTED);    
}

TEST(test_querycpp_helpers, test_type_to_sql_str_char_types)
{
    std::string EXPECTED;

    char a = 'a';
    EXPECTED = "'a'";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(a), EXPECTED);

    std::string b = "we are testing";
    EXPECTED = "'we are testing'";
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(b), EXPECTED);
}

TEST(test_querycpp_helpers, test_type_to_sql_str_column)
{
    std::string EXPECTED = "id";

    querycpp::column col ("id", querycpp::type::postgres::numerical::SERIAL);
    EXPECT_EQ(querycpp::helpers::type_to_sql_str(col), EXPECTED);
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
