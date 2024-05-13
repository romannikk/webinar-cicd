#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<int> splitToOctet(const std::string &str)
{
    std::vector<int> r;

    std::string::size_type start = 0;
    std::string::size_type stopOctet = 0;
    while (stopOctet != std::string::npos)
    {
        stopOctet = str.find_first_of(".", start);
        std::string strOctet = str.substr(start, stopOctet - start);
        r.push_back(std::stoi(strOctet));

        start = stopOctet + 1;
    }

    return r;
}

void printIpPool(std::vector<std::vector<int>> &ip_pool, bool (*printFunc)(const std::vector<int> &) = nullptr)
{
    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        if ((printFunc == nullptr) || (printFunc(*ip)))
        {
            for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {

                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
    }
}

int main([[__maybe_unused__]]int argc, [[__maybe_unused__]]char const *argv[])
{
    try
    {
        std::vector<std::vector<int>> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<int> v = splitToOctet(line);
            ip_pool.push_back(v);
        }

        // Reverse lexicographically sort
        auto lexRevSort = [](const std::vector<int> &a, const std::vector<int> &b) -> bool
        {
            for (size_t i = 0; i < a.size(); i++)
            {
                if (a[i] == b[i])
                    continue;
                else
                    return a[i] > b[i];
            }
            return false;
        };

        std::sort(ip_pool.begin(), ip_pool.end(), lexRevSort);
        printIpPool(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        auto checkFirstOctet = [](const std::vector<int> &a) -> bool
        {
            int reqOctet = 1;
            return (a.front() == reqOctet);
        };
        printIpPool(ip_pool, checkFirstOctet);

        // Filter by first byte and output

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        auto check46and70 = [](const std::vector<int> &a) -> bool
        {
            int reqOctetFirst = 46;
            int reqOctetSecond = 70;
            return (a.front() == reqOctetFirst && a.at(1) == reqOctetSecond);
        };
        printIpPool(ip_pool, check46and70);
        // Filter by first and second bytes and output

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        auto check46 = [](const std::vector<int> &a) -> bool
        {
            int reqOctet = 46;
            if (std::find(a.begin(), a.end(), reqOctet) != a.end())
                return true;

            return false;
        };
        printIpPool(ip_pool, check46);

        // Filter by any byte and output

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
