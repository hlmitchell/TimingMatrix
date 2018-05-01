// --- File SparseMat.h follows ---

#ifndef SparseMat_h
#define SparseMat_h

#include "FHlist.h"
#include "FHvector.h"
#include "MatNode.h"

#include <iostream>
#include <iomanip>

using namespace std;

template <class Object>
class SparseMat
{
protected:
    typedef FHlist< MatNode<Object> > MatRow;
    typedef FHvector<MatRow> MasterCol;
    
    typename MatRow::iterator begin;
    typename MatRow::iterator end;
    
    MasterCol rows;
    Object defaultVal;
    int rowSize, colSize;
    
    //for EC overloaded set
    int tempC, tempR;
    
public:
    SparseMat(int, int, const Object &);
    
    //accessors
    const Object & get(int, int) const;
    
    //mutators
    bool set(int, int, const Object &);
    void clear();
    void showSubSquare(int, int);
    
    //EC overload set
    SparseMat<Object>& set(int, int);
    void operator=(const Object &);
    
    // for exception throwing
    class OutOfBoundsException
    {};
};

template <class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object &dVal)
{
    rowSize = r;
    colSize = c;
    defaultVal = dVal;
    tempC, tempR = -1;
    
    //fill vector with empty lists to the size of r
    MatRow nodes;
    for (int i = 0; i < r; i++)
    {
        rows.push_back(nodes);
    }
}

//returns the data at specified row and column
template <class Object>
const Object& SparseMat<Object>::get(int r, int c) const
{
    //check for out of bounds
    if (c >= colSize || r >= rowSize || r < 0 || c < 0)
    {
        throw OutOfBoundsException();
    }
    
    //const function mandates use of const_iterator
    typename MatRow::const_iterator begin_const = rows[r].begin();
    typename MatRow::const_iterator end_const = rows[r].end();
    
    for (begin_const; begin_const != end_const; begin_const++)
    {
        if ((*begin_const).getCol() == c)
        {
            return (*begin_const).data;
        }
    }
    
    return defaultVal;
}

//adds a node to a row based on c value
template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x)
{
    //return false if bounds exceeded
    if (c >= colSize || r >= rowSize || r < 0 || c < 0)
    {
        return false;
    }
    
    //set iterators
    begin = rows[r].begin();
    end = rows[r].end();
    
    //create new node
    MatNode<Object> node(c,x);
    
    //place node in list
    for (begin; begin != end; begin++)
    {
        //for replacing an existing value
        if ((*begin).getCol() == c)
        {
            //if x is NOT the default value, create a replacement node first
            if ( x != defaultVal)
            {
                rows[r].insert(begin, node);
            }
            //then delete original
            rows[r].erase(begin);
            break;
        }
        //for inserting anywhere before the end of list
        else if ((*begin).getCol() > c && x != defaultVal)
        {
            rows[r].insert(begin, node);
            break;
        }
    }
    
    //otherwise add to end of list
    if (x != defaultVal)
    {
        rows[r].push_back(node);
    }
    return true;
}

//saves data points temporarily if overloaded syntax used.
template <class Object>
SparseMat<Object>& SparseMat<Object>::set(int r, int c)
{
    tempC = c;
    tempR = r;
    
    return *this;
}

//sets data points using previously saved coordinates
template <class Object>
void SparseMat<Object>::operator=(const Object &x)
{
    set(tempR, tempC, x);
}

//empties entire matrix
template <class Object>
void SparseMat<Object>::clear()
{
    for (int i = 0; i < colSize; i++)
    {
        rows[i].clear();
    }
}

//displays matrix given specified coordinates
template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size)
{
    //if parameters extend out of bounds, only print the values that are
    //within bounds by changing variables to be in bounds
    if (start < 0) {start = 0;}
    if (start + size > colSize) {size = rowSize - start;}
    if (start + size > rowSize) {size = colSize - start;}
    
    cout << endl;
    
    for (int i = start; i < start + size; i++)
    {
        begin = rows[i].begin();
        
        for (int j = start; j < start + size; j++)
        {
            //prevents an empty list from outputting 0 as the
            //data value for the first column (as opposed to defaultVal)
            if (rows[i].size() == 0)
            {
                cout << fixed << setprecision(2) << setw(5) << defaultVal;
                continue;
            }
            //if list isn't empty, prints out data value
            else if ((*begin).getCol() == j)
            {
                cout << fixed << setprecision(2) << setw(5) << (*begin).data;
                begin++;
            }
            //if list isn't empty, enters defaultVal in empty spots
            else
            {
                cout << fixed << setprecision(2) << setw(5) << defaultVal;
            }
        }
        cout << endl;
    }
    
    cout << endl;
}

#endif

