#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

/*
*   \brief Sfinae test
*/

template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_ip(const T& ip);


template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value>::type
print_ip(const T& ip); 


template <template<typename, typename...> class Container, typename T, typename... Args>
typename std::enable_if<std::is_same<Container<T, Args...>, std::vector<T, Args...>>::value ||
                        std::is_same<Container<T, Args...>, std::list<T, Args...>>::value>::type
print_ip(const Container<T, Args...>& ip);