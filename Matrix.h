#include <map>
#include <array>
#include <iostream>
#include <vector>

template <typename T, T defaultVal = T{}>
class Matrix
{
private:
    class Indexer
    {
    public:
        using storage_type = std::map<std::vector<std::size_t>, T>;

    private:
        std::vector<std::size_t> indexes;
        storage_type storage;

        friend Matrix;

    public:
        Indexer(){};

        Indexer &operator[](std::size_t index)
        {
            set(index);
            return *this;
        }

        void set(std::size_t index)
        {
            indexes.push_back(index);
        }

        Indexer &operator=(const T& value)
        {
            if (value == defaultVal)
            {
                auto index = storage.find(indexes);
                if (index != storage.end())
                    storage.erase(index);
            }
            else
            {
                storage[indexes] = value;
            }

            return *this;
        }

        void resetIndex()
        {
            indexes.clear();
        }

        operator T()
        {
            auto d = storage.find(indexes);
            if (d != storage.end())
                return d->second;
            else
                return defaultVal;
        }

        friend std::ostream &operator<<(std::ostream& out, const Indexer& index)
        {
            auto d = index.storage.find(index.indexes);
            if (d != index.storage.end())
                out << d->second;
            else
                out << defaultVal;
            return out;
        }
    };

public:
    Matrix() {}

    Indexer &operator[](std::size_t index)
    {
        indexer.resetIndex();
        indexer.set(index);
        return indexer;
    }

    typename Indexer::storage_type::size_type size() const noexcept
    {
        return indexer.storage.size();
    }

    auto begin()
    {
        return indexer.storage.begin();
    }

    auto end()
    {
        return indexer.storage.end();
    }

    void clear()
    {
        indexer.storage.clear();
    }

private:
    Indexer indexer;
};
