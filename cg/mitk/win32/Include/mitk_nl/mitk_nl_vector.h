/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





//////////////////////////////////////////////////////////////////////////
/// \class mitk_nl_vector
/// \brief This is the base structure of vector 
/// @{
//////////////////////////////////////////////////////////////////////////

#ifndef _MITK_NL_VECTOR_H
#define _MITK_NL_VECTOR_H

/*============================================================================
  \brief Program: 
  this is the basic class vector
  \author written on Aug 2,2006
============================================================================*/
#include <assert.h>
#include <math.h>

#include <vector>

//#define NULL  0

namespace mitk_nl {

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) 
{
    while (first != last) *result++ = *first++;
    return result;
}

} //End namespace mitk_nl

template<class T>
class mitk_nl_vector
{
    public:
    //////////////////////////////////////////////////////////////////////////
    /// Constructor.
    /// \note Create an empty vector
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector():num_elmts(0) , data(0), ref_flag(false){}
    
    //////////////////////////////////////////////////////////////////////////
    /// Constructor.
    /// \note Creates vector containing len elements.
    /// Elements are not initialized.
    /// \param len point out the length of the vector
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector(unsigned int len);

    //////////////////////////////////////////////////////////////////////////
    /// Constructor.
    /// \note Creates vector of len elements, all set to v0
    /// \param len point out the length of the vector 
    /// \param v0 point out the value of all of the data in the vector
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector(unsigned int len, T const& v0);  

    //////////////////////////////////////////////////////////////////////////
    /// Constructor.
    /// \note Creates a vector of specified length and initialize first n elements with values. O(n).
    /// \param len point out the length of the vector
    /// \param n point out how many data of the vector will be set
    /// \param values the array contains the value for the vector
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector(unsigned int len, unsigned int n, T const values[]);

    //////////////////////////////////////////////////////////////////////////
    /// Constructor
    /// \note Create n element vector and copy data from data_block
    /// \param n point out the length of the vector
    /// \param data_block contains the data for the vector
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector(unsigned int n,T const* data_block);

    //////////////////////////////////////////////////////////////////////////  
    /// Constructor.
    /// \note Copy constructor
    /// \param vec the vector from which a new vector will be created.
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector(mitk_nl_vector<T> const& vec);

    //////////////////////////////////////////////////////////////////////////
    ///  Destructor.
    //////////////////////////////////////////////////////////////////////////
        ~mitk_nl_vector() { clear(); }

    //////////////////////////////////////////////////////////////////////////
    /// Set all num to zero
    //////////////////////////////////////////////////////////////////////////
        void zeros();

    //////////////////////////////////////////////////////////////////////////
    /// get the number of the data in the vector
    //////////////////////////////////////////////////////////////////////////
        unsigned int size() const { return num_elmts; }
    
    //////////////////////////////////////////////////////////////////////////
    /// Put value at given position in vector.
    /// \param i point the index of the data that will be changed
    /// \param d the data for the (i +1 )th value of the vector  
    //////////////////////////////////////////////////////////////////////////
        void put(unsigned int i, T const& d);
    
    //////////////////////////////////////////////////////////////////////////
    /// Get value at element i
    /// \param i the index of the value that will get 
    //////////////////////////////////////////////////////////////////////////
        T get(unsigned int i) const;

    //////////////////////////////////////////////////////////////////////////
    /// get norm of the vector
    //////////////////////////////////////////////////////////////////////////
        T get_norm() const;

    //////////////////////////////////////////////////////////////////////////
    /// check if the vector is empty
    //////////////////////////////////////////////////////////////////////////
        bool is_empty() { return num_elmts == 0 ? true : false; }

    //////////////////////////////////////////////////////////////////////////
    /// check if the vector is not empty
    //////////////////////////////////////////////////////////////////////////
        bool is_unempty() { return num_elmts == 0 ? false : true; }

    //////////////////////////////////////////////////////////////////////////
    /// Set all values to v
    /// \param v the value with which to fill the vector
    //////////////////////////////////////////////////////////////////////////
        void fill(T const& v);

        void assign(unsigned int num, T const& v);

    //////////////////////////////////////////////////////////////////////////
    /// Set elements by a stl vector
    //////////////////////////////////////////////////////////////////////////
        void copy_in(const std::vector<T>& vec);

    //////////////////////////////////////////////////////////////////////////
    /// Copy elements to a stl vector
    //////////////////////////////////////////////////////////////////////////
        void copy_out(std::vector<T>& vec) const;
    
    //////////////////////////////////////////////////////////////////////////
    /// Sets elements by ptr[]
    /// \note: ptr[i] must be valid for i=0..size()-1
    /// \param ptr the buffer from which the data will be copied
    //////////////////////////////////////////////////////////////////////////
        void copy_in(T const * ptr);

    //////////////////////////////////////////////////////////////////////////
    /// Copy elements to ptr[i]
    /// \note: ptr[i] must be valid for i=0..size()-1
    /// \param ver the buffer to receive data form the vector
    //////////////////////////////////////////////////////////////////////////
        void copy_out(T *ver) const;

        void copy_in(mitk_nl_vector<T> const &ver);

        void copy_in_ref(mitk_nl_vector<T> const &ver);

    //////////////////////////////////////////////////////////////////////////
    /// Set the num of element in the vector
    /// \param num the new length of the vector
    //////////////////////////////////////////////////////////////////////////
        void set_size(unsigned int num);

    //////////////////////////////////////////////////////////////////////////
    /// get the number i in the vector
    /// \param i the index of the data which will be returned
    //////////////////////////////////////////////////////////////////////////
        T const & operator()(unsigned int i) const { return data[i]; }

    //////////////////////////////////////////////////////////////////////////
    /// get the number i in the vector
    /// \param i the index of the data which will be returned and set
    //////////////////////////////////////////////////////////////////////////
        T & operator() (unsigned int i) { return data[i]; }

    //////////////////////////////////////////////////////////////////////////
    /// Reference to the element at specified index. No range checking.
    /// \param i the index of the data which will be returned
    //////////////////////////////////////////////////////////////////////////
        T const & operator[](unsigned int i) const { return data[i]; }
        
    //////////////////////////////////////////////////////////////////////////
    /// Reference to the element at specified index. No range checking.
    /// \param i the index of the data which will be returned
    //////////////////////////////////////////////////////////////////////////
        T & operator[](unsigned int i) { return data[i]; }

    //////////////////////////////////////////////////////////////////////////
    /// Judge if the two vectors are the same
    /// \return Return true if the two vector are the same
    /// \return Return false if the two vector are not the same 
    //////////////////////////////////////////////////////////////////////////  
        bool operator==(mitk_nl_vector<T> const &rhs);

    //////////////////////////////////////////////////////////////////////////
    /// Judge if all the data in vector are var
    /// \return Return true if all data in vector are var
    /// \return Return false if not all the data in vector are var
    //////////////////////////////////////////////////////////////////////////
        bool operator == (const T var);

    //////////////////////////////////////////////////////////////////////////
    /// Judge if two vectors are the same
    /// \return Return true if the two vectors are not the same
    /// \return Return false if the two vectors are the same
    //////////////////////////////////////////////////////////////////////////
        bool operator!= (mitk_nl_vector<T>const &rhs)
        {
            return (*this == rhs) ? false : true;
        }

    //////////////////////////////////////////////////////////////////////////
    /// Judge if the all the data in vector are not var
    /// \return Return true if not all the data in vector are true
    /// \return Return false if all the data are var 
    //////////////////////////////////////////////////////////////////////////
        bool operator != (const T var)
        {
            return (*this == var) ? false : true;
        }

    //////////////////////////////////////////////////////////////////////////
    /// Set all elements to value v
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T>& operator=(T const&v) { fill(v); return *this; }

    //////////////////////////////////////////////////////////////////////////
    /// Copy operator
    //////////////////////////////////////////////////////////////////////////  
        mitk_nl_vector<T>& operator=(mitk_nl_vector<T> const& rhs);

    //////////////////////////////////////////////////////////////////////////
    /// Add scalar value to all elements
    //////////////////////////////////////////////////////////////////////////  
        mitk_nl_vector<T>& operator+=(T ver);
    
    //////////////////////////////////////////////////////////////////////////
    /// Add scalar value to all elements
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T> operator + (T ver)
        {
            mitk_nl_vector<T> _temp = *this;
            return _temp += ver;
        }

    //////////////////////////////////////////////////////////////////////////
    /// Subtract scalar value from all elements
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T>& operator-=(T value) { return *this += (-value); }
        
    //////////////////////////////////////////////////////////////////////////
    /// Subtract scalar value from all elements
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T> operator - (T value)
        {
            mitk_nl_vector<T> _temp = *this;
            return _temp -= value;
        }

    //////////////////////////////////////////////////////////////////////////
    /// Multiply all elements by scalar
    //////////////////////////////////////////////////////////////////////////  
        mitk_nl_vector<T>& operator*=(T ver);

    //////////////////////////////////////////////////////////////////////////
    /// Multiply all elements by scalar
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T> operator * (T ver)
        {
            mitk_nl_vector<T> _temp = *this;
            return _temp *= ver;
        }

    //////////////////////////////////////////////////////////////////////////
    /// Divide all elements by scalar
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T>& operator/=(T ver);

    //////////////////////////////////////////////////////////////////////////
    /// Divide all elements by scalar
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T> operator/ (T ver)
        {
            mitk_nl_vector<T> _temp = *this;
            return _temp /= ver;
        }

    //////////////////////////////////////////////////////////////////////////
    /// Add rhs to this and return *this
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T>& operator+=(mitk_nl_vector<T> const& rhs);

    //////////////////////////////////////////////////////////////////////////
    /// Add rhs to this and return *this
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T> operator + (mitk_nl_vector<T>const &rhs)
        {
            mitk_nl_vector<T> _temp = *this;
            return _temp += rhs;
        }

    //////////////////////////////////////////////////////////////////////////
    /// Subtract rhs from this and return *this
    //////////////////////////////////////////////////////////////////////////  
        mitk_nl_vector<T>& operator-=(mitk_nl_vector<T> const& rhs);

    //////////////////////////////////////////////////////////////////////////
    /// Subtract rhs from this and return *this
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T> operator - (mitk_nl_vector<T> const& rhs)
        {
            mitk_nl_vector<T> _temp = *this;
            return _temp -= rhs;
        }

    //////////////////////////////////////////////////////////////////////////
    /// Access the contiguous block storing the elements in the vector. O(1).
    /// \note  data_block()[0] is the first element of the vector
    //////////////////////////////////////////////////////////////////////////
        T const* data_block() const { return data; }

    //////////////////////////////////////////////////////////////////////////
    /// Access the contiguous block storing the elements in the vector. O(1).
    /// \note data_block()[0] is the first element of the vector
    //////////////////////////////////////////////////////////////////////////
        T      * data_block() { return data; }

    //////////////////////////////////////////////////////////////////////////
    /// Type def for iterators
    //////////////////////////////////////////////////////////////////////////
        typedef T element_type;

    //////////////////////////////////////////////////////////////////////////
    /// pointer
    //////////////////////////////////////////////////////////////////////////
        typedef T *iterator;

    //////////////////////////////////////////////////////////////////////////
    /// point to the first data
    //////////////////////////////////////////////////////////////////////////
        iterator begin() {return data;}

    //////////////////////////////////////////////////////////////////////////
    /// point to the end
    //////////////////////////////////////////////////////////////////////////
        iterator end()   {return data + num_elmts;}

    //////////////////////////////////////////////////////////////////////////
    /// const iterator type
    //////////////////////////////////////////////////////////////////////////
        typedef T const *const_iterator;

    //////////////////////////////////////////////////////////////////////////
    /// to the begin
    //////////////////////////////////////////////////////////////////////////
        const_iterator begin()const {return data;}

    //////////////////////////////////////////////////////////////////////////
    /// to the end
    //////////////////////////////////////////////////////////////////////////
        const_iterator end() const { return data + num_elmts;}

    //////////////////////////////////////////////////////////////////////////
    /// Returns a sub vector specified by the start index and length. O(n).
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T> extract(unsigned int len, unsigned int start=0) const;

    //////////////////////////////////////////////////////////////////////////
    /// Replaces elements with index beginning at start, by values of v. O(n).
    //////////////////////////////////////////////////////////////////////////
        mitk_nl_vector<T>& update(mitk_nl_vector<T> const&rhs, unsigned int start=0);

    protected:
        virtual void alloc(unsigned int num);
        virtual void clear();

        unsigned    num_elmts;         /**< Number of elements (length) */
        T*          data;              /**< Pointer to the actual data */
        bool        ref_flag;
};

/// @}

//-----------------------------------------------------------------------------
template <class T>
inline mitk_nl_vector<T>::mitk_nl_vector(unsigned int len)
{
    if(len < 0) return;

    // allocate memory
    this->alloc(len);
    
    // set all elements to zero
    this->zeros();
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T>::mitk_nl_vector(unsigned int len,T const &v0)
{
    if (len < 0) return;

    // allocate memory
    this->alloc(len);

    // set all elements to zero
    this->fill(v0);
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T>::mitk_nl_vector(unsigned int len, unsigned int n, T const values[])
{
    if (len < 0) return;

    // allocate memory
    this->alloc(len);

    //init
    this->zeros();

    iterator p = begin();
    const_iterator p_end = end();
    unsigned int pos = 0;

    while(p != p_end)
    {
        *p = values[pos];
        p++; pos++;
        if(pos >= n)
        {
            return;
        }
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T>::mitk_nl_vector(unsigned int n, T const* data_block)
{
    if (n <= 0) return;

    // allocate memory
    this->alloc(n);

    // copy data
    for (unsigned int i = 0; i < num_elmts; i ++)
    {
        data[i] = data_block[i];
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T>::mitk_nl_vector(mitk_nl_vector<T>const &ver)
{
    if( ver.size() == 0 ) return;

    // allocate memory
    this->alloc(ver.size());

    // copy data
    for (unsigned int i = 0; i < num_elmts; i ++)
    {
        data[i] = ver[i];
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_vector<T>::alloc(unsigned int num)
{
    if( num > 0)
    {
        num_elmts = num;
        data = new T[num_elmts];
        ref_flag = false;
    }
    else
    {
        this->clear();   /* FIXME */
    }
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_vector<T>::clear()
{
    if (data && !ref_flag)
    {
        delete[] data;
    }

    data = NULL;
    num_elmts = 0;
    ref_flag = false;      /* FIXME */
}
//-----------------------------------------------------------------------------
template<class T>
inline void mitk_nl_vector<T>::zeros()
{
    if( num_elmts <= 0) return;

    iterator p = begin();
    const_iterator p_end = end();

    while(p != p_end)
    {
        *p = 0;
        p++;
    }
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::fill(T const& v)
{
    if (num_elmts == 0) return;

    iterator p = begin();
    const_iterator p_end = end();

    while(p != p_end)
    {
        *p = v;
        p++;
    }
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::assign(unsigned int num, T const& v)
{
    this->set_size(num);
    this->fill(v);
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::set_size(unsigned int num)
{
    if( num <= 0 ) return;

    if( num_elmts == num ) return;

    // clear data first
    this->clear();

    // reallocate memory
    this->alloc(num);

    // init elements
    this->zeros();          /* FIXME */
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::put(unsigned int i, T const& d)
{
    assert(i < num_elmts && i >= 0);
    
#ifndef _DEBUG
    if (i >= num_elmts)
    {
        i = num_elmts - 1;
    }
    else if (i < 0)
    {
        i = 0;
    }
#endif

    data[i] = d;
}
//-----------------------------------------------------------------------------
template<class T>
inline T mitk_nl_vector<T>::get(unsigned int i) const
{
    assert(i < num_elmts && i >= 0);

#ifndef _DEBUG
    if (i >= num_elmts)
    {
        i = num_elmts - 1;
    }
    else if (i < 0)
    {
        i = 0;
    }
#endif

    return data[i];
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::copy_in(T const * ptr)
{
    //if there is no number in the vector
    if (num_elmts == 0) return;

    for (unsigned int i = 0; i < num_elmts; i ++)
    {
        data[i] = ptr[i];
    }
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::copy_out(T *ver) const
{
    //if there is no number in the vector
    if (num_elmts == 0) return;

    for (unsigned int i = 0 ; i < num_elmts; i ++)
    {
        ver[i] = data[i];
    }
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::copy_in(const std::vector<T>& vec)
{
    assert(num_elmts == vec.size());

    if(num_elmts != vec.size())
    {
        return;
    }

    for(unsigned int i = 0; i < num_elmts; i ++)
    {
        data[i] = vec[i];
    }
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::copy_out(std::vector<T>& vec)  const
{
    assert(num_elmts == vec.size());

    if(num_elmts != vec.size())
    {
        return;
    }

    for(unsigned int i = 0; i < num_elmts; i ++)
    {
        vec[i] = data[i];
    }
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::copy_in(mitk_nl_vector<T> const &ver)
{
    assert(num_elmts == ver.size());

    if(num_elmts != ver.size())
    {
        return;
    }

    for (unsigned int i = 0; i < num_elmts; i ++)
    {
        data[i] = ver[i];
    }
}
//-----------------------------------------------------------------------------
template<class T>
void mitk_nl_vector<T>::copy_in_ref(mitk_nl_vector<T> const &ver)
{
    // clear data
    this->clear();

    // set data pointer
    data = const_cast<T*>(ver.data_block());

    num_elmts = ver.size();
    ref_flag = true;
}
//-----------------------------------------------------------------------------
template<class T>
inline bool mitk_nl_vector<T>::operator==(mitk_nl_vector<T> const &rhs)
{
    //if both vectors have nothing in them
    if (rhs.size() == 0 && num_elmts == 0)
    {
        return true;
    }

    // unequal size
    if (rhs.size() != num_elmts)
    {
        return false;
    }

    for (unsigned int i = 0; i < num_elmts; i ++)
    {
        if (data[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}
//-----------------------------------------------------------------------------
template<class T>
inline bool mitk_nl_vector<T>::operator == (const T var)
{
    if (num_elmts <= 0)
    {
        return false;
    }

    for (unsigned int i = 0; i < num_elmts; i ++)
    {
        if (data[i] != var)
        {
            return false;
        }
    }

    return true;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T>& mitk_nl_vector<T>::operator = (mitk_nl_vector<T> const& rhs)
{
/*  if (*this == rhs)
    {
        return *this;
    }
*/
    unsigned int vsize = rhs.size();

    // reallocate memory if needed
    if(num_elmts < vsize)
    {
        this->clear();
        this->alloc(vsize);
    }

    // copy data
    for (unsigned int i = 0; i < vsize; i ++) 
        data[i] = rhs[i];

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T>& mitk_nl_vector<T> ::operator += (T ver)
{   
    iterator p = begin();
    const_iterator p_end = end();

    while(p != p_end)
    {
        *p += ver;
        p++;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T> & mitk_nl_vector<T> ::operator *= (T ver)
{
    iterator p = begin();
    const_iterator p_end = end();

    while(p != p_end)
    {
        *p *= ver;
        p++;
    }

    return *this;
}   
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T> & mitk_nl_vector<T> ::operator /= (T ver)
{
    if(ver == 0) return *this;

    iterator p = begin();
    const_iterator p_end = end();

    while(p != p_end)
    {
        *p /= ver;
        p++;
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T> & mitk_nl_vector<T>::operator += (mitk_nl_vector<T>const & rhs)
{
    //the number in the vector must be the same
    if(num_elmts != rhs.size())
    {
        return *this;
    }

    if (num_elmts == 0)
    {
        return *this;
    }

    for (unsigned int i = 0 ; i < num_elmts; i ++)
    {
        data[i] += rhs[i];
    }

    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T> & mitk_nl_vector<T> ::operator -= (mitk_nl_vector<T> const& rhs)
{
    if(num_elmts != rhs.size()) 
    {
        return *this;
    }

    if (num_elmts == 0)
    {
        return *this;
    }

    for (unsigned int i = 0; i < num_elmts ; i ++)
    {
        data[i] -= rhs[i];
    }
    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T> mitk_nl_vector<T> ::extract(unsigned int len, unsigned int start/* =0 */)const
{
    assert(len > 0);
    assert((start + len) <= num_elmts);
    
    //create a vector for return
    mitk_nl_vector<T> res(len);

    for (unsigned int i = start; i < start + len; i ++)
    {
        res[i - start] = data[i];
    }
    return res;
}
//-----------------------------------------------------------------------------
template<class T>
inline mitk_nl_vector<T>& mitk_nl_vector<T>::update(mitk_nl_vector<T> const&rhs, unsigned int start/* =0 */)
{
    //the numbers to update must < numbers in the vector
    assert((start + rhs.size()) <= num_elmts);

    for (int i = start; i < start + rhs.size(); i ++)
    {
        data[i] = rhs[i - start];
    }
    return *this;
}
//-----------------------------------------------------------------------------
template<class T>
inline T mitk_nl_vector<T>::get_norm() const
{
    T sum = 0;
    for( unsigned int i = 0; i < num_elmts; i++ )
    {
        const T v = data[i];
        sum += v * v;
    }
    return sqrt(double(sum));
}
//-----------------------------------------------------------------------------
template<class T>
class mitk_nl_vector_ref : public mitk_nl_vector<T>
{
public:
    mitk_nl_vector_ref()
    {
        mitk_nl_vector<T>::num_elmts = 0;
        mitk_nl_vector<T>::data = NULL;
    }

    mitk_nl_vector_ref(unsigned int n, T* data_block)
    {
        mitk_nl_vector<T>::num_elmts = n;
        mitk_nl_vector<T>::data = data_block;
    }

    ~mitk_nl_vector_ref()
    {
        this->clear();
    }
protected:
    void alloc(unsigned int num)
    {
        // do noting
    }

    void clear()
    {
        mitk_nl_vector<T>::data = NULL;
        mitk_nl_vector<T>::num_elmts = 0;
    }
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#endif



