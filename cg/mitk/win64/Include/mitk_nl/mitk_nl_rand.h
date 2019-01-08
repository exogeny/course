/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/





//////////////////////////////////////////////////////////////////////////
/// @defgroup RANDOM
///  @{
//////////////////////////////////////////////////////////////////////////

#ifndef _RANDOM_H
#define _RANDOM_H

#if defined(MITK_CC_MSVC)
    #pragma warning ( disable : 4146 )
#endif

#define RandCoef2053 2053   
#define RandCoef13849 13849
#define MODUL65536 65536

#include <time.h>

//////////////////////////////////////////////////////////////////////////
/// @name Functions for the generation of random number
/// @{
//////////////////////////////////////////////////////////////////////////

//?[0,1]???¦Á
//////////////////////////////////////////////////////////////////////////
///  Generates a random number in [0,1]  
/// @param[in]  seed target number
/// @param[out]  rand the random number
/// @return  none 
/// @par example:
/// @code
///void test_rand_01_one()
///{
///    double seed = 0.05;
///    rand_01_one(rand, seed);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////

namespace mitk_nl {

void rand_01_one(double rand, double& seed)
{       //seed?
    seed = ((unsigned long)seed) % MODUL65536;      //65536???
    seed = RandCoef2053 * (seed) + RandCoef13849;   //??
    seed = ((unsigned long)seed) % MODUL65536;      //65536???
    rand = (seed) / (double)MODUL65536;     //?[0,1]                                //?
}

//[0,1]???¦Á
//////////////////////////////////////////////////////////////////////////
///  Generates many random numbers in [0,1]  
/// @param[in]  seed target number
/// @param[in] st_count   number of random numbers
/// @param[out]  dp  the array of random numbers   
/// @return none
/// @par example:
/// @code
///void test_rand_01_Series()
///{
///    double seed = 0.05;
///    int st_count = 5;
///    rand_01_series(seed,dp,st_count);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
void rand_01_series(double& seed, mitk_nl_vector<double>& dp, const unsigned int st_count)
{   //seed??dp?§µsrCount???
    for(unsigned int st=0; st<st_count; st++)
    {
        seed = RandCoef2053 * (seed) + RandCoef13849;
        seed = (unsigned long)seed % MODUL65536;    //65536???
        dp[st] = seed / (double)MODUL65536;
    }
}

//[a,b]???¦Á
//////////////////////////////////////////////////////////////////////////
///  generates a random number in [a,b]  
/// @param[in]  seed target number
/// @param[in]  a  
/// @param[in]  b
/// @param[out]  rand the pseudo random integer
/// @return  none 
/// @par example:
/// @code
///void test_rand_ab_one()
///{
///    double seed = 0.05;
///    double a = 0.05;
///    double b = 0.53;
///    double res = rand_ab_one(rand,a,b,seed);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
void rand_ab_one(unsigned int &rand, unsigned int a, unsigned int b, unsigned int& seed)
{           //a,b????seed?
    unsigned int stk = b - a + 1;
    unsigned int stl = 2;
    while(stl < stk) stl = stl + stl;
    unsigned int modul = 4 * stl;
    stk = seed;
    unsigned int sti = 1;
    while(sti <= 1)
    {
        stk = 5 * stk;
        stk = stk % modul;
        stl = stk /4 +a;
        if (stl<=b)
        {
            rand=stl; 
            sti=sti+1;
        }
      }
    seed=stk;
}

//[a,b]???¦Á
//////////////////////////////////////////////////////////////////////////
///  generates a numbers of random number in [a,b]  
/// @param[in]  seed target number
/// @param[in]  a
/// @param[in]  b
/// @param[in]  st_count the number of random numbers to be generated
/// @param[out] sp  the array of random numbers 
/// @return none
/// @par example:
/// @code
///void test_rand_ab_series()
///{
///    double seed = 0.05;
///    double a = 0.05;
///    double b = 0.53;
///    int st_count = 8;
///    rand_ab_series(a,b,seed,sp,st_count);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
void rand_ab_series(unsigned int a, unsigned int b, unsigned int& seed
                    , mitk_nl_vector<unsigned int>& sp, unsigned int st_count)
{   //a,b????seed??sp§µst_count?
    unsigned int stk = b - a + 1;
    unsigned int stl = 2;
    while(stl < stk) stl = stl + stl;
    unsigned int modul = 4 * stl;
    stk = seed;
    unsigned int sti = 0;
    while(sti < st_count)
    {
        stk = 5 * stk;
        stk = stk % modul;
        stl = stk / 4 +a;
        if (stl <= b)
        {
            sp[sti]=stl; 
            sti = sti + 1;
        }
    }
    seed=stk;
}

//?????
//?muro(???)????§Ý¨¢
//?§Ön????(12)????
//////////////////////////////////////////////////////////////////////////
///  generate a random number with given mean value and a variant
/// @param[in]  seed target number
/// @param[in]  mu the mean value
/// @param[in]  ro the a variant
/// @param[out]  rand the random number
/// @return  none 
/// @par example:
/// @code
///void test_rand_normal_distributing_one()
///{
///    double mu = 0.05;
///    double ro = 0.36;
///    double seed = 0.03;
///    rand_normal_distributing_one( rand,mu,ro,seed );
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
void rand_normal_distributing_one(double& rand, double mu, double ro, double& seed)
{
    rand = 0.0;
    for (unsigned int st=0; st<12; st++)
    {
        seed = (seed) * RandCoef2053 + RandCoef13849;   //??
        seed =(unsigned long)seed % MODUL65536;         //65536???
        rand = rand + (seed) / (double)MODUL65536;
    }
    rand = mu + ro * (rand - 6.0);
}

//????
//?muro(???)????§Ý¨¢
//?§Ön????(12)????
//////////////////////////////////////////////////////////////////////////
///  generates a number of random number with  given mean value and a variant
/// @param[in]  seed target number
/// @param[in]  mu mean value
/// @param[in]  ro a variant
/// @param[in]  st_count number of random numbers
/// @param[out] dp the array of random numbers 
/// @return none

/// @par example:
/// @code

///void test_normal_distributing_series()
///{
///    double mu = 0.05;
///    double ro = 0.36;
///    double seed = 0.04;
///    int st_count = 9;
///    rand_normal_distributing_series( mu,ro,seed,dp,st_count);
///}
/// @endcode
//////////////////////////////////////////////////////////////////////////
void rand_normal_distributing_series(double mu, double ro
                                    , double seed, mitk_nl_vector<double>& dp, unsigned int st_count)
{           //seed??dp§µstCount???
    for (unsigned int st = 0; st < st_count; st++)
    {
        double rand = 0.0;
        for (unsigned int sr=1; sr<=12; sr++)
        {
            seed = (seed) * RandCoef2053 + RandCoef13849;
            seed = (unsigned long)seed % MODUL65536;            //65536???
            rand = rand + (seed) / (double)MODUL65536;
        }
        dp[st] = mu + ro * (rand - 6.0);
    }
}

///////////////////////////////////////////////////////////////////////////////

typedef unsigned int IntegerType;

class rand_mersenne_twister
{
public:
    rand_mersenne_twister();
    ~rand_mersenne_twister();

    void Initialize();
    void Initialize( const IntegerType oneSeed );

    /** Get a range variate in the range (0, n) */
    double GetVariateWithOpenRange( const double& n );

    /** Get an integer variate in [0, 2^32-1] */
    IntegerType GetIntegerVariate();

    // Re-seeding functions with same behavior as initializers
    inline void SetSeed( const IntegerType oneSeed );
    inline void SetSeed();

protected:
    /* Reload array with N new values */
    void reload();
    static IntegerType hash( time_t t, clock_t c );

    IntegerType hiBit( const IntegerType& u ) const { return u & 0x80000000UL; }
    IntegerType loBit( const IntegerType& u ) const { return u & 0x00000001UL; }
    IntegerType loBits( const IntegerType& u ) const { return u & 0x7fffffffUL; }
    IntegerType mixBits( const IntegerType& u, const IntegerType& v ) const { return hiBit(u) | loBits(v); }
    IntegerType twist( const IntegerType& m, const IntegerType& s0, const IntegerType& s1 ) const 
    {
        return m ^ (mixBits(s0,s1)>>1) ^ (-loBit(s1) & 0x9908b0dfUL); 
    }

    unsigned int StateVectorLength;
    unsigned int M;
    IntegerType* state;   // internal state
    IntegerType* pNext;     // next value to get from state
    int left;  // number of values left before reload needed

};
//-------------------------------------------------------------------------
inline rand_mersenne_twister::rand_mersenne_twister()
: StateVectorLength(624), M(397)
{
    state = new IntegerType [StateVectorLength];
    Initialize(121212);
    reload();
}
//-------------------------------------------------------------------------
inline rand_mersenne_twister::~rand_mersenne_twister()
{
    delete [] state;
}
//-------------------------------------------------------------------------
inline IntegerType rand_mersenne_twister::GetIntegerVariate()
{
    if( left == 0 ) reload();
    --left;

    register IntegerType s1;
    s1 = *pNext++;
    s1 ^= (s1 >> 11);
    s1 ^= (s1 <<  7) & 0x9d2c5680UL;
    s1 ^= (s1 << 15) & 0xefc60000UL;
    return ( s1 ^ (s1 >> 18) );
}
//-------------------------------------------------------------------------
inline double rand_mersenne_twister::GetVariateWithOpenRange(const double& n)
{
    return ( double(GetIntegerVariate()) + 0.5 ) * (1.0/4294967296.0) * n; 
}
//-------------------------------------------------------------------------
inline void rand_mersenne_twister::Initialize()
{
    SetSeed(); 
}
//-------------------------------------------------------------------------
inline void rand_mersenne_twister::Initialize( const IntegerType seed )
{
    // Initialize generator state with seed
    // See Knuth TAOCP Vol 2, 3rd Ed, p.106 for multiplier.
    // In previous versions, most significant bits (MSBs) of the seed affect
    // only MSBs of the state array.  Modified 9 Jan 2002 by Makoto Matsumoto.
    register IntegerType *s = state;
    register IntegerType *r = state;
    register IntegerType i = 1;
    *s++ = seed & 0xffffffffUL;
    for( i = 1; i < StateVectorLength; ++i )
    {
        *s++ = ( 1812433253UL * ( *r ^ (*r >> 30) ) + i ) & 0xffffffffUL;
        r++;
    }
}
//-------------------------------------------------------------------------
inline void rand_mersenne_twister::reload()
{
    // Generate N new values in state
    // Made clearer and faster by Matthew Bellew 
    // matthew dot bellew at home dot com

    // get rid of VS warning
    register int index = static_cast< int >(M - StateVectorLength);

    register IntegerType *p = state;
    register int i;
    for( i = StateVectorLength - M; i--; ++p )
    {
        *p = twist( p[M], p[0], p[1] );
    }
    for( i = M; --i; ++p )
    {
        *p = twist( p[index], p[0], p[1] );
    }
    *p = twist( p[index], p[0], state[0] );

    left = StateVectorLength, pNext = state;
}
//-------------------------------------------------------------------------
inline void rand_mersenne_twister::SetSeed( const IntegerType oneSeed )
{
    Initialize(oneSeed);
    reload();
}
//-------------------------------------------------------------------------
inline void rand_mersenne_twister::SetSeed()
{
    // use time() and clock() to generate a unlikely-to-repeat seed.
    SetSeed( hash( time(0), clock() ) );
}
//-------------------------------------------------------------------------
inline IntegerType rand_mersenne_twister::hash( time_t t, clock_t c )
{
    // Get a IntegerType from t and c
    // Better than IntegerType(x) in case x is floating point in [0,1]
    // Based on code by Lawrence Kirby: fred at genesis dot demon dot co dot uk 

    static IntegerType differ = 0;  // guarantee time-based seeds will change

    IntegerType h1 = 0;
    unsigned char *p = (unsigned char *) &t;
    for( size_t i = 0; i < sizeof(t); ++i )
    {
        h1 *= UCHAR_MAX + 2U;
        h1 += p[i];
    }
    IntegerType h2 = 0;
    p = (unsigned char *) &c;
    for( size_t j = 0; j < sizeof(c); ++j )
    {
        h2 *= UCHAR_MAX + 2U;
        h2 += p[j];
    }
    return ( h1 + differ++ ) ^ h2;
}
//-------------------------------------------------------------------------

} //end of namespace mitk_nl

#endif 

/// @}
/// @}

