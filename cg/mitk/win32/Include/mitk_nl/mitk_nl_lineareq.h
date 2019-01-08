/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





//////////////////////////////////////////////////////////////////////////
/// @defgroup LINEAREQUATIPON
/// @{
//////////////////////////////////////////////////////////////////////////

#ifndef _MITK_LINEAREQ_H
#define _MITK_LINEAREQ_H

#define LINEAR_EQUATION_NN_FAIL 0
#define LINEAR_EQUATION_TRIDIAGONAL_WRONG_INPUT -1
#define LINEAR_EQUATION_TRIDIAGONAL_FAIL -2
#define LINEAR_EQUATION_TRIDIAGONAL_SUCCESSFUL 1
#define LINEAR_EQUATION_NN_SUCCESSFUL 2

#include "mitk_nl_matrix_algo.h"

namespace mitk_nl {

//////////////////////////////////////////////////////////////////////////
/// @name Functions to solve the linear equations
/// @{
/// @brief These functions are used in Real Number Area
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// get roots of n*n Coefficient Matrix with Gauss Method
/// @param[in] A the Coefficient Matrix which size is (n*n),
/// @param[in] B the Constant Matrix which is (n*1)
/// @param[out] b the result
/// @note we use vector to express B in this function
/// @return an integer telling whether the calculation is successful
/// @par example:
/// @code
///    int data[]={1,3,2,13,7,2,1,-2,9,15,3,-2,-2,-2,11,5};
///    double data1[]={9,6,11,-2};
///    mitk_nl_matrix<int> A(4,4,16,data);
///    mitk_nl_vector<double> B(4,data1);
///    mitk_nl_vector<double> X(4);
///    get_root_nn_matrix_1(X,A,B);
/// @endcode
//////////////////////////////////////////////////////////////////////////

template <class T,class U>
int get_root_nn_matrix_1(mitk_nl_vector<double> &b, mitk_nl_matrix<T>& A
                                           , mitk_nl_vector<U>& B )  
{ 
    
    mitk_nl_matrix<double> a = type_cast<double,T>(A);
    b = type_cast<double,U>(B);
    
    long double MaxValue, tmp;      
    int l, i, j, is;
    
    int n = a.cols();           
    
    mitk_nl_vector<int> js(n);          
    
    for(int k = 0; k < n - 1; k++)  
    {   
        MaxValue = 0.0;             
                
        for(i = k; i < n; i++)
            for(j = k; j < n; j++)
            {       
                tmp = abs(a(i, j)); //the fabs of m(i,j)
                if(tmp > MaxValue)  
                { 
                    MaxValue = tmp; 
                    js[k] = j;      
                    is = i;         
                }
            }
            
        if(MaxValue == 0) 
        {
            l = 0;              
            return LINEAR_EQUATION_NN_FAIL;             // calculate failed
        }
        else
        {
            if(js[k] != k)          //change the columns
                for(i = 0; i < n; i++) swap(a(i, k), a(i, js[k]));
                                
            if(is != k)             //change the rows
            { 
                for (j = k; j < n; j++) swap(a(k, j), a(is, j));

                swap(b[k], b[is]);  //exchange the k element and the is element 
                                    //in the right of linear equations
            }
        }
        
        
        MaxValue =  abs(a(k, k));

        for(j = k + 1; j < n; j++)  a(k, j) /= a(k, k); //MaxValue;
        
        b[k] /= a(k, k); //MaxValue;
        for(i = k + 1; i < n; i++)
        {
            for(j = k + 1; j < n; j++)
            {
                a(i, j) = a(i, j) - a(i, k) * a(k, j);
            }
            
            b[i] = b[i] - a(i, k) * b[k];
        }
    }
    
    MaxValue = abs(a((n - 1), (n - 1)));    

    if(MaxValue == 0)                           
    {
       return LINEAR_EQUATION_NN_FAIL;              //calculate failed
    }

    b[n - 1] /= a((n - 1), (n - 1));

    for(i = n - 2; i >= 0; i--)     
    {
        double t = 0.0;
        
        for(j = i + 1; j < n; j++)  t = t + a(i, j) * b[j];
        
        b[i] = b[i] - t;
    }
    
    js[n - 1] = n - 1;              
    for(k = n - 2; k >= 0; k --)    
        if(js[k] != k)              //change the positions of X elements
            swap(b[k], b[js[k]]);
        
        
    return LINEAR_EQUATION_NN_SUCCESSFUL;                       //calculate success
}

//////////////////////////////////////////////////////////////////////////
/// get roots of n*n Coefficient Matrix with Gauss-Jordan Method
/// @param[in] A the Coefficient Matrix which size is (n*n),
/// @param[in] B the Constant Matrix which is (n*m)
/// @param[out] b the result
/// @note this function is used to solve the n rank linear equations with m constant vectors
/// @return an integer telling whether the calculation is successful
/// @par Example:
/// @code
///    int data[]={1,2,3,4,5,6,7,8,9};
///    int data1[]={9,0,6,4,11,7,-2,1};
///    mitk_nl_matrix<int> A(3,3,9,data);
///    mitk_nl_matrix<int> B(3,2,6,data1);
///    mitk_nl_matrix<double> X(3,2);
///    get_root_nn_matrix_m(X,A,B);
/// @endcode
//////////////////////////////////////////////////////////////////////////

template <class T,class U>
int get_root_nn_matrix_m(mitk_nl_matrix<double> &b, mitk_nl_matrix<T> & A
                                          , mitk_nl_matrix<U> & B)
{ 
    mitk_nl_matrix<double>a = type_cast<double,T> (A);
    b = type_cast<double,U> (B);
    
    long double MaxValue, tmp;  
    int l, k, i, j, is;
    
    int n = a.cols();       //the rank of linear equations
    int m = b.cols();       //number of vectors in right of linear equations

    mitk_nl_vector<int> js(n);  
    for(k = 0; k < n; k++)
    {
        MaxValue = long double(0.0);
        
        for(i = k; i < n; i++)
            for(j = k; j < n; j++)
            {
                tmp = abs( a(i, j) );
                if(tmp > MaxValue)
                { 
                    MaxValue = tmp;
                    js[k] = j;
                    is = i;
                }
            }
        
        if(MaxValue == 0)
        {
            l = 0;
            return LINEAR_EQUATION_NN_FAIL;
        }
        else
        {
            if(js[k] != k)
                for(i = 0; i < n; i++)
                    swap(a(i, k), a(i, js[k]));
                
            if(is != k)
            {
                for(j = k; j < n; j++)
                    swap(a(k, j), a(is, j));
                
                for(j = 0; j < m; j++)
                    swap(b(k, j), b(is, j));

            }
        }

        
        for(j = k + 1; j < n; j++)
            a(k, j) /= a(k, k);

        for(j = 0; j < m; j++)
            b(k, j) /= a(k, k);             

        for(j = k + 1; j < n; j++)
            for(i = 0; i < n; i++)
                if(i != k)
                    a(i, j) -= a(i, k) * a(k, j);

        for(j = 0; j < m; j++)
            for(i = 0; i< n; i++)
                if(i != k)
                    b(i, j) -= a(i, k) * b(k, j);                   
    }

    for(k = n - 1; k >= 0; k --)
    {
        if(js[k] != k)
            for(j = 0 ; j < m;  j++)
                swap(b(k, j), b(js[k], j));

    }               //success
    return LINEAR_EQUATION_NN_SUCCESSFUL;
}

//------------------------tri-diagonal matrix-----------------------------
//////////////////////////////////////////////////////////////////////////
/// get roots of n*n Coefficient tri-diagonal Matrix
/// @param[out] d the result
/// @param[in] A This vector is used to place the tri-diagonal matrix elements in row sequence
/// @param[in] B The Constant vector which length is n
/// @return an integer telling whether the calculation is successful
/// @par Example:
/// @code
///    int data[]={13,12,11,10,9,8,7,6,5,4,3,2,1};
///    int data1[]={3,0,-2,6,8};
///    mitk_nl_vector<int> A(13,data);
///    mitk_nl_vector<int> B(5,data1);
///    mitk_nl_vector<double> X(5);
///    get_root_nn_matrix_tridiagonal(X,A,B);
/// @endcode
//////////////////////////////////////////////////////////////////////////

template <class T>
int get_root_nn_matrix_tridiagonal(mitk_nl_vector<double> &d, mitk_nl_vector<T>& A
                                                     , mitk_nl_vector<T>& B)
{
    int j, k;
    double s;
    bool yn;

    mitk_nl_vector<double> b = type_cast<double,T>(A);
    d = type_cast<double,T>(B);

    int n = d.size();   //the rank of linear equations

    int m = b.size();   
    //m is the total number of elements on the tri-diagonal which belongs to n rank matrix
    //m is also the length of vector b
    //it should be m=3n-2,so it will be checked in this function

    if(m != (3 * n - 2))    //check whether m is 3*n-2
    {
        return LINEAR_EQUATION_TRIDIAGONAL_WRONG_INPUT;
    }
    
    for(k = 0; k < n - 1; k++)
    {
        j = 3 * k;
        s = b[j];

        yn = float_equal(s, 0.0);
        if(yn)                      
        {
            return LINEAR_EQUATION_TRIDIAGONAL_FAIL;
        }

        b[j + 1] = b[j + 1] / s;
        d[k] = d[k] / s;
        b[j + 3] = b[j + 3] - b[j + 2] * b[j + 1];
        d[k + 1] = d[k + 1] - b[j + 2] * d[k];
    }
    
    s = b[3 * n - 3];
    
    yn = float_equal(s, 0.0);
    if(yn)                      
    {
        return LINEAR_EQUATION_TRIDIAGONAL_FAIL;
    }
    
    d[n - 1] = d[n - 1] / s;
    
    for(k = n - 2; k >= 0; k--)
        d[k] = d[k] - b[3 * k + 1] * d[k + 1];
    
    return LINEAR_EQUATION_TRIDIAGONAL_SUCCESSFUL;  //success
}


//-------------------------use in m*n linearequations-------------------
//////////////////////////////////////////////////////////////////////////
/// get roots of m*n Coefficient Matrix
/// @param[in] A The Coefficient Matrix which size is (n*n)
/// @param[in] B The Constant vector which length is n
/// @return The root vector X which type is double
/// @par Example:
/// @code
///    int data[]={1,1,-1,2,1,0,1,-1,0,-1,2,1};
///    double data1[]={2,-3,1,4};
///    mitk_nl_matrix<int>a(4,3,12,data);
///    mitk_nl_vector<double>b(4,data1);
///    mitk_nl_vector<double>x(3);
///    x = get_root_mn_matrix(a,b);
/// @endcode
//////////////////////////////////////////////////////////////////////////
template <class T,class U>
mitk_nl_vector<double> get_root_mn_matrix(mitk_nl_matrix<T>& A
                                         , mitk_nl_vector<U>& B)
{
    int n = A.cols();       //the columns of Coefficient Matrix A,m>=n
    int m = A.rows();       //the rows of Coefficient Matrix An<=m
    assert(n <= m);
    
    int i = 0,j = 0;
    double d;
    
    mitk_nl_matrix<double>tem = type_cast<double,T>(A);
    mitk_nl_vector<double>b = type_cast<double,U>(B);
    mitk_nl_matrix<double>q,a;
    
    mitk_nl_vector<double> c(n);

    qr(q, a ,tem);          //QR decompose function


    for(i = 0; i < n; i++)
    {
        d = 0.0;

        for(j = 0; j < m; j ++)
                d = d + q(j ,i) * b[j];
        
        c[i] = d;
    }
    
    b[n - 1] = c[n - 1] / a((n - 1), (n - 1));
    
    for(i = n - 2; i >= 0; i--)
    {
        d = 0.0;

        for(j = i + 1; j < n; j++)
                d = d + a(i,j) * b[j];
        
        b[i] = (c[i] - d) / a(i, i);
    }
    for (i = 0; i < n; i ++)
    {
        c(i) = b[i];
    }
    return c;   //success
}

} //end namespace mitk_nl

#endif
/// @}
/// @}

