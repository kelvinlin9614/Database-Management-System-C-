#ifndef TABLE_CLASS_BPLUSTREE_H
#define TABLE_CLASS_BPLUSTREE_H
#include "BTree_function.h"
#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):it(_it), key_ptr(_key_ptr){}
        T operator *(){
            return it->data[key_ptr];
        }
        Iterator operator++(int un_used)
        {
            // go through the inner data first
            if (key_ptr<it->data_count-1)
                key_ptr++;
            // go to the next node
            else
            {
                it = it->next;
                key_ptr = 0;
            }
            return *this;
        }
        Iterator operator++()
        {
            // go through the inner data first
            if (key_ptr<it->data_count-1)
                key_ptr++;
            // go to the next node
            else
            {
                it = it->next;
                key_ptr = 0;
            }
            return *this;
        }

        // overload the == operator
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr);
        }
        // overload the != operator
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return (lhs.it != rhs.it || lhs.key_ptr != rhs.key_ptr);
        }
        // print the item
        void print_Iterator()
        {
            cout << it->data[key_ptr] << endl;
        }
        // return true if it is null
        bool is_null(){return !it;}
    private:
        BPlusTree<T>* it;
        int key_ptr;
    };
    // CTOR
    BPlusTree(bool dups = false);
    // Big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    void clear_tree();                   //clear this object (delete all nodes)
    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    bool contains(const T& entry) const; //true if entry can be found in the array

    T& get(const T& entry);           //return a reference to entry in the tree
    const T& get(const T& entry)const;//return a reference to entry in the tree
    T& get_existing(const T& entry);  //return a reference to entry in the tree

    //return an iterator to this key. NULL if not there.
    Iterator find(const T& entry);

    Iterator begin()
    {
        // return the smallest node
        return Iterator(get_smallest_node());
    }
    Iterator end() const
    {
        // return the null ptr
        return Iterator(nullptr);
    }

    // return first that goes NOT BEFORE key entry or next if does not
    Iterator lower_bound(const T& key)
    {
        int i = first_ge(data, data_count, key);
        bool found = (i<data_count && data[i] == key);
        if(!is_leaf())
        {
            if (found)
                return subset[i + 1]->lower_bound(key);
            else
                return subset[i]->lower_bound(key);
        }
        else
        {
            if(i < data_count)
            {
                if(key <= data[i])
                    return BPlusTree<T>::Iterator(this, i);
                else if(i + 1 < data_count)
                    return BPlusTree<T>::Iterator(this, i + 1);
                else
                    return BPlusTree<T>::Iterator(this->next, 0);
            }
            else
                return BPlusTree<T>::Iterator(this->next, 0);
        }
    }

    // return first that goes AFTER key
    Iterator upper_bound(const T& key)
    {
        int i = first_ge(data, data_count, key);
        bool found = (i<data_count && data[i] == key);
        if(!is_leaf())
        {
            if (found)
                return subset[i + 1]->upper_bound(key);
            else
                return subset[i]->upper_bound(key);
        }
        else
        {
            if(i < data_count)
            {
                if(key < data[i])
                    return BPlusTree<T>::Iterator(this, i);
                else if(i + 1 < data_count)
                    return BPlusTree<T>::Iterator(this, i + 1);
                else
                    return BPlusTree<T>::Iterator(this->next, 0);
            }
            else
                return BPlusTree<T>::Iterator(this->next, 0);
        }
    }
    int size() const;                //count the number of elements in the tree
    bool empty() const;              //true if the tree is empty

    void print(ostream& outs=cout) const;

    //print a readable version of the tree
    void print_tree(int level = 0, ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me)
    {
        print_me.print();
        //print_me.print_tree(0, outs);
        return outs;
    }
    // return true if the bplustree is valid
    bool is_valid();


private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                      //true if duplicate keys may be inserted
    int data_count;                    //number of data elements
    T data[MAXIMUM + 1];               //holds the keys
    int child_count;                   //number of children
    BPlusTree* subset[MAXIMUM + 2];    //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}           //true if this is a leaf node

    //return a pointer to this key. NULL if not there.
    T* find_ptr(const T& entry);
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);
    //insert element functions, allows MAXIMUM+1 data elements in the root
    void loose_insert(const T& entry);
    //fix excess of data elements in child i
    void fix_excess(int i);
    //remove element functions, allows MINIMUM-1 data elements in the root
    void loose_remove(const T& entry);
    //fix shortage of data elements in child i
    BPlusTree<T>* fix_shortage(int i);
    //return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    const BPlusTree<T>* get_smallest_node() const;
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    //void remove_biggest(T& entry);//remove the biggest child of this tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with subset i+1
};

//---------------------------------------------------------------------
//            C T O R  /  B I G   T H R E E
//---------------------------------------------------------------------

template <typename T>
BPlusTree<T>::BPlusTree(bool dups):dups_ok(dups), data_count(0),
                                   child_count(0), next(NULL){
    //left empty
}

template <typename T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other):data_count(0), child_count(0)
{
    copy_tree(other);
}

template <typename T>
BPlusTree<T>::~BPlusTree()
{
    const bool debug = false;
    if (debug) cout<<"** destructor fired!"<<endl;
    clear_tree();
}

template <typename T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS)
{
    const bool debug = false;
    if (debug) cout<<"** assignment operator fired!"<<endl;
    copy_tree(RHS);
    return *this;
}

//------------------------------------------------
//          I N S E R T
//------------------------------------------------
template <typename T>
void BPlusTree<T>::insert(const T& entry)
{
    //in order for this class to be able to keep track of the number of the keys,
    //      this function (and the functions it calls ) must return a success code.
    //If we are to keep track of the number the keys (as opposed to key/values)
    //  then the success code must distinguish between inserting a new key, or
    //  adding a new key to the existing key. (for "dupes_ok")
    //
    //loose_insert this entry into this root.
    //loose_insert(entry) will insert entry into this tree. Once it returns,
    //  all the subtrees are valid
    //  btree subtrees EXCEPT this root may have one extra data item:
    //    in this case (we have excess in the root)
    //      create a new node, copy all the contents of this root into it,
    //      clear this root node,
    //      make the new node this root's only child (subset[0])
    //
    //Then, call fix_excess on this only subset (subset[0])

    loose_insert(entry);

    // excess in the root
    if(data_count > MAXIMUM) {
        // create a new node
        BPlusTree<T>* hold = new BPlusTree<T>;
        // copy all the contents of this root into the new node
        copy_array(hold->data, data, hold->data_count, data_count);
        copy_array(hold->subset, subset, hold->child_count, child_count);
        // clear this root node
        data_count = 0;
        child_count = 1;
        // make the new node this root's only child
        subset[0] = hold;
        // call fix_excess on this only subset
        fix_excess(0);
    }
}

template <typename T>
void BPlusTree<T>::loose_insert(const T& entry){
    /*
       int i = first_ge(data, data_count, entry);
       bool found = (i<data_count && data[i] == entry);

       three cases:
         found
         a. found/leaf: deal with duplicates: call +
         b. found/no leaf: subset[i+1]->loose_insert(entry)
                           fix_excess(i+1) if there is a need

         ! found:
         c. !found / leaf : insert entry in data at position i
         c. !found / !leaf: subset[i]->loose_insert(entry)
                            fix_excess(i) if there is a need

            |   found          |   !found         |
      ------|------------------|------------------|-------
      leaf  |a. dups? +        | c: insert entry  |
            |                  |    at data[i]    |
      ------|------------------|------------------|-------
            | b.               | d.               |
            |subset[i+1]->     | subset[i]->      |
      !leaf | loose_insert(i+1)|  loose_insert(i) |
            |fix_excess(i+1)   | fix_excess(i)    |
            |                  |                  |
      ------|------------------|------------------|-------
    */
    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if(!is_leaf())
    {
        if(found)
        {
            subset[i+1]->loose_insert(entry);
            if(subset[i+1]->data_count > MAXIMUM)
                fix_excess(i+1);
        }
        else
        {
            subset[i]->loose_insert(entry);
            if(subset[i]->data_count > MAXIMUM)
                fix_excess(i);
        }
    }
    else
    {
        if(found)
            data[i] = data[i] + entry;
        else
            insert_item(data,i,data_count,entry);
    }
}

template <typename T>
void BPlusTree<T>::fix_excess(int i){
    //this node's child i has one too many items: 3 steps:
    //1. add a new subset at location i+1 of this node
    //2. split subset[i] (both the subset array and the data array) and move half into
    //      subset[i+1] (this is the subset we created in step 1.)
    //3. detach the last data item of subset[i] and bring it and insert
    //      it into this node's data[]
    //
    //Note that this last step may cause this node to have too many itesm.
    //  This is OK. This will be
    //  dealt with at the higher recursive level. (my parent will fix it!)
    //
    //NOTE: ODD/EVENNESS
    // when there is an excess, data_count will always be odd
    //  and child_count will always be even.
    //  so, splitting is always the same.

    //  000 B_PLUS_TREE
    //  if (subset[i]->is_leaf())
    //  transfer the middle entry to the right and...
    //  Deal with next pointers. just like linked list insert
    // add a new subset at location i+1 of this node
    BPlusTree<T>* newTree = new BPlusTree<T>;
    insert_item(subset, i + 1, child_count, newTree);
    T entry;

    // split subset[i] (both the subset array and the data array)
    // and move half into subset[i + 1]
    split(subset[i]->data, subset[i]->data_count, newTree->data,
          newTree->data_count);
    split(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,
          subset[i+1]->child_count);

    // detach the last data item of subset[i] and bring it
    detach_item(subset[i]->data, subset[i]->data_count, entry);

    // insert entry into this node's data[]
    ordered_insert(data, data_count, entry);

    if(subset[i]->is_leaf())
    {
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, entry);
        subset[i + 1]->next = subset[i]->next;
        subset[i]->next = subset[i + 1];
    }
}

template<typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T &entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);

    if(is_leaf())
    {
        if(found)
            return BPlusTree<T>::Iterator(this, i);
        else
            return BPlusTree<T>::Iterator(nullptr);
    }
    else
    {
        if(found)
            return subset[i + 1]->find(entry);
        else
            return subset[i]->find(entry);
    }
}

template<typename T>
T * BPlusTree<T>::find_ptr(const T &entry)
{
    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if(is_leaf())
    {
        if(found)
            return &data[i];
        else
            assert(found);
    }
    if(found)
        subset[i + 1]->find_ptr(entry);
    else
        subset[i]->find_ptr(entry);
}

template <typename T>
T& BPlusTree<T>::get(const T& entry) {
    //If entry is not in the tree, add it to the tree
    //assert(contains(entry));
    const bool debug = false;
    if (!contains(entry))
        insert(entry);

    return get_existing(entry);
}

template <typename T>
const T & BPlusTree<T>::get(const T &entry) const
{
    //If entry is not in the tree, add it to the tree
    //assert(contains(entry));
    const bool debug = false;
    if (!contains(entry))
        insert(entry);

    return get_existing(entry);
}

template <typename T>
T& BPlusTree<T>::get_existing(const T& entry) {
    /*
 * ---------------------------------------------------------------
 * This routing explains plainly how the BPlusTree is organized.
 * i = first_ge
 *       |      found         |    !found         |
 * ------|--------------------|-------------------|
 * leaf  |  you're done       | it's not there    |
 *       |                    |                   |
 * ------|--------------------|-------------------|
 * !leaf | subset[i+1]->get() |  subset[i]->get() |
 *       | (inner node)       |                   |
 * ------|--------------------|-------------------|
 *       |                    |                   |
 *
 * ---------------------------------------------------------------
 *
 */
    //assert that entry is not in the tree.
    //assert(contains(entry));

    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    if (is_leaf())
        if (found){
            return data[i];
        }
        else{
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found);
        }
    if (found) //inner node
        return subset[i+1]->get(entry);
        //or just return true?
    else //not found yet...
        return subset[i]->get(entry);
}

template<class T>
void BPlusTree<T>::print(ostream &outs) const
{
    // print from the very bottom right
    for(int i = data_count; i >= 0; i--)
    {
        if(!is_leaf())
        {
            subset[i]->print();
        }
        else if(i != 0)
            outs << "" << "[" << data[i - 1] << "]\n";
    }
}

template<typename T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const
{
    // print from the very bottom right
    for(int i = data_count; i >= 0; i--)
    {
        if(!is_leaf())
        {
            subset[i]->print_tree(level + 1);
        }
        if(i != 0)
            outs << setw(4 * level) << "" << "[" << data[i - 1] << "]\n";
    }
}

//---------------------------------------------------------------
//      S I Z E  /  E M P T Y
//---------------------------------------------------------------
template <typename T>
int BPlusTree<T>::size() const{
    //this function counts the number of keys in the btree
    const BPlusTree<T>* temp = get_smallest_node();
    int counter = 0;
    while(temp != nullptr)
    {
        counter += temp->data_count;
        temp = temp->next;
    }
    return counter;
}

template <typename T>
bool BPlusTree<T>::empty() const{
    return (data_count ==0);
}

//---------------------------------------------------------------
//      C L E A R   /  C O P Y
//---------------------------------------------------------------

template <typename T>
void BPlusTree<T>::clear_tree()
{
    // recursion to delete the subset
    for(int i = 0; i < child_count; i++)
    {
        subset[i]->clear_tree();
        delete subset[i];
        subset[i] = nullptr;
    }
    child_count = 0;
    data_count = 0;
}

template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other)
{
    //assert(empty());
    BPlusTree<T> *last_node = nullptr;
    copy_tree(other, last_node);
}

template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_node)
{
    // copy the root data first
    copy_array(data, other.data, data_count, other.data_count);
    child_count = other.child_count;
    for(int i = 0; i < child_count; i++)
    {
        subset[i] = new BPlusTree<T>;
        subset[i]->copy_tree(*other.subset[i], last_node);
        if(subset[i]->is_leaf() && last_node == nullptr)
        {
            last_node = subset[i];
        }
        else if(subset[i]->is_leaf())
        {
            last_node->next = subset[i];
            last_node = subset[i];
        }
    }
}

template <typename T>
bool BPlusTree<T>::contains(const T &entry) const
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if(is_leaf())
    {
        return found;
    }
    else
    {
        if(found)
            return true;
        else
            subset[i]->contains(entry);
    }
}

template <typename T>
bool BPlusTree<T>::is_valid(){

    //should check that every data[i] < data[i+1]
    if (is_leaf())
        return true;

    //data[data_count-1] must be less than equal to
    //  every subset[child_count-1]->data[ ]

    //every data[i] is greater than every subset[i]->data[ ]

    //B+Tree: Every data[i] is equal to subset[i+1]->smallest

    //Recursively validate every subset[i]

    return true;
}

template <typename T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node()
{
    if(is_leaf()){
        return this;
    }
    else{
        return subset[0]->get_smallest_node();
    }
}

template <typename T>
const BPlusTree<T>* BPlusTree<T>::get_smallest_node() const
{
    if(is_leaf()){
        return this;
    }
    else{
        return subset[0]->get_smallest_node();
    }
}


//------------------------------------------------
//          R E M O V E
//------------------------------------------------
template <typename T>
void BPlusTree<T>::remove(const T& entry){
    /*
     * ---------------------------------------------------------------------------------
     * Same as BTree:
     * Loose_remove the entry from this tree.
     * Shrink if you have to
     * ---------------------------------------------------------------------------------
     * once you return from loose_remove, the root (this object) may have no data and
     * only a single subset:
     * now, the tree must shrink:
     *
     * point a temporary pointer (shrink_ptr) and point it to this root's only subset
     * copy all the data and subsets of this subset into the root (through shrink_ptr)
     * now, the root contains all the data and poiners of it's old child.
     * now, simply delete shrink_ptr, and the tree has shrunk by one level.
     * Note, the root node of the tree will always be the same, it's the
     * child node we delete
     */
    loose_remove(entry);
    // handle shrink
    if(data_count == 0 && child_count == 1)
    {
            BPlusTree<T>* shrink_ptr = subset[0];
            copy_array(data, subset[0]->data, data_count, subset[0]->data_count);
            copy_array(subset, subset[0]->subset, child_count, subset[0]->child_count);
            shrink_ptr->child_count = 0;
            delete shrink_ptr;
    }
}
template <typename T>
void BPlusTree<T>::loose_remove(const T& entry){
    /* four cases:
          leaves:
               a. not found: there is nothing to do
               b. found    : just remove the target
          non leaf:
               c. not found: subset[i]->loose_remove, fix_shortage(i)
               d. found    : subset[i+1]->loose_remove, fix_shortage(i+1) [...]
                   (No More remove_biggest)

            |   !found               |   found                 |
      ------|------------------------|-------------------------|-------
      leaf  |  a: nothing            | b: delete               |
            |     to do              |    target               |
      ------|------------------------|-------------------------|-------
      !leaf | c:                     | d: B_PLUS_TREE          |
            |  [i]->  loose_remove   |   [i+1]-> loose_remove  |
            |  fix_shortage(i)       | fix_shortage(i+1) [...] |
      ------|------------------------|-------------------------|-------
    */
    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    T found_entry;
    T entry_temp = entry;
    if (is_leaf())
    {
        if(!found)
        {
            //[a.] nothing to do
            cout << "entry not in this tree" << endl;
        }
        else
        {
            //[b.] just delete the item
            //   my parent will take care of my shortage
            delete_item(data, i, data_count, found_entry);
        }
    }
    else
    {
        //not leaf:
        // ---- 000 B_PLUS_TREE: no more remove_biggest
        if (!found)
        {
            //[c.] Not here: subset[i]->loose_remove
            //not found yet. search in the next level:
            subset[i]->loose_remove(entry);
            if (subset[i]->data_count < MINIMUM)
                fix_shortage(i);
        }
        else
        {
            //[d.] found key in an inner node:subset[i+1]->loose_remove
            subset[i + 1]->loose_remove(entry);
            if (subset[i + 1]->data_count < MINIMUM)
                fix_shortage(i + 1);
        }
    }
}

template <typename T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i){
    /*
     * fix shortage in subtree i:
     * if child i+1 has more than MINIMUM,
     *          (borrow from right) transfer / rotate left(i+1)
     * elif child i-1 has more than MINIMUM,
     *          (borrow from left) transfer /rotate right(i-1)
     * elif there is a left sibling,
     *          merge with prev child: merge(i-1)
     * else
     *          merge with next (right) child: merge(i)
     *
     *
     * returns a pointer to the fixed_subset
     */
    const bool debug = false;
    if ((i<child_count-1) && (subset[i+1]->data_count > MINIMUM)){
        //borrow from right subtree if you can
        transfer_left(i+1);
        return subset[i];
    }
    else if((i > 0) && (subset[i - 1]->data_count > MINIMUM))
    {
        transfer_right(i);
        return subset[i];
    }
    else if(i > 0)
    {
        merge_with_next_subset(i-1);
        return subset[i - 1];
    }
    else
    {
        merge_with_next_subset(i);
        return subset[i];
    }
}


template <typename T>
void BPlusTree<T>::get_smallest(T& entry){
    //replace entry with the left_most leaf of this tree
    // Keep looking in the first subtree (recursive)
    //  until you get to a leaf.
    // Then, replace entry with data[0] of the leaf node
    const bool debug = false;
    if(is_leaf())
        entry = data[0];
    else
        subset[0]->get_smallest(entry);
}

template <typename T>
void BPlusTree<T>::get_biggest(T &entry)
{
    const bool debug = false;
    if(is_leaf())
        entry = data[data_count - 1];
    else
        subset[child_count - 1]->get_biggest(entry);
}

template <typename T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i){
    /*
     * ----------------------------------------------------------------------
     *  Merge subset[i] with subset [i+1] REMOVE data[i];
     *  non leaf: same as BTree
     *  leaves  : delete but do not bring down data[i]
     * ----------------------------------------------------------------------
     *
     *   1. remove data[i] from this object
     *   2. if not a leaf, append it to child[i]->data:
     *   3. Move all data items from subset[i+1]->data to right of subset[i]->data
     *   4. Move all subset pointers from subset[i+1]->subset to
     *          right of subset[i]->subset
     *   5. delete subset[i+1] (store in a temp ptr)
     *   6. if a leaf, point subset[i]->next to temp_ptr->next
     *   6. delete temp ptr
     *
     *
     * non-leaf nodes: (same as BTree)
     * ------------------
     *  i = 0:
     *             [50  100]
     *          /      |     \
     *  [  ]         [75]       ....
     *    |         /    \
     *   [a]      [b]    [c]
     *
     *  bring down data[i], merge it with subset[i] and subset[i+1]:
     *      then, get rid of subset[i+1]
     *             [100]
     *               |
     *            [50|75]       ....
     *            /  |  \
     *         [a]  [b]  [c]
     *
     *
     *
     * leaf node:
     * ----------------
     * Exactly the same, but do not attach the deleted data[i] to subset[i]->data[ ]
     *
     *  i = 0 : merge 5 and [()]
     *        [7 | 10]
     *      /    |     \
     *  [5]->   [()]->  [10]
     *
     *  Delete data[i] (7), merge subset[i] and subset[i+1]
     *      WITHOUT bringing down data[i]
     *
     *        [10]
     *      /      \
     *  [5]->      [10]
     *
     *
     * i = 1 merge 7 and [()]
     *        [7 | 10]
     *      /    |     \
     *  [5]->   [7]->  [()]
     *
     *  Delete data[i] (10), merge subset[i] and subset[i+1]
     *      WITHOUT bringing down data[i]
     *
     *        [7]
     *      /     \
     *  [5]->      [7]
     *
     *
     *
     *
     */
    const bool debug = false;
    T hold;
    // remove data[i] from this object
    delete_item(data, i, data_count, hold);
    // if not a leaf, append it to child[i]->data
    if(!subset[i]->is_leaf())
        attach_item(subset[i]->data, subset[i]->data_count, hold);
    // Move all data items from subset[i+1]->data to right of subset[i]->data
    merge(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset
          [i + 1]->data_count);
    // Move all subset pointers from subset[i+1]->subset to right of subset[i]->subset
    merge(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset
            ,subset[i + 1]->child_count);
    subset[i]->next = subset[i + 1]->next;
    BPlusTree<T>* temp;
    // delete subset[i+1] (store in a temp ptr)
    delete_item(subset,i + 1, child_count, temp);
    // delete temp ptr
    delete temp;
    return subset[i];
}

template <typename T>
void BPlusTree<T>::transfer_left(int i){
    /*
     * --------------------------------------------------------------
     * transfer_left: from subset[i] to subset[i-1]
     *      non-leaf: same as BTree
     *      leaves  : rotate and leave and update data[i-1] with subset[i]->data[0]
     *                  leftmost key after you borrowed goes to replace data[i-1]
     * --------------------------------------------------------------
     *
     * non-leaf keys: BTree's rotate_left
     * ---------------
     *
     * (0 < i < child_count) and (subset[i]->data_count > MINIMUM)
     * subset[i-1] has only MINIMUM - 1 entries.
     *
     * item transfers from child[i] to child [i-1]
     *
     * FIRST item of subset[i]->data moves up to data to replace data[i-1],
     * data[i-1] moves down to the RIGHT of subset[i-1]->data
     *
     *  i = 1:
     *              [50  100]
     *  [  ]         [65 75]       ....
     *   [a]      [b]  [c]  [d]
     *
     *  65 move up to replace 50 (data[i])
     *  65's child (its child 0) moves over to be the future child of 50
     *  50 moves down to the right of subset[i]->data
     *
     *               [65 100]
     *   [50]         [ 75 ]       ....
     * [a]  [b]      [c]  [d]
     *
     * ****This does not belong here:
     * last item of subset[i-1]->data moves up to data to replace data[i],
     * data[i] moves down to the RIGHT of subset[i]->data
     *
     * leaf keys:
     * -------------
     *  fix_shortage(0) calls trnasfer_left(1) so, i = 1
     *          [7 | 10]
     *        /    |     \
     * [( )]<=[(7) | 8]  [10]
     *
     * 1. transfer subset[i(1)]->data[0] to end of subset[i-1]
     *        [7 | 10]
     *      /    |     \
     *   [7]    [8]   [10]
     *
     * 2. update parent of the transfered subset: data[i-1 (0)] = subset[i(1)]->data[0]
     *
     *        [(8) | 10]
     *      /      |     \
     *   [7]     [(8)]   [10]
     */

    /*  i = 1:
    *              [50  100]
    *  [  ]         [65 75]       ....
    *
    *              [65 100]
    *   []         [50 75]       ....
    */
    if(subset[i]->is_leaf())
    {
        T hold;
        // delete and store 65 into hold
        delete_item(subset[i]->data, 0, subset[i]->data_count, hold);
        // move 65 to the blank node
        attach_item(subset[i-1]->data, subset[i-1]->data_count, hold);
        // replace 50 with 75
        data[i-1] = subset[i]->data[0];
    }
    else
    {
        T hold;
        // delete and hold 50
        delete_item(data,i-1,data_count,hold);
        T hold_subset;
        // delete and hold 65
        delete_item(subset[i]->data,0,subset[i]->data_count,hold_subset);
        // insert 65 to the data[i-1]
        insert_item(data,i-1,data_count,hold_subset);
        // insert 50 to the blank node
        attach_item(subset[i-1]->data, subset[i-1]->data_count, hold);
        BPlusTree<T>* temp = nullptr;
        // move b to the subset[i-1] as a child
        delete_item(subset[i]->subset,0,subset[i]->child_count, temp);
        attach_item(subset[i-1]->subset, subset[i-1]->child_count, temp);
    }
}

template <typename T>
void BPlusTree<T>::transfer_right(int i){
    /*
     * --------------------------------------------------------------
     * transfer right from subset[i] to subset[i+1]
     *      non-leaf: same as BTree
     *      leaves  : rotate and leave a 'trace':
     *              data[i] is replaced with subset[i+1]->data[0]
     *              after you borrowed the key,
     * --------------------------------------------------------------
     *
     * non-leaf keys: BTree's rotate_right
     * ---------------
     * (i < child_count - 1) and (subset[i-1]->data_count > MINIMUM)
     * subset[i+ 1] has only MINIMUM - 1 entries.
     *
     * item transfers from child[i] to child [i+1]
     *
     * LAST item of subset[i]->data moves up to data to replace data[i],
     * data[i] moves down to the LEFT of subset[i+1]->data
     *
     * i = 1
     *                     [50 100]
     *      [20 30]        [65 75]          [ ]
     *  [..] [..] [..]   [a] [b] [c]        [..]
     *
     *  75 moves up to replace 100 (data[i])
     *  75's child (its last child) moves over to be the (child 0) child of 100
     *  100 moves down to subset[i]->data
     *
     *                     [50 75]
     *      [20 30]          [65]          [100]
     *  [..] [..] [..]     [a] [b]        [c] [..]
     *
     * last item of subset[i-1]->data moves up to data,
     * data[i] moves down to the RIGHT of subset[i]->data
     *
     * leaf keys:
     * -------------
     *  fix_shortage(2) calls trnasfer_right(1) so, i = 1 subset[i] is ([7|8])
     *  subset[i+1] is the one being fixed.
     *        [7 | 10]
     *      /    |     \
     * [5|6]->[7 | (8)]=>[()]
     *
     * 1. transfer subset[i(1)]->data[last item] to left of subset[i+1]->data
     *        [7 | (10)]
     *      /    |     \
     *   [5|6]->[7]-> [8]
     *
     * 2. update parent of the transfered subset: data[i (1)] = subset[i+1(2)]->data[0]
     *
     *        [7 | 8]
     *      /    |    \
     *   [5|6]->[7]-> [8]
     *
     *
     *                    [50 100]
     *      [20 30]        [65 75]          [ ]
     *
     *                     [50 75]
     *      [20 30]          [65]          [75]
     */
    const bool debug = false;
    if(subset[i-1]->is_leaf())
    {
        // delete 75 and replace 100 with 75
        detach_item(subset[i-1]->data, subset[i-1]->data_count, data[i-1]);
        // insert 75 to the blank node
        insert_item(subset[i]->data, 0, subset[i]->data_count, data[i-1]);
    }
    else
    {
        // insert 100 to the blank node
        insert_item(subset[i]->data, 0, subset[i]->data_count, data[i-1]);
        // delete 75 and replace 100 with 75
        detach_item(subset[i-1]->data, subset[i-1]->data_count, data[i-1]);
        BPlusTree<T>* temp = nullptr;
        // delete and store the subset of the subset[i-1]
        detach_item(subset[i-1]->subset, subset[i-1]->child_count, temp);
        // insert the temp BTree(C) to 100's subset
        insert_item(subset[i]->subset,0,subset[i]->child_count, temp);
    }
}

#endif //TABLE_CLASS_BPLUSTREE_H
