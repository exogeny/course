/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkNeighborhoodIterator_h
#define __mitkNeighborhoodIterator_h

#include "mitkVolumeIterator.h"
#include "mitkNeighborhood.h"

///////////////////////////////////////////////////////////////////////////////////
// ---------------------- mitkNeighborhoodIterator --------------------------------
//You should first invoke mitkNeumannBoundary to get volume with NeumannBoundary
//which is defined in mitkNeumannBoundary.h
//a example:
//mitkNeumannBoundary *NeumannBoundary = new mitkNeumannBoundary;
//NeumannBoundary->SetInput(vol);
//NeumannBoundary->Run();
//m_NeumannBoundaryVol = NeumannBoundary->GetOutput();
//NeumannBoundary->Delete();
//mitkNeighborhoodIterator<int> it(m_NeumannBoundaryVol);
//  [8/20/2010 Xiuli Li]
//////////////////////////////////////////////////////////////////////////

template<class T>
class mitkNeighborhoodIterator : public mitkVolumeIterator<T>
{
public:
    mitkNeighborhoodIterator();

    mitkNeighborhoodIterator(mitkVolume* vol, VectorIndexType& radius);

    mitkNeighborhoodIterator(mitkVolume* vol, VectorIndexType& region, VectorIndexType& radius);

    ~mitkNeighborhoodIterator();

    void SetRadius(VectorIndexType& radius);

    virtual ScalarPixelType GetCenterPixel() const
    {
        return static_cast<ScalarPixelType>( *m_Position );
    }

    const VectorIndexType & GetInnerImageRegion();

    // Get Neighborhood values
    virtual void GetNeighborhood(const ScalarIndexType* index, ScalarPixelType* value, int ch=0)

    // Get given offset vector point value
    virtual ScalarPixelType GetOffsetVal(VectorIndexType& m_Offset);
protected:
    mitkNeighborhood* m_Neighborhood;
    VectorPixelType   m_NeighborhoodVec;
private:
};

template<class T>
ScalarPixelType mitkNeighborhoodIterator<T>::GetOffsetVal( VectorIndexType& m_Offset )
{
    T* pos = m_DataPointer;
    ScalarPixelType OffsetVal;
    if(m_Neighborhood->m_Dimension == 2)
    {
        int inc = m_Offset[0] + m_Offset[1]*m_Increments[1];
        OffsetVal = static_cast<ScalarPixelType>( *(pos + inc) );
    }
    else if(m_Neighborhood->m_Dimension == 3)
    {
        int inc = m_Offset[0] + m_Offset[1]*m_Increments[1] + m_Offset[2]*m_Increments[2];
        OffsetVal = static_cast<ScalarPixelType>( *(pos + inc) );
    }
}
template<class T>
void mitkNeighborhoodIterator<T>::GetNeighborhood( const ScalarIndexType* index, VectorPixelType& m_NeighborhoodVec, int ch/*=0*/ )
{
    ScalarIndexType offset = this->ComputeOffset(index);
    T* pos = m_DataPointer + offset + ch;

    if(m_Neighborhood->m_Dimension == 2)
    {
        unsigned int len = m_Neighborhood->m_OffsetTable.size();
        m_NeighborhoodVec = VectorPixelType(len,0.0);

        unsigned int i; 
        for (i=0;i<len;i++)
        {
            int inc = m_Neighborhood->m_OffsetTable[i][0] + m_Neighborhood->m_OffsetTable[i][1]*m_Increments[1];
            m_NeighborhoodVec[i] = static_cast<ScalarPixelType>( *(pos + inc) );
        }
    }
    else if(m_Neighborhood->m_Dimension == 3)
    {
        unsigned int len = m_Neighborhood->m_OffsetTable.size();
        m_NeighborhoodVec = VectorPixelType(len,0.0);

        unsigned int i; 
        for (i=0;i<len;i++)
        {
            int inc = m_Neighborhood->m_OffsetTable[i][0] + m_Neighborhood->m_OffsetTable[i][1]*m_Increments[1]
                                        +m_Neighborhood->m_OffsetTable[i][2]*m_Increments[2];
            m_NeighborhoodVec[i] = static_cast<ScalarPixelType>( *(pos + inc) );
        }
    }
}
//-------------------------------------------------------------------------------
template<class T>
const VectorIndexType & mitkNeighborhoodIterator<T>::GetInnerImageRegion()
{
    for(unsigned int i=0;i<m_ImageDimension;i++)
    {
        m_Region[i*2] = 2;
        m_Region[i*2+1] = m_Dimensions[i] - 5;      //Notice:width
    }

    return m_Region; 
}
//-----------------------------------------------------------------------------
template<class T>
mitkNeighborhoodIterator<T>::~mitkNeighborhoodIterator()
{
    delete m_Neighborhood;
}
//-------------------------------------------------------------------------------
template<class T>
void mitkNeighborhoodIterator<T>::SetRadius( VectorIndexType& radius )
{
    m_Neighborhood->SetRadius(radius);
}
//-------------------------------------------------------------------------------
template<class T>
mitkNeighborhoodIterator<T>::mitkNeighborhoodIterator()
: mitkVolumeIterator<T>()
{
    m_Neighborhood = new mitkNeighborhood;
}
//---------------------------------------------------------------------------------
template<class T>
mitkNeighborhoodIterator<T>::mitkNeighborhoodIterator( mitkVolume* vol, VectorIndexType& region, VectorIndexType& radius )
: mitkVolumeIterator<T>(vol, region)
{
    m_Neighborhood = new mitkNeighborhood;
    m_Neighborhood->SetRadius(radius);
}
//------------------------------------------------------------------------------------
template<class T>
mitkNeighborhoodIterator<T>::mitkNeighborhoodIterator( mitkVolume* vol, VectorIndexType& radius )
:  mitkVolumeIterator<T>(vol)
{
    m_Neighborhood = new mitkNeighborhood;
    m_Neighborhood->SetRadius(radius);
}
//-------------------------------------------------------------------------------------------
#endif
