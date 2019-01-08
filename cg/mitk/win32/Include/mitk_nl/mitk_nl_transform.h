/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





//////////////////////////////////////////////////////////////////////////
/// @defgroup TRANSFORM
///  @{
//////////////////////////////////////////////////////////////////////////

#define convolve_success 1
#define convolve_failed  0 

#ifndef _MITK_NL_TRANSFORM_H
#define _MITK_NL_TRANSFORM_H

/************************************************************************
**   functions for fft 
************************************************************************/
#include "mitk_nl_matrix.h"
#include "mitk_nl_vector.h"
#include <math.h>

namespace mitk_nl {

//////////////////////////////////////////////////////////////////////////
/// @name Functions for fast fourier transform and concolove
/// @{
//////////////////////////////////////////////////////////////////////////

//:--------------------------four1---------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
/// In-place 1d fast Fourier transform
/// @param[in] vec the target vector
/// @param[in] isign (1/-1) transform / inverse transform
/// @param[out] vec1
/// @return none
/// @par example:
/// @code
///#include <mitk_nl_transform.h>
///void test_fft_four1()
///{
///    double data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
///    mitk_nl_vector<double>vec(16,data);
///    mitk_nl_vector<double>vec1(16);
///    const int isign = 1;
///    four1(vec1,vec,isign);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
 
template<class T>
void four1(mitk_nl_vector<T>&data,mitk_nl_vector<T>const &data1,const int isign)
{
    data=data1;
    
    int n,mmax,m,j,istep,i;
    double wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;
    
    int nn = data.size()/2;
    n = nn << 1;
    j = 1;
    
    for (i = 1;i < n;i += 2)
    {
        if (j > i)
        {
            swap(data[j-1],data[i-1]);
            swap(data[j],data[i]);
        }
        m = nn;
        while (m >= 2 && j > m)
        {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
    mmax = 2;
    
    while (n > mmax) 
    {
        istep = mmax << 1;
        theta = isign*(6.28318530717959/mmax);
        wtemp = sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        
        for (m = 1;m < mmax;m += 2) 
        {
            for (i = m;i <= n; i += istep) 
            {
                j = i + mmax;
                tempr = wr * data[j-1] - wi * data[j];
                tempi = wr * data[j] + wi * data[j-1];
                data[j-1] = data[i-1] - tempr;
                data[j] = data[i]-tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wr = (wtemp = wr) * wpr - wi * wpi + wr;
            wi = wi * wpr + wtemp * wpi + wi;
        }
        mmax = istep;
    }

    for (i = 1; i < nn/2; i ++)
    {
        swap(data[2*i] , data[2*nn - 2*i]);
        swap(data[2*i+1],data[2*nn-2*i+1]);
    }
    if (isign == -1) {
        for(i=0;i<2*nn;i++){
            data[i]=data[i]/nn;
        }  
    }
}


//-------------------------2D FFT---------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////
/// In-place 2D fast Fourier transform
/// @param[in] vec the target vector
/// @param[in] vec1 the size of target vector
/// @param[in] isign(1/-1) 2D fast Fourier transform /inverse Fourier transform
/// @param[out] res the vector of transformed
/// @return none
/// @par example:
/// @code
///#include<mitk_nl_transform.h>
///void test_transform_four2()
///{
///    int data[]={1,2,3,4,5,6,7,8};
///    mitk_nl_vector<int>vec(8,data);
///    mitk_nl_vector<int>res(8);
///    int data1[] ={2,2};
///    mitk_nl_vector<int>vec1(2,data1);
///    const int isign = 1;
///    four2(res,vec,vec1,isign);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
template<class T>
void four2(mitk_nl_vector<T>&data,
           mitk_nl_vector<T> const &data1,mitk_nl_vector<int>&nn, const int isign)
{   
    data = data1;
    int i,idim,i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
    int ibit,k1,k2,n,nprev,nrem,ntot;
    double tempi,tempr,theta,wi,wpi,wpr,wr,wtemp;
    
    int ndim = nn.size();
    ntot = data.size()/2;
    nprev = 1;                                          //???
    
    for(idim = ndim-1; idim >= 0; idim --)
    {
        n = nn[idim];
        nrem = ntot / (n * nprev);
        ip1 = nprev << 1;
        ip2 = ip1 * n;
        ip3 = ip2 * nrem;
        i2rev = 0;
        
        for(i2 = 0; i2 < ip2; i2 += ip1)
        {
            if (i2 < i2rev) 
            {
                for (i1 = i2; i1 < i2 + ip1 - 1; i1 += 2) 
                {
                    for (i3 = i1; i3 < ip3; i3 += ip2) 
                    {
                        i3rev = i2rev + i3 - i2;
                        swap(data[i3],data[i3rev]);
                        swap(data[i3 + 1],data[i3rev + 1]);
                    }
                }
            }
            ibit = ip2 >> 1;
            
            while (ibit >= ip1 && i2rev + 1 > ibit) 
            {
                i2rev -= ibit;
                ibit >>= 1;
            }
            i2rev += ibit;
        }
        ifp1 = ip1;
        
        while (ifp1 < ip2)
        {
            ifp2 = ifp1 << 1;
            theta = isign * 6.28318530717959 /(ifp2 / ip1);
            wtemp = sin(0.5 * theta);
            wpr = -2.0 * wtemp * wtemp;
            wpi = sin(theta);
            wr = 1.0;
            wi = 0.0;
            
            for (i3 = 0; i3 < ifp1; i3 += ip1) 
            {
                for (i1 = i3; i1 < i3 + ip1-1; i1 += 2) 
                {
                    for (i2 = i1; i2 < ip3; i2 += ifp2)
                    {
                        k1 = i2;
                        k2 = k1 + ifp1;
                        tempr = wr * data[k2] - wi * data[k2+1];
                        tempi = wr * data[k2 + 1] + wi * data[k2];
                        data[k2] = data[k1]-tempr;
                        data[k2 + 1] = data[k1 + 1]-tempi;
                        data[k1] += tempr;
                        data[k1+1] += tempi;
                    }
                }
                wr = (wtemp = wr) * wpr - wi * wpi + wr;
                wi = wi * wpr + wtemp * wpi + wi;
            }
            ifp1 = ifp2;
        }
        nprev *= n;
    }
    for (i = 1; i < ntot; i ++)
    {
        swap(data[2*i] , data[2*i+1]);
    }
}
//----------------two fft----------------------------------------------
//////////////////////////////////////////////////////////////////////////
/// In-place two fast Fourier transform
/// @param[in] vec1 the target vector
/// @param[in] vec2 the target vector
/// @param[out] fft1  transformed vec1
/// @param[out] fft2  transformed vec2
/// @return 1/0  convolve_success / convolve_failed
/// @par example:
/// @code
///#include<mitk_nl_transform.h>
///void test_transform_twofft()
///{
///    int data1[] ={1,2,3,4,5,6,7,8};
///    mitk_nl_vector<int>vec1(8,data1);
///    int data2[] ={9,10,11,12,13,14,15,16};
///    mitk_nl_vector<int>vec2(8,data2);
///    mitk_nl_vector<double>fft1;
///    mitk_nl_vector<double>fft2;
///    twofft(vec1,vec2,fft1,fft2);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
template<class T>
void twofft(mitk_nl_vector<T>&data1, mitk_nl_vector<T>&data2,
            mitk_nl_vector<double>&fft1, mitk_nl_vector<double>&fft2 )
{
    int nn3,nn2,jj,j;
    double rep,rem,aip,aim;
    
    //---init fft1 and fft2
    fft1 = mitk_nl_vector<double>(data1.size() + data2.size());
    fft2 = mitk_nl_vector<double>(data1.size() + data2.size());

    int n = data1.size();
    nn3 = 1 + (nn2 = n + n);
    
    for (j = 0,jj = 0; j < n; j++,jj+=2)
    {
        fft1[jj] = data1[j];
        fft1[jj + 1] = data2[j];
    }
    four1(fft1,fft1,1);
    fft2[0] = fft1[1];
    fft1[1] = fft2[1] = 0.0;
    
    for (j = 2; j < n + 1; j += 2)
    {
        rep = 0.5 * (fft1[j] + fft1[nn2 - j]);
        rem = 0.5 * (fft1[j] - fft1[nn2 - j]);
        aip = 0.5 * (fft1[j + 1] + fft1[nn3 - j]);
        aim = 0.5 * (fft1[j + 1] - fft1[nn3 - j]);
        fft1[j] = rep;
        fft1[j + 1] = aim;
        fft1[nn2 - j] = rep;
        fft1[nn3 - j] = -aim;
        fft2[j] = aip;
        fft2[j + 1] = -rem;
        fft2[nn2 - j] = aip;
        fft2[nn3 - j] = rem;
    }
}

//----------------real fft---------------------------------------------
//////////////////////////////////////////////////////////////////////////
/// In-place real number function fast Fourier transform
/// @param[in] vec the target vector
/// @param[in] isign(1/-1) stants for real fft/inverse real fft
/// @param[out] res  the vector of transformed
/// @return none
/// @par example:
/// @code
///#include<mitk_nl_transform.h>
///void test_FFT_realft()
///{
///    int data[] = {1,2,3,4,5,6,7,8};
///    mitk_nl_vector<int>vec(8,data);
///    mitk_nl_vector<int>res(8);
///    const int isign=1;
///    realft(res,vec,isign);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
template<class T>
void realft(mitk_nl_vector<T>&data,mitk_nl_vector<T> const &data1, const int isign)
{
    data = data1;
    int i,i1,i2,i3,i4;
    double c1 = 0.5,c2,h1r,h1i,h2r,h2i,wr,wi,wpr,wpi,wtemp,theta;
    int n = data.size();
    theta = 3.141592653589793/(double) (n>>1);
    if (isign == 1)
    {
        c2 = -0.5;
        four1(data,data,1);
    }
    else
    {
        c2 = 0.5;
        theta = -theta;
    }
    wtemp=sin(0.5*theta);
    wpr = -2.0*wtemp*wtemp;
    wpi = sin(theta);
    wr = 1.0 + wpr;
    wi = wpi;
    for (i = 1; i < (n >> 2) ; i++)
    {
        i2 = 1 + (i1 = i + i );
        i4 = 1 + (i3 = n - i1);
        h1r = c1 * (data[i1] + data[i3]);
        h1i = c1 * (data[i2] - data[i4]);
        h2r = -c2 * (data[i2] + data[i4]);
        h2i=c2*(data[i1]-data[i3]);
        data[i1] = h1r + wr * h2r - wi * h2i;
        data[i2] = h1i + wr * h2i + wi * h2r;
        data[i3] = h1r - wr * h2r + wi * h2i;
        data[i4] = -h1i + wr * h2i + wi * h2r;
        wr = (wtemp = wr) * wpr - wi * wpi + wr;
        wi = wi * wpr + wtemp * wpi + wi;
    }
    if (isign == 1)
    {
        h1r=data[0];
        data[0] = h1r + data[1];
        data[1] = h1r - data[1];
    } 
    else
    {
        h1r = data[0];
        data[0] = c1 * (h1r + data[1]);
        data[1] = c1 * (h1r - data[1]);
        four1(data,data,-1);
    }  
}
//----------------convolve---------------------------------------------
//////////////////////////////////////////////////////////////////////////
/// get the convolve 
/// @param[in] v1 the target vector
/// @param[in] v2 the time response function
/// @param[in] isign (1/-1) convolve / inverse convolve
/// @param[out] res the convolve
/// @return  1/0  success / failed
/// @note the size of v1 should be N times power of 2
/// @par example:
/// @code
///void test_conv()
///{
///    double data[] = {1,0,2,0,3,0,4,0,5,0,6,0,0,000};
///    mitk_nl_vector<double>v1(16, data);
///    double data1[] = {1,0,2,0,3,0};
///    mitk_nl_vector<double>v2(6, data1);
///    mitk_nl_vector<double>res(16);
///    convlv(v1, v2, isign=1,res);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
template<class T>
int convlv(mitk_nl_vector<T>&data,mitk_nl_vector<T>&respns,const int isign,
            mitk_nl_vector<T>&ans )
{
    int i,no2;
    double mag2,tmp;
    
    int n = data.size();
    int m = respns.size();
    mitk_nl_vector<double> temp(n); 
    for(i = 0; i < m; i ++)
    {
        temp[i] = respns[i];    
    }
    for(i = m; i < n; i++)
    {
        temp[i] = 0;
    }
    for(i = 0; i < n; i++)
    {
        ans[i]=data[i];
    }
    
    realft(ans,ans,1);
    realft(temp,temp,1);

    no2 = n>>1;
    
    if (isign == 1)
    {
        for(i = 2; i < n; i += 2)  
        {
            tmp = ans[i];
            ans[i] = (ans[i] * temp[i] - ans[i+1] * temp[i+1])/no2;
            ans[i + 1] = (ans[i + 1] * temp[i] + tmp * temp[i + 1])/no2;
        }
        ans[0] = ans[0] * temp[0]/no2;
        ans[1] = ans[1] * temp[1]/no2;
        for(i=0;i<n;i++)
        {
            ans[i]=ans[i]*n/2;
        }
    } 
    else if (isign == -1) 
    {
        for(i = 2; i < n; i += 2)
        {
            if ((mag2 = sqr(temp[i]) + sqr(temp[i+1])) == 0.0)
            {   
                 return 0;
            }
            tmp = ans[i];
            ans[i] = (ans[i] * temp[i] + ans[i + 1] * temp[i + 1])/mag2/no2;
            ans[i+1] = (ans[i + 1] * temp[i]-tmp * temp[i + 1])/mag2/no2;
        }
        if (temp[0] == 0.0 || temp[1] == 0.0) 
        {   
            return 0;
        }
        ans[0] = ans[0] / temp[0] / no2;
        ans[1] = ans[1] / temp[1] / no2;
        for(i=0;i<n;i++)
        {
            ans[i]=ans[i]*n/2;
        }
        
    }   
    realft(ans,ans, -1);
return 1;
}
//-------------walshTransform----------------------------
//////////////////////////////////////////////////////////////////////////
/// In-place  walshtransform
/// @param[in] v1 the target vector
/// @param[out] v2  the vector of transformed
/// @return none
/// @par example:
/// @code
///#include<mitk_nl_transform.h>
///void test_walshtransform()
///{
///    double data[] = { 1,2,3,4,5,6,7,8 };
///    mitk_nl_vector<double>v1(8, data);
///    mitk_nl_vector<double>v2(8);
///    walshtransform(v1,v2);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
template <class T>
void walsh_transform(mitk_nl_vector<T>&data, mitk_nl_vector<T>&data1)
{
    int i, k(0);
    int n = data.size();            //§Ö??n>0
    for(i=1; ; i*=2)            //n2k¦Ç
    {
        if(i==n) break;
        k++;
        if(k>64) return;
    }

    int l=n, m(1), it=2, ii=n/2;
    data1[0]=1;
    data1[ii]=2;
    for(i=1; i<k; i++)
    {
        m=m+m;
        l=l/2;
        it=it+it;
        for(int j=0; j<m; j++)  data1[j*l+l/2]=it+1-data1[j*l];
    }
    for(i=0; i<n; i++)
    {
        ii=data1[i]-1;
        data1[i]=data[ii];
    }
    l=1;
    for(i=1; i<=k; i++)
     {
        m=n/(2*l)-1;
        for(int j=0; j<=m; j++)
        {
            it=2*l*j;
            double q;
            for(int is=0; is<l; is++)
            {
                q = data1[it+is]+data1[it+is+l];
                data1[it+is+l]=data1[it+is]-data1[it+is+l];
                data1[it+is] = q;
            }
        }
        l=2*l;
    }
}

}//end namespace mitk_nl

#endif

/// @}
/// @}

