/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeIterator_h
#define __mitkVolumeIterator_h

#ifndef MITK_VER_OOC
#include "mitkVolume.h"
#else
#include "mitkICVolume.h"
#endif


/// mitkVolumeIterator
///////////////////////////////////////////////////////////////////////////

//*********************************************************************************
//                            mitkVolumeIteratorBase
//*********************************************************************************

class mitkVolumeIteratorBase
{
public:
    mitkVolumeIteratorBase() {}

    ~mitkVolumeIteratorBase() {}

    virtual void SetVolume(mitkVolume* vol) = 0;

//  virtual ScalarPixelType  GetPixel(const ScalarIndexType* index) = 0;
    virtual ScalarPixelType  GetPixel(const ScalarIndexType* index, int ch=0) = 0;
    virtual ScalarPixelType  GetPixel(const VectorIndexType& index, int ch=0) = 0;
    virtual ScalarPixelType  GetPixel(ScalarIndexType x, ScalarIndexType y, ScalarIndexType z, int ch=0) = 0;
    virtual void             GetPixel(const ScalarIndexType* index, ScalarPixelType* value) = 0;
    virtual void             GetPixel(const VectorIndexType& index, VectorPixelType& value) = 0;

    virtual void SetPixel(ScalarPixelType val, ScalarIndexType x, ScalarIndexType y, ScalarIndexType z, int ch=0) = 0;

    virtual void GetSequence(ScalarPixelType* values, int mode) = 0;
    virtual void SetSequence(const ScalarPixelType* values, int mode) = 0;

    // 4 neighbors in 2D, 8 neighbors in 3D
    virtual void GetNeighbors2x(const ScalarIndexType* index, ScalarPixelType* value, int ch=0) = 0;
    // 16 neighbors in 2D, 64 neighbors in 3D
    virtual void GetNeighbors4x(const ScalarIndexType* index, ScalarPixelType* value, int ch=0) = 0;
    // 8 neighbors in 2D, 26 neighbors in 3D
//  virtual void   GetNeighbors3x(const ScalarIndexType* index, ScalarPixelType* value, int ch=0) = 0;

    virtual ScalarPixelType Value() = 0;                    // single channel
    virtual ScalarParameterType Value(int c) = 0;           // multi channel
    virtual void  Get(ScalarPixelType* v) = 0;              // multi channel
    virtual void  Get(VectorPixelType& v) = 0;              // multi channel
    virtual void  Get(ScalarParameterType* v) = 0;          // multi channel
    virtual void  Get(VectorParameterType& v) = 0;          // multi channel

    virtual void  Set(const ScalarPixelType& pixel) = 0;
    virtual void  Set(const ScalarPixelType* pixel) = 0;        // multi channel
    virtual void  Set(const VectorPixelType& pixel) = 0;        // multi channel
    virtual void  Set(const ScalarParameterType& pixel) = 0;
    virtual void  Set(const ScalarParameterType* pixel) = 0;    // multi channel
    virtual void  Set(const VectorParameterType& pixel) = 0;    // multi channel

    virtual void  GoToBegin(void) = 0;
    virtual void  GoToEnd(void) = 0;
    virtual void  GoToNextRow(void) = 0;
    virtual void  GoToNextCol(void) = 0;
    virtual void  GoToNextSlice(void) = 0;
    virtual void  GoToNextX(int mode) = 0;
    virtual void  SetIndex(const VectorIndexType &ind) = 0;

//  virtual int GetPointer(const VectorIndexType & index) = 0; // for test
//  virtual int GetPointer() = 0;

    virtual void operator++() = 0;  // next voxel
    virtual void operator--() = 0;  // previous voxel

    // for random volume iterator
    virtual void SetNumberOfSamples( unsigned long number ) {}
    virtual unsigned long GetNumberOfSamples( void ) const {return 0;}
    virtual void ReinitializeSeed() {}
    virtual void ReinitializeSeed(int) {}

    void SetDefaultChannel(int ch)
    {
        m_DefaultChannel = ch;
    }

    virtual bool IsAtBegin(void) const
    {
        bool res = true;
        for(unsigned int i=0;i<m_ImageDimension;i++)
            if(m_PositionIndex[i] != m_BeginIndex[i])
                res = false;
        return res; 
    }

    virtual bool IsAtEnd(void) const
    {
        return !m_Remaining;
    }

    void SetRegion(const VectorIndexType& region)
    {
        m_Region = region;
        if(m_ImageDimension == 0) return;
        this->initRegion();
    }

    const VectorIndexType & GetRegion(void) const
    {
        return m_Region;
    }

    const VectorIndexType & GetEntireImageRegion(void)
    {
        if(m_ImageDimension == 0) return m_Region;

        if(m_Region.size() == 0)
        {
            m_Region = VectorIndexType(m_ImageDimension*2,0);
        }

        for(unsigned int i=0;i<m_ImageDimension;i++)
        {
            m_Region[i*2] = 0;
            m_Region[i*2+1] = m_Dimensions[i] - 1;      //Notice
        }

        return m_Region; 
    }

    const VectorIndexType& GetIndex(void) const
    { 
        return m_PositionIndex;
    }

    virtual ScalarIndexType ComputeOffset(const VectorIndexType& index)
    {
        ScalarIndexType offset = 0;
        for(unsigned int i=0;i<m_ImageDimension;i++)
        {
            offset += index[i] * m_Increments[i];
        }
        return offset;
    }

    virtual ScalarIndexType ComputeOffset(const ScalarIndexType* index)
    {
        ScalarIndexType offset = 0;
        for(unsigned int i=0;i<m_ImageDimension;i++)
        {
            offset += index[i] * m_Increments[i];
        }
        return offset;
    }

    virtual ScalarIndexType ComputeOffset(const ScalarIndexType x, const ScalarIndexType y, const ScalarIndexType z=0)
    {
        ScalarIndexType offset = 0;
        offset += x * m_Increments[0];
        offset += y * m_Increments[1];
        offset += z * m_Increments[2];
        return offset;
    }

    unsigned int GetNumberOfPixelsInRegion()
    {
        unsigned int counts = m_Region[1] - m_Region[0] + 1;
        for(unsigned int i=1;i<m_ImageDimension;i++)
        {
            counts *= m_Region[2*i+1] - m_Region[2*i] + 1;
        }
        return (counts == 1) ? 0 : counts;
    }

    virtual void SetIOMode(int mode) {};

protected:
    virtual void init() = 0;
    virtual void initRegion() = 0;

    mitkVolume*         m_Volume;

    VectorIndexType     m_PositionIndex;
    VectorIndexType     m_BeginIndex;
    VectorIndexType     m_EndIndex;   

    VectorIndexType     m_Region;
    int                 m_Dimensions[3];
    int                 m_Dimensions2[3];
    int                 m_Increments[3];
    int                 m_DefaultChannel;

    unsigned int        m_ImageDimension;
    unsigned int        m_NumberOfChannels;
    bool                m_Remaining;
};

//*********************************************************************************
//                              mitkVolumeIterator
//*********************************************************************************

template<class T>
class mitkVolumeIterator : public mitkVolumeIteratorBase
{
protected:
    virtual void init();
    virtual void initRegion();

    T*                  m_DataPointer;

    T*                  m_Position;
    T*                  m_Begin;
    T*                  m_End;

    ScalarIndexType     m_OffsetTable[3];
    ScalarIndexType     m_IncremetTable[8]; //for test

public: 
    mitkVolumeIterator();

    mitkVolumeIterator(mitkVolume* vol);

    mitkVolumeIterator(mitkVolume* vol, VectorIndexType& region);

    ~mitkVolumeIterator() {};

    virtual void SetIOMode(int mode) {};

    virtual void SetVolume(mitkVolume* vol);

    virtual ScalarPixelType GetPixel(const ScalarIndexType* index, int ch=0)
    {
        ScalarIndexType offset = this->ComputeOffset(index) + ch;
        return static_cast<ScalarPixelType>( *(m_DataPointer + offset) );
    }

    virtual ScalarPixelType GetPixel(const VectorIndexType & index, int ch=0) 
    {
        ScalarIndexType offset = this->ComputeOffset(index) + ch;
        return static_cast<ScalarPixelType>( *(m_DataPointer + offset) );
    }

    virtual ScalarPixelType GetPixel(ScalarIndexType x, ScalarIndexType y, ScalarIndexType z=0, int ch=0)
    {
        ScalarIndexType offset = this->ComputeOffset(x,y,z) + ch;
        return static_cast<ScalarPixelType>( *(m_DataPointer + offset) );
    }

    virtual void GetPixel(const ScalarIndexType* index, ScalarPixelType* value)
    {
        ScalarIndexType offset = this->ComputeOffset(index);
        T* pos = m_DataPointer + offset;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            value[i] = static_cast<ScalarPixelType>( *pos );
            pos++;
        }
    }

    virtual void GetPixel(const VectorIndexType & index, VectorPixelType& value)
    {
        ScalarIndexType offset = this->ComputeOffset(index);
        T* pos = m_DataPointer + offset;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            value[i] = static_cast<ScalarPixelType>( *pos );
            pos++;
        }
    }

    virtual void SetPixel(ScalarPixelType val, ScalarIndexType x, ScalarIndexType y, ScalarIndexType z, int ch=0)
    {
        ScalarIndexType offset = this->ComputeOffset(x,y,z) + ch;
        *(m_DataPointer + offset) = static_cast<T>( val );
    }

    virtual void GetSequence(ScalarPixelType* values, int mode);
    virtual void SetSequence(const ScalarPixelType* values, int mode);

    virtual ScalarPixelType Value()
    {
        return static_cast<ScalarPixelType>( *m_Position );
    }

    virtual ScalarParameterType Value(int c)
    {
        return static_cast<ScalarParameterType>( *(m_Position + c) );
    }

    virtual void Set(const ScalarPixelType* pixel)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            *pos = static_cast<T>( pixel[i] );
            pos++;
        }
    }

    virtual void Set(const VectorPixelType& pixel)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            *pos = static_cast<T>( pixel[i] );
            pos++;
        }
    }

    virtual void Set(const ScalarParameterType* pixel)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            *pos = static_cast<T>( pixel[i] );
            pos++;
        }
    }

    virtual void Set(const VectorParameterType& pixel)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            *pos = static_cast<T>( pixel[i] );
            pos++;
        }
    }

    virtual void Set(const ScalarPixelType& pixel)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            *pos = static_cast<T>( pixel );
            pos++;
        }
    }

    virtual void Set(const ScalarParameterType& pixel)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            *pos = static_cast<T>( pixel );
            pos++;
        }
    }

    virtual void Get(ScalarPixelType* v)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            v[i] = static_cast<ScalarPixelType>( *pos );
            pos++;
        }
    }

    virtual void Get(VectorPixelType& v)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            v[i] = static_cast<ScalarPixelType>( *pos );
            pos++;
        }
    }

    virtual void Get(VectorParameterType& v)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            v[i] = static_cast<ScalarParameterType>( *pos );
            pos++;
        }
    }

    virtual void Get(ScalarParameterType* v)
    {
        T* pos = m_Position;
        for(unsigned int i=0;i<m_NumberOfChannels;i++)
        {
            v[i] = static_cast<ScalarParameterType>( *pos );
            pos++;
        }
    }

    virtual void GetNeighbors2x(const ScalarIndexType* index, ScalarPixelType* value, int ch=0);
    virtual void GetNeighbors4x(const ScalarIndexType* index, ScalarPixelType* value, int ch=0);

    virtual void GoToBegin(void);
    virtual void GoToEnd(void);
    virtual void GoToNextRow(void);
    virtual void GoToNextCol(void);
    virtual void GoToNextSlice(void);
    virtual void GoToNextX(int mode);

    virtual void SetIndex(const VectorIndexType &ind);
/*
    virtual int GetPointer(const VectorIndexType & index)
    {
        ScalarIndexType offset = this->ComputeOffset(index);
        return (int) (m_DataPointer + offset);
    }
    virtual int GetPointer()
    {
        return (int) m_Position;
    }
*/
    virtual void operator++();
    virtual void operator--();

private:
    mitkVolumeIterator(const mitkVolumeIterator&);
    void operator=(const mitkVolumeIterator&);

};

///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
template<class T>
mitkVolumeIterator<T>::mitkVolumeIterator()
{
    m_Volume = NULL;
    m_Remaining = false;
    m_ImageDimension = 0;
    m_NumberOfChannels = 0;
    m_DefaultChannel = 0;
}
//-------------------------------------------------------------------------
template<class T>
mitkVolumeIterator<T>::mitkVolumeIterator(mitkVolume* vol)
{
    m_Remaining = false;
    m_ImageDimension = 0;
    m_NumberOfChannels = 0;
    m_DefaultChannel = 0;

    this->SetVolume(vol);
}
//-------------------------------------------------------------------------
template<class T>
mitkVolumeIterator<T>::mitkVolumeIterator(mitkVolume* vol, VectorIndexType& region)
{
    m_Remaining = false;
    m_ImageDimension = 0;
    m_NumberOfChannels = 0;
    m_DefaultChannel = 0;

    this->SetRegion(region);
    this->SetVolume(vol);
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::init()  //after set volume
{
    m_BeginIndex = VectorIndexType(m_ImageDimension, 0);
    m_EndIndex = VectorIndexType(m_ImageDimension, 0);

    this->initRegion();

    // initialize increment table for 2x neighbors
    if(m_ImageDimension == 2)
    {
        m_IncremetTable[0] = 0;
        m_IncremetTable[1] = m_Increments[0];
        m_IncremetTable[2] = m_Increments[1];
        m_IncremetTable[3] = m_Increments[1] + m_Increments[0];
    }
    else if(m_ImageDimension == 3)
    {
        m_IncremetTable[0] = 0;
        m_IncremetTable[1] = m_Increments[0];
        m_IncremetTable[2] = m_Increments[1];
        m_IncremetTable[3] = m_Increments[1] + m_Increments[0];
        m_IncremetTable[4] = m_Increments[2];
        m_IncremetTable[5] = m_Increments[2] + m_Increments[0];
        m_IncremetTable[6] = m_Increments[2] + m_Increments[1];
        m_IncremetTable[7] = m_Increments[2] + m_Increments[1] + m_Increments[0];
    }

}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::initRegion()
{
    unsigned int i;

    for(i=0;i<m_ImageDimension;i++)
    {
        m_BeginIndex[i] = m_Region[2*i];
        m_EndIndex[i] = m_Region[2*i+1];
    }

    // compute begin and end buffer offset
    ScalarIndexType offset = this->ComputeOffset(m_BeginIndex);
    m_Begin = m_DataPointer + offset;

    offset  = this->ComputeOffset(m_EndIndex);
    m_End = m_DataPointer + offset;

    this->GoToBegin();

    // initialize offset table
    for(i=0;i<m_ImageDimension;i++)
    {
        m_OffsetTable[i] = m_Increments[i] * (m_Region[2*i+1] - m_Region[2*i] /* -1 */);
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::SetVolume(mitkVolume* vol)
{
    if(vol == NULL) return;

    // in-core volume check
#ifdef MITK_VER_OOC
    if(vol->GetDataObjectType() != MITK_IC_VOLUME)
    {
        //MITK_REG_GLOBAL::RegMessage("mitkVolumeIterator can't handle out-of-core volume.");
        return;
    }
#endif
    
    // volume pointer copy
    m_Volume = vol;

    // volume data buffer
    m_DataPointer = (T*) m_Volume->GetData();

    m_ImageDimension = m_Volume->GetImageNum() == 1 ? 2: 3;
    m_NumberOfChannels  = m_Volume->GetNumberOfChannel();
    
    // volume dimensions
    m_Volume->GetDimensions(m_Dimensions);

    for(unsigned int i = 0;i<m_ImageDimension;i++)
        m_Dimensions2[i] = 2 * m_Dimensions[i] - 2;

    // volume increments
    m_Volume->GetIncrements(m_Increments);

    if(m_Region.size() == 0)    //otherwise: image region was already set
    {
        this->GetEntireImageRegion();
    }
    
    this->init();
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::GoToBegin(void)
{
    m_PositionIndex = m_BeginIndex;
    m_Position = m_Begin;
    
    if( this->GetNumberOfPixelsInRegion() )
    {
        m_Remaining = true;
    }
    else
    {
        m_Remaining = false;
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::GoToEnd(void)
{
    m_PositionIndex = m_EndIndex;

    m_Position = m_End;
    m_Remaining = false;
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::GoToNextRow(void)
{
    m_Position -= (m_PositionIndex[0] - m_BeginIndex[0]) * m_Increments[0];
    m_PositionIndex[0] = m_BeginIndex[0];

    m_Remaining = false;
    for( unsigned int i=1; i<m_ImageDimension; i++ )
    {
        m_PositionIndex[i]++;
        if( m_PositionIndex[i] <= m_EndIndex[i] )
        {
            m_Position += m_Increments[i];
            m_Remaining = true;
            break;
        }
        else 
        {
            m_Position -= m_OffsetTable[i];
            m_PositionIndex[i] = m_BeginIndex[i]; 
        }
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::GoToNextCol(void)
{
    m_Position -= (m_PositionIndex[1]- m_BeginIndex[1]) * m_Increments[1];
    m_PositionIndex[1] = m_BeginIndex[1];

    m_Remaining = false;
    for( unsigned int i=0; i<m_ImageDimension; i++ )
    {
        if(i==1) continue;

        m_PositionIndex[i]++;
        if( m_PositionIndex[i] <= m_EndIndex[i] )
        {
            m_Position += m_Increments[i];
            m_Remaining = true;
            break;
        }
        else 
        {
            m_Position -= m_OffsetTable[i];
            m_PositionIndex[i] = m_BeginIndex[i]; 
        }
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::GoToNextSlice(void)
{
    m_Position -= (m_PositionIndex[2]- m_BeginIndex[2]) * m_Increments[2];
    m_PositionIndex[2] = m_BeginIndex[2];

    m_Remaining = false;
    for( unsigned int i=0; i<m_ImageDimension-1; i++ )
    {
        m_PositionIndex[i]++;
        if( m_PositionIndex[i] <= m_EndIndex[i] )
        {
            m_Position += m_Increments[i];
            m_Remaining = true;
            break;
        }
        else 
        {
            m_Position -= m_OffsetTable[i];
            m_PositionIndex[i] = m_BeginIndex[i]; 
        }
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::GoToNextX(int mode)
{
    switch(mode)
    {
    case 0:
        this->GoToNextRow();
        break;
    case 1:
        this->GoToNextCol();
        break;
    case 2:
        this->GoToNextSlice();
        break;
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::SetIndex(const VectorIndexType &ind)
{
    m_Position = m_DataPointer + this->ComputeOffset( ind ); 

    for(unsigned int i=0; i<m_ImageDimension; i++)
        m_PositionIndex[i] = ind[i];  
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::operator++()
{
    m_Remaining = false;
    for( unsigned int i=0; i<m_ImageDimension; i++ )
    {
        m_PositionIndex[i]++;
        if( m_PositionIndex[i] <= m_EndIndex[i] )
        {
            m_Position += m_Increments[i];
            m_Remaining = true;
            break;
        }
        else 
        {
            m_Position -= m_OffsetTable[i];
            m_PositionIndex[i] = m_BeginIndex[i]; 
        }
    }

    if( !m_Remaining )
    {
        m_Position = m_End;
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkVolumeIterator<T>::operator--()
{
    m_Remaining = false;
    for( unsigned int i=0; i<m_ImageDimension; i++ )
    {
        if( m_PositionIndex[i] > m_BeginIndex[i] )
        {
            m_PositionIndex[i]--;
            m_Position -= m_Increments[i];
            m_Remaining = true;
            break;
        }
        else 
        {
            m_Position += m_OffsetTable[i];
            m_PositionIndex[i] = m_EndIndex[i]; 
        }
    }

    if( !m_Remaining )
    {
        m_Position = m_End;
    }
}
//-------------------------------------------------------------------------
template<class T>
inline void mitkVolumeIterator<T>::GetNeighbors2x(const ScalarIndexType* index, ScalarPixelType* value, int ch)
{
    ScalarIndexType offset = this->ComputeOffset(index);
    T* pos = m_DataPointer + offset + ch;

    if(m_ImageDimension == 2)
    {
        value[0] = static_cast<ScalarPixelType>( *(pos) );                          // (i  , j  )
        value[1] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[1]) );     // (i+1, j  )
        value[2] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[2]) );     // (i  , j+1)
        value[3] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[3]) );     // (i+1, j+1)
    }
    else if(m_ImageDimension == 3)
    {
        value[0] = static_cast<ScalarPixelType>( *(pos) );                          // (i  , j  , k  )
        value[1] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[1]) );     // (i+1, j  , k  )
        value[2] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[2]) );     // (i  , j+1, k  )
        value[3] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[3]) );     // (i+1, j+1, k  )
        value[4] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[4]) );     // (i  , j  , k+1)
        value[5] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[5]) );     // (i+1, j  , k+1)
        value[6] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[6]) );     // (i  , j+1, k+1)
        value[7] = static_cast<ScalarPixelType>( *(pos + m_IncremetTable[7]) );     // (i+1, j+1, k+1)
    }

}
//-------------------------------------------------------------------------
template<class T>
inline void mitkVolumeIterator<T>::GetNeighbors4x(const ScalarIndexType* index, ScalarPixelType* value, int ch)
{
    unsigned int i,j;
    ScalarIndexType nIndex[3][4];

    for(i=0;i<m_ImageDimension;i++) {
        for (j = 0; j < 4; j++)
        {
            nIndex[i][j] = index[i] - 1 + j;

            if(m_Dimensions[i] == 1)
            {
                nIndex[i][j] = 0;
            }
            else
            {
                if(nIndex[i][j] < 0)
                {
                    nIndex[i][j] = -nIndex[i][j] - m_Dimensions2[i] * ((-nIndex[i][j]) / m_Dimensions2[i]);
                }
                else
                {
                    nIndex[i][j] = nIndex[i][j] - m_Dimensions2[i] * (nIndex[i][j] / m_Dimensions2[i]);
                }
            }

            if (m_Dimensions[i] <= nIndex[i][j]) 
            {
                nIndex[i][j] = m_Dimensions2[i] - nIndex[i][j];
            }
        }
    }

    if(m_ImageDimension == 2)
    {
        for(j = 0; j < 4; j++) {
            for(i = 0; i < 4; i++) {
                value[i+4*j] = (ScalarPixelType) m_DataPointer[m_Increments[1] * nIndex[1][j]
                + m_Increments[0] * nIndex[0][i] +ch];
            }
        }
    }
    else
    {
        for(unsigned int k = 0; k < 4; k++) {
            for(j = 0; j < 4; j++) {
                for(i = 0; i < 4; i++) {
                    value[i+4*j+16*k] = (ScalarPixelType) m_DataPointer[m_Increments[2] * nIndex[2][k]
                    + m_Increments[1] * nIndex[1][j]
                    + m_Increments[0] * nIndex[0][i] + ch];
                }
            }
        }
    }
}
//-------------------------------------------------------------------------
template<class T>
inline void mitkVolumeIterator<T>::GetSequence(ScalarPixelType* values, int mode)
{
    //a. read a sequence (suppose the pointer is already in the beginning of the sequence)
    //b. move pointer to next sequence start position
    //c. do NOT need iterator operation ++ / --

    /* mode : 0  by row
     *        1  by col
     *        2  by z-direction */

    int i,j=0;
    T* pos = m_Position;
    switch(mode)
    {
    case 0:
        for(i=m_Region[0];i<=m_Region[1];i++)
        {
            values[j] = (ScalarPixelType) *(pos+m_DefaultChannel);
            pos += m_Increments[0];
            j++;
        }
        break;
    case 1:
        for(i=m_Region[2];i<=m_Region[3];i++)
        {
            values[j] = (ScalarPixelType) *(pos+m_DefaultChannel);
            pos += m_Increments[1];
            j++;
        }
        break;
    case 2:
        for(i=m_Region[4];i<=m_Region[5];i++)
        {
            values[j] = (ScalarPixelType) *(pos+m_DefaultChannel);
            pos += m_Increments[2];
            j++;
        }
        break;
    default:
        //do nothing
        break;
    }
}
//-------------------------------------------------------------------------
template<class T>
inline void mitkVolumeIterator<T>::SetSequence(const ScalarPixelType* values, int mode)
{
    int i,j=0;
    T* pos = m_Position;
    switch(mode)
    {
    case 0:
        for(i=m_Region[0];i<=m_Region[1];i++)
        {
            *(pos+m_DefaultChannel) = (T) values[j];
            pos += m_Increments[0];
            j++;
        }
        break;
    case 1:
        for(i=m_Region[2];i<=m_Region[3];i++)
        {
            *(pos+m_DefaultChannel) = (T) values[j];
            pos += m_Increments[1];
            j++;
        }
        break;
    case 2:
        for(i=m_Region[4];i<=m_Region[5];i++)
        {
            *(pos+m_DefaultChannel) = (T) values[j];
            pos += m_Increments[2];
            j++;
        }
        break;
    default:
        //do nothing
        break;
    }
}
//-------------------------------------------------------------------------
#ifndef MITK_VER_OOC
namespace MITK_VOL_ITERATOR
{

static bool GenerateVolumeIterator(mitkVolume* vol, mitkVolumeIteratorBase* &it, bool autorelease = false)
{
    if( it != NULL && autorelease)
    {
        delete it;
    }

    bool run_flag = true;

    switch(vol->GetDataType()) 
    {
    case MITK_DOUBLE:
        it =  new mitkVolumeIterator<double>(vol); 
        break;
    case MITK_FLOAT:
        it = new mitkVolumeIterator<float>(vol); 
        break;
    case MITK_LONG:
        it = new mitkVolumeIterator<long>(vol); 
        break;
    case MITK_UNSIGNED_LONG:
        it = new mitkVolumeIterator<unsigned long>(vol); 
        break;
    case MITK_INT:
        it = new mitkVolumeIterator<int>(vol); 
        break;
    case MITK_UNSIGNED_INT:
        it = new mitkVolumeIterator<unsigned int>(vol); 
        break;
    case MITK_SHORT:
        it = new mitkVolumeIterator<short>(vol); 
        break;
    case MITK_UNSIGNED_SHORT:
        it = new mitkVolumeIterator<unsigned short>(vol); 
        break;
    case MITK_CHAR:
        it = new mitkVolumeIterator<char>(vol); 
        break;
    case MITK_UNSIGNED_CHAR:
        it = new mitkVolumeIterator<unsigned char>(vol); 
        break;
    default:
        it = NULL; 
        run_flag = false;
    }
    return run_flag;
}

} // END namespace MITK_VOL_ITERATOR

#endif //MITK_VER_OOC

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
 
//#define DEFINED_mitkVolumeIterator



#endif

