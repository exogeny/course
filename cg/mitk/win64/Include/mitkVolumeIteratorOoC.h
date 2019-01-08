/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeIteratorOoC_h
#define __mitkVolumeIteratorOoC_h

#ifdef MITK_VER_OOC

#include "mitkOoCVolume.h"
#include "mitkVolumeIterator.h"

#define MITK_VOL_ITREATOR_IO_MODE_READ          1
#define MITK_VOL_ITERATOR_IO_MODE_WRITE         2
#define MITK_VOL_ITERATOR_IO_MODE_READWRITE     3

/// mitkVolumeIteratorOoC -
///////////////////////////////////////////////////////////////////////////
/// mitkVolumeIteratorOoC
///

template<class T>
class mitkOoCVolumeIterator : public mitkVolumeIterator<T>
{
protected:
    virtual void init();
    virtual void initRegion();

    int         m_CurrentSliceNum;
    int         m_IOMode;
    T*          m_XZSliceData;
    int         m_XZSliceNum;
    bool        m_FlagWriteXZSlice;

public: 
    mitkOoCVolumeIterator();

    mitkOoCVolumeIterator(mitkVolume* vol);

    mitkOoCVolumeIterator(mitkVolume* vol, VectorIndexType& region);

    ~mitkOoCVolumeIterator();

    void SetIOMode(int mode) 
    {
        m_IOMode = mode;

        this->m_Volume->UnFreezeSlice(m_CurrentSliceNum);

        m_CurrentSliceNum = 0;
        switch(m_IOMode)
        {
        case MITK_VOL_ITREATOR_IO_MODE_READ:
            this->m_DataPointer = (T*) this->m_Volume->GetSliceForRead(m_CurrentSliceNum);
            break;
        case MITK_VOL_ITERATOR_IO_MODE_WRITE:
            this->m_DataPointer = (T*) this->m_Volume->GetSliceForWrite(m_CurrentSliceNum);
            break;
        case MITK_VOL_ITERATOR_IO_MODE_READWRITE:
            this->m_DataPointer = (T*) this->m_Volume->GetSliceForReadWrite(m_CurrentSliceNum);
            break;
        default:
            this->m_DataPointer = (T*) this->m_Volume->GetSliceForReadWrite(m_CurrentSliceNum);
        }

        this->m_Volume->FreezeSlice(m_CurrentSliceNum);
    }

    void MakeCurrentSlice(int slice_num)
    {
        if(m_CurrentSliceNum == slice_num) return;

//      this->m_Volume->UnFreezeSlice(m_CurrentSliceNum);

        m_CurrentSliceNum = slice_num;
        switch(m_IOMode)
        {
        case MITK_VOL_ITREATOR_IO_MODE_READ:
            this->m_DataPointer = (T*) this->m_Volume->GetSliceForRead(m_CurrentSliceNum);
            break;
        case MITK_VOL_ITERATOR_IO_MODE_WRITE:
            this->m_DataPointer = (T*) this->m_Volume->GetSliceForWrite(m_CurrentSliceNum);
            break;
        case MITK_VOL_ITERATOR_IO_MODE_READWRITE:
            this->m_DataPointer = (T*) this->m_Volume->GetSliceForReadWrite(m_CurrentSliceNum);
            break;
        default:
            this->m_DataPointer = (T*) this->m_Volume->GetSliceForReadWrite(m_CurrentSliceNum);
        }
        
//      this->m_Volume->FreezeSlice(m_CurrentSliceNum);
    }

    bool WriteXZSliceToVolume(int yIdx, void *src);

    void MakeXZSlice(int slice_num)
    {
        if(m_XZSliceNum == slice_num) return;

        if(m_XZSliceData == NULL)
        {
            m_XZSliceData = new T [this->m_Volume->GetWidth() * this->m_Volume->GetSliceNum()];
        }

        if(m_FlagWriteXZSlice)
        {
            this->WriteXZSliceToVolume(m_XZSliceNum,m_XZSliceData);
            m_FlagWriteXZSlice = false;
        }

        this->m_Volume->ReadXZSliceData(slice_num, m_XZSliceData);
        m_XZSliceNum = slice_num;
        this->m_DataPointer = m_XZSliceData;
    }

    ScalarIndexType ComputeXZSliceOffset(const VectorIndexType& index)
    {
        this->MakeXZSlice(index[1]);

        ScalarIndexType offset = 0;
        offset += index[0] * this->m_Increments[0];
        offset += index[2] * this->m_Increments[1];

        return offset;
    }

    virtual ScalarIndexType ComputeOffset(const VectorIndexType& index)
    {
        this->MakeCurrentSlice(index[2]);

        ScalarIndexType offset = 0;
        for(unsigned int i=0;i<this->m_ImageDimension - 1;i++)
        {
            offset += index[i] * this->m_Increments[i];
        }
        return offset;
    }

    virtual ScalarIndexType ComputeOffset(const ScalarIndexType* index)
    {
        this->MakeCurrentSlice(index[2]);

        ScalarIndexType offset = 0;
        for(unsigned int i=0;i<this->m_ImageDimension - 1;i++)
        {
            offset += index[i] * this->m_Increments[i];
        }
        return offset;
    }

    virtual ScalarIndexType ComputeOffset(const ScalarIndexType x, const ScalarIndexType y, const ScalarIndexType z)
    {
        this->MakeCurrentSlice(z);

        ScalarIndexType offset = 0;
        offset += x * this->m_Increments[0];
        offset += y * this->m_Increments[1];
        return offset;
    }

    virtual void SetVolume(mitkVolume* vol);

    virtual void GetSequence(ScalarPixelType* values, int mode);
    virtual void SetSequence(const ScalarPixelType* values, int mode);

    virtual void GetNeighbors2x(const ScalarIndexType* index, ScalarPixelType* value, int ch=0);
    virtual void GetNeighbors4x(const ScalarIndexType* index, ScalarPixelType* value, int ch=0);

    virtual void GoToBegin(void);
    virtual void GoToEnd(void);
    virtual void GoToNextRow(void);
    virtual void GoToNextCol(void);
    virtual void GoToNextSlice(void);
    virtual void GoToNextX(int mode);

    virtual void SetIndex(const VectorIndexType &ind);

    virtual void operator++();
    virtual void operator--();

private:
    mitkOoCVolumeIterator(const mitkOoCVolumeIterator&);
    void operator=(const mitkOoCVolumeIterator&);

};

///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
template<class T>
mitkOoCVolumeIterator<T>::mitkOoCVolumeIterator()
{
    m_IOMode = MITK_VOL_ITERATOR_IO_MODE_READWRITE;
    this->m_Begin = this->m_End = NULL;
    m_XZSliceData = NULL;
}
//-------------------------------------------------------------------------
template<class T>
mitkOoCVolumeIterator<T>::mitkOoCVolumeIterator(mitkVolume* vol)
{
    m_IOMode = MITK_VOL_ITERATOR_IO_MODE_READWRITE;
    this->m_Begin = this->m_End = NULL;
    m_XZSliceData = NULL;

    this->m_Remaining = false;
    this->m_ImageDimension = 0;
    this->m_NumberOfChannels = 0;
    this->m_DefaultChannel = 0;

    this->SetVolume(vol);
}
//-------------------------------------------------------------------------
template<class T>
mitkOoCVolumeIterator<T>::mitkOoCVolumeIterator(mitkVolume* vol, VectorIndexType& region)
{
    m_IOMode = MITK_VOL_ITERATOR_IO_MODE_READWRITE;
    this->m_Begin = this->m_End = NULL;
    m_XZSliceData = NULL;

    this->m_Remaining = false;
    this->m_ImageDimension = 0;
    this->m_NumberOfChannels = 0;
    this->m_DefaultChannel = 0;

    this->SetRegion(region);
    this->SetVolume(vol);
}
//-------------------------------------------------------------------------
template<class T>
mitkOoCVolumeIterator<T>::~mitkOoCVolumeIterator()
{
    if(m_XZSliceData)
    {
        delete [] m_XZSliceData;
        m_XZSliceData = NULL;
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::init()  //after set volume
{
    this->m_BeginIndex = VectorIndexType(this->m_ImageDimension, 0);
    this->m_EndIndex = VectorIndexType(this->m_ImageDimension, 0);

    this->initRegion();

    // initialize increment table for 2x neighbors
    this->m_IncremetTable[0] = 0;
    this->m_IncremetTable[1] = this->m_Increments[0];
    this->m_IncremetTable[2] = this->m_Increments[1];
    this->m_IncremetTable[3] = this->m_Increments[1] + this->m_Increments[0];
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::initRegion()
{
    unsigned int i;

    for(i=0;i<this->m_ImageDimension;i++)
    {
        this->m_BeginIndex[i] = this->m_Region[2*i];
        this->m_EndIndex[i] = this->m_Region[2*i+1];
    }

    this->GoToBegin();

    // initialize offset table
    for(i=0;i<this->m_ImageDimension;i++)
    {
        this->m_OffsetTable[i] = this->m_Increments[i] * (this->m_Region[2*i+1] - this->m_Region[2*i] /* -1 */);
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::SetVolume(mitkVolume* vol)
{
    if(vol == NULL) return;

    // out-of-core volume check
    if(vol->GetDataObjectType() != MITK_OOC_VOLUME)
    {
        //MITK_REG_GLOBAL::RegMessage("mitkOoCVolumeIterator can't handle in-core volume.");
        return;
    }

    if(vol->GetSliceNum() <= 1)
    {
        //MITK_REG_GLOBAL::RegMessage("mitkOoCVolumeIterator can't handle non-3D volume.");
        return;
    }

    // volume pointer copy
    this->m_Volume = vol;

    // volume data buffer
    m_CurrentSliceNum = -1;
    this->MakeCurrentSlice(0);

    m_XZSliceNum = -1;
    m_FlagWriteXZSlice = false;

    this->m_ImageDimension = 3;
    this->m_NumberOfChannels  = this->m_Volume->GetNumberOfChannel();

    // volume dimensions
    this->m_Volume->GetDimensions(this->m_Dimensions);

    for(unsigned int i = 0;i<this->m_ImageDimension;i++)
        this->m_Dimensions2[i] = 2 * this->m_Dimensions[i] - 2;

    // volume increments
    this->m_Volume->GetIncrements(this->m_Increments);

    if(this->m_Region.size() == 0)  //otherwise: image region was already set
    {
        this->GetEntireImageRegion();
    }

    this->init();
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::GoToBegin(void)
{
    this->m_PositionIndex = this->m_BeginIndex;

    ScalarIndexType offset = this->ComputeOffset(this->m_BeginIndex);
    this->m_Position = this->m_DataPointer + offset;

    if( this->GetNumberOfPixelsInRegion() )
    {
        this->m_Remaining = true;
    }
    else
    {
        this->m_Remaining = false;
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::GoToEnd(void)
{
    this->m_PositionIndex = this->m_EndIndex;

    ScalarIndexType offset = this->ComputeOffset(this->m_EndIndex);
    this->m_Position = this->m_DataPointer + offset;

    this->m_Remaining = false;
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::GoToNextRow(void)
{
    this->m_Position -= (this->m_PositionIndex[0] - this->m_BeginIndex[0]) * this->m_Increments[0];
    this->m_PositionIndex[0] = this->m_BeginIndex[0];

    this->m_Remaining = false;
    for( unsigned int i=1; i<this->m_ImageDimension; i++ )
    {
        this->m_PositionIndex[i]++;
        if( this->m_PositionIndex[i] <= this->m_EndIndex[i] )
        {
            if(i != 2){
                this->m_Position += this->m_Increments[i];
            }
            else {
                ScalarIndexType offset = this->ComputeOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
            this->m_Remaining = true;
            break;
        }
        else 
        {
            this->m_PositionIndex[i] = this->m_BeginIndex[i];

            if(i != 2) {
                this->m_Position -= this->m_OffsetTable[i];
            }
            else {
                ScalarIndexType offset = this->ComputeOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
        }
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::GoToNextCol(void)
{
    this->m_Position -= (this->m_PositionIndex[1]- this->m_BeginIndex[1]) * this->m_Increments[1];
    this->m_PositionIndex[1] = this->m_BeginIndex[1];

    this->m_Remaining = false;
    for( unsigned int i=0; i<this->m_ImageDimension; i++ )
    {
        if(i==1) continue;

        this->m_PositionIndex[i]++;
        if( this->m_PositionIndex[i] <= this->m_EndIndex[i] )
        {
            if(i != 2){
                this->m_Position += this->m_Increments[i];
            }
            else {
                ScalarIndexType offset = this->ComputeOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
            this->m_Remaining = true;
            break;
        }
        else 
        {
            this->m_PositionIndex[i] = this->m_BeginIndex[i];

            if(i != 2) {
                this->m_Position -= this->m_OffsetTable[i];
            }
            else {
                ScalarIndexType offset = this->ComputeOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
        }
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::GoToNextSlice(void)
{
    this->m_Position -= (this->m_PositionIndex[2]- this->m_BeginIndex[2]) * this->m_Increments[1];
    this->m_PositionIndex[2] = this->m_BeginIndex[2];

    this->m_Remaining = false;
    for( unsigned int i=0; i<this->m_ImageDimension-1; i++ )
    {
        this->m_PositionIndex[i]++;
        if( this->m_PositionIndex[i] <= this->m_EndIndex[i] )
        {
            if(i == 0) {
                this->m_Position += this->m_Increments[i];
            }
            else {
                ScalarIndexType offset = this->ComputeXZSliceOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
            this->m_Remaining = true;
            break;
        }
        else 
        {
            this->m_PositionIndex[i] = this->m_BeginIndex[i];

            if(i == 0) {
                this->m_Position -= this->m_OffsetTable[i];
            }
            else {
                ScalarIndexType offset = this->ComputeXZSliceOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
        }
    }

    if(!this->m_Remaining)
    {
        if(m_XZSliceData)
        {
            delete [] m_XZSliceData;
            m_XZSliceData = NULL;
        }
        this->MakeCurrentSlice(0);
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::GoToNextX(int mode)
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
void mitkOoCVolumeIterator<T>::SetIndex(const VectorIndexType &ind)
{
    this->m_PositionIndex = ind; 

    ScalarIndexType offset = this->ComputeOffset(ind);
    this->m_Position = this->m_DataPointer + offset;     
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::operator++()
{
    this->m_Remaining = false;
    for( unsigned int i=0; i<this->m_ImageDimension; i++ )
    {
        this->m_PositionIndex[i]++;
        if( this->m_PositionIndex[i] <= this->m_EndIndex[i] )
        {
            if(i != 2){
                this->m_Position += this->m_Increments[i];
            }
            else {
                ScalarIndexType offset = this->ComputeOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
            this->m_Remaining = true;
            break;
        }
        else 
        {
            this->m_PositionIndex[i] = this->m_BeginIndex[i];

            if(i != 2) {
                this->m_Position -= this->m_OffsetTable[i];
            }
            else {
                ScalarIndexType offset = this->ComputeOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
        }
    }

    if( !this->m_Remaining )
    {
        this->GoToEnd();
    }
}
//-------------------------------------------------------------------------
template<class T>
void mitkOoCVolumeIterator<T>::operator--()
{
    this->m_Remaining = false;
    for( unsigned int i=0; i<this->m_ImageDimension; i++ )
    {
        if( this->m_PositionIndex[i] > this->m_BeginIndex[i] )
        {
            this->m_PositionIndex[i]--;
            if(i != 2){
                this->m_Position -= this->m_Increments[i];
            }
            else {
                ScalarIndexType offset = this->ComputeOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
            
            this->m_Remaining = true;
            break;
        }
        else 
        {
            this->m_PositionIndex[i] = this->m_EndIndex[i]; 

            if(i != 2){
                this->m_Position += this->m_OffsetTable[i];
            }
            else{
                ScalarIndexType offset = this->ComputeOffset(this->m_PositionIndex);
                this->m_Position = this->m_DataPointer + offset;
            }
        }
    }

    if( !this->m_Remaining )
    {
        this->GoToEnd();
    }
}
//-------------------------------------------------------------------------
template<class T>
inline void mitkOoCVolumeIterator<T>::GetNeighbors2x(const ScalarIndexType* index, ScalarPixelType* value, int ch)
{
    ScalarIndexType offset = this->ComputeOffset(index);
    T* pos = this->m_DataPointer + offset + ch;

    value[0] = static_cast<ScalarPixelType>( *(pos) );                          // (i  , j  , k  )
    value[1] = static_cast<ScalarPixelType>( *(pos + this->m_IncremetTable[1]) );       // (i+1, j  , k  )
    value[2] = static_cast<ScalarPixelType>( *(pos + this->m_IncremetTable[2]) );       // (i  , j+1, k  )
    value[3] = static_cast<ScalarPixelType>( *(pos + this->m_IncremetTable[3]) );       // (i+1, j+1, k  )

    offset = this->ComputeOffset(index[0], index[1], index[2]+1);
    pos = this->m_DataPointer + offset + ch;
    value[4] = static_cast<ScalarPixelType>( *(pos) );                          // (i  , j  , k+1)
    value[5] = static_cast<ScalarPixelType>( *(pos + this->m_IncremetTable[1]) );       // (i+1, j  , k+1)
    value[6] = static_cast<ScalarPixelType>( *(pos + this->m_IncremetTable[2]) );       // (i  , j+1, k+1)
    value[7] = static_cast<ScalarPixelType>( *(pos + this->m_IncremetTable[3]) );   // (i+1, j+1, k+1)
}
//-------------------------------------------------------------------------
template<class T>
inline void mitkOoCVolumeIterator<T>::GetNeighbors4x(const ScalarIndexType* index, ScalarPixelType* value, int ch)
{
    unsigned int i,j;
    ScalarIndexType nIndex[3][4];

    for(i=0;i<this->m_ImageDimension;i++) {
        for (j = 0; j < 4; j++)
        {
            nIndex[i][j] = index[i] - 1 + j;

            if(this->m_Dimensions[i] == 1)
            {
                nIndex[i][j] = 0;
            }
            else
            {
                if(nIndex[i][j] < 0)
                {
                    nIndex[i][j] = -nIndex[i][j] - this->m_Dimensions2[i] * ((-nIndex[i][j]) / this->m_Dimensions2[i]);
                }
                else
                {
                    nIndex[i][j] = nIndex[i][j] - this->m_Dimensions2[i] * (nIndex[i][j] / this->m_Dimensions2[i]);
                }
            }

            if (this->m_Dimensions[i] <= nIndex[i][j]) 
            {
                nIndex[i][j] = this->m_Dimensions2[i] - nIndex[i][j];
            }
        }
    }

    for(unsigned int k = 0; k < 4; k++) {
        for(j = 0; j < 4; j++) {
            for(i = 0; i < 4; i++) {
                this->MakeCurrentSlice(nIndex[2][k]);
                value[i+4*j+16*k] = static_cast<ScalarPixelType>
                    (this->m_DataPointer[this->m_Increments[1] * nIndex[1][j] + this->m_Increments[0] * nIndex[0][i] + ch]);
            }
        }
    }
}
//-------------------------------------------------------------------------
template<class T>
inline void mitkOoCVolumeIterator<T>::GetSequence(ScalarPixelType* values, int mode)
{
    //a. read a sequence (suppose the pointer is already in the beginning of the sequence)
    //b. move pointer to next sequence start position
    //c. do NOT need iterator operation ++ / --

    /* mode :   0  by row
     *          1  by col
     *          2  by z-direction */

    int i,j=0;
    T* pos = this->m_Position;
    switch(mode)
    {
    case 0:
        for(i=this->m_Region[0];i<=this->m_Region[1];i++)
        {
            values[j] = (ScalarPixelType) *(pos+this->m_DefaultChannel);
            pos += this->m_Increments[0];
            j++;
        }
        break;
    case 1:
        for(i=this->m_Region[2];i<=this->m_Region[3];i++)
        {
            values[j] = (ScalarPixelType) *(pos+this->m_DefaultChannel);
            pos += this->m_Increments[1];
            j++;
        }
        break;
    case 2:
        if( m_XZSliceData == NULL )
        {
            ScalarIndexType offset = this->ComputeXZSliceOffset(this->m_PositionIndex);
            pos = this->m_Position = this->m_DataPointer + offset;
        }

        for(i=this->m_Region[4];i<=this->m_Region[5];i++)
        {
            values[j] = (ScalarPixelType) *(pos+this->m_DefaultChannel);
            pos += this->m_Increments[1];
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
inline void mitkOoCVolumeIterator<T>::SetSequence(const ScalarPixelType* values, int mode)
{
    int i,j=0;
    T* pos = this->m_Position;
    switch(mode)
    {
    case 0:
        for(i=this->m_Region[0];i<=this->m_Region[1];i++)
        {
            *(pos+this->m_DefaultChannel) = (T) values[j];
            pos += this->m_Increments[0];
            j++;
        }
        break;
    case 1:
        for(i=this->m_Region[2];i<=this->m_Region[3];i++)
        {
            *(pos+this->m_DefaultChannel) = (T) values[j];
            pos += this->m_Increments[1];
            j++;
        }
        break;
    case 2:
        if( m_XZSliceData == NULL )
        {
            ScalarIndexType offset = this->ComputeXZSliceOffset(this->m_PositionIndex);  /* FIXME */
            pos = this->m_Position = this->m_DataPointer + offset;
        }

        for(i=this->m_Region[4];i<=this->m_Region[5];i++)
        {
            *(pos+this->m_DefaultChannel) = (T) values[j];
            pos += this->m_Increments[1];
            j++;
        }
        m_FlagWriteXZSlice = true;
        break;
    default:
        //do nothing
        break;
    }
}
//-------------------------------------------------------------------------
template<class T>
bool mitkOoCVolumeIterator<T>::WriteXZSliceToVolume(int yIdx, void *src)
{
    if (yIdx<0 || yIdx>=this->m_Volume->GetHeight() || src==NULL) return false;

    int lineSize = this->m_Volume->GetDataTypeSize() * this->m_Volume->GetIncrementY();
    int dstSkip = yIdx * lineSize;

    char *dstPtr;
    char *srcPtr = (char *)src;

    for (int slice = 0; slice < this->m_Volume->GetSliceNum(); ++slice, srcPtr+=lineSize)
    {
        dstPtr = (char *)this->m_Volume->GetSliceForReadWrite(slice); /* FIXME */
        if (dstPtr)
        {
            memcpy(dstPtr+dstSkip, srcPtr, lineSize);
        }
    }

    return true;
}
//-------------------------------------------------------------------------
namespace MITK_VOL_ITERATOR
{

static bool GenerateVolumeIterator(mitkVolume* vol, mitkVolumeIteratorBase* &it, bool autorelease = false)
{
    if( it != NULL && autorelease)
    {
        delete it;
    }

    bool run_flag = true;

    if(vol->GetDataObjectType() == MITK_IC_VOLUME)
    {
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
    }
    else if(vol->GetDataObjectType() == MITK_OOC_VOLUME)
    {
        switch(vol->GetDataType()) 
        {
        case MITK_DOUBLE:
            it =  new mitkOoCVolumeIterator<double>(vol); 
            break;
        case MITK_FLOAT:
            it = new mitkOoCVolumeIterator<float>(vol); 
            break;
        case MITK_LONG:
            it = new mitkOoCVolumeIterator<long>(vol); 
            break;
        case MITK_UNSIGNED_LONG:
            it = new mitkOoCVolumeIterator<unsigned long>(vol); 
            break;
        case MITK_INT:
            it = new mitkOoCVolumeIterator<int>(vol); 
            break;
        case MITK_UNSIGNED_INT:
            it = new mitkOoCVolumeIterator<unsigned int>(vol); 
            break;
        case MITK_SHORT:
            it = new mitkOoCVolumeIterator<short>(vol); 
            break;
        case MITK_UNSIGNED_SHORT:
            it = new mitkOoCVolumeIterator<unsigned short>(vol); 
            break;
        case MITK_CHAR:
            it = new mitkOoCVolumeIterator<char>(vol); 
            break;
        case MITK_UNSIGNED_CHAR:
            it = new mitkOoCVolumeIterator<unsigned char>(vol); 
            break;
        default:
            it = NULL; 
            run_flag = false;
        }
    }

    return run_flag;
}

} // END namespace MITK_VOL_ITERATOR
//-------------------------------------------------------------------------


//#define DEFINED_mitkVolumeIteratorOoC



#endif  // END IF DEFINED OF MITK_VER_OOC

#endif

