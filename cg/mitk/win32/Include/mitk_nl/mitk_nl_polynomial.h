/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





//////////////////////////////////////////////////////////////////////////
/// @defgroup POLYNOMIAL
///  @{
//////////////////////////////////////////////////////////////////////////

#define polyroot_success 1
#define polyroot_failed  0
#define polydiv_success  3
#define polydiv_failed   2
#ifndef _MITK_NL_PLOYNOMIAL_H
#define _MITK_NL_PLOYNOMIAL_H

//////////////////////////////////////////////////////////////////////////
/// @name Functions for the calculation of polynomial
/// @{
//////////////////////////////////////////////////////////////////////////

#include "mitk_nl_matrix.h"
#include "mitk_nl_vector.h"
#include "mitk_nl_matrix_algo.h"
#include <assert.h>

namespace mitk_nl {

//--------------------get the value of the poly--------------------------
//////////////////////////////////////////////////////////////////////////
/// calculate the value of the poly
/// @param[in] v1 the target vector
/// @param[in] a  the value of x  
/// @return polyvalue
/// @par example:
/// @code
///void test_polynomial_value()
///{
///    int data[] = {6,4,10};
///    int a = 1.11;
///    mitk_nl_vector<int>v1(3, data);
///    double res = polyvalue<double> (v1, a);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////

template<class U, class T>
U polyvalue(mitk_nl_vector<T>const &coff, U x)
{
    //get the degree of the poly
    int no = coff.size();

    mitk_nl_vector<U>_temp_coff = type_cast< U > (coff);
    U dvalue = _temp_coff[no - 1];
    
    int i = 0;
    for (i = no - 2; i > -1; i --)
    {
        dvalue = dvalue * x + _temp_coff[i];
    }
    return dvalue;
}

//-------------------get the value of poly A * poly B-------------------
//////////////////////////////////////////////////////////////////////////
/// calculate the value of poly A * poly B
/// @param[in] v1 The target vector
/// @param[in] v2 The target vector
/// @param[out] v3  The value of poly A * B
/// @return none
/// @par example:
/// @code
///void test_polynomial_multiplication()
///{
///    int data[] = {6,4,10};
///    mitk_nl_vector<int>v1(3, data);
///    int data1[] = {5,2};
///    mitk_nl_vector<int>v2(2, data1);
///    mitk_nl_vector<int>v3(4);
///    polymul(v3,v1, v2);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
template<class T>
void polymul(mitk_nl_vector<T>&C,mitk_nl_vector<T>const&A, mitk_nl_vector<T>const&B)
{
    //get the degree of ploy A and B
    int _da = A.size() - 1;
    int _db = B.size() - 1;

    int _dc = _da + _db;

    //set all the value to C

    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i <= _db; i ++)
    {
        for (j = 0 ; j <= _da; j ++) 
        {
            C[i + j] += B[i] * A[j];
        }
    }
}

//-----------------get the value of ploy A / ploy B------------------------
//-----------------coffs get the quotient  and coffr get the residue-------
//////////////////////////////////////////////////////////////////////////
///  calculate the value of poly A / poly B
/// @param[in] v1 The target vector
/// @param[in] v2 The target vector
/// @param[out] vq  The quotient of poly A / poly B
/// @param[out] vr  The residue of poly A / poly B
/// @return 3/2   ( polydiv_success / polydiv_failed )
/// @par example:
/// @code
///int test_polynomial_division()
///{
///    double data[] = {8.0,-5.0,-3.0,6.0,3.0};
///    double data1[] = {1.0,-1.0,2.0};
///    mitk_nl_vector<double>v1(5,data);
///    mitk_nl_vector<double>v2(3,data1);
///    mitk_nl_vector<double>vr;
///    mitk_nl_vector<double>vq;
///    polydiv(v1, v2, vq,vr);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
template<class T>
int polydiv(mitk_nl_vector<T>const &coffp, mitk_nl_vector<T>const &coffq,
             mitk_nl_vector<T> &coffs, mitk_nl_vector<T> & coffr)
{
    size_t stNoP = coffp.size();
    size_t stNoQ = coffq.size();
    
    //init coffs and coffr
    coffs = mitk_nl_vector<T>(stNoP - stNoQ + 1);
    coffr = mitk_nl_vector<T>(stNoQ - 1);

    mitk_nl_vector<T>_tempV(coffp);

    size_t stNoS = coffs.size();
    size_t stNoR = coffr.size();

    for(size_t st = 0; st < stNoS; st++) 
    {
        coffs[st] = 0;
    }

    if(float_equal(abs(coffq[stNoQ-1]),0)) return (2);
    
    size_t stk = stNoP - 1;
    
    for(st = stNoS; st > 0; st--)
    {
        coffs[st-1] = _tempV[stk] / coffq[stNoQ-1];
        size_t stm = stk;
        for(size_t sr = 1; sr < stNoQ; sr++)
        {
            _tempV[stm-1] = _tempV[stm-1] - coffs[st-1] * coffq[stNoQ-sr-1];
            stm = stm-1;
        }
        stk = stk - 1;
    }

    for(st = 0; st < stNoR; st++) 
    {
        coffr[st] = _tempV[st];
    }
    
    return (3);

}

//---------------------get the addition of two polys------------------------------------------
//////////////////////////////////////////////////////////////////////////
/// @{
/// calculate the addition of two polys
/// @param[in] data The addend
/// @param[in] data1 The augend
/// @param[out] data0 The result of data + data1
/// @return none
/// @par example:
/// @code
///void test_polynomial_summation()
///{
///    double data2[] = {2,3,4,5,6};
///    double data3[] = {1,2,3};
///    double data1[];
///    polyadd(data1,data2, data3);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
template<class T>
void polyadd(mitk_nl_vector<T>&polyc,mitk_nl_vector<T>const &polya, mitk_nl_vector<T>const&polyb)
{
    //get the size of the result
    size_t res_size = (polya.size() > polyb.size())?polya.size():polyb.size();

    size_t res_size_small = (polya.size() < polyb.size())?polya.size():polyb.size();

    mitk_nl_vector<T> res = mitk_nl_vector<T>(res_size);
    int i = 0;
    
    for (i = 0; i < res_size_small; i ++)
    {
        res[i] = polya[i] + polyb[i];
    }

    if (polya.size() > polyb.size())
    {
        for (i = res_size_small; i < res_size; i ++)
        {
            res[i] = polya[i];
        }
    }
    else
    {
        for (i = res_size_small; i < res_size; i ++)
        {
            res[i] = polyb[i];
        }
    }

    polyc=res;
}



//---------------------the functions is needed in the function poly---------------------------

void g60(double*t, double *x, double *y, double*x1, double *y1, double*dx,
         double*dy, double*p, double*q, int*k, int *it)
{
    *it = 1;
    while (*it == 1)
    {
        *t = *t/1.67;
        *it = 0;
        *x1 = *x - (*t)*(*dx);
        *y1 = *y - (*t)*(*dy);
        if (*k >= 50)
        {
            *p = sqrt((*x1)*(*x1) + (*y1)*(*y1));
            *q = exp(85.0/(*k));

            if (*p >= *q)
            {
                *it = 1;
            }
        }
    }
}

void g90(double xr[], double xi[], double dblCoef[], double* x, double *y, 
         double *p, double *q, double *w, int * k)
{
    int i = 0;

    if (fabs(*y) <= 1.0e-06)
    {
        *p = -(*x);
        *y = 0.0;
        *q = 0.0;
    }
    else
    {
        if (*k <= 0)
        {
            return;
        }
        *p = -2.0*(*x);
        *q = (*x) * (*x) + (*y) * (*y);
        xr[*k - 1] = (*x) * (*w);
        xi[*k - 1] = -(*y)*(*w);
        *k = *k - 1;
    }

    if (*k < 1)
    {
        return;
    }
    for (i = 1; i <= *k; i ++)
    {
        dblCoef[i] = dblCoef[i] - dblCoef[i - 1]*(*p);
        dblCoef[i + 1] = dblCoef[i + 1] - dblCoef[i - 1]*(*q);
    }

    xr[*k - 1] = (*x) * (*w);
    xi[*k - 1] = (*y) * (*w);

    *k = *k - 1;
    if (*k == 1)
    {
        xr[0] = -dblCoef[1]*(*w)/dblCoef[0];
        xi[0] = 0.0;
    }
}

void g65(double *x, double *y, double *x1, double *y1, double *dx, 
         double *dy, double *dd, double *dc, double *c, int *k, 
         int *is, int *it)
{
    if (*it == 0)
    {
        *is = 1;
        *dd = sqrt((*dx)*(*dx) + (*dy)*(*dy));

        if (*dd > 1.0)
        {
            *dd = 1.0;
        }
        *dc = 6.28/(4.5 * (*k));
        *c = 0;
    }
    while (true)
    {
        *c = *c + (*dc);
        *dx = (*dd)*cos(*c);
        *dy = (*dd) * sin(*c);
        *x1 = *x + *dx;
        *y1 = *y + *dy;

        if (*c <= 6.29)
        {
            *it = 0;
            return;
        }

        *dd = *dd / 1.67;
        if (*dd <= 1.0e-07)
        {
            *it = 1;
            return;
        }
        *c = 0.0;
    }
}


//---------------------xr get the real part of the root and xi get the image of the root------
int getroot(int n, double dblCoef[], double xr[], double xi[])
{
    //get the degree of the vector

    int m,i,jt,k,is,it;
    double t,x,y,x1,y1,dx,dy,p,q,w,dd,dc,c;
    double g,u,v,pq,g1,u1,v1;
    //times of loop
    int nums = 0;

    m = n;
    while ((m > 0) && (fabs(dblCoef[m]) + 1.0 == 1.0))
    {
        m = m -1;
    }
    
    if (m <= 0)
    {
        return 0;
    }
    for (i = 0; i <= m; i ++)
    {
        dblCoef[i] = dblCoef[i]/dblCoef[m];
    }

    for (i = 0; i <= m/2; i ++)
    {
        w = dblCoef[i];
        dblCoef[i] = dblCoef[m - i];
        dblCoef[m - i] = w;
    }

    k = m;
    is = 0;
    w = 1.0;
    jt = 1;
    while (jt == 1)
    {
        pq = fabs(dblCoef[k]);
        while (pq < 1.0e-12)
        {
            xr[k - 1] = 0.0;
            xi[k - 1] = 0.0;
            k = k - 1;
            
            if (k == 1) 
            {
                xr[0] = -dblCoef[1] * w/dblCoef[0];
                xi[0] = 0.0;

                return 1;
            }
            pq = fabs(dblCoef[k]);
        }
        q = log(pq);
        q = q / (1.0*k);
        q = exp(q);

        p = q;
        w = w * p;
        for (i = 1; i <= k; i ++)
        {
            dblCoef[i] = dblCoef[i] / q;
            q = q * p;
        }

        x = 0.0001;
        x1 = x;
        y = 0.2;
        y1 = y;
        dx = 1.0;
        g = 1.0e+37;
    loop:
        if(nums > 600)
        {
            break;
        }
        nums ++;
        u = dblCoef[0];
        v = 0.0;
        for (i = 1; i <= k; i ++)
        {
            p = u * x1;
            q = v * y1;
            pq = (u + v)*(x1 + y1);
            u = p -q + dblCoef[i];
            v = pq - p -q;
        }

        g1 = u * u + v * v;
        if (g1 >= g)
        {
            if (is != 0)
            {
                it = 1;
                g65(&x, &y, &x1, &y1, &dx, &dy, &dd, &dc, &c, &k, &is, &it);
                if (it == 0)
                {
                    goto loop;
                }
            }
            else
            {
                g60(&t, &x, &y, &x1, &y1, &dx, &dy, &p, &q, &k, &it);
                if (t >= 1.0e-03)
                {
                    goto loop;
                }

                if (t > 1.0e-18)
                {
                    it = 0;
                    g65(&x, &y, &x1, &y1, &dx, &dy, &dd, &dc, &c, &k, &is, &it);
                    if (it == 0)
                    {
                        goto loop;
                    }
                }

            }
            g90(xr, xi, dblCoef, &x, &y, &p, &q, &w, &k);

        }
        else
        {
            g = g1;
            x = x1;
            y = y1;
            is = 0;
            if (g <= 1.0e-22)
            {
                g90(xr, xi, dblCoef, &x, &y, &p, &q, &w, &k);
            }
            else
            {
                u1 = k * dblCoef[0];
                v1 = 0.0;
                for (i = 2; i <= k; i ++)
                {
                    p = u1 * x;
                    q = v1 * y;
                    pq = (u1 + v1) * (x + y);
                    u1 = p -q + (k -i + 1) * dblCoef[i - 1];
                    v1 = pq - p - q;
                }

                p = u1 * u1 + v1 * v1;

                if (p <= 1.0e-20)
                {
                    it = 0;
                    g65(&x, &y, &x1, &y1, &dx, &dy, &dd, &dc, &c, &k, &is, &it);
                    if (it == 0)
                    {
                        goto loop;
                    }

                    g90(xr, xi, dblCoef, &x, &y, &p, &q, &w, &k);
                }
                else
                {
                    dx = (u * u1 + v * v1)/p;
                    dy = (u1 * v- v1 * u)/p;
                    t = 1.0 + 4.0/k;
                    g60(&t, &x, &y, &x1,&y1, &dx, &dy, &p, &q, &k, &it);
                    if (t >= 1.0e-03)
                    {
                        goto loop;
                    }

                    if (g >= 1.0e-18)
                    {
                        it = 0;
                        g65(&x, &y, &x1, &y1, &dx, &dy, &dd, &dc, &c, &k, &is, &it);
                        if (it == 0)
                        {
                            goto loop;
                        }
                    }
                    g90(xr, xi, dblCoef, &x, &y, &p, &q, &w, &k);
                }
            }
        }
        if (k == 1)
        {
            jt = 0;
        }
        else 
        {
            jt = 1;
        }
    }
    return 1;
}
//---------------------get all the root of the ploy-------------------------------------------
//////////////////////////////////////////////////////////////////////////
///  calculate all the roots of the poly
/// @param[in] v1 The coefficient of poly
/// @param[out] vr The real part of all roots
/// @param[out] vq The imaginary part of all roots
/// @return 1/0 (polyroot_success/polyroot_failed)
/// @par example:
/// @code
///void test_polynomial_roots()
///{
///    double data[] = {8.0,-5.0,-3.0,6.0,3.0};
///    mitk_nl_vector<double>v1(5,data);
///    mitk_nl_vector<double>vr;
///    mitk_nl_vector<double>vq;
///    polyroot(v1,vr,vq);
///}
 /// @endcode
//////////////////////////////////////////////////////////////////////////

int polyroot(mitk_nl_vector<double>const& coff, 
             mitk_nl_vector<double>&realp, 
             mitk_nl_vector<double>&imagp)
{
    int _size = coff.size() - 1;

    //--init realp and imagp----
    realp = mitk_nl_vector<double>(_size);
    imagp = mitk_nl_vector<double>(_size);
    
    double *xr = new double[_size];
    double *xi = new double[_size];
    double *dblCoef = new double[_size + 1];

    int i = 0;

    for (i = _size; i >= 0; i --)
    {
        dblCoef[i] = coff[_size - i];
    }
    int res = 0;

    res = getroot(_size, dblCoef, xr, xi);
    for (i = 0; i < _size; i ++)
    {
        realp[i] = xr[i];
        imagp[i] = xi[i];
    }

    if (xi)
    {
        delete[] xi;
        xi = NULL;
    }
    if (xr)
    {
        delete[] xr;
        xr = NULL;
    }
    if (dblCoef)
    {
        delete[] dblCoef;
        dblCoef = NULL;
    }

    return res;
}

} //end namespace mitk_nl

#endif

/// @}
/// @}














