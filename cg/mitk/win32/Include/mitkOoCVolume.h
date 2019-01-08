/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkOoCVolume_h
#define __mitkOoCVolume_h

#include "mitkVolume.h"

class SliceHeapNode;
class SliceHeap;
class SliceBufferBlockNode;
class SliceBufferFreeQueue;

class mitkThreadDelegate;
class mitkSemaphore;

class mitkOoCVolume;
template <class UserClass> class mitkOoCIODelegate;
typedef mitkOoCIODelegate<mitkOoCVolume> mitkOoCVolumeIODelegate;

/// mitkOoCVolume - a concrete data object to represent a out-of-core multi-dimensional medical image dataset
///////////////////////////////////////////////////////////////////////////
/// mitkOoCVolume is a concrete data object to represent a out-of-core
/// multi-dimensional medical image dataset.
class MITK_COMMON_API mitkOoCVolume : public mitkVolume
{
public:
    MITK_TYPE(mitkOoCVolume, mitkVolume)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////////
    mitkOoCVolume();
    
    ///////////////////////////////////////////////////////////////////////////
    /// Return the data object type.
    /// \return Always return MITK_OUT_OF_CORE_VOLUME
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const { return MITK_OOC_VOLUME; }

    ///////////////////////////////////////////////////////////////////////////
    /// You can not get a permanent pointer to the entire volume data since
    /// it can not be loaded to the main memory all together, so do not call
    /// this function when using a mitkOoCVolume object, and it will always
    /// return NULL.
    /// \return Return NULL.
    /// \warning Do not call this function to get volume data. Use GetSliceData()
    ///          or ReadSliceData() instead.
    ///////////////////////////////////////////////////////////////////////////
    virtual void const* GetData() const { return NULL; }

    ///////////////////////////////////////////////////////////////////////////
    /// You can not get a permanent pointer to the entire volume data since
    /// it can not be loaded to the main memory all together, so do not call
    /// this function when using a mitkOoCVolume object, and it will always
    /// return NULL.
    /// \return Return NULL.
    /// \warning Do not call this function to get volume data. Use GetSliceData()
    ///          or ReadSliceData() instead.
    ///////////////////////////////////////////////////////////////////////////
    virtual void* GetData() { return NULL; }

    ///////////////////////////////////////////////////////////////////////////
    /// Lock the physical memory containing sliceIdx'th slice data. (only useful
    /// for out-of-core volume data (mitkOoCVolume) to avoid swapping some slice
    /// data from memory buffer to disk buffer, i.e. to keep the returned pointer
    /// of some 'Get' functions, such as GetSliceData(), GetSliceForRead() and
    /// so on, always be valid until call UnFreezeSlice().
    /// \param sliceIdx the index of the slice to freeze.
    ///////////////////////////////////////////////////////////////////////////
    virtual void FreezeSlice(int sliceIdx);

    ///////////////////////////////////////////////////////////////////////////
    /// Unlock the physical memory containing sliceIdx'th slice data.
    /// \param sliceIdx the index of the slice to un-freeze.
    /// \see FreezeSlice()
    ///////////////////////////////////////////////////////////////////////////
    virtual void UnFreezeSlice(int sliceIdx);

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of a specified slice in the volume (for read only).
    /// \param sliceIdx the index of the slice to get (in [0, GetImageNum()-1])
    /// \return Return a const void pointer to data.
    /// \note The returned type is void const *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///          The returned value is not a permanently valid pointer. After
    ///          the next call of this function, the previous returned pointer
    ///          could be invalid or point to another slice. Use this function
    ///          carefully.
    ///////////////////////////////////////////////////////////////////////////
    virtual void const* GetSliceForRead(int sliceIdx);

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of a specified slice in the volume (for write only).
    /// \param sliceIdx the index of the slice to get (in [0, GetImageNum()-1])
    /// \return Return a const void pointer to data.
    /// \note The returned type is void *, it should be converted to some
    ///       useful data type according to the return value of GetDataType().
    ///       This function returns an empty buffer for writing the specified
    ///       slice at FIRST time, and it will not load any data from the disk
    ///       buffer even if the specified slice has already contained data
    ///       in the disk buffer, so don't use it if you really want GetSliceForReadWrite().
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///          The returned value is not a permanently valid pointer. After
    ///          the next call of this function, the previous returned pointer
    ///          could be invalid or point to another slice. Use this function
    ///          carefully.
    ///////////////////////////////////////////////////////////////////////////
    virtual void* GetSliceForWrite(int sliceIdx);

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of a specified slice in the volume (for read & write).
    /// \param sliceIdx the index of the slice to get (in [0, GetImageNum()-1])
    /// \return Return a const void pointer to data.
    /// \note The returned type is void *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///          The returned value is not a permanently valid pointer. After
    ///          the next call of this function, the previous returned pointer
    ///          could be invalid or point to another slice. Use this function
    ///          carefully.
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
    /// Generate the buffer for the volume data on disk and allocate necessary
    /// space in memory for holding the buffered image data. 
    /// The previous allocated data will be deleted if exists.
    /// \return Return true if successful, otherwise return false.
    /////////////////////////////////////////////////////////////////////////// 
    virtual bool Allocate();

    ///////////////////////////////////////////////////////////////////////////
    /// Return the actual memory size occupied by the buffered volume data. The unit is BYTE.
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

    ///////////////////////////////////////////////////////////////////////////
    /// Set the modified flag of the sliceIdx'th slice.
    /// \param sliceIdx the index of the slice to set
    /// \param modified whether the slice data is modified
    /// \note Call this function to ensure the specified slice written back to
    ///       disk, when you use GetSliceData() to get the pointer
    ///       to a slice data and change its content subsequently.
    ///////////////////////////////////////////////////////////////////////////
    void SetSliceDataModified(int sliceIdx, bool modified = true);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the memory buffer for containing cached slices.
    /// \param s the size of the buffer in bytes
    /// \note When calling this function, the number of buffered slice is also
    ///       calculated by (buffer size) / (slice size), so it is unnecessary
    ///       to call SetBufferedSliceNum() again.
    ///////////////////////////////////////////////////////////////////////////
    void SetMemoryBufferSize(size_type s);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the number of buffered slice in memory.
    /// \param n the number of buffered slice
    /// \note When calling this function, the buffer size is also calculated
    ///       by (slice size) * (slice number), so it is unnecessary to call
    ///       SetMemoryBufferSize() again.
    ///////////////////////////////////////////////////////////////////////////
    void SetBufferedSliceNum(unsigned int n);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the number of buffered slice in memory.
    /// \return Return the number of buffered slice.
    ///////////////////////////////////////////////////////////////////////////
    unsigned int GetBufferedSliceNum() { return m_BufferedSliceNum; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the full path of the disk buffer to contain all the slices of the 
    /// volume.
    /// \param path the full path of the disk buffer
    ///////////////////////////////////////////////////////////////////////////
    void SetPathOfDiskBuffer(char const *path);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the full path of the disk buffer which contains all the slices of the 
    /// volume.
    /// \return Return the full path of the disk buffer.
    ///////////////////////////////////////////////////////////////////////////
    char const* GetPathOfDiskBuffer();

    ///////////////////////////////////////////////////////////////////////////
    /// Set the name prefix of the volume cache files. For quick restore of
    /// an out-of-core volume.
    /// \param prefix the name prefix to be set
    ///////////////////////////////////////////////////////////////////////////
    void SetNamePrefix(char const *prefix);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the name prefix of the volume cache files. For quick restore of
    /// an out-of-core volume.
    /// \return Return the name prefix
    ///////////////////////////////////////////////////////////////////////////
    char const* GetNamePrefix();

    ///////////////////////////////////////////////////////////////////////////
    /// Set whether or not to keep the cache files. To set it to true for quick restore of
    /// an out-of-core volume.
    /// \param keep true for keep, false for delete
    ///////////////////////////////////////////////////////////////////////////
    void SetKeepCacheFiles(bool keep=true) { m_KeepCacheFiles = keep; }

    virtual void PrepareSlicesForRead(int startSliceIdx,int sliceNum=1,bool freeze=false);
    virtual void PrepareSlicesForWrite(int startSliceIdx,int sliceNum=1,bool freeze=false);

protected:
    virtual ~mitkOoCVolume();

    bool _loadSlice(int sliceIdx);
    bool _writeSliceBack(int sliceIdx);
    void _clearDiskCache();
    void _flush();
    SliceBufferBlockNode* _getFreeBufferBlock();
    SliceBufferBlockNode* _getSliceBufferBlock(int sliceIdx);

    void const* _getSliceForRead(int sliceIdx);
    void* _getSliceForWrite(int sliceIdx);
    
    bool _changeBufferSize(unsigned int bufSliceNum);

    void _freezeSlice(int sliceIdx);
    void _unFreezeSlice(int sliceIdx);

    void _prepareSlicesForRead();
    void _prepareSlicesForWrite();

    mitkString *m_DiskPath;
    mitkString *m_NamePrefix;

    size_type m_MemBufSize;
    
    unsigned int m_BufferedSliceNum;

    SliceHeap *m_BufferedSliceHeap;
    SliceHeapNode *m_SliceHeapNodes;

    SliceBufferFreeQueue *m_FreeQueue;
    SliceBufferBlockNode *m_BufferBlockNodes;

    void *m_SliceBuffer;

    bool m_KeepCacheFiles;

    mitkOoCVolumeIODelegate *m_IODelegate;

    int m_IOSliceStartIdx,m_IOSliceNumber;
    bool m_IOFreeze;

private:
    mitkOoCVolume(const mitkOoCVolume&);
    void operator = (const mitkOoCVolume&);

};


//#define DEFINED_mitkOoCVolume



#endif

