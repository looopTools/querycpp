# Coding Style 

| Version    | 1.0.0a       | 
|------------|--------------|
| Language   | C++          |
|------------|--------------|
| Maintainer | Lars Nielsen |

This document describe the coding style for C++ used in Query C++. 

# Parentheses placement

## Function definition

For function implementations, the curly brackets must appear on lines by themselves. 

*Not approved functions:*

```c++
std::size_t add(const std::size_t lhs,, const std::size_t rhs) {
    return lhs + rhs; 
}
```

```c++
std::size_t add(const std::size_t lhs,, const std::size_t rhs) {
    return lhs + rhs;}
```

```c++
std::size_t add(const std::size_t lhs,, const std::size_t rhs) { return lhs + rhs; }
```

*Approved* 

```c++
std::size_t add(const std::size_t lhs,, const std::size_t rhs)
{
    return lhs + rhs; 
}
```



