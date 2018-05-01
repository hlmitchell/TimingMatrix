#ifndef SparseMatWMult_h
#define SparseMatWMult_h

#include "SparseMat.h"
#include <iostream>
using namespace std;

template <class Object>
class SparseMatWMult : public SparseMat<double>
{
public:
    SparseMatWMult(int,int);
    bool matMult(SparseMatWMult<Object>&, SparseMatWMult<Object>&, int);
};

template <class Object>
SparseMatWMult<Object>::SparseMatWMult(int r, int c)
    : SparseMat<double>(r, c, 0.0)
{
    //stuffs
}

template <class Object>
bool SparseMatWMult<Object>::matMult(SparseMatWMult<Object>& aMatrix,
                                     SparseMatWMult<Object>& bMatrix, int size)
{
    //'a' row size must equal 'b' column size
    //answer matrix must have rows less than 'a' row size
    //and columns less than 'b' column size
    if (aMatrix.colSize != bMatrix.rowSize || rowSize < aMatrix.rowSize ||
        colSize < bMatrix.colSize)
    {
        return false;
    }
    
    //define iterators
    typename MatRow::iterator aBegin;
    typename MatRow::iterator aEnd;
    typename MatRow::iterator bBegin;
    typename MatRow::iterator bEnd;
    
    double tempSum;
    int aColumn;
    
    //loops through the rows of matrix a
    for (int i = 0; i < aMatrix.rowSize; i++)
    {
        //skips all empty 'a' rows because they will come out to 0 anyway
        if (aMatrix.rows[i].size() == 0)
        {
            continue;
        }
        
        //loops through the columns of matrix b
        for (int j = 0; j < bMatrix.colSize; j++)
        {
            //set iterators for 'a' matrix
            aBegin = aMatrix.rows[i].begin();
            aEnd = aMatrix.rows[i].end();
            
            tempSum = 0;
            
            for (aBegin; aBegin != aEnd; aBegin++)
            {
                //save column value of non defult in 'a'
                aColumn = (*aBegin).getCol();
                
                //set iterators
                bBegin = bMatrix.rows[aColumn].begin();
                bEnd = bMatrix.rows[aColumn].end();
                
                for (bBegin; bBegin != bEnd; bBegin++)
                {
                    if ((*bBegin).getCol() > j)
                    {
                        break;
                    }
                    else if ((*bBegin).getCol() == j)
                    {
                        cout << tempSum << " : ";
                        tempSum += ((*aBegin).data * (*bBegin).data);
                        cout << ((*aBegin).data) << " * " << ((*bBegin).data) << endl;
                        break;
                    }
                }
            }
            if (tempSum != 0)
            {
                cout << tempSum << "---" << endl;
                set(i,j,tempSum);
            }
        }
    }
    return true;
}


#endif
