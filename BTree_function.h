#ifndef TABLE_CLASS_BTREE_FUNCTION_H
#define TABLE_CLASS_BTREE_FUNCTION_H

//return the larger of the two items
template <class T>
T maximal(const T& a, const T& b)
{
    if(a < b)
        return b;
    else
        return a;
}

//swap the two items
template <class T>
void swap(T& a, T& b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

//return index of the largest item in data
template <class T>
int index_of_maximal(T data[ ], int n)
{
    T max = data[0];
    int index = 0;
    for(int i = 0; i < n - 1; i++)
    {
        if(data[i + 1] > max)
        {
            max = data[i + 1];
            index = i;
        }
    }
    return index;
}

template <class T>
void shift_right(T data[], int start_pos, int size)
{
    for(int i = size; i > start_pos ; i--)
    {
        data[i] = data[i - 1];
    }
}

//insert entry into the sorted array data with length n
template <class T>
void ordered_insert(T data[ ], int& n, T entry)
{
    int index = -1;
    for(int i = 0; i < n; i++)
    {
        if(entry <= data[i])
        {
            index = i;
            break;
        }
    }
    if(index != -1)
    {
        shift_right(data, index, n);
        data[index] = entry;
        n++;
    }
    else
    {
        data[n] = entry;
        n++;
    }
}

//return the first element in data that is not less than entry
template <class T>
int first_ge(const T data[ ], int n, const T& entry)
{
    int i = 0;
    while(i < n)
    {
        if(data[i] >= entry)
            return i;
        else
            i++;
    }
}

//append entry to the right of data
template <class T>
void attach_item(T data[ ], int& n, const T& entry)
{
    data[n] = entry;
    n++;
}

//insert entry at index i in data
template <class T>
void insert_item(T data[ ], int i, int& n, T entry)
{
    shift_right(data, i, n);
    data[i] = entry;
    n++;
}

// shift all the elements to the left
template <class T>
void shift_left(T data[], int start_pos, int& size)
{
    for(int i = start_pos; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }
    size--;
}

//remove the last element in data and place it in entry
template <class T>
void detach_item(T data[ ], int& n, T& entry)
{
    entry = data[n - 1];
    n--;
}


//delete item at index i and place it in entry
template <class T>
void delete_item(T data[ ], int i, int& n, T& entry)
{
    entry = data[i];
    shift_left(data, i, n);
}

//append data2 to the right of data1
template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2)
{
    for(int i = 0; i < n2; i++)
    {
        data1[n1 + i] = data2[i];
    }
    n1 += n2;
    n2 = 0;
}

//move n/2 elements from the right of data1 and move to data2
template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2)
{
    int k = 0;
    if(n1 % 2 == 0)
    {
        for(int i = n1 / 2; i < n1; i++)
        {
            data2[k] = data1[i];
            k++;
            n2++;
        }
    }
    else
    {
        for(int i = n1 / 2 + 1; i < n1; i++)
        {
            data2[k] = data1[i];
            k++;
            n2++;
        }
    }
    n1 = n1 - n2;
}

//copy src[] into dest[]
template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size)
{
    dest_size = src_size;
    for(int i = 0; i < src_size; i++)
    {
        dest[i] = src[i];
    }
}

//print array data
template <class T>
void print_array(const T data[], int n, int pos = -1)
{
    if(pos >= 0)
    {
        for(int i = pos; i < n; i++)
            std::cout << data[i] << " ";
    }
    else
    {
        for(int i = 0; i < n; i++)
            std::cout << data[i] << " ";
    }
}

//item > all data[i]
template <class T>
bool is_gt(const T data[], int n, const T& item)
{
    for(int i = 0; i < n; i++)
    {
        if(data[i] >= item)
            return false;
    }
    return true;
}

//item <= all data[i]
template <class T>
bool is_le(const T data[], int n, const T& item)
{
    for(int i = 0; i < n; i++)
    {
        if(data[i] < item)
            return false;
    }
    return true;
}

#endif //TABLE_CLASS_BTREE_FUNCTION_H