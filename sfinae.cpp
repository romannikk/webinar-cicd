#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_ip(const T& ip) 
{
    for (int i = sizeof(T) - 1; i > -1; --i) 
    {
        std::cout << ((ip >> i * 8) & 0xFF);
        if (i != 0)
        {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}


template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value>::type
print_ip(const T& ip) 
{
    std::cout << ip << std::endl;
}


template <template<typename, typename...> class Container, typename T, typename... Args>
typename std::enable_if<std::is_same<Container<T, Args...>, std::vector<T, Args...>>::value ||
                        std::is_same<Container<T, Args...>, std::list<T, Args...>>::value>::type
print_ip(const Container<T, Args...>& ip) 
{
    auto it = ip.begin();
    std::cout << *it;
    ++it;
    while (it != ip.end()) 
    {
        std::cout << "." << *it;
        ++it;
    }
    std::cout << std::endl;
}

int main()
{
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100

    return 0;
}
