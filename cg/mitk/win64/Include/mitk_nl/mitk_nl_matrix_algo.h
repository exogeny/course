/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




//////////////////////////////////////////////////////////////////////////
/// @defgroup MATRIX
/// @{
//////////////////////////////////////////////////////////////////////////

#ifndef _MITK_MATRIX_H
#define _MITK_MATRIX_H

/************************************************************************
**   functions to operate matrix and vector
************************************************************************/
#include <assert.h>
#include "mitk_nl_matrix.h"
#include "mitk_nl_vector.h"
#include <math.h>

namespace mitk_nl {

//:-------------------declarations------------------------------------------
typedef enum { mitk_nl_rank_row, mitk_nl_rank_column, mitk_nl_rank_both } mitk_nl_rank_type;
typedef enum { mitk_nl_rank_pivot_one, mitk_nl_rank_pivot_all } mitk_nl_rank_pivot_type;
static int iminarg1,iminarg2;
#define imin(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ?\
        (iminarg1) : (iminarg2))

static double maxarg1,maxarg2;
#define fmax(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
        (maxarg1) : (maxarg2))

static double sqrarg;
#define sqr(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

#define sign(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

#define float_equal(a,b) (a==b)?true:false

#define float_not_equal(a,b) (a!=b)?true:false

//#define min(a,b) (a>b)?b:a

//------------------------use in is_symmetry_regular-----------------------
typedef enum enum_regular_symmetry
{ 
    regular_not_symmetry ,  //=   1,
    regular_symmetry     ,  //=   2,
    not_regular_symmetry ,  //=   0,
    not_square           ,  //=   -1,
    not_regular_not_symmetry //= -2
}regular_symmetry_res;

//-----------------------use in eigenvalue_vector------------------------
typedef enum enum_eigenvalue_vector
{
    eigen_not_square , //=  0,
    eigen_success  ,   //=  1,
    eigen_fail        //=  -1
}eigenvalue_vector_res;

//--------------------use in lu------------------------------------------
typedef enum enum_lu
{
    lu_success ,//= 1,
    lu_fail    //= 0
}lu_res;

//////////////////////////////////////////////////////////////////////////
/// @name MatrixFunctions
/// @{
//////////////////////////////////////////////////////////////////////////

//:-------------------matrix and vector----------------------------------

//--------------------type cast of matrix--------------------------------
//////////////////////////////////////////////////////////////////////////
///  Change all the elements type in a matrix from class T to class U
///  @param[in] M The target matrix
///  @return The changed matrix
///  @par Example:
///  @code
///  //D and A are both class mitk_nl_matrix
///  mitk_nl_matrix<double> D = type_cast<double,int>(A);
///  @endcode
//////////////////////////////////////////////////////////////////////////


template<class U, class T>
mitk_nl_matrix<U> type_cast(mitk_nl_matrix<T> const &M)
{
    if (M.cols() == 0 || M.rows() == 0)
    {
        mitk_nl_matrix<U>res;
        return res;
    }

    unsigned int i,j;
    mitk_nl_matrix<U>res(M.rows(), M.cols());
    for (i = 0; i < M.rows(); i ++)
    {
        for (j = 0; j < M.cols(); j ++)
        {
            U temp_data = static_cast< U > ( M(i, j) );
            res.put(i, j, temp_data);
        }
    }
    return res;
}

//-------------------type cast of vector---------------------------------
//////////////////////////////////////////////////////////////////////////
///  Change all the elements type in a vector from class T to class U
///  @param[in] M The target vector
///  @return The changed vector
///  @par Example:
///  @code
///  //D and A are both class mitk_nl_vector
///  mitk_nl_vector<double> D = type_cast<double,int>(A);
///  @endcode
//////////////////////////////////////////////////////////////////////////

template<class U, class T>
mitk_nl_vector<U> type_cast(mitk_nl_vector<T> const &V)
{
    if (V.size() == 0 )
    {
        mitk_nl_vector<U>res;
        return res;
    }

    int i = 0;
    mitk_nl_vector<U>res(V.size());
    for (i = 0; i < V.size(); i ++)
    {
        U temp_data = static_cast<U> ( V[i] );
        res.put(i, temp_data);
    }
    return res;
}

//--------------------M*V------------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  Multiply a matrix with a vector
///  @param[in] M The target matrix
///  @param[in] V The target vector
///  @return The result vector
///  @note The columns of M and the length of V should be matched
///  @par Example:
///  @code
///    double data[]={1,2,3,4,5,6,7,8,9,10,11,12}
///    mitk_nl_matrix<double>M(3,4,12,data);
///    mitk_nl_vector<double>V(4,data);
///    mitk_nl_vector<double>res;
///    pre_multiply(res,M,V);
///  @endcode
//////////////////////////////////////////////////////////////////////////
 
template<class T>
void pre_multiply(mitk_nl_vector<T>&R, mitk_nl_matrix<T> const& M, 
                                 mitk_nl_vector<T>const& V)
{
    assert(M.cols() == V.size());
    assert(M.cols() > 0);
    assert(M.rows() > 0);

#ifndef _DEBUG
    if (M.cols() != V.size() || M.cols() <= 0 || M.rows() <= 0)
    {
        mitk_nl_vector<T> _res;
        R = _res;
        return ;
    }
#endif

    mitk_nl_vector<T>res(M.rows());
    int i = 0;
    int j = 0;
    //the result of the multiply of one of M's row and V
    T   add_res = 0;

    for (i = 0; i < M.rows(); i ++)
    {
        for (j = 0; j < M.cols(); j ++)
        {
            add_res += M(i,j) * V[j];
        }
        res.put(i, add_res);
        add_res = 0;
    }
    R = res;
}

//-------------------------V*M-----------------------------------------------
//////////////////////////////////////////////////////////////////////////
/// Multiply a vector with a matrix
/// @param[in] V The target vector
/// @param[in] M The target matrix
/// @return The result vector
/// @note The length of V and the rows of M should be matched
/// @par Example:
/// @code
///   double data[]={1,2,3,4,5,6,7,8,9,10,11,12}
///   mitk_nl_matrix<double>M(4,3,12,data);
///   mitk_nl_vector<double>V(4,data);
///   mitk_nl_vector<double>res;
///   pos_multiply(res,V,M);
/// @endcode
//////////////////////////////////////////////////////////////////////////

template<class T>
void pos_multiply(mitk_nl_vector<T>&R, mitk_nl_vector<T>const& V, 
                                 mitk_nl_matrix<T> const& M)
{
    assert(V.size() == M.rows());
    assert(V.size() > 0);
    assert(M.rows() > 0);

#ifndef _DEBUG
    if (V.size() != M.rows() || V.size() <= 0 || M.rows() <= 0)
    {
        mitk_nl_vector<T> _res;
        R = _res;
        return ;
    }
#endif

    mitk_nl_vector<T>res(M.cols());
    int i = 0;
    int j = 0;
    T add_res = 0;

    for (j = 0; j < M.cols(); j ++)
    {
        for (i = 0; i < M.rows(); i ++)
        {
            add_res += V[i] * M(i, j);
        }
        res.put(j, add_res);
        add_res = 0;
    }
    R = res;
}

//-------------------transpose of the matrix------------------------------------------
//////////////////////////////////////////////////////////////////////////
/// Calculate the transpose of a matrix
///  @param[in] M The target matrix
///  @return The changed matrix
///  @par Example:
///  @code
///   double data[]={1,2,3,4,5,6,7,8,9,10,11,12}
///   mitk_nl_matrix<double>M(3,4,12,data);
///   transpose(M, M);
///  @endcode
//////////////////////////////////////////////////////////////////////////

template<class T>
void transpose(mitk_nl_matrix<T>&R, mitk_nl_matrix<T>const &M)
{
    assert(M.rows() > 0);
    assert(M.cols() > 0);

#ifndef _DEBUG
    if (M.rows() <= 0 || M.cols() <= 0)
    {
        mitk_nl_matrix<T> _res;
        R = _res;
        return ;
    }
#endif

    int i = 0;
    mitk_nl_matrix<T>res(M.cols(), M.rows());
    
    for (i = 0; i < res.rows(); i ++)
    {
        res.set_row(i, M.get_column(i));
    }
    R = res;
}


//-------------functions used in the function of the rank of the matrix--------------------------

template <class T>
mitk_nl_matrix<T> nl_rank_row_reduce(mitk_nl_matrix<T> const& mat, mitk_nl_rank_pivot_type t)
{
  mitk_nl_matrix<T> a = mat;
  bool changed = true;
  unsigned int m = a.rows(), n=a.cols();
  while (changed)
  {
    changed = false;
    for (unsigned int r=0; r<m; ++r)
    {
      unsigned int c=0; while (c<n && a[r][c] != 1 && a[r][c] != -1) ++c;
      if (c==n) continue;
      for (unsigned int s=0; s<m; ++s)
      {
        if (s==r || a[s][c] == 0) continue;
        for (unsigned int d=0; d<n; ++d)
          if (d!=c) a[s][d] -= a[r][d] * a[r][c] * a[s][c];
        a[s][c] = T(0);
        changed = true;
      }
    }
  }
  if (t == mitk_nl_rank_pivot_one) return a;
  changed = true;
  while (changed)
  {
    changed = false;
    for (unsigned int r=0; r<m; ++r)
    {
      unsigned int c=0; while (c<n && a[r][c] == 0) ++c;
      if (c==n) continue; // zero row
      for (unsigned int s=0; s<m; ++s)
      {
        if (s==r) continue;
        T scale = a[s][c] / a[r][c];
        // Note that this can possibly be an integer division, so
        // it is *not* guaranteed that a[r][c] * scale == a[s][c] .
        if (scale == 0) continue;
        for (unsigned int d=0; d<n; ++d)
          if (d!=c) a[s][d] -= a[r][d] * scale;
        a[s][c] -= a[r][c] * scale;
        changed = true;
      }
    }
  }
  return a;
}

template <class T>
mitk_nl_matrix<T> nl_rank_column_reduce(mitk_nl_matrix<T> const& mat
                                        , mitk_nl_rank_pivot_type t)
{
  mitk_nl_matrix<T> a = mat;
  bool changed = true;
  unsigned int m = a.rows(), n = a.cols();
  while (changed)
  {
    changed = false;
    for (unsigned int c = 0; c < n; ++ c)
    {
      unsigned int r = 0; 
      while (r < m && a[r][c] != 1 && a[r][c] != -1)
      {
          ++r;
      }
      if (r==m) 
      {
          continue;
      }
      for (unsigned int d = 0; d < n; ++ d)
      {
        if (d == c || a[r][d] == 0)
        {
            continue;
        }
        for (unsigned int s = 0; s < m; ++ s)
        {
            if (s != r)
            {
                a[s][d] -= a[s][c] * a[r][c] * a[r][d];
            }
        }
        a[r][d] = T(0);
        changed = true;
      }
    }
  }
  if (t == mitk_nl_rank_pivot_one) return a;
  changed = true;
  while (changed)
  {
    changed = false;
    for (unsigned int c = 0; c < n; ++ c)
    {
      unsigned int r = 0; 
      while (r < m && a[r][c] == 0) 
      {
          ++ r;
      }
      if (r == m)
      {
          continue;// zero row
      }
      for (unsigned int d = 0; d < n; ++ d)
      {
        if (d==c) 
        {
            continue;
        }
        T scale = a[r][d] / a[r][c];       // Note that this can possibly be an integer division, so
                                           // it is *not* guaranteed that a[r][c] * scale == a[r][d] .
        if (scale == 0) 
        {
            continue;
        }
        for (unsigned int s = 0; s < m; ++ s)
        {
            if (s != r) 
          {
              a[s][d] -= a[s][c] * scale;
          }
        }
        a[r][d] -= a[r][c] * scale;
        changed = true;
      }
    }
  }
  return a;
}

template <class T>
mitk_nl_matrix<T> nl_rank_row_column_reduce(mitk_nl_matrix<T> const& mat
                                            , mitk_nl_rank_pivot_type t)
{
  mitk_nl_matrix<T> a = mat;
  bool changed = true;
  unsigned int m = a.rows(), n = a.cols();
  while (changed)
  {
    changed = false;
    for (unsigned int r = 0; r < m; ++ r)
    {
      unsigned int c = 0;
      while (c < n && a[r][c] != 1 && a[r][c] != -1) 
      {
          ++c;
      }
      if (c==n) 
      {
          continue;
      }
      for (unsigned int s = 0; s < m; ++s)
      {
        if (s==r || a[s][c] == 0) continue;
        for (unsigned int d=0; d<n; ++d)
          if (d!=c) a[s][d] -= a[r][d] * a[r][c] * a[s][c];
        a[s][c] = T(0);
        changed = true;
      }
    }
    for (unsigned int c=0; c<n; ++c)
    {
      unsigned int r=0; 
      while (r < m && a[r][c] != 1 && a[r][c] != -1) 
      {
          ++ r;
      }
      if (r == m) 
      {
          continue;
      }
      for (unsigned int d = 0; d < n; ++ d)
      {
        if (d == c || a[r][d] == 0) 
        {
            continue;
        }
        for (unsigned int s = 0; s < m; ++ s)
        {
            if (s!=r) 
          {
              a[s][d] -= a[s][c] * a[r][c] * a[r][d];
          }
        }
        a[r][d] = T(0);
        changed = true;
      }
    }
  }
  if (t == mitk_nl_rank_pivot_one) return a;
  changed = true;
  while (changed)
  {
    changed = false;
    for (unsigned int r=0; r<m; ++r)
    {
      unsigned int c = 0;
      while (c < n && a[r][c] == 0)
      {
          ++c;
      }
      if (c == n)
      {
          continue; // zero row
      }
      for (unsigned int s = 0; s < m; ++ s)
      {
        if (s == r) 
        {
            continue;
        }
        T scale = a[s][c] / a[r][c];         // Note that this can possibly be an integer division, so
        // it is *not* guaranteed that a[r][c] * scale == a[s][c] .
        if (scale == 0) 
        {
            continue;
        }
        for (unsigned int d = 0; d < n; ++ d)
        {
            if (d != c) 
            {
                a[s][d] -= a[r][d] * scale;
            }
        }
        a[s][c] -= a[r][c] * scale;
        changed = true;
      }
    }
    for (unsigned int c = 0; c < n; ++ c)
    {
      unsigned int r = 0;
      while (r < m && a[r][c] == 0) 
      {
          ++r;
      }
      if (r == m) 
      {
          continue; // zero row
      }
      for (unsigned int d = 0; d < n; ++ d)
      {
        if (d == c) 
        {
            continue;
        }
        T scale = a[r][d] / a[r][c];     // Note that this can possibly be an integer division, so
                                         // it is *not* guaranteed that a[r][c] * scale == a[r][d] .
        if (scale == 0)
        {
            continue;
        }
        for (unsigned int s = 0; s < m; ++ s)
        {
            if (s != r) 
            {
                a[s][d] -= a[s][c] * scale;
            }
        }
        a[r][d] -= a[r][c] * scale;
        changed = true;
      }
    }
  }
  return a;
}
//--------------------the rank of the matrix-----------------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  Calculate the rank of a matrix
///  @param[in] mat The target matrix
///  @return The rank of mat
///  @par Example:
///  @code
///    double data[]={1,2,3,4,5,6,7,8,9,10,11,12}
///    mitk_nl_matrix<double>M(3,4,12,data);
///    int _rank = rank(M);
///  @endcode
//////////////////////////////////////////////////////////////////////////
 
template <class T>
unsigned int rank(mitk_nl_matrix<T> const& mat, mitk_nl_rank_type t = mitk_nl_rank_both)
{
  unsigned int rank = 0;
  if (t == mitk_nl_rank_row)
  {
    mitk_nl_matrix<T> a = nl_rank_row_reduce(mat, mitk_nl_rank_pivot_all);
    for (unsigned int r = 0; r < a.rows(); ++ r)
    {
      unsigned int c=0;
      while (c < a.cols() && a[r][c] == 0)
      {
          ++c;
      }
      if (c != a.cols())
      {
          ++rank; // not all elements in row r are 0
      }
    }
  }
  else
  {
    mitk_nl_matrix<T> a = (t == mitk_nl_rank_column) ? nl_rank_column_reduce(mat,mitk_nl_rank_pivot_all) :
                                               nl_rank_row_column_reduce(mat,mitk_nl_rank_pivot_all);
    for (unsigned int c = 0; c < a.cols(); ++ c)
    {
      unsigned int r = 0;
      while (r < a.rows() && a[r][c] == 0) 
      {
          ++r;
      }
      if (r != a.rows()) 
      {
          ++rank; // not all elements in column c are 0
      }
    }
  }
  return rank;
}


//-----------------------the functions below is used in det------------------------------------
template <class T>
T cofactor(T ** data,int width,int height,int widthPos, int heightPos)
{

    int i;
    T ** newdata = new T * [height-1];
    for(i = 0;i < height-1;i ++)
        newdata[i]=new T [width-1];

    int xindex = 0,yindex = 0;
    for(i = 0;i < height;i ++)      //new matrix value
    {
        yindex = 0;
        if(i != heightPos)
        {
            for(int j = 0;j < width;j++)
            {
                if(j == widthPos)
                {
                    continue;
                }
                newdata[xindex][yindex] = data[i][j];
                yindex ++;
            }
            xindex ++;
        }
    }
    width --;
    height--;
    T sum = 0;
    if(1 == width)
    {
        sum = newdata[0][0];
    }
    else
    {
        int index = 1;
        for(i = 0;i < width; i ++)
        {
            sum += newdata[0][i] * index * cofactor(newdata,width,height,i,0);
            index = -1 * index;
        }
    }
    for(i = 0; i < height; i++)
    {
        delete[] newdata[i];
    }
    delete[] newdata;
    return sum;

}

template <class T>
T _det(T ** data,int width,int height)
{   

    T sum = 0;  
    int index = 1;  

    for(int i = 0; i < width; i ++)
    {   
        sum += data[0][i] * index * cofactor(data,width,height,i,0);
        index = -1*index;

    }

    return sum;
}

//-------------------------the det of the matrix-----------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  Calculate the det of a matrix
///  @param[in] mat The target matrix
///  @return The det of mat
///  @note The result is expressed in the same type of mat
///  @par Example:
///  @code
///    double data[]={1,2,3,4,5,6,7,8,9,10,11,12}
///    mitk_nl_matrix<double>M(3,3,9,data);
///    double _det = det(M);
///  @endcode
//////////////////////////////////////////////////////////////////////////
 
template <class T>
T det(mitk_nl_matrix <T> const &mat)
{
     int width,height;
     
     int i = 0,j = 0;
     
     width = mat.rows();
     height = mat.cols();//cols and rows
     
     assert(width==height && width>1);//square
     
     T ** data = new T* [height];
     for(i = 0;i < height; i++)
     {
         data[i]=new T [width];
     }
     
     for(i = 0;i < width; i++)
     {
         for(j = 0;j < height; j++)
         {
             data[i][j] = mat.get(i,j);
         }
     }
     
     T sum = 0;
     sum = _det(data,width,height);
     for( i = 0; i < height; i ++)
     {
         delete[] data[i];
     }
     delete[] data;
     return sum;
     
}

//-----------------------ths functions below is used in inv -----------------------------------
void sweep(long k1, long k2, mitk_nl_matrix<double> &a)
{
    //double eps = 1.0e-8;
    double eps = 1.0e-8;
    double d;
    long i, j, k, n, it;
    
    assert(a.rows() == a.cols());

#ifndef _DEBUG
    if (a.rows() != a.cols())
    {
        mitk_nl_matrix<double>_res;
        a = _res;
        return ;
    }
#endif
    
    n = a.rows();
    if (k2 < k1) { k = k1; k1 = k2; k2 = k; }
    
    for (k = k1; k < k2; k++)   
    {
        if ( fabs( a(k, k) ) < eps)
            for (it = 0; it < n; it++)
                a(it, k) = a(k, it) = 0.0;
            else 
            {
                d = 1.0 / a(k, k);
                a(k, k) = d;
                for (i = 0; i < n; i++) 
                    if (i != k) 
                    {
                        a(i, k) *= (double) - d;
                    }
                    for (j = 0; j < n; j++) 
                        if (j != k)
                        {
                            a(k, j) *= (double) d; 
                        }
                        for (i = 0; i < n; i++)
                        {
                            if (i != k) 
                            {
                                for (j = 0; j < n; j++)
                                {
                                    if (j != k)
                                    {
                                        a(i, j) += a(i, k) *a(k, j) / d;
                                    }
                                } // end for j
                            } // end for i != k
                        } // end for i
            } // end else
    } // end for k  
}// sweep(long k1, long k2, tmat<T> &a)
//-----------------------the inv of the matrix ------------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  Calculate the inverse matrix of the target matrix
///  @param[in] M The target matrix
///  @return The changed matrix
///  @note 1:M should be a square matrix\n
///        2:The result is expressed in double type
///  @par Example:
///  @code
///    int data[]={1,2,3,4,5,6,7,8,9,10,11,12}
///    mitk_nl_matrix<int>M(3,3,9,data);
///    mitk_nl_matrix<double>N;
///    inv(N,M);
///  @endcode
//////////////////////////////////////////////////////////////////////////

template<class T>
void inv(mitk_nl_matrix<double>& R, mitk_nl_matrix<T>const & M)
{
    assert(M.cols() == M.rows());

#ifndef _DEBUG
    if (M.cols() != M.rows())
    {
        mitk_nl_matrix<T> _res;
        R = _res;
        return ;
    }
#endif

    assert(M.cols() > 0);

#ifndef _DEBUG
    if (M.cols() <= 0)
    {
        mitk_nl_matrix<T> _res;
        R = _res;
        return ;
    }
#endif
    
    mitk_nl_matrix<double> b = type_cast<double, T>(M);
    sweep(0, b.rows(), b);
    R = b;
}

//-----------------------the trace of the matrix-----------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  Calculate the trace of the target matrix
///  @param[in] M The target matrix
///  @return The trace of M
///  @par Example:
///  @code
///    double data[]={1,2,3,4,5,6,7,8,9,10,11,12}
///    mitk_nl_matrix<double>M(3,4,12,data);
///    double _trace = trace(M);
///  @endcode
//////////////////////////////////////////////////////////////////////////
 
template <class T>
T trace(mitk_nl_matrix<T> const& M) {
    T sum(0);
    const unsigned int N = M.rows() < M.cols() ? M.rows() : M.cols();
    for (unsigned int i = 0; i < N; ++ i)
        sum += M(i, i);
    return sum;
}

//---------------------the qr decompose of the matrix-------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  Achieve the QR decompose of the target matrix
///  @param[in] M The target matrix
///  @param[out] rhq This matrix is used to place the Q matrix
///  @param[out] rhs This matrix is used to place the R matrix
///  @return Void
///  @note This function is only used for the matrix which rows are larger than columns
///  @par Example:
///  @code
///   int data[] = {1,2,3,4,5,6,7,8,9,10,11,12};
///   mitk_nl_matrix<int>M(4,3,12,data);
///   mitk_nl_matrix<double>Q;
///   mitk_nl_matrix<double>R;
///   qr(Q,R,M);
///  @endcode
//////////////////////////////////////////////////////////////////////////
 
template <class T>
void qr(mitk_nl_matrix<double>&rhq, mitk_nl_matrix<double>&rhs, 
        mitk_nl_matrix<T>const &M)
{
    rhq.clear();
    rhs.clear();
    
    rhq.set_size(M.rows(), M.rows());
    rhs.set_size(M.rows(), M.cols());

    rhq.zeros();
    rhs.zeros();
    
    
    int stRow = M.rows();
    int stCol = M.cols();
    
    rhs = type_cast< double, T>(M);
    if (stRow < stCol)
    {
        return;
    }
    
    
    int i,j,nn,k,jj;
    double u,alpha,w,t;
    
    for(i = 0; i < stRow; i ++)
        for(j = 0; j < stRow; j ++)
        { 
            rhq(i,j) = 0.0;
            if(i == j) 
                rhq(i,j) = 1.0;
        }
        
        nn = stCol;
        
        if(stRow == stCol) nn=stRow-1;
        
        for(k = 0; k < nn; k ++)
        {
            u = 0.0;
            
            for(i = k; i < stRow; i++)
            { 
                w = fabs(rhs(i,k));
                if(w > u) u = w;
            }
            alpha = 0.0;
            for(i = k; i < stRow; i++)
            {
                t = rhs(i,k)/u;
                alpha = alpha + t * t;
            }
            
            if(rhs(k,k) > 0.0)
            {
                u = -u;
            }
            
            alpha = u * sqrt(alpha);
            
            if(alpha == 0.0) 
            {
                return;
            }
            
            u = sqrt(2.0 * alpha * (alpha - rhs(k,k)));
            
            if(u != 0.0)
            { 
                rhs(k,k) = (rhs(k,k) - alpha) / u;
                
                for(i = k + 1; i < stRow; i ++)
                {
                    rhs(i,k) /= u;
                }
                
                for(j = 0; j < stRow; j ++)
                {
                    t = 0.0;
                    
                    for(jj = k; jj < stRow; jj ++)
                        t = t + rhs(jj,k) * rhq(jj,j);
                    
                    for(i = k; i < stRow; i ++)
                        rhq(i,j) = rhq(i,j) - 2.0 * t * rhs(i,k);
                }
                
                for(j = k + 1; j < stCol; j ++)
                { 
                    t = 0.0;
                    
                    for(jj = k; jj < stRow; jj++)
                        t = t + rhs(jj,k) * rhs(jj,j);
                    
                    for(i = k; i < stRow; i ++)
                        rhs(i,j) = rhs(i,j) - 2.0 * t * rhs(i,k);
                }
                
                rhs(k,k) = alpha;
                
                for(i = k + 1; i < stRow; i ++)
                    rhs(i,k) = 0.0;
            }
        }
        
        for(i = 0; i < stRow - 1; i ++)
        {
            for(j = i + 1; j < stRow; j ++)
            {
                t = rhq(i,j);
                rhq(i,j) = rhq(j,i);
                rhq(j,i) = t;
            }
        }
        return;


}

//--------------------the function below is used in svd-----------------------------------------
double pythag(const double a,const double b)
{
    double absa,absb;

    absa = fabs(a);
    absb = fabs(b);

    if (absa > absb) 
    {
        return absa * sqrt(1.0 + sqr(absb / absa));
    }
    else
        return (absb == 0.0 ? 0.0 : absb * sqrt(1.0 + sqr(absa / absb)));
}

template<class T>
void free_arrey(T *vec)
{
    delete[] vec;
}

template<class T>
void free_darrey(T **mat,int m)
{
    int i = 0;
    for(i = 0;i < m; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
}

template<class T>
T * new_arrey(int m)
{
    T * vec =  new T[m];
    return vec;
}

template<class T>
T ** new_darrey(int m,int n)
{
    int i = 0;
    T ** vec = new T * [m];
    for(i = 0; i < m; i++)
    {
        vec[i]=new T [n];
    }
    return vec;
}

template<class T>
void init_darrey(T ** a,mitk_nl_matrix<T> &mat)
{
    unsigned int i,j;
    for(i = 0;i < mat.rows(); i++)
    {
        for(j = 0;j < mat.cols(); j++)
        {
            a[i][j] = mat.get(i,j);
        }
    }
}

template<class T>
void init_darrey(T ** a,int m,int n)
{
    int i = 0;
    int j = 0;
    for(i = 0;i < m; i++)
    {
        for(j = 0;j < n; j++)
        {
            a[i][j] = 0;
        }
    }

}
//--------------------the svd decompose of the matrix-------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  Achieve the SVD decompose of the target matrix  (Numerical Recipes C Version)
///  @param[in]  M The target matrix
///  @param[out] S This matrix is used to place the S matrix
///  @param[out] V This matrix is used to place the V matrix
///  @param[out] D This matrix is used to place the D matrix
///  @return Void
///  @note The sizes of matrix S,V,D are m*n,n*n and n*n 
///  @par example:
///  @code
///    int data[] = {1, 2, 3,4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16};
///    mitk_nl_matrix<int>M(4,4,16,data);
///    mitk_nl_matrix<double>S;
///    mitk_nl_matrix<double>V;
///    mitk_nl_matrix<double>D;
///    svd(S,V,D,M);
///  @endcode
//////////////////////////////////////////////////////////////////////////

template<class T>
void svd(mitk_nl_matrix<double>&S,mitk_nl_matrix<double>&V,
         mitk_nl_matrix<double>&D,mitk_nl_matrix<T>const&M)
{
    //--first init S,V and D-----------------------
    S.clear();
    V.clear();
    D.clear();

    //--set the rows and the cols of Matrix D , S  and V
    D.set_size(M.cols(), M.cols());
    S.set_size(M.rows(), M.cols());
    V.set_size(M.cols(), M.cols());

    //--init--------------------------------------
    V.zeros();
    D.zeros();
    S.zeros();

    S = type_cast<double, T>(M);       //change the type to double;

    int i,its,flag,j,jj,k,l,nm;
    double anorm,c,f,g,h,s,scale,x,y,z;
    int m = S.rows();
    int n = S.cols();
 
    double * w = new_arrey<double>(n);
    double *rv1 = new_arrey<double>(n);
    
    double ** a = new_darrey<double>(m,n);
    init_darrey(a,S);

    double ** v =  new_darrey<double>(n,n);
    init_darrey(v,n,n);

    g = scale = anorm = 0.0;
    for (i = 0; i < n; i ++) {
        l = i + 2;
        rv1[i] = scale * g;
        g = s = scale = 0.0;
        if (i < m) {
            for (k = i; k < m; k++) 
            {
                scale += fabs(a[k][i]);
            }
            if ( scale != 0.0 )
            {
                for (k = i; k < m; k ++) {
                    a[k][i] /= scale;
                    s += a[k][i] * a[k][i];
                }
                f = a[i][i];
                g = -sign(sqrt(s),f);
                h = f * g -s ;
                a[i][i] = f - g;
                for (j = l - 1; j < n; j ++)
                {
                    for (s = 0.0,k = i; k < m; k ++) 
                    {
                        s += a[k][i]*a[k][j];
                    }
                    f = s / h;
                    for (k = i; k < m; k ++)
                    {
                        a[k][j] += f * a[k][i];
                    }
                }
                for (k = i; k < m; k ++)
                {
                    a[k][i] *= scale;
                }
            }
        }
        w[i] = scale *g;
        g = s = scale = 0.0;
        if (i+1 <= m && i != n) {          
            for (k = l-1; k < n; k ++)
            {
                scale += fabs(a[i][k]);
            }
            if (scale != 0.0) {
                for (k = l - 1; k < n; k ++) {
                    a[i][k] /= scale;
                    s += a[i][k]*a[i][k];
                }
                f = a[i][l-1];
                g = -sign(sqrt(s),f);
                h = f * g - s;
                a[i][l-1] = f - g;
                for (k = l - 1; k < n; k++)
                {
                    rv1[k] = a[i][k] / h;
                }
                for (j = l - 1; j < m; j++) 
                {
                    for (s = 0.0,k = l - 1; k < n; k++)
                    {
                        s += a[j][k] * a[i][k];
                    }
                    for (k = l - 1; k < n; k++)
                    {
                        a[j][k] += s * rv1[k];
                    }
                }
                for (k = l - 1; k < n; k++)
                {
                    a[i][k] *= scale;
                }
            }
        }
        anorm=fmax(anorm,(fabs(w[i]) + fabs(rv1[i])));
    }
    for (i = n - 1; i >= 0; i--) 
    {
        if (i < n-1) {
            if (g != 0.0) {
                for (j = l; j < n; j++)
                    v[j][i]=(a[i][j]/a[i][l])/g;
                for (j = l; j < n; j++)
                {
                    for (s = 0.0,k = l; k < n; k++)
                    {
                        s += a[i][k]*v[k][j];
                    }
                    for (k = l; k < n; k++) 
                    {
                        v[k][j] += s*v[k][i];
                    }
                }
            }
            for (j = l; j < n; j++) 
            {
                v[i][j] = v[j][i] = 0.0;
            }
        }
        v[i][i] = 1.0;
        g = rv1[i];
        l = i;
    }
    for (i = imin(m,n) - 1; i >= 0; i--) {
        l = i + 1;
        g = w[i];
        for (j = l; j < n; j++) 
            a[i][j]=0.0;
        if (g)
        {
            g = 1.0 / g;
            for (j = l; j < n; j++) 
            {
                for (s = 0.0,k = l; k < m; k++)
                    s += a[k][i]*a[k][j];
                f = ( s/a[i][i] ) * g;
                for (k = i; k < m; k++)
                    a[k][j] += f*a[k][i];
            }
            for (j = i; j < m; j ++)
                a[j][i] *= g;
        } else for (j = i; j < m; j++)
            a[j][i] = 0.0;
        ++a[i][i];
    }
    for (k = n - 1; k >= 0; k--) {
        for (its = 0; its < 30; its++) {
            flag = 1;
            for (l = k; l >= 0; l--) {
                nm = l - 1;
                if ((double)(fabs(rv1[l])+anorm) == anorm) 
                {
                    flag = 0;
                    break;
                }
                if ((double)(fabs(w[nm])+anorm) == anorm) 
                {
                    break;
                }
            }
            if (flag)
            {
                c = 0.0;
                s = 1.0;
                for (i = l - 1; i < k + 1; i++) {
                    f = s * rv1[i];
                    rv1[i] = c * rv1[i];
                    if ((double)(fabs(f)+anorm) == anorm) 
                    {
                        break;
                    }
                    g = w[i];
                    h = pythag(f,g);
                    w[i] = h;
                    h = 1.0 / h;
                    c = g * h;
                    s = -f * h;
                    for (j = 0; j < m; j ++)
                    {
                        y = a[j][nm];
                        z = a[j][i];
                        a[j][nm] = y * c + z * s;
                        a[j][i] = z * c - y * s;
                    }
                }
            }
            z =w[k];
            if (l == k) {
                if (z < 0.0) {
                    w[k] = -z;
                    for (j = 0; j < n ; j ++)
                    {
                        v[j][k] = -v[j][k];
                    }
                }
                break;
            }
            x = w[l];
            nm = k - 1;
            y = w[nm];
            g = rv1[nm];
            h = rv1[k];
            f = ((y-z) * (y+z) + (g-h) * (g+h)) / (2.0 * h * y);
            g = pythag(f,1.0);
            f = ((x-z) * (x+z) + h * ((y/(f+sign(g,f))) - h)) / x;
            c = s = 1.0;
            for (j = l; j <= nm; j++) {
                i = j + 1;
                g = rv1[i];
                y = w[i];
                h = s * g;
                g = c * g;
                z = pythag(f,h);
                rv1[j] = z;
                c = f / z;
                s = h / z;
                f = x * c + g * s;
                g = g*c-x*s;
                h = y * s;
                y *= c;
                for (jj = 0; jj < n; jj++) {
                    x = v[jj][j];
                    z = v[jj][i];
                    v[jj][j] = x * c + z * s;
                    v[jj][i] = z * c - x * s;
                }
                z = pythag(f,h);
                w[j] = z;
                if (z) 
                {
                    z = 1.0 / z;
                    c = f * z;
                    s = h * z;
                }
                f = c * g + s * y;
                x = c * y - s * g;
                for (jj = 0; jj < m; jj ++)
                {
                    y = a[jj][j];
                    z = a[jj][i];
                    a[jj][j] = y * c + z * s;
                    a[jj][i] = z * c - y * s;
                }
            }
            rv1[l] = 0.0;
            rv1[k] = f;
            w[k] = x;
        }
    }

    for(i = 0;i < m; i++)
    {
        for(j = 0;j < n; j++)
        {
            S.put(i,j,a[i][j]);
        }
    }

    for(i = 0;i < n; i++)
    {
        for(j = 0;j < n; j++)
        {
            D.put(i,j,v[i][j]);
        }
    }

     for (i = 0; i < n; i ++)
     {
         for (j = 0; j < n; j ++)
         {
             if (i == j)
             {
                 V.put(i, j, w[i]);
             }
             else
             {
                 V.put(i, j, 0);
             }
         }
     }
     
    free_darrey(a,m);
    free_darrey(v,n);
    free_arrey(w);
    free_arrey(rv1);
}

//-----------------------Solve the matrix equation M X = B, returning X-------------------------
////////////////////////////////////////////////////////////////////////////////
///     Solve the matrix equation M X = B, returning X
///     @param[in] M matrix
///     @param[in] B matrix
///     @return X matrix
////////////////////////////////////////////////////////////////////////////////
template<class T>
mitk_nl_matrix<T> svd_solve(mitk_nl_matrix<T> const& M, mitk_nl_matrix<T> const& B)  //const
{
    mitk_nl_matrix<T> U_,W_,V_;
    svd(U_,W_,V_,M);

    mitk_nl_matrix<T> x;                                    // solution matrix
    if (U_.rows() < U_.cols())                              // augment y with extra rows of
    {                       
        mitk_nl_matrix<T> yy(U_.rows(), B.cols(), T(0));    // zeros, so that it matches
        yy.update(B);                                       // cols of u.transpose. ???
        x = U_.transpose() * yy;                            //simplified to calc read number is transpose only
    } 
    else
    {
        x = U_.transpose() * B;
    }

    for (unsigned long i = 0; i < x.rows(); ++i)            // multiply with diagonal 1/W
    {
        T weight = W_(i, i);
        if (weight != T(0))
            weight = T(1) / weight;
        for (unsigned long j = 0; j < x.cols(); ++j)
            x(i, j) *= weight;
    }
    x = V_ * x;                                           // pre-multiply with v.
    return x;
}

//-------------------------LU decompose of the matrix-------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  Achieve the LU decompose of the target matrix
///  @param[in]  M The target matrix
///  @param[out] L This matrix is used to place the L matrix
///  @param[out] U This matrix is used to place the U matrix
///  @return 1:success\n
///          0:fail
///  @par Example:
///  @code
///     int data[] = {3,-3,-2,2,-3,8,4,1,-2,4,6,3,2,1,3,9};
///     mitk_nl_matrix<int>M(4,4,16,data);
///     mitk_nl_matrix<double>L;
///     mitk_nl_matrix<double>U;
///     lu_res i = lu(L, U, M);
///     if(i == lu_success)
///     {
///       ...
///     }
///  @endcode
//////////////////////////////////////////////////////////////////////////
template<class T>
lu_res lu(mitk_nl_matrix<double>&L,mitk_nl_matrix<double> &U, mitk_nl_matrix<T>const &M)
{
    int row = M.rows();
    int col = M.cols();

    assert(row == col); //must be square

#ifndef _DEBUG
    if (row != col)
    {
        L.clear();
        U.clear();
        return lu_fail;
    }
#endif

    //----init L and U--------
    L.clear();
    U.clear();

    L.set_size(row, row);
    U.set_size(row, row);

    L.zeros();
    U.zeros();

    mitk_nl_matrix<double>_temp = type_cast<double, T> (M);

    int i = 0;
    int j = 0;
    int k = 0;
    
    for(k = 0; k< col - 1; k ++)
    {
        if(float_equal(_temp(k,k),0))
        {
            return lu_fail; 
        }
        for(i = k+1; i < col; i++)
        {
            _temp(i,k) /= _temp(k,k);
        }
        for(i = k+1; i < col; i++)
        {
            for(j = k+1; j < col; j++)
            {
                _temp(i,j) = _temp(i,j)-_temp(i,k)*_temp(k,j);
            }
        }
    }
    //-----set L and U ---------
    for(i = 0; i < col; i ++)
    {
        for(j = 0; j < i; j ++)
        {
            L(i,j) = _temp(i,j);
            U(i,j) = 0.0;
        }
        
        L(i,i) = 1.0;
        U(i,i) = _temp(i,i);
        for(j = i+1; j < col; j ++)
        {
            L(i,j) = 0.0;
            U(i,j) = _temp(i,j);
        }
    }
    return lu_success;
}

//-------------------------------cholesky--------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  Achieve the CHOLESKY decompose of the target matrix
///  @param[in] A The target matrix
///  @param[out] R The decomposed matrix
///  @return none
///  @par Example:
///  @code
///   double data[] = {0.9,0.06,-0.39,-0.24,0.06,1.604,0.134,0.464,-0.39,0.134,2.685,0.802, -0.24, 0.464, 0.802, 1.977};
///   mitk_nl_matrix<double>M(4,4,16, data);
///   mitk_nl_matrix<double>C;
///   cholesky(C, M);
///  @endcode
//////////////////////////////////////////////////////////////////////////
 
template<class T>
void cholesky(mitk_nl_matrix<double> &R, mitk_nl_matrix<T>& A)
{

    regular_symmetry_res res = is_symmetry_regular(A, 0);       // make sure the matrix is positive definite
    //the matrix for return if error occur
    mitk_nl_matrix<double>_res;
    
    if (res == regular_not_symmetry)
    {
        int a;
        a = A.rows();
        mitk_nl_vector<double> p(a);
        mitk_nl_matrix<double>mat = type_cast<double,T>(A);

        int i,j,k;
        double sum;
        for (i = 0;i < a;i ++)
        {
            for (j = i;j < a;j ++)
            {
                for (sum = mat[i][j],k = i-1;k >= 0;  k--)
                    sum -= mat[i][k]*mat[j][k];
                if(i == j)
                {
                    if (sum <= 0.0)
                    {//fail to execute the code
                        R = _res;
                        return ;
                    }

                    p[i]=sqrt(sum);
                    mat[i][j]=p[i];
                }
                else mat(j,i) = sum/p[i];
            }
        }
            for (i=0; i<a; i++)
        {
            for (j=(i+1);j<a;j++)
                mat[i][j]=0;
        }
        R = mat; 
        return ;

    }
    else
    {
        R = _res;
        return ;
    }
}

//-------------------------functions to get the eigenvalue and eigenvector----------------------
//////////////////////////////////////////////////////////////////////////
///  Calculate the eigenvalues and eigenvectors of the target matrix
///  @param[in] A The target matrix
///  @param[out] val This vector is used to place all the eigenvalues
///  @param[out] vec This matrix is used to place all the eigenvectors 
///  @return 1:Calculate successed\n
///          0:Calculate failed
///  @par Example:
///  @code
///    int data[] = {10,1,2,3,4,1,9,-1,2,-3,2,-1,7,3,-5,3,2,3,12,-1,4,-3,-5,-1,15};
///    mitk_nl_matrix<int>A(5,5,25,data);
///    mitk_nl_matrix<double>vec;
///    mitk_nl_vector<double>val;
///    eigenvalue_vector_res c= eigenvalue_vector(val,vec,A);
///    if(c == eigen_success)
///    {
///       ...
///    }
///  @endcode
//////////////////////////////////////////////////////////////////////////

 
template <class T>
eigenvalue_vector_res eigenvalue_vector(mitk_nl_vector<double>& val
                     ,mitk_nl_matrix<double>& vec,mitk_nl_matrix<T>& A)
{
    if(is_symmetry(A) != true)  //??
    {
        return eigen_not_square;
    }

    int i,j, p, q, l(1), stRank;
    double fm,cn,sn,omega,x,y,d;
    double eps = 1.0e-8;
    int jt = 200;
    stRank = A.cols();      // 
    
    mitk_nl_matrix<double> a = type_cast<double,T>(A);
    vec = mitk_nl_matrix<double>(stRank,stRank);
    
    for(i = 0; i < stRank; i ++)
    {
        vec(i,i) = 1.0;
        for(j = 0; j < stRank; j ++)
            if(i != j) 
            {
                vec(i,j)=0.0;
            }
    }
    while(1)
    { 
        fm = 0.0;
        for(i = 1; i < stRank; i ++)
        for(j = 0; j < i; j ++)
        {
            d = fabs( a(i,j) );
            if((i != j) &&( d > fm))
            {
                fm = d; 
                p = i;
                q = j;
            }
        }
        if(fm < eps)  
        {
            val = mitk_nl_vector<double>(A.cols());
            for (i = 0; i < val.size(); i ++)
            {
                val(i) = a(i,i);
            }
            return eigen_success;
        }
        if(l>jt)
        {
            return eigen_fail;
        }
        l = l + 1;
        x = -a(p,q);
        y = (a(q,q) - a(p,p)) / 2.0;
        omega = x / sqrt( x * x + y * y);
        if(y < 0.0) 
        {
            omega = -omega;
        }
        sn = 1.0 + sqrt(1.0 - omega * omega);
        sn = omega / sqrt(2.0 * sn);
        cn = sqrt(1.0 - sn * sn);
        fm = a(p , p);
        a(p , p) = fm * cn * cn + a(q,q) * sn * sn + a(p,q) * omega;
        a(q,q) = fm * sn * sn + a(q,q) * cn * cn - a(p,q) * omega;
        a(p,q) = 0.0; 
        a(q,p) = 0.0;
        for(j = 0; j < stRank; j ++)
        if((j != p)&&(j != q))
        {
            fm = a(p,j);
            a(p,j) = fm * cn + a(q,j) * sn;
            a(q,j) = -fm * sn + a(q,j) * cn;
        }
        for(i = 0; i < stRank; i ++)
          if((i != p)&&( i != q))
          { 
              fm = a(i,p);
              a(i,p) = fm * cn + a(i,q) * sn;
              a(i,q) = -fm * sn + a(i,q) * cn;
          }
        for(i = 0; i < stRank; i++)
        {
            fm = vec(i,p);
            vec(i,p) = fm * cn + vec(i,q) * sn;
            vec(i,q) = -fm * sn + vec(i,q) * cn;
        }
    }
}


//-------------------------M*V------------------------------------------------------------------
template<class T>
mitk_nl_vector<T> operator *(mitk_nl_matrix<T>const &M, 
                              mitk_nl_vector<T>const &V)
{
    mitk_nl_vector<T>_res ;
    pre_multiply<T>(_res,M, V);
    return _res;
}

//------------------------V*M--------------------------------------------------------------------
template<class T>
mitk_nl_vector<T> operator *(mitk_nl_vector<T> const &V,
                              mitk_nl_matrix<T> const &M)
{
    mitk_nl_vector<T> _res;
    pos_multiply<T> (_res, V, M);
    return _res;
}

//-----------------------M1/M2 = inv(M2)*M1-------------------------------------------------------
template<class T>
mitk_nl_matrix<double> operator / (mitk_nl_matrix<T> const&M1,
                               mitk_nl_matrix<T> const &M2)
{
    mitk_nl_matrix<double>temp_M = type_cast<double, T> (M1);
    
    assert(det(M2) != 0);

#ifndef _DEBUG
    if (det(M2) == 0)
    {
        mitk_nl_matrix<T> _res;
        return _res;
    }
#endif
    mitk_nl_matrix<double>res;
    inv(res, M2);
    return res * temp_M;
}

/************************************************************************
**  the functions below is used to get the attributes of the matrix
************************************************************************/
//////////////////////////////////////////////////////////////////////////
//------------------whether the matrix is Symmetry-------------------------------------------------
///  Whether the matrix is Symmetry
///  @param[in] rhs The target matrix
///  @return TRUE:The target matrix is a Symmetry Matrix\n
///          FALSE:The target matrix is a Symmetry Matrix
//////////////////////////////////////////////////////////////////////////

template<class T>
bool is_symmetry(mitk_nl_matrix<T> const &rhs)
{
    bool bSy = true;
    size_t stRow = rhs.rows();

    size_t i = 0;
    size_t j = 0;

    if(rhs.cols() == stRow)
    {
        for(i = 1; i < stRow; i ++)
            for(j = 0; j < i; j ++)
                if(float_not_equal((long double)rhs(i, j), 
                    (long double)rhs(j, i)))
                {
                    bSy =  false;
                    goto RET;
                }
    }
    else
        bSy = false;
    RET: return bSy;
}

//----------------whether the matrix is regular----------------------------------------------------
//////////////////////////////////////////////////////////////////////////
/// Whether the matrix is regular
///  @param[in] rhs The target matrix
///  @param[in] sym If sym = 1, whether the matrix is symmetry is needed to be determined
///  @return regular_not_symmetry: The matrix is regular but not symmetry\n
/// regular_symmetry: The matrix is regular and symmetry\n
/// not_regular_symmetry: The matrix is not regular but symmetry\n
/// not_square: The matrix is not square\n
/// not_regular_not_symmetry: The matrix is not symmetry and not regular
//////////////////////////////////////////////////////////////////////////
 
template<class T>
regular_symmetry_res is_symmetry_regular(mitk_nl_matrix<T> const &rhs, int sym)
{
    long double ldDet;
    size_t i, j, k;
    
    size_t sC = rhs.cols(); 
    size_t sR = rhs.rows(); 
    
    size_t stRank = sR; 
    if(stRank != rhs.rows())
    {
        return not_square;  
    }
    
    regular_symmetry_res _res = not_regular_symmetry;

    //not need to judge whether the matrix is symmetry so the function will 
    //say the matrix is not symmetry without any judgment
    if (sym == 0)
    {
        _res = regular_not_symmetry;
        for(k = 0; k < stRank; k ++)
        {
            if(float_equal(rhs(k, k), 0) || rhs(k, k) < 0)
            {
                _res = not_regular_not_symmetry;
            }
        }
        
        for(k = 2; k <= sR; k++)
        {
            mitk_nl_matrix<long double> m(k, k);
            
            for(i=0; i<k; i++)
            {
                for(j=0; j<k; j++)
                {
                    m(i, j) = (long double)rhs(i, j);
                }
            }
                
            ldDet = det(m);                 
            if(float_equal(ldDet,0) || ldDet < 0.0)
            {
                _res = not_regular_not_symmetry;    
            }
        }
    }
    else
    {//need to judge whether the matrix is symmetry
        if (is_symmetry(rhs) == false)
        {
            _res = not_regular_not_symmetry;
        }
        else
        {
            _res = not_regular_symmetry;
        }
        
        if (_res == not_regular_not_symmetry)
        {
            _res = regular_not_symmetry;
            for(k = 0; k < stRank; k ++)
            {
                if(float_equal(rhs(k, k), 0) || rhs(k, k) < 0)
                {
                    _res = not_regular_not_symmetry;
                }
            }
            
            for(k = 2; k <= sR; k++)
            {
                mitk_nl_matrix<long double> m(k, k);
                
                for(i=0; i<k; i++)
                {
                    for(j=0; j<k; j++)
                    {
                        m(i, j) = (long double)rhs(i, j);
                    }
                }
                
                ldDet = det(m);                 
                if(float_equal(ldDet,0) || ldDet < 0.0)
                {
                    _res = not_regular_not_symmetry;    
                }
            }
        }
        else if(_res == not_regular_symmetry)
        {
            _res = regular_symmetry;
            for(k = 0; k < stRank; k ++)
            {
                if(float_equal(rhs(k, k), 0) || rhs(k, k) < 0)
                {
                    _res = regular_not_symmetry;
                }
            }
            
            for(k = 2; k <= sR; k++)
            {
                mitk_nl_matrix<long double> m(k, k);
                
                for(i=0; i<k; i++)
                {
                    for(j=0; j<k; j++)
                    {
                        m(i, j) = (long double)rhs(i, j);
                    }
                }
                
                ldDet = det(m);                 
                if(float_equal(ldDet,0) || ldDet < 0.0)
                {
                    _res = regular_not_symmetry;    
                }
            }
        }
    }
    return _res;
}

} //end namespace mitk_nl

#endif

/// @}
/// @}

