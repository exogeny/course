/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeRandomIterator_h
#define __mitkVolumeRandomIterator_h

#include "mitkVolumeIterator.h"
#include "mitk_nl/mitk_nl_rand.h"


///////////////////////////////////////////////////////////////////////////
// ---------------------- mitkVolumeRandomIterator ------------------------
///////////////////////////////////////////////////////////////////////////

template<class T>
class mitkVolumeRandomIterator : public mitkVolumeIterator<T>
{
public: 
    mitkVolumeRandomIterator();

    mitkVolumeRandomIterator(mitkVolume* vol);

    mitkVolumeRandomIterator(mitkVolume* vol, VectorIndexType& region);

    ~mitkVolumeRandomIterator();

    virtual void GoToBegin(void)
    {
        this->RandomJump();
        m_NumberOfSamplesDone = 0L;
    }

    virtual void GoToEnd(void)
    {
        this->RandomJump();
        m_NumberOfSamplesDone = m_NumberOfSamplesRequested;
    }

    virtual bool IsAtBegin(void) const
    {
        return (m_NumberOfSamplesDone == 0L); 
    }

    virtual bool IsAtEnd(void) const
    { 
        return (m_NumberOfSamplesDone >= m_NumberOfSamplesRequested);  
    }

    virtual void operator++()
    {
        this->RandomJump();
        m_NumberOfSamplesDone++;
    }

    virtual void operator--()
    {
        this->RandomJump();
        m_NumberOfSamplesDone--;
    }

    virtual void SetNumberOfSamples( unsigned long number );
    virtual unsigned long GetNumberOfSamples( void ) const;

    virtual void ReinitializeSeed();
    virtual void ReinitializeSeed(int);

private:
    void RandomJump();
    mitk_nl::rand_mersenne_twister* m_Generator;
    unsigned long  m_NumberOfSamplesRequested;
    unsigned long  m_NumberOfSamplesDone;
    unsigned long  m_NumberOfPixelsInRegion;
};
//-------------------------------------------------------------------------
template<class T>
mitkVolumeRandomIterator<T>::mitkVolumeRandomIterator()
: mitkVolumeIterator<T>()
{
    m_NumberOfPixelsInRegion    = 0L;
    m_NumberOfSamplesRequested  = 0L;
    m_NumberOfSamplesDone       = 0L;
    m_Generator = new mitk_nl::rand_mersenne_twister;
}
//-------------------------------------------------------------------------
template<class T>
mitkVolumeRandomIterator<T>::mitkVolumeRandomIterator(mitkVolume* vol)
: mitkVolumeIterator<T>(vol)
{
    m_NumberOfPixelsInRegion    = this->GetNumberOfPixelsInRegion();
    m_NumberOfSamplesRequested  = 0L;
    m_NumberOfSamplesDone       = 0L;
    m_Generator = new mitk_nl::rand_mersenne_twister;
}
//-------------------------------------------------------------------------
template<class T>
mitkVolumeRandomIterator<T>::mitkVolumeRandomIterator(mitkVolume* vol, VectorIndexType& region)
: mitkVolumeIterator<T>(vol, region)
{
    m_NumberOfPixelsInRegion    = this->GetNumberOfPixelsInRegion();
    m_NumberOfSamplesRequested  = 0L;
    m_NumberOfSamplesDone       = 0L;
    m_Generator = new mitk_nl::rand_mersenne_twister;
}
//-------------------------------------------------------------------------
template<class T>
mitkVolumeRandomIterator<T>::~mitkVolumeRandomIterator()
{

}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeRandomIterator<T>::SetNumberOfSamples( unsigned long number )
{
    m_NumberOfSamplesRequested = number;
}
//-------------------------------------------------------------------------
template<class T>
unsigned long mitkVolumeRandomIterator<T>::GetNumberOfSamples( void ) const
{
    return m_NumberOfSamplesRequested;
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeRandomIterator<T>::ReinitializeSeed()
{
    m_Generator->SetSeed();
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeRandomIterator<T>::ReinitializeSeed(int seed)
{
    m_Generator->SetSeed(seed);
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeRandomIterator<T>::RandomJump()
{
    const unsigned long randomPosition =
        static_cast<unsigned long > (  m_Generator->GetVariateWithOpenRange ( static_cast<double>(m_NumberOfPixelsInRegion)-0.5 ) );

    unsigned long position = randomPosition;
    unsigned long residual;
    for( unsigned int dim = 0; dim < m_ImageDimension; dim++ )
    {
        const unsigned long sizeInThisDimension = m_Region[2*dim+1] - m_Region[2*dim];
        residual = position % sizeInThisDimension;
        m_PositionIndex[dim] =  residual + m_BeginIndex[dim];
        position -= residual;
        position /= sizeInThisDimension;
    }

    m_Position = m_DataPointer + this->ComputeOffset( m_PositionIndex );

}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
namespace MITK_VOL_ITERATOR
{

static bool GenerateRandomVolumeIterator(mitkVolume* vol, mitkVolumeIteratorBase* &it, bool autorelease = false)
{
    if( it != NULL && autorelease)
    {
        delete it;
    }

    bool run_flag = true;

    switch(vol->GetDataType())
    {
    case MITK_DOUBLE:
        it = new mitkVolumeRandomIterator<double>(vol);
        break;
    case MITK_FLOAT:
        it = new mitkVolumeRandomIterator<float>(vol);
        break;
    case MITK_LONG:
        it = new mitkVolumeRandomIterator<long>(vol);
        break;
    case MITK_UNSIGNED_LONG:
        it = new mitkVolumeRandomIterator<unsigned long>(vol);
        break;
    case MITK_INT:
        it = new mitkVolumeRandomIterator<int>(vol);
        break;
    case MITK_UNSIGNED_INT:
        it = new mitkVolumeRandomIterator<unsigned int>(vol);
        break;
    case MITK_SHORT:
        it = new mitkVolumeRandomIterator<short>(vol);
        break;
    case MITK_UNSIGNED_SHORT:
        it = new mitkVolumeRandomIterator<unsigned short>(vol);
        break;
    case MITK_CHAR:
        it = new mitkVolumeRandomIterator<char>(vol);
        break;
    case MITK_UNSIGNED_CHAR:
        it = new mitkVolumeRandomIterator<unsigned char>(vol);
        break;
    default:
        it = NULL;
        run_flag = false;
    }

    return run_flag;
}

} // END namespace MITK_VOL_ITERATOR
//-------------------------------------------------------------------------
#ifdef MITK_DLL_EXPORT 
#define DEFINED_mitkVolumeRandomIterator
#include "mitkTemplateExport.h" 
#endif      // MITK_DLL_EXPORT

#endif


