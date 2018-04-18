#include "include/solid_bucket.hpp"
#include <iostream>
#include <string>

int main()
{
    HashMap<std::string, double> map{};
    std::cout << map.size() << '-' << std::boolalpha << map.empty() << '\n';
    map["Pi"]    = 112.0;
    map["Blue"]  = 123.45;
    map["Pi"]    = (22 / 7);
    map["Hello"] = 2324.001;
    std::cout << map.size() << '-' << std::boolalpha << map.empty() << '\n';
    std::cout << "Value of Pi: " << map["Pi"] << '\n';
    map.for_each([](const auto &key, const auto &value) {
        std::cout << key << ": " << value << '\n';
    });
    std::cout << std::boolalpha << (map.count("Pi") == 1) << '\n';
    map.erase("Pi");
    std::cout << std::boolalpha << (map.count("Pi") == 0) << '\n';
    std::cout << map.size() << '-' << std::boolalpha << map.empty() << '\n';
    map.clear();
    std::cout << map.size() << '-' << std::boolalpha << map.empty() << '\n';
}
