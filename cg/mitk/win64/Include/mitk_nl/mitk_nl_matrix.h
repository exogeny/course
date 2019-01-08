/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





//////////////////////////////////////////////////////////////////////////
/// \class mitk_nl_matrix
/// \brief This is the base structure of matrix 
/// @{
//////////////////////////////////////////////////////////////////////////
#ifndef _MITK_nl_MATRIX_H
#define _MITK_nl_MATRIX_H

/************************************************************************
**  this is the basic class matrix
**  written on Aug 2,2006
************************************************************************/

#include <assert.h>
#include "mitk_nl_vector.h"

#undef _DEBUG

template<class T>
class mitk_nl_matrix
{

//****************************************************************************
//                              constructors
//****************************************************************************

public:
    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note Default constructor creates an empty matrix of size 0,0.
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix() : num_rows(0), num_cols(0), data(0) {}
    
    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note Construct a matrix of size r rows by c columns
    /// @param r the number of rows of the matrix
    /// @param c the number of column of the matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix(unsigned int r, unsigned int c);

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note construct a matrix of size r rows by c columns, and all elements
    ///  equal to v0
    /// @param r the number of rows of the matrix
    /// @param c the number of column of the matrix
    /// @param v0 the value assigned
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix(unsigned int r, unsigned int c, T const& v0);

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note construct a matrix of r rows by c columns, initialized by an 
    ///  array giving the first n elements of the matrix row-wise
    /// @param r the number of rows of the matrix
    /// @param c the number of column of the matrix
    /// @param n number of row-wise elements of the matrix to be initialized
    ///  by the array
    /// @param value[] the array used to the initialization 
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix(unsigned int r, unsigned int c, unsigned int n, T const values[]);

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note Construct a matrix of r rows by c columns, initialized by a 
    ///  vector giving the first n elements of the matrix row-wise
    /// @param r the number of rows of the matrix
    /// @param c the number of column of the matrix
    /// @param V the vector used for the row-wise initialization of the first
    ///  elements of the matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix(unsigned int r, unsigned int c, mitk_nl_vector<T>const&V);

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note Construct a matrix of r rows by c columns, initialized by an 
    ///  array giving the first elements of the matrix row-wise
    /// @param r the number of rows of the matrix
    /// @param c the number of column of the matrix
    /// @param data_block the array used for the row-wise initialization of 
    ///  the first elements of the matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix(unsigned int r, unsigned int c, T const* data_block);

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note copy the constructor of another matrix
    /// @param mat the matrix the constructor of which is to be copied
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix(mitk_nl_matrix<T> const&mat);

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note allocate memory for the matrix data
    /// @param row the value of the number of the rows to be set
    /// @param col the value of the number of the cols to be set
    //////////////////////////////////////////////////////////////////////////
    void  alloc(unsigned int row, unsigned int col);

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note set the number of rows
    /// @param row the value of the number of the rows to be set
    //////////////////////////////////////////////////////////////////////////
    void  set_row_num(unsigned int row);

    //////////////////////////////////////////////////////////////////////////
    /// constructor 
    /// @note set the number of columns
    /// @param col the value of the number of the columns to be set
    //////////////////////////////////////////////////////////////////////////
    void  set_col_num(unsigned int col);

//****************************************************************************
//                      deconstructor
//****************************************************************************

    //////////////////////////////////////////////////////////////////////////
    /// deconstructor
    //////////////////////////////////////////////////////////////////////////
    void clear();

    //////////////////////////////////////////////////////////////////////////
    /// deconstructor
    //////////////////////////////////////////////////////////////////////////
    ~mitk_nl_matrix() { clear(); }

//****************************************************************************
//                              functions
//****************************************************************************

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note get the number of the rows
    /// @return the number of the rows
    //////////////////////////////////////////////////////////////////////////
    unsigned int rows()const{ return num_rows;}

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note get the number of the columns
    /// @return the number of the columns
    //////////////////////////////////////////////////////////////////////////
    unsigned int cols()const{ return num_cols;}

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note return the size of the matrix as a number given by the 
    ///  multiplication of the numbers of rows and columns
    /// @return the total number of elements of the matrix
    //////////////////////////////////////////////////////////////////////////
    unsigned int size()const { return rows() * cols(); }

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note set element the value of the [r-1, c-1] element to val
    /// @param r the horizontal index of the element
    /// @param c the vertical index of the element
    /// @param val the value the element to be set to
    //////////////////////////////////////////////////////////////////////////
    void put(unsigned r, unsigned c, T const&val) { data[r][c] = val; }

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note get element the value of the [r-1, c-1] element to val
    /// @param r the horizontal index of the element
    /// @param c the vertical index of the element
    //////////////////////////////////////////////////////////////////////////
    T    get(unsigned r, unsigned c) const { return data[r][c]; }

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note return the r-th row of the matrix
    /// @param r the index of the row to be returned
    /// @return data[r] the r-th row elements of the matrix 
    //////////////////////////////////////////////////////////////////////////
    T     * operator[](unsigned r) { return data[r]; }

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note return the r-th row of the matrix
    /// @param r the index of the row to be returned
    /// @return data[r] the r-th row elements of the matrix 
    //////////////////////////////////////////////////////////////////////////
    T const * operator[](unsigned r) const { return data[r]; }

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note return pointer to given row
    //////////////////////////////////////////////////////////////////////////
    T       & operator()(unsigned r, unsigned c) { return this->data[r][c]; }

    //////////////////////////////////////////////////////////////////////////
    /// constructor
    /// @note get the r-th row c-th column element of the matrix
    /// @param r the horizontal index of the element
    /// @param c the vertical index of the element
    /// @return data[r][c] the value of the element at the specific position
    //////////////////////////////////////////////////////////////////////////
    T const & operator()(unsigned r, unsigned c) const { return this->data[r][c]; }

    //////////////////////////////////////////////////////////////////////////
    /// set all the elements of the matrix to a constant 
    /// @param val the value to be assigned
    //////////////////////////////////////////////////////////////////////////
    void fill(T const & val);

    //////////////////////////////////////////////////////////////////////////
    /// set all diagonal elements of matrix to a specified value.
    /// @param val the value to be assigned
    //////////////////////////////////////////////////////////////////////////
    void fill_diagonal(T const& val);

    //////////////////////////////////////////////////////////////////////////
    /// fill (laminate) this matrix with the given data.
    /// We assume that p points to a contiguous rows*cols array, stored rowwise.
    /// @param val the value to be used
    //////////////////////////////////////////////////////////////////////////
    void copy_in(T const *val);

    //////////////////////////////////////////////////////////////////////////
    /// fill (laminate) this matrix with the given data.
    /// @note A synonym for copy_in()
    /// @param d the array containing the data to be copied
    //////////////////////////////////////////////////////////////////////////
    void set(T const *d) { copy_in(d); }

    //////////////////////////////////////////////////////////////////////////
    /// fill the given array with this matrix.
    /// @note We assume that p points to a contiguous rows*cols array, stored rowwise.
    /// @param buf the array the data to be copied to
    //////////////////////////////////////////////////////////////////////////
    void copy_out(T *buf) const;

    //////////////////////////////////////////////////////////////////////////
    /// set all elements to value v
    /// @param v the value
    /// @return the matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator=(T const&v) { fill(v); return *this; }


//****************************************************************************
//                              operators
//****************************************************************************

    //////////////////////////////////////////////////////////////////////////
    /// judge whether it is true that the two matrices are the same
    /// @param mat the other matrix used in this comparison
    //////////////////////////////////////////////////////////////////////////
    bool operator==(mitk_nl_matrix<T> const &mat);

    //////////////////////////////////////////////////////////////////////////
    /// judge whether it is true that all elements of the matrix equal to a same value
    /// @param val the value
    //////////////////////////////////////////////////////////////////////////
    bool operator==(const T var);

    //////////////////////////////////////////////////////////////////////////
    /// judge whether it is true that the two matrices are different
    /// @param mat the matrix used in this comparison
    //////////////////////////////////////////////////////////////////////////
    bool operator!=(mitk_nl_matrix<T> const &mat) { return (*this == mat) ? false : true; }

    //////////////////////////////////////////////////////////////////////////
    /// judge whether it is true that no element of a matrix equals a value
    /// @param var the value
    //////////////////////////////////////////////////////////////////////////
    bool operator != (const T var) { return (*this == var) ? false : true; }

    //////////////////////////////////////////////////////////////////////////
    /// copies all elements of a matrix into the current matrix.
    /// @param mat the matrix elements of which are to be copied into the current matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator=(mitk_nl_matrix<T> const& mat);

    //////////////////////////////////////////////////////////////////////////
    /// add this matrix with another matrix
    /// @param mat the matrix elements of which are to be added to the current matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T> operator + (mitk_nl_matrix<T> const &mat);

    //////////////////////////////////////////////////////////////////////////
    /// minus this matrix with another matrix
    /// @param mat the matrix elements of which are to be deduced from the current's
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T> operator - (mitk_nl_matrix<T>const & mat);

    //////////////////////////////////////////////////////////////////////////
    /// add a constant to each element of the matrix
    /// @param value the value
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator+=(T value);

    //////////////////////////////////////////////////////////////////////////
    /// add a constant to each element of the matrix
    /// @param value the value
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T> operator + (T value)
    {
        mitk_nl_matrix<T> _temp = *this;
        _temp += value;
        return _temp;
    }

    //////////////////////////////////////////////////////////////////////////
    /// subtract a constant from each element of the matrix
    /// @param value the value
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator -= (T value);

    //////////////////////////////////////////////////////////////////////////
    /// Subtract a constant from each element of the matrix
    /// @param value the value
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>  operator - (T value)
    {
        mitk_nl_matrix<T> _temp = *this;
        return _temp -= value;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Scalar multiplication of the matrix by a constant
    /// @param value the value
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator*=(T value);

    //////////////////////////////////////////////////////////////////////////
    /// Scalar multiplication of the matrix by a constant
    /// @param value the value
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T> operator* (T value)
    {
        mitk_nl_matrix<T> _temp = *this;
        return _temp *= value;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Divide all elements of the matrix by a constant 
    /// @param value the value
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator/=(T value);

    //////////////////////////////////////////////////////////////////////////
    /// Divide all elements of the matrix by a constant 
    /// @param value the value
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T> operator / (T value)
    {
        mitk_nl_matrix<T> _temp = *this;
        return _temp /= value;
    }

    //////////////////////////////////////////////////////////////////////////
    ///Add this matrix with another matrix
    /// @param mat the matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator+=(mitk_nl_matrix<T> const&mat);

    //////////////////////////////////////////////////////////////////////////
    ///Minus this matrix with another matrix
    /// @param mat the matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator-=(mitk_nl_matrix<T> const&mat);

    //////////////////////////////////////////////////////////////////////////
    ///Multiply this matrix with another matrix
    /// @param rhs the matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator*=(mitk_nl_matrix<T> const&rhs);

    //////////////////////////////////////////////////////////////////////////
    ///Multiply this matrix with another matrix
    /// @param rhs the matrix
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T> operator * (mitk_nl_matrix<T>const&rhs)
    {
        mitk_nl_matrix<T> _temp = *this;
        return _temp *= rhs;
    }

    //////////////////////////////////////////////////////////////////////////
    ///Multiply all elements of the matrix by -1
    //////////////////////////////////////////////////////////////////////////
    mitk_nl_matrix<T>& operator-();


//****************************************************************************
//                      addition functions
//****************************************************************************

    //: Return transpose
    mitk_nl_matrix<T> transpose() const;

    //: Set all elements in the matrix to zero
    void zeros();

    //: Resize matrix
    void set_size(unsigned int rows, unsigned int cols);

    //: Set values of this matrix to those of M, starting at [top,left]
    mitk_nl_matrix<T>& update(mitk_nl_matrix<T> const&, unsigned top=0, unsigned left=0);

    //: Set identity
    void set_identity();

    //: Make a new matrix by applying function to each element.
    mitk_nl_matrix<T> apply(T (*f)(T)) const;

    //: Make a new matrix by applying function to each element.
    mitk_nl_matrix<T> apply(T (*f)(T const&)) const;

    //: Set the elements of the i'th column to v[j]  (No bounds checking)
    void set_column(unsigned int i, T const * v);

    //: Set the elements of the i'th column to value
    void set_column(unsigned int i, T value );

    //: Set j-th column to v
    void set_column(unsigned int i, mitk_nl_vector<T> const& v);

    //: Set the elements of the i'th row to v[j]  (No bounds checking)
    void set_row(unsigned i, T const * v);

    //: Set the elements of the i'th row to value
    void set_row(unsigned i, T value );

    //: Set the i-th row
    void set_row(unsigned i, mitk_nl_vector<T> const&);

    //: Get a vector equal to the given row
    mitk_nl_vector<T> get_row(unsigned int r) const;

    //: Get a vector equal to the given column
    mitk_nl_vector<T> get_column(unsigned int c) const;

    //: Get n rows beginning at rowstart
    mitk_nl_matrix<T> get_n_rows(unsigned int rowstart, unsigned int n) const;

    //: Get n columns beginning at colstart
    mitk_nl_matrix<T> get_n_columns(unsigned int colstart, unsigned int n) const;

    //: Scale elements in given row by a factor of T
    void scale_row(unsigned int row, T value);

    //: Scale elements in given column by a factor of T
    void scale_column(unsigned int col, T value);

    //: Swap this matrix with that matrix
    void swap(mitk_nl_matrix<T> & that);

    //: Access the contiguous block storing the elements in the matrix. (stored row-wise)
    T const* data_block() const { return this->begin(); }

    //: Access the contiguous block storing the elements in the matrix.
    T      * data_block() { return this->begin(); }

    //: Check if the matrix is empty
    bool is_empty() { return (num_rows * num_cols == 0) ? true : false; }

    typedef T element_type;

    //: Iterators
    typedef T       *iterator;

    //: Iterator pointing to start of data
    iterator       begin() { return data ? data[0] : 0; }

    //: Iterator pointing to element beyond end of data
    iterator       end() { return data ? data[0]+num_rows*num_cols : 0; }

    //: Const iterators
    typedef T const *const_iterator;

    //: Iterator pointing to start of data
    const_iterator begin() const { return data ? data[0] : 0; }

    //: Iterator pointing to element beyond end of data
    const_iterator end() const { return data ? data[0]+num_rows*num_cols : 0; }

//****************************************************************************
//                      members
//****************************************************************************

protected:
    unsigned int num_rows;   //the rows of the matrix
    unsigned int num_cols;   //the cols of the matrix
    T ** data;               //the data of the matrix
};
/// @}

//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>::mitk_nl_matrix(unsigned int r, unsigned int c)
:   num_rows(r), num_cols(c)
{
    assert(r > 0 && c > 0);

#ifdef _DEBUG
    if (r <= 0 || c <= 0)
    {
        num_rows = num_cols = 0;
        return;
    }
#endif

    // allocate memory
    this->alloc(r,c);

    // set all elements to zero
    this->zeros();
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>::mitk_nl_matrix(unsigned int r, unsigned int c, T const& v0)
:   num_rows(r), num_cols(c)
{
    assert(r >0 && c > 0);

#ifdef _DEBUG
    if (r <= 0 || c <= 0)
    {
        num_rows = num_cols = 0;
        return;
    }
#endif

    // allocate memory
    this->alloc(r,c);

    // fill all elements with v0
    this->fill(v0);
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>::mitk_nl_matrix(unsigned int r, unsigned int c, unsigned int n, T const values[])
:   num_cols(c), num_rows(r)
{
    assert(r > 0 && c > 0 && n > 0);

#ifdef _DEBUG
    if (r <= 0 || c <= 0 || n <= 0)
    {
        num_rows = num_cols = 0;
        return;
    }
#endif

    // allocate memory
    this->alloc(r,c);

    // set all elements to zero
    this->zeros();

    // copy data from input array
    iterator p = this->begin();
    const_iterator p_end = this->end();
    unsigned int pos = 0;

    while(p != p_end)
    {
        *p = values[pos];
        p++; pos++;
        if (pos >= n)
        {
            return;
        }
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>::mitk_nl_matrix(unsigned int r, unsigned int c, const mitk_nl_vector<T>& values)
:   num_cols(c), num_rows(r)
{
    assert(r > 0 && c > 0 );

#ifdef _DEBUG
    if (r <= 0 && c <= 0)
    {
        num_rows = num_cols = 0;
        return;
    }
#endif

    // allocate memory
    this->alloc(r,c);

    // set all elements to zero
    this->zeros();

    // copy data from input vector
    unsigned int pos = 0;
    unsigned int n = values.size();

    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p = values[pos];
        p++; pos++;
        if (pos >= n)
        {
            return;
        }
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>::mitk_nl_matrix(unsigned int r, unsigned int c, T const* data_block)
:   num_rows(r), num_cols(c)
{
    assert(r > 0 && c > 0);

#ifdef _DEBUG
    if (r <= 0 || c <= 0)
    {
        num_rows = num_cols = 0;
        return;
    }
#endif

    // allocate memory
    this->alloc(r,c);

    // copy data from input array, the num of elements in data_block must be r*c
    unsigned int n = r * c;  
    unsigned int pos = 0;

    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p = data_block[pos];
        p++; pos++;
        if (pos >= n)
        {
            return;
        }
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>::mitk_nl_matrix(mitk_nl_matrix<T>const &mat)
:   num_rows(mat.rows()), num_cols(mat.cols())
{
    assert(num_rows > 0 && num_cols > 0);

#ifdef _DEBUG
    if (num_rows <= 0 || num_cols <= 0)
    {
        num_rows = num_cols = 0;
        return;
    }
#endif

    // allocate memory
    this->alloc(num_rows, num_cols);

    // copy data from input matrix
    for(unsigned int i = 0; i < num_rows; i ++)
    {
        for(unsigned int j = 0; j < num_cols; j ++)
        {
            data[i][j] = mat[i][j];
        }
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::alloc(unsigned int row, unsigned int col)
{
    // allocate memory by on dimensional vector
    do 
    {
        num_rows = row;
        num_cols = col;
        if (num_rows && num_cols) 
        {
            // Allocate memory to hold the row pointers
            data = new T* [num_rows];

            // Allocate memory to hold the elements of the matrix
            T* elmns = new T [num_rows * num_cols];
            
            // Fill in the array of row pointers
            for (unsigned int i = 0; i < num_rows; ++ i)
                data[i] = elmns + i * num_cols;
        }
        else 
        {
            data = NULL;
            num_rows = num_cols = 0;
        }
    } 
    while (false);
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::clear()
{   
    do
    {
        if (num_cols && num_rows) 
        {
            if (data) 
            {
                // deallocate the memory holding matrix elements
                delete [] data[0];
                
                // deallocate the memory holding row pointers
                delete [] data;
            } 
        }
    }
    while (false);

    data = NULL;
    num_rows = 0;
    num_cols = 0;
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_size(unsigned int rows, unsigned int cols)
{
    assert(cols >= 0 && rows >= 0);

#ifdef _DEBUG
    if (cols < 0 || rows < 0)
    {
        rows = 0;
        cols = 0;
    }
#endif

    if (this->data) 
    {
        // if no change in size, just return
        if (this->num_rows == rows && this->num_cols == cols)
            return;
    }

    // clear data first if the data buffer is not empty
    if(data != NULL) 
    {
        this->clear();
    }

    // reallocate memory
    this->alloc(rows, cols);
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_row_num(unsigned int row)
{
    assert(row >= 0);

#ifdef _DEBUG
    if (row < 0)
    {
        row = 0;
    }
#endif

    // clear data first if the data buffer is not empty
    if(data != NULL) 
    {
        this->clear();
    }
    
    // reallocate memory
    this->alloc(row, num_cols);

    // set all elements to zero
    //this->zeros();
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_col_num(unsigned int col)
{
    assert(col >= 0); 

#ifdef _DEBUG
    if (col < 0)
    {
        col = 0;
    }
#endif

    // clear data first if the data buffer is not empty
    if(data != NULL) 
    {
        this->clear();
    }

    // reallocate memory
    this->alloc(num_rows, col);

    // set all elements to zero
    //this->zeros();
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::zeros()
{
    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p = 0;
        p++;
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::fill(T const & val)
{
    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p = val;
        p++;
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::fill_diagonal(T const& val)
{
    assert(num_cols == num_rows);

#ifdef _DEBUG
    if (num_cols != num_rows)
    {
        return;
    }
#endif

    //set diagonal elements
    for (unsigned int i = 0 ; i < num_rows; i ++)
    {
        for (unsigned int j = 0; j < num_cols; j ++)
        {
            if (i == j)
            {
                data[i][j] = val;
            }
        }
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::copy_in(T const *val)
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_cols <= 0 || num_rows <= 0)
    {
        return;
    }
#endif

    //the numbers of val that have been used
    unsigned int pos = 0;
    
    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p = val[pos];
        p++;
        pos++;
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::copy_out(T *buf) const
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_cols <= 0 || num_rows <= 0)
    {
        return;
    }
#endif

    //the numbers that have been copy into the buffer
    unsigned int pos = 0;

    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        buf[pos] = *p;
        p++;
        pos++;
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline bool mitk_nl_matrix<T>::operator==(mitk_nl_matrix<T>const &mat)
{
    //if there is nothing in both matrix
    if ((num_cols * num_rows == 0) && (mat.rows() * mat.cols() == 0))
    {
        return true;
    }

    //if two matrices do not have equal sizes 
    if (num_cols != mat.cols() || num_rows != mat.rows())
    {
        return false;
    }

    //else if two matrices have the same col and row
    for (unsigned int i = 0; i < num_rows; i ++)
    {
        for (unsigned int j = 0; j < num_cols ; j++)
        {
            if (data[i][j] != mat[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
//-----------------------------------------------------------------------------
template<class T>
inline bool mitk_nl_matrix<T>::operator==(const T var)
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_cols <= 0 || num_rows <= 0)
    {
        return false;
    }
#endif

    for (unsigned int i = 0; i < num_rows; i ++)
    {
        for (unsigned int j = 0; j < num_cols; j ++)
        {
            if (data[i][j] != var)
            {
                return false;
            }
        }
    }

    return true;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>& mitk_nl_matrix<T>::operator = (mitk_nl_matrix<T> const &mat)
{
    if (*this == mat)
    {
        return *this;
    }

    //if two matrices do not have equal sizes
    if (num_cols != mat.cols() || num_rows != mat.rows())
    {
        // clear data first if the data buffer is not empty
        if(data != NULL) 
        {
            this->clear();
        }

        // reallocate memory
        this->alloc(mat.rows(), mat.cols());
    }

    // copy data
    for (unsigned int i = 0; i < num_rows; i ++)
    {
        for (unsigned int j = 0 ;j < num_cols; j ++)
        {
            data[i][j] = mat[i][j];
        }
    }
    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>& mitk_nl_matrix<T>::operator += (T value)
{
    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p += value;
        p++;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>& mitk_nl_matrix<T>::operator *= (T value)
{
    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p *= value;
        p++;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>&mitk_nl_matrix<T>::operator +=(mitk_nl_matrix<T>const &mat)
{
    if (num_cols == mat.cols() && num_rows == mat.rows())
    {
        for (unsigned int i = 0; i < num_rows; i ++)
        {
            for (unsigned int j = 0 ; j < num_cols; j ++)
            {
                data[i][j] += mat[i][j];
            }
        }
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>&mitk_nl_matrix<T>::operator -=(mitk_nl_matrix<T>const &mat)
{
    if (num_cols == mat.cols() && num_rows == mat.rows())
    {
        for (unsigned int i = 0; i < num_rows; i ++)
        {
            for (unsigned int j = 0 ; j < num_cols; j ++)
            {
                data[i][j] -= mat[i][j];
            }
        }
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>& mitk_nl_matrix<T>::operator *=(mitk_nl_matrix<T> const &mat)
{
    if(num_cols == mat.rows())
    {
        unsigned int i, j, k;
        num_cols = mat.cols();

        mitk_nl_matrix<T> temp(num_rows, num_cols);
        for (i = 0 ; i < num_rows; i ++)
        {
            for (j = 0; j < num_cols; j ++)
            {
                for (k = 0; k < mat.rows(); k ++)
                {
                    temp[i][j] += data[i][k] * mat[k][j];
                }
            }
        }
        *this = temp;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>& mitk_nl_matrix<T>::operator -()
{
    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p *= -1;
        p++;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>& mitk_nl_matrix<T>::operator -= (T value)
{
    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p -= value;
        p++;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>& mitk_nl_matrix<T>::operator /=(T value)
{
    if(value == 0) return *this;

    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p /= value;
        p++;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T> mitk_nl_matrix<T>::apply(T (*f)(T)) const
{
    assert(num_cols >0 && num_rows >0);

#ifdef _DEBUG
    if (num_rows <= 0 || num_cols <= 0)
    {
        return *this;
    }
#endif

    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p = (*f)(*p);
        p++;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T> mitk_nl_matrix<T>::apply(T (*f)(T const&)) const
{
    assert(num_cols >0 && num_rows >0);

#ifdef _DEBUG
    if (num_cols <=0 || num_rows <= 0)
    {
        return *this;
    }
#endif

    iterator p = this->begin();
    const_iterator p_end = this->end();

    while(p != p_end)
    {
        *p = (*f)(*p);
        p++;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_column(unsigned int i, T const * v)
{
    assert(num_cols > 0 && num_rows > 0);
    
#ifdef _DEBUG
    if (num_cols <= 0 || num_rows <= 0)
    {
        return; 
    }
#endif

    assert(i < num_cols);

#ifdef _DEBUG
    if (i >= num_cols)
    {
        return;
    }
#endif

    assert(i >= 0);

#ifdef _DEBUG
    if (i < 0)
    {
        return;
    }
#endif

    for (unsigned int j = 0; j < num_rows; j ++)
    {
        data[j][i] = v[j];
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_column(unsigned int i, T v)
{
    assert(num_rows > 0 && num_cols > 0);

#ifdef _DEBUG
    if (num_cols <= 0 || num_rows  <= 0)
    {
        return ;
    }
#endif

    assert(i < num_cols);
    
#ifdef _DEBUG
    if (i >= num_cols)
    {
        return;
    }
#endif

    assert(i >= 0);

#ifdef _DEBUG
    if (i < 0)
    {
        return;
    }
#endif
    
    for (unsigned int j = 0; j < num_rows; j ++)
    {
        data[j][i] = v;
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_column(unsigned int i, mitk_nl_vector<T>const &v)
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_cols <= 0 || num_rows <= 0)
    {
        return;
    }
#endif

    assert(num_rows == v.size());

#ifdef _DEBUG
    if (num_rows != v.size())
    {
        return;
    }
#endif

    assert(i < num_cols);

#ifdef _DEBUG
    if (i >= num_cols)
    {
        return;
    }
#endif

    assert(i >= 0);

#ifdef _DEBUG
    if (i < 0)
    {
        return;
    }
#endif

    for (unsigned int j = 0; j < num_rows; j ++)
    {
        data[j][i] = v[j];
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_row(unsigned int i, T const *v)
{
    assert(num_rows >0 && num_cols > 0);

#ifdef _DEBUG
    if (num_cols <= 0 || num_rows <= 0)
    {
        return ;
    }
#endif

    assert(i < num_rows);

#ifdef _DEBUG
    if (i >= num_rows)
    {
        return ;
    }
#endif

    assert(i >= 0);

#ifdef _DEBUG
    if (i < 0)
    {
        return ;
    }
#endif

    for (unsigned int j = 0; j < num_cols; j ++)
    {
        data[i][j] = v[j];
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_row(unsigned int i, T v)
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_rows <= 0 || num_cols <= 0)
    {
        return ;
    }
#endif

    assert(i < num_rows);

#ifdef _DEBUG
    if (i >= num_rows)
    {
        return ;
    }
#endif

    assert(i >= 0);

#ifdef _DEBUG
    if (i < 0)
    {
        return ;
    }
#endif

    for (unsigned int j = 0; j < num_cols ; j ++)
    {
        data[i][j] = v;
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_row(unsigned int i, mitk_nl_vector<T>const &v)
{
    assert(num_cols > 0  && num_rows > 0);

#ifdef _DEBUG
    if (num_rows <= 0 || num_cols <= 0)
    {
        return ;
    }
#endif

    assert(num_cols == v.size());

#ifdef _DEBUG
    if (num_cols != v.size())
    {
        return ;
    }
#endif

    assert(i < num_rows);

#ifdef _DEBUG
    if (i >= num_rows)
    {
        return ;
    }
#endif

    assert(i >= 0);

#ifdef _DEBUG
    if (i < 0)
    {
        return ;
    }
#endif

    for (unsigned int j = 0; j < num_cols; j ++)
    {
        data[i][j] = v[j];
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T> mitk_nl_matrix<T>::get_row(unsigned int r) const
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_rows <= 0 || num_cols <= 0)
    {
        mitk_nl_vector<T> _res;
        return _res;
    }
#endif

    assert(r < num_rows && r >= 0);

#ifdef _DEBUG
    if (r >= num_rows || r < 0)
    {
        mitk_nl_vector<T> _res;
        return _res;
    }
#endif

    mitk_nl_vector<T> res(num_cols);
    for (unsigned int i = 0; i < num_cols; i ++)
    {
        res[i] = data[r][i];
    }
    return res;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T> mitk_nl_matrix<T>::get_column(unsigned int c)const
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_rows <= 0 || num_cols <= 0)
    {
        mitk_nl_vector<T> _res;
        return _res;
    }
#endif

    assert(c < num_cols && c >= 0);

#ifdef _DEBUG
    if (c >= num_cols || c < 0)
    {
        mitk_nl_vector<T> _res;
        return _res;
    }
#endif

    mitk_nl_vector<T> res(num_rows);
    for (unsigned int i = 0; i < num_rows; i ++)
    {
        res[i] = data[i][c];
    }
    return res;
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::scale_row(unsigned int row, T value)
{
    assert(num_rows > 0 && num_cols > 0);

#ifdef _DEBUG
    if (num_cols <= 0 || num_rows <= 0)
    {
        return;
    }
#endif

    assert(row >= 0 && row < num_rows);

#ifdef _DEBUG
    if (row < 0 || row >= num_rows)
    {
        return;
    }
#endif

    for (unsigned int i = 0; i < num_cols; i ++)
    {
        data[row][i] *= value; 
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::scale_column(unsigned int col, T value)
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_cols <= 0 || num_rows <= 0)
    {
        return;
    }
#endif

    assert(col >=0 && col < num_cols);

#ifdef _DEBUG
    if (col < 0 || col >= num_cols)
    {
        return ;
    }
#endif

    for (unsigned int i = 0; i < num_rows; i ++)
    {
        data[i][col] *= value;
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::swap(mitk_nl_matrix<T> & that)
{
    mitk_nl_matrix<T> temp = *this;
    *this = that;
    that = temp;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T> mitk_nl_matrix<T>::get_n_rows(unsigned int rowstart, unsigned int n) const
{
    assert(num_rows > 0 && num_cols > 0);

#ifdef _DEBUG
    if (num_cols <= 0 || num_rows <= 0)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    assert(rowstart >= 0 && n >= 0);

#ifdef _DEBUG
    if (rowstart < 0 || n < 0)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    assert((rowstart + n) < num_rows);

#ifdef _DEBUG
    if ((rowstart + n) >= num_rows)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    if (n == 0)
    {
        return mitk_nl_matrix<T>();
    }
    mitk_nl_matrix<T> res(n, num_cols);
    for (unsigned int i = rowstart; i < rowstart + n; i ++)
    {
        res.set_row((i-rowstart), this->get_row(i));
    }
    return res;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T> mitk_nl_matrix<T>::get_n_columns(unsigned int colstart, unsigned int n) const
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_rows <= 0 || num_cols <= 0)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    assert((colstart + n) < num_cols);

#ifdef _DEBUG
    if ((colstart + n) >= num_cols)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    assert(colstart >= 0 && n >= 0);
    
#ifdef _DEBUG
    if (colstart < 0 || n < 0)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    if (n == 0)
    {
        return mitk_nl_matrix<T>();
    }

    mitk_nl_matrix<T> res(num_rows, n);
    for (unsigned int i = colstart; i < colstart + n; i ++)
    {
        res.set_column((i - colstart), this->get_column(i));
    }
    return res;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T>  mitk_nl_matrix<T>::operator + (mitk_nl_matrix<T>const &mat)
{
    assert(num_rows == mat.rows() && num_cols == mat.cols());

#ifdef _DEBUG
    if (num_rows != mat.rows() || num_cols != mat.cols())
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    assert(num_cols > 0);

#ifdef _DEBUG
    if (num_cols <= 0)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    assert(num_rows > 0);

#ifdef _DEBUG
    if (num_rows <= 0)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    mitk_nl_matrix<T> _temp = *this;

    for (unsigned int i = 0; i < num_rows; i ++)
    {
        for (unsigned int j = 0; j < num_cols; j ++)
        {
            _temp[i][j] += mat[i][j]; 
        }
    }
    return _temp;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_matrix<T> mitk_nl_matrix<T>::operator - (mitk_nl_matrix<T>const& mat)
{
    assert(num_rows == mat.rows() && num_cols == mat.cols());

#ifdef _DEBUG
    if (num_rows != mat.rows() || num_cols != mat.cols())
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    assert(num_cols > 0);

#ifdef _DEBUG
    if (num_cols <= 0)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    assert(num_rows > 0);

#ifdef _DEBUG
    if (num_rows <= 0)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif

    mitk_nl_matrix<T> _temp = *this;

    _temp -= mat;
      
    return _temp;
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_matrix<T>::set_identity()
{
    assert(num_cols > 0 && num_rows > 0);

#ifdef _DEBUG
    if (num_rows <= 0 || num_cols <= 0)
    {
        return;
    }
#endif

    assert(num_cols == num_rows);

#ifdef _DEBUG
    if(num_cols != num_rows)
    {
        return;
    }
#endif

    for (unsigned int i = 0; i < num_rows; i ++)
    {
        for (unsigned int j = 0; j < num_cols; j ++)
        {
            if (i == j)
            {
                data[i][j] = 1;
            }
            else
            {
                data[i][j] = 0;
            }
        }
    }
}
//-----------------------------------------------------------------------------
template<class T>
mitk_nl_matrix<T>& mitk_nl_matrix<T>::update(mitk_nl_matrix<T> const& m, unsigned top, unsigned left)
{
    unsigned int bottom = top + m.num_rows;
    unsigned int right = left + m.num_cols;

    for (unsigned int i = top; i < bottom; i++)
        for (unsigned int j = left; j < right; j++)
            this->data[i][j] = m.data[i-top][j-left];

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
mitk_nl_matrix<T> mitk_nl_matrix<T>::transpose() const
{
    mitk_nl_matrix<T> result(this->num_cols, this->num_rows);
    for (unsigned int i = 0; i < this->num_cols; i++)
        for (unsigned int j = 0; j < this->num_rows; j++)
            result.data[i][j] = this->data[j][i];
    return result;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#endif




