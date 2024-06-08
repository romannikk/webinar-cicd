#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <map>
#include <iostream>
#include <memory>
#include <cassert>

#define USE_PRETTY 1

template <typename T, std::size_t NumElem>
struct CustomAllocator
{
    using value_type = T;

    CustomAllocator() = default;
    ~CustomAllocator() {}

    T *allocate(std::size_t n)
    {
        // std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        if (pollCnt + n > NumElem)
            throw std::bad_alloc();
        else if (!pollPtr)
            pollPtr = reinterpret_cast<T *>(::operator new(NumElem * sizeof(T)));
        if (!pollPtr)
        {
            throw std::bad_alloc();
        }
        T *c_p = pollPtr + pollCnt;
        pollCnt += n;
        return c_p;
    }

    void deallocate(T *p, std::size_t n)
    {
        // std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        if (!p)
        {
            return;
        }
        pollCnt -= n;
        if (pollCnt != 0)
        {
            return;
        }
        delete pollPtr;
        pollPtr = nullptr;
    }

    template <typename U, typename... Args>
    void construct(U *p, Args &&...args)
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
        ::new (p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p)
    {
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~T();
    }

    template <typename U>
    struct rebind
    {
        using other = CustomAllocator<U, NumElem>;
    };

private:
    T *pollPtr = nullptr;
    size_t pollCnt = 0;
};

template <typename T, typename U, std::size_t N>
constexpr bool operator==(const CustomAllocator<T, N> &a1, const CustomAllocator<U, N> &a2) noexcept
{
    return a1.pool == a2.pool;
}

template <typename T, typename U, std::size_t N>
constexpr bool operator!=(const CustomAllocator<T, N> &a1, const CustomAllocator<U, N> &a2) noexcept
{
    return a1.pool != a2.pool;
}

template <typename T>
struct Node
{
    Node *next;
    T val;

    template <typename... Args>
    Node(Args &&...args) : next(nullptr), val(std::forward<Args>(args)...) {}
};

template <typename T, typename Alloc>
class CustomList
{
public:
    CustomList() : first(nullptr), last(nullptr)
    {
    }

    ~CustomList()
    {
        auto current = first;
        while (current != nullptr)
        {
            auto p_rm = current;
            current = current->next;
            allocator.destroy(p_rm);
            allocator.deallocate(p_rm, 1);
        }
    }

    bool is_empty()
    {
        return first == nullptr;
    }

    template <typename... Args>
    void push_back(Args &&...args)
    {
        Node<T> *newNode = allocator.allocate(1);
        allocator.construct(newNode, std::forward<Args>(args)...);

        if (is_empty())
        {
            first = newNode;
            last = newNode;
            return;
        }
        last->next = newNode;
        last = newNode;
    }

    void print()
    {
        if (is_empty())
            return;
        Node<T> *p = first;
        int count = 1;
        while (p)
        {
            std::cout << count << ". Value: " << p->val << std::endl;
            p = p->next;
            count++;
        }
    }

private:
    Node<T> *first;
    Node<T> *last;
    using Allocator = typename Alloc::template rebind<Node<T>>::other;
    Allocator allocator;
};

int factorial(int i)
{
    if (i != 0)
        return i * factorial(i - 1);
    else
        return 1;
}

template <typename T, typename Alloc>
int fillMap(std::map<T, T, std::less<T>, Alloc> &map, size_t sizeMap)
{
    int res = 0;
    for (size_t i = 0; i < sizeMap; ++i)
    {
        map.insert({i, factorial(i)});
    }

    return res;
}

template <typename T, size_t N>
int fillList(CustomList<T, CustomAllocator<T, N>> &list, size_t size)
{
    int res = 0;
    for (size_t i = 0; i < size; ++i)
    {
        list.push_back(factorial(i));
    }

    return res;
}

template <typename T, typename Alloc>
void printMap(std::map<T, T, std::less<T>, Alloc> &map)
{
    for (auto &i : map)
        std::cout << "Key: " << i.first << " Value: " << i.second << std::endl;

    std::cout << std::endl;
}

template <typename T, typename Alloc>
void printList(CustomList<T, Alloc> &list)
{
    list.print();
    std::cout << std::endl;
}

int main()
{
    std::cout << "STD Map data printed: " << std::endl;
    std::map<int, int> stdMapFactorial;
    fillMap(stdMapFactorial, 10);
    printMap(stdMapFactorial);

    const uint maxElem = 10;
    std::cout << "STD Map with custom allocator data printed: " << std::endl;
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<int, int>, maxElem>> stdMapFactorialAlloc;
    fillMap(stdMapFactorialAlloc, maxElem);
    printMap(stdMapFactorialAlloc);

    std::cout << "Custom list with custom allocator data printed: " << std::endl;
    CustomList<int, CustomAllocator<int, maxElem>> list;
    fillList(list, maxElem);
    printList(list);
}
