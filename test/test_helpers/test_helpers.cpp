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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
