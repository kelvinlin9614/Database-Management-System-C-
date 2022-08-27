#ifndef TABLE_CLASS_MMAP_BPLUS_H
#define TABLE_CLASS_MMAP_BPLUS_H

#include "BPlusTree.h"
#include "vector.h"

template <typename K, typename V>
struct MPair{
    K key;
    Vector<V> value_list;

    //-------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a Btree of values (to replace value_list)
     */
    //-------------------------------------------------------------------------
    MPair(const K& k=K())
    {
        key = k;
    }
    MPair(const K& k, const V& v)
    {
        key = k;
        value_list.push_back(v);
    }
    MPair(const K& k, const Vector<V>& vlist)
    {
        key = k;
        value_list = vlist;
    }
    //-------------------------------------------------------------------------
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs << print_me.key << "," << print_me.value_list;
        return outs;
    }
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key == rhs.key);
    }
    friend bool operator !=(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key != rhs.key);
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key < rhs.key);
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key <= rhs.key);
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key > rhs.key);
    }
    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs.key >= rhs.key);
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return rhs;
    }
};

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it){_it = it;}
        Iterator operator ++(int unused)
        {
            Iterator temp = *this;
            ++(_it);
            return temp;
        }
        Iterator operator ++()
        {
            ++(_it);
            return *this;
        }
        MPair<K, V> operator *()
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

    MMap();

//  Iterators
    Iterator begin()
    {
        return mmap.begin();
    }
    Iterator end()
    {
        return mmap.end();
    }

    // Capacity
    int size() const;

    // return true if the mmap is empty
    bool empty() const;

    // Element Access
    const Vector<V>& operator[](const K& key) const;
    Vector<V>& operator[](const K& key);

    // insert a Mpair info into the BPlustree
    void insert(const K& k, const V& v);

    // erase a key from the mmap
    void erase(const K& key);

    // clear the mmap
    void clear();

    // Operations:
    // return true if the key is exist
    bool contains(const K& key);

    // if the key is exist, then return the Vector, if not exist, then insert
    // this key
    Vector<V> &get(const K& key);
    Iterator find(const K& key);

    int count(const K& key);
    // return the walker that less than the key
    Iterator lower_bound(const K& key)
    {
//        if(contains(key))
//            return mmap.find(MPair<K,V>(key));
//        else
//        {
//            Iterator walker = mmap.begin();
//            while(walker != mmap.end() && *walker < key)
//                walker++;
//            return walker;
//        }
        return mmap.lower_bound(key);
    }

    // return the walker that less than and equal to the key
    Iterator upper_bound(const K& key)
    {
//        Iterator walker = mmap.begin();
//        while(walker != mmap.end() && *walker <= key)
//            walker++;
//        return walker;
        return mmap.upper_bound(key);
    }

    // return true if the tree is valid
    bool is_valid();

    // overload << operator
    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

// CTOR
template <typename K, typename V>
MMap<K,V>::MMap():mmap(true)
{
    // No need to initialize the BTree
}

// return the size of MMap
template<typename K, typename V>
int MMap<K,V>::size() const
{
    return mmap.size();
}

// return true if the mmap is empty
template <typename K, typename V>
bool MMap<K,V>::empty() const
{
    return mmap.empty();
}

// overload [] operator
template<typename K, typename V>
Vector<V> & MMap<K,V>::operator[](const K &key)
{
    return mmap.get(key).value_list;
}

// overload [] operator (const version)
template<typename K, typename V>
const Vector<V> & MMap<K,V>::operator[](const K &key) const
{
    return mmap.get(key).value_list;
}

// insert a new pair info into the MMap
template <typename K, typename V>
void MMap<K,V>::insert(const K &k, const V &v)
{
    if(mmap.find(k) != nullptr)
        mmap.get(k).value_list.push_back(v);
    else
        mmap.insert(MPair<K,V>(k,v));
}

// delete the specific key
template <typename K, typename V>
void MMap<K,V>::erase(const K &key)
{
    mmap.remove(key);
}

// clear the MMap
template <typename K, typename V>
void MMap<K,V>::clear()
{
    mmap.clear_tree();
}

// return true if the key exists
template <typename K, typename V>
bool MMap<K,V>::contains(const K &key)
{
    return mmap.contains(key);
}

// if the key exists, then return the Vector, if not, then insert this key
template <typename K, typename V>
Vector<V> & MMap<K,V>::get(const K &key)
{
    return mmap.get(key).value_list;
}

// return the size of the specific key's value list
template <typename K, typename V>
int MMap<K,V>::count(const K &key)
{
    return mmap.get(key).value_list.size();
}


#endif //TABLE_CLASS_MMAP_BPLUS_H
