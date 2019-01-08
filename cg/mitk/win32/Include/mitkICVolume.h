/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkICVolume_h
#define __mitkICVolume_h

#include "mitkVolume.h"

/// mitkICVolume - a concrete data object to represent an in-core multi-dimensional medical image dataset
///////////////////////////////////////////////////////////////////////////
/// mitkICVolume is a concrete data object to represent an in-core
/// multi-dimensional medical image dataset.
class MITK_COMMON_API mitkICVolume : public mitkVolume
{
public:
    MITK_TYPE(mitkICVolume, mitkVolume)

    virtual void PrintSelf(ostream& os);

    ///////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////
    mitkICVolume();

    ///////////////////////////////////////////////////////////////////////////
    /// Return the data object type.
    /// \return Always return MITK_IN_CORE_VOLUME
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const { return MITK_IC_VOLUME; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of the volume data (unchangeable). 
    /// \return Return a void pointer to const data.
    /// \note The returned type is void const *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    ///////////////////////////////////////////////////////////////////////////
    virtual void const* GetData() const { return m_Data; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of the volume data (changeable). 
    /// \return Return a void pointer to data.
    /// \note The returned type is void *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void* GetData() { return m_Data; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of a specified slice in the volume (for read only).
    /// \param sliceIdx the index of the slice to get (in [0, GetImageNum()-1])
    /// \return Return a const void pointer to data.
    /// \note The returned type is void const *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void const* GetSliceForRead(int sliceIdx);

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of a specified slice in the volume (for write only).
    /// \param sliceIdx the index of the slice to get (in [0, GetImageNum()-1])
    /// \return Return a const void pointer to data.
    /// \note The returned type is void *, it should be converted to some
    ///       useful data type according to the return value of GetDataType().
    ///       This function returns an empty buffer for writing the specified
    ///       slice the first time.
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void* GetSliceForWrite(int sliceIdx);

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of a specified slice in the volume (changeable).
    /// \param sliceIdx the index of the slice to get (in [0, GetImageNum()-1])
    /// \return Return a void pointer to data.
    /// \note The returned type is void *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void* GetSliceForReadWrite(int sliceIdx);

    ///////////////////////////////////////////////////////////////////////////
    /// Copy slice data from the volume to a specified memory buffer.
    /// \param sliceIdx the index of the slice to read (in [0, GetImageNum()-1])
    /// \param dst the pointer to the destination memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of destination memory buffer should be
    ///       GetWidth() * GetHeight() * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool ReadSliceData(int sliceIdx, void *dst);

    ///////////////////////////////////////////////////////////////////////////
    /// Copy x-directional slice from the volume to a specified memory buffer.
    /// \param xIdx the position of the x-directional slice to read (in [0, GetWidth()-1])
    /// \param dst the pointer to the destination memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of destination memory buffer should be
    ///       GetHeight() * GetImageNum() * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool ReadYZSliceData(int xIdx, void *dst);

    ///////////////////////////////////////////////////////////////////////////
    /// Copy y-directional slice from the volume to a specified memory buffer.
    /// \param yIdx the position of the y-directional slice to read (in [0, GetHeight()-1])
    /// \param dst the pointer to the destination memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of destination memory buffer should be
    ///       GetWidth() * GetImageNum() * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool ReadXZSliceData(int yIdx, void *dst);

    ///////////////////////////////////////////////////////////////////////////
    /// Get arbitrary directional slice from the volume to a specified memory
    /// buffer (i.e. re-slicing).
    /// \param w width of the new slice (in pixels)
    /// \param h height of the new slice (in pixels)
    /// \param o start position (left-bottom) of the new slice in the volume space
    /// \param ux the step (in pixels) vector of moving to the next pixel along the
    ///           x-direction of the new slice in the volume space
    /// \param uy the step (in pixels) vector of moving to the next pixel along the
    ///           y-direction of the new slice in the volume space
    /// \param dst the pointer to the destination memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of destination memory buffer should be
    ///       w * h * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool GetArbitrarySlice(int w, int h, double o[3], double ux[3], double uy[3], void *dst);

    ///////////////////////////////////////////////////////////////////////////
    /// Copy slice data from a specified memory buffer to the volume.
    /// \param sliceIdx the index of the slice to write (in [0, GetImageNum()-1])
    /// \param src the pointer to the source memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of source memory buffer should be
    ///       GetWidth() * GetHeight() * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool WriteSliceData(int sliceIdx, void const *src);

    ///////////////////////////////////////////////////////////////////////////
    /// Copy a sub-volume (start position = (x, y, z), size = w * h * d) from the
    /// volume to a specified memory buffer.
    /// \param x the x-coordinate of the start point
    /// \param y the y-coordinate of the start point
    /// \param z the z-coordinate of the start point
    /// \param w the width of the sub-volume
    /// \param h the height of the sub-volume
    /// \param d the depth of the sub-volume
    /// \param tw return the true width of the sub-volume copied (in case that
    ///           x+w > GetWidth())
    /// \param th return the true height of the sub-volume copied (in case that
    ///           y+h > GetHeight())
    /// \param td return the true depth of the sub-volume copied (in case that
    ///           z+d > GetSliceNum())
    /// \param dst the pointer to the destination memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of destination memory buffer should be
    ///       w * h * d * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool ReadSubVolume(int x, int y, int z, int w, int h, int d, int &tw, int &th, int &td, void *dst);

    virtual bool ReadSubVolume(int x, int y, int z, int w, int h, int d,
        int dstx, int dsty, int dstz, int dstw, int dsth, int dstd,
        void *dst, bool zeropad=true);

    virtual bool ReadSubVolume(int x, int y, int z, int w, int h, int d, void *dst, bool zeropad=true);

    ///////////////////////////////////////////////////////////////////////////
    /// Copy a sub-volume (start position = (x, y, z), size = w * h * d) from a
    /// specified memory buffer to the volume.
    /// \param x the x-coordinate of the start point
    /// \param y the y-coordinate of the start point
    /// \param z the z-coordinate of the start point
    /// \param w the width of the sub-volume
    /// \param h the height of the sub-volume
    /// \param d the depth of the sub-volume
    /// \param tw return the true width of the sub-volume copied (in case that
    ///           x+w > GetWidth())
    /// \param th return the true height of the sub-volume copied (in case that
    ///           y+h > GetHeight())
    /// \param td return the true depth of the sub-volume copied (in case that
    ///           z+d > GetSliceNum())
    /// \param src the pointer to the source memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of source memory buffer should be
    ///       w * h * d * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool WriteSubVolume(int x, int y, int z, int w, int h, int d, int &tw, int &th, int &td, void const *src);

    ///////////////////////////////////////////////////////////////////////////
    /// Allocate necessary space for holding the image data. It calculate the
    /// memory size using current Dimensions, DataType and NumberOfChannel
    /// settings. The equation is shown as follow: \n
    /// Width * Height * SliceNum * sizeof(DataType) * NumberOfChannel \n
    /// The previous allocated data will be deleted if exists.
    /// \return Return true if successful, otherwise return false.
    /////////////////////////////////////////////////////////////////////////// 
    virtual bool Allocate();

    ///////////////////////////////////////////////////////////////////////////
    /// Return the actual memory size occupied by the volume data. The unit is BYTE.
    /// \return Return the actual memory size occupied by this volume. The unit is BYTE.
    ///////////////////////////////////////////////////////////////////////////
    virtual unsigned long long GetActualMemorySize() const;

    ///////////////////////////////////////////////////////////////////////////
    /// Delete the allocated memory (if any) and initialize to default status.
    ///////////////////////////////////////////////////////////////////////////
    virtual void Initialize();

    ///////////////////////////////////////////////////////////////////////////
    /// \warning Don't call this function directly.
    ///////////////////////////////////////////////////////////////////////////
    virtual void ShallowCopy(mitkDataObject *src);

    ///////////////////////////////////////////////////////////////////////////
    /// \warning Don't call this function directly.
    ///////////////////////////////////////////////////////////////////////////
    virtual void DeepCopy(mitkDataObject *src);

protected:
    virtual ~mitkICVolume();    

    void  *m_Data;

private:
    mitkICVolume(const mitkICVolume&);
    void operator=(const mitkICVolume&);

};

#endif


