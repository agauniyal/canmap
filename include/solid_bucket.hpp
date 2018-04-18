#ifndef BUCKET_HPP
#define BUCKET_HPP

#include <algorithm>
#include <array>
#include <list>
#include <utility>
#include <iterator>

template <typename Key>
struct HashMap_Traits {
    using hash                         = std::hash<Key>;
    static constexpr size_t numBuckets = 10;
};

template <typename Key, typename T, typename Traits = HashMap_Traits<Key>>
class HashMap {
    using key_value = std::pair<Key, T>;
    size_t len{};
    std::array<std::list<key_value>, Traits::numBuckets> data{};

    auto getIndex(const Key &k) const
    {
        return ((typename Traits::hash{}(k)) % Traits::numBuckets);
    }

public:
    T &operator[](const Key &k)
    {
        auto &list = data[getIndex(k)];
        const auto position
          = std::find_if(begin(list), end(list),
                         [&](const auto &pair) { return pair.first == k; });

        if (position != end(list)) {
            return position->second;
        } else {
            ++len;
            return list.insert(position, { k, T{} })->second;
        }
    }

    template <typename Func>
    auto for_each(Func f) const
    {
        for (const auto &list : data) {
            for (const auto &[key, value] : list) {
                f(key, value);
            }
        }
    }

    auto empty() const { return len == 0; }
    auto size() const { return len; }

    auto clear()
    {
        for (auto &list : data) {
            list.clear();
        }
        len = 0;
    }

    auto erase(const Key &k)
    {
        auto &list = data[getIndex(k)];
        list.remove_if([&](const auto &pair) {
            if (pair.first == k) {
                --len;
                return true;
            } else {
                return false;
            }
        });
    }

    size_t count(const Key &k) const
    {
        auto &list = data[getIndex(k)];
        const auto position
          = std::find_if(begin(list), end(list),
                         [&](const auto &pair) { return pair.first == k; });

        return (position == end(list)) ? 0 : 1;
    }
};

#endif
