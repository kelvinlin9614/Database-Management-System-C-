#ifndef TABLE_CLASS_MAP_BPLUS_H
#define TABLE_CLASS_MAP_BPLUS_H

#include "BPlusTree.h"
template <typename K, typename V>
struct Pair
{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V())
    {
        key = k;
        value = v;
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs << print_me.key << "," << print_me.value;
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs.key == rhs.key);
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs.key < rhs.key);
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs.key > rhs.key);
    }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs.key >= rhs.key);
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs.key <= rhs.key);
    }
    friend bool operator != (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs.key != rhs.key);
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return rhs;
    }
};

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator
    {
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it = nullptr):_it(it){}

        // overload ++ operator
        Iterator operator ++(int unused)
        {
            Iterator temp = *this;
            ++(_it);
            return temp;
        }

        // overload ++ operator
        Iterator operator ++()
        {
            ++(_it);
            return *this;
        }
        // return the value
        Pair<K, V> operator *()
        {
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs._it == rhs._it);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs._it != rhs._it);
        }
    private:
        typename map_base::Iterator _it;

    };

    Map();
    // Iterators
    Iterator begin()
    {
        return map.begin();
    }
    Iterator end()
    {
        return map.end();
    }

    // Capacity
    int size() const;
    // return true if the map is empty
    bool empty() const;

    // Element Access
    V& operator[](const K& key);
    V& at(const K& key);
    const V& at(const K& key) const;


    // Modifiers
    // insert a new pair info into the map
    void insert(const K& k, const V& v);
    // delete a key
    void erase(const K& key);
    // delete the map
    void clear();
    V get(const K& key);

    // Operations:
    Iterator find(const K& key)
    {
        return map.find(key);
    }
    // return true if the target exists
    bool contains(const Pair<K, V>& target) const;
    bool is_valid(){return map.is_valid();}
    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me)
    {
        outs << print_me.map << endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

// CTOR
template <typename K, typename V>
Map<K,V>::Map()
{
    key_count = 0;
}

// return size of the map
template <typename K, typename V>
int Map<K,V>::size() const
{
    return key_count;
}

// return true if the map is empty
template <typename K, typename V>
bool Map<K,V>::empty() const
{
    return map.empty();
}

// [] overload
template<typename K, typename V>
V & Map<K,V>::operator[](const K &key)
{
    if(map.find(key) == nullptr)
        key_count++;
    return map.get(key).value;
}

// same function with [] overload
template <typename K, typename V>
V & Map<K,V>::at(const K &key)
{
    if(map.find(key) == nullptr)
        key_count++;
    return map.get(key).value;
}

// const version
template <typename K, typename V>
const V & Map<K,V>::at(const K &key) const
{
    return map.get(key).value;
}

// insert a new key and value
template <typename K, typename V>
void Map<K,V>::insert(const K &k, const V &v)
{
    if(map.find(k) == nullptr)
        key_count++;
    map.insert(Pair<K,V>(k,v));
}

// erase a item using the key
template <typename K, typename V>
void Map<K,V>::erase(const K &key)
{
    if(map.find(key) != nullptr)
        key_count--;
    map.remove(key);
}

// clear all the key and value
template <typename K, typename V>
void Map<K,V>::clear()
{
    key_count = 0;
    map.clear_tree();
}

// if the key doesn't exist, then insert this key and 0 value to the map
template <typename K, typename V>
V Map<K,V>::get(const K &key)
{
    if(map.find(key) == nullptr)
        key_count++;
    return map.get(key).value;
}

// check if the target exists
template <typename K, typename V>
bool Map<K,V>::contains(const Pair<K, V> &target) const
{
    return map.contains(target);
}

#endif //TABLE_CLASS_MAP_BPLUS_H
