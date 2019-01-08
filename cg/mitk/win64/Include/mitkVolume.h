/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolume_h
#define __mitkVolume_h

#include "mitkDataObject.h"

/// mitkVolume - an abstract class to represent a multi-dimensional medical image dataset
///////////////////////////////////////////////////////////////////////////
/// mitkVolume is a very important class in MITK. And most algorithms 
/// may use it as input or output. In concept, it is a multi-dimensional 
/// dataset. You can access the property and actual data of this dataset 
/// through the interface provided by mitkVolume. mitkVolume supports 1D, 
/// 2D and 3D dataset, various data type, multi-channel image, and out-of-core
/// data loading. Two examples using mitkVolume are given below. \n
/// Example 1: If you want to create a new volume and fill its data, for 
/// example, read a file into volume, the code snippet is:
/// \code
/// // mitkVolume is an abstract class, so you should new mitkICVolume
/// // (for in-core data) or mitkOoCVolume (for out-of-core data) for actual
/// // use.
/// mitkVolume *aVolume = new mitkICVolume; // or mitkOoCVolume 
/// aVolume->SetWidth(sliceWidth);
/// aVolume->SetHeight(sliceHeight);
/// aVolume->SetSliceNum(sliceNum); 
/// aVolume->SetSpacingX(sliceSpacingX);
/// aVolume->SetSpacingY(sliceSpacingY);
/// aVolume->SetSpacingZ(sliceSpacingZ);    
/// aVolume->SetChannelNum(sliceChannelNum);
/// aVolume->SetDataType(sliceDataType);        
/// // volume has got enough information, now allocate memory
/// if (aVolume->Allocate())
/// {
///     Read the content of disk file to aVolume via WriteSliceData();
///     Use aVolume ...;
/// }
/// \endcode
/// Example 2: If you want to read/access the content of a volume, the
/// code snippet is:
/// \code
/// sliceWidth = aVolume->GetWidth();
/// sliceHeight = aVolume->GetHeight();
/// sliceNum = aVolume->GetSliceNum();
/// sliceSpacingX = aVolume->GetSpacingX();
/// sliceSpacingY = aVolume->GetSpacingY();
/// sliceSpacingZ = aVolume->GetSpacingZ();
/// sliceChannelNum = aVolume->GetChannelNum();
/// sliceDataType = aVolume->GetDataType();     
/// for(int i = 0; i < imageNum; i++)  //Access every slice data
/// {
///     sliceData = aVolume->GetSliceData(i); 
///     // or using ReadSliceData() to copy data to a user specified buffer
///     Process sliceData according to sliceDataType;
/// }
/// \endcode
class MITK_COMMON_API mitkVolume : public mitkDataObject
{
public:
    MITK_TYPE(mitkVolume, mitkDataObject)

    virtual void PrintSelf(ostream& os);

    mitkVolume();

    ///////////////////////////////////////////////////////////////////////////
    /// Delete the allocated memory (if any) and initialize to default status.
    ///////////////////////////////////////////////////////////////////////////
    virtual void Initialize();

    ///////////////////////////////////////////////////////////////////////////
    /// Return the data object type.
    /// \return Always return MITK_VOLUME
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const { return MITK_VOLUME; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set dimension in x, y, z direction of this volume.
    /// \param dims[0] the dimension in x direction
    /// \param dims[1] the dimension in y direction
    /// \param dims[2] the dimension in z direction
    ///////////////////////////////////////////////////////////////////////////
    void SetDimensions(int dims[3])
    {
        m_Dimensions[0] = dims[0];
        m_Dimensions[1] = dims[1];
        m_Dimensions[2] = dims[2];
        this->_computeIncrements();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get dimension in x, y, z direction of this volume.
    /// \param dims[0] Return the dimension in x direction. It is equal to
    /// the return value of GetWidth()
    /// \param dims[1] Return the dimension in y direction. It is equal to
    /// the return value of GetHeight()
    /// \param dims[2] Return the dimension in z direction. It is equal to
    /// the return value of GetSliceNum()
    ///////////////////////////////////////////////////////////////////////////
    void GetDimensions(int dims[3]) const 
    {
        dims[0] = m_Dimensions[0];
        dims[1] = m_Dimensions[1];
        dims[2] = m_Dimensions[2];
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the width of this volume (dimension in x).
    /// \param w The width of this volume, the unit is pixel.   
    ///////////////////////////////////////////////////////////////////////////
    void SetWidth(int w) { m_Dimensions[0] = w; this->_computeIncrements(); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the width of this volume (dimension in x).
    /// \return Return the width of this volume, the unit is pixel. 
    ///////////////////////////////////////////////////////////////////////////    
    int GetWidth() const { return m_Dimensions[0]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the height of this volume (dimension in y).
    /// \param h The height of this volume, the unit is pixel.  
    ///////////////////////////////////////////////////////////////////////////
    void SetHeight(int h) { m_Dimensions[1] = h; this->_computeIncrements(); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the height of this volume (dimension in y).
    /// \return Return the height of this volume, the unit is pixel.    
    ///////////////////////////////////////////////////////////////////////////
    int GetHeight() const { return m_Dimensions[1]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the slice/image number of this volume (dimension in z).
    /// \param s The image/slice number of this volume. 
    ///////////////////////////////////////////////////////////////////////////
    void SetSliceNum(int s) { m_Dimensions[2] = s; }

    ///////////////////////////////////////////////////////////////////////////
    /// Provided for convenience, just the same as SetSliceNum().
    ///////////////////////////////////////////////////////////////////////////
    void SetImageNum(int s) { this->SetSliceNum(s); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the slice/image number of this volume (dimension in z).
    /// \return Return the image/slice number of this volume.   
    ///////////////////////////////////////////////////////////////////////////
    int  GetSliceNum() const { return m_Dimensions[2]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Provided for convenience, just the same as GetSliceNum().
    ///////////////////////////////////////////////////////////////////////////
    int  GetImageNum() const { return this->GetSliceNum(); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the dimension of this volume.
    /// return 2 --- 2D image \n
    /// return 3 --- 3D image \n
    ///////////////////////////////////////////////////////////////////////////
    int  GetDimensionality() const 
    { 
        if (m_Dimensions[2]==1)
        {
            return 2;
        } 
        else
        {
            return 3;
        }
         
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Set spacing information in x, y and z axis, the unit is mm.
    /// \param s[0] the spacing (mm) in two adjacent voxels in x axis.
    /// \param s[1] the spacing (mm) in two adjacent voxels in y axis.
    /// \param s[2] the spacing (mm) in two adjacent voxels in z axis.
    ///////////////////////////////////////////////////////////////////////////
    void SetSpacings(float s[3])
    {
        m_Spacings[0] = s[0];
        m_Spacings[1] = s[1];
        m_Spacings[2] = s[2];
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get spacing information in x, y and z axis, the unit is mm.
    /// \param s[0] Return the spacing (mm) in two adjacent voxels in x axis.
    /// It is equal to the return value of GetSpacingX()
    /// \param s[1] Return the spacing (mm) in two adjacent voxels in y axis.
    /// It is equal to the return value of GetSpacingY()
    /// \param s[2] Return the spacing (mm) in two adjacent voxels in z axis.
    /// It is equal to the return value of GetSpacingZ()
    ///////////////////////////////////////////////////////////////////////////
    void GetSpacings(float s[3]) const 
    {
        s[0] = m_Spacings[0];
        s[1] = m_Spacings[1];
        s[2] = m_Spacings[2];
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Set spacing information in x axis, the unit is mm.
    /// \param px the spacing (mm) in two adjacent voxels in x axis.
    ///////////////////////////////////////////////////////////////////////////
    void SetSpacingX(float px) { m_Spacings[0] = px; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get spacing information in x axis, the unit is mm.
    /// \return Return the spacing (mm) in two adjacent voxels in x axis.
    ///////////////////////////////////////////////////////////////////////////
    float GetSpacingX() const { return m_Spacings[0]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set spacing information in y axis, the unit is mm.
    /// \param py the spacing (mm) in two adjacent voxels in y axis.
    ///////////////////////////////////////////////////////////////////////////
    void SetSpacingY(float py) { m_Spacings[1] = py; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get spacing information in y axis, the unit is mm.
    /// \return Return the spacing (mm) in two adjacent voxels in y axis.
    ///////////////////////////////////////////////////////////////////////////
    float GetSpacingY() const { return m_Spacings[1]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set spacing information in z axis, the unit is mm.
    /// \param pz the spacing (mm) in two adjacent voxels in z axis.
    ///////////////////////////////////////////////////////////////////////////
    void SetSpacingZ(float pz) { m_Spacings[2] = pz; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get spacing information in z axis, the unit is mm.
    /// \return Return the spacing (mm) in two adjacent voxels in z axis.
    ///////////////////////////////////////////////////////////////////////////
    float GetSpacingZ() const { return m_Spacings[2]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the channel number of this volume.
    /// \param n The channel number of this volume. \n
    /// n = 1 --- gray image \n
    /// n = 3 --- RGB image \n
    /// n = 4 --- RGBA image \n
    ///////////////////////////////////////////////////////////////////////////
    void SetChannelNum(int n) { m_NumberOfChannel = n; this->_computeIncrements(); }

    ///////////////////////////////////////////////////////////////////////////
    /// Just the same as SetChannelNum().
    ///////////////////////////////////////////////////////////////////////////
    void SetNumberOfChannel(int n) { this->SetChannelNum(n); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the channel number of this volume.
    /// \return Return the channel number of this volume. \n
    /// return 1 --- gray image \n
    /// return 3 --- RGB image \n
    /// return 4 --- RGBA image \n
    ///////////////////////////////////////////////////////////////////////////
    int GetChannelNum() const { return m_NumberOfChannel; }

    ///////////////////////////////////////////////////////////////////////////
    /// Just the same as GetChannelNum().
    ///////////////////////////////////////////////////////////////////////////
    int GetNumberOfChannel() const { return this->GetChannelNum(); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the increments in x, y and z directions.
    /// \param incs[0] the increment in x directions. It is equal to the 
    /// return value of GetIncrementX()
    /// \param incs[1] the increment in y directions. It is equal to the 
    /// return value of GetIncrementY()
    /// \param incs[2] the increment in z directions. It is equal to the 
    /// return value of GetIncrementZ() 
    ///////////////////////////////////////////////////////////////////////////
    void GetIncrements(int incs[3]) const
    {
        incs[0] = m_Increments[0];
        incs[1] = m_Increments[1];
        incs[2] = m_Increments[2];
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the increment in x direction.
    /// \return Return the increment in x direction. If the channel number
    /// is channelNum, then the return value is channelNum.
    /// \note This function is provided for the convenient traversal of 
    /// the volume. It doesn't take data type of the volume into account.
    /// So if you get the data of a volume in void* form, you must convert
    /// it to unsigned char*, and the increment must multiply Sizeof(data 
    /// type of volume).   
    ///////////////////////////////////////////////////////////////////////////
    int GetIncrementX() const { return m_Increments[0]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the increment in y direction.
    /// \return Return the increment in y direction. If the channel number
    /// is channelNum, then the return value is channelNum * widthOfVolume.
    /// \note This function is provided for the convenient traversal of 
    /// the volume. It doesn't take data type of the volume into account.
    /// So if you get the data of a volume in void* form, you must convert
    /// it to unsigned char*, and the increment must multiply Sizeof(data 
    /// type of volume).   
    ///////////////////////////////////////////////////////////////////////////
    int GetIncrementY() const { return m_Increments[1]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the increment in z direction.
    /// \return Return the increment in z direction. If the channel number
    /// is channelNum, then the return value is channelNum * widthOfVolume
    /// * heightOfVolume.
    /// \note This function is provided for the convenient traversal of 
    /// the volume. It doesn't take data type of the volume into account.
    /// So if you get the data of a volume in void* form, you must convert
    /// it to unsigned char*, and the increment must multiply Sizeof(data 
    /// type of volume).   
    ///////////////////////////////////////////////////////////////////////////
    int GetIncrementZ() const { return m_Increments[2]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get value of a specified voxel's channel.
    /// \param x the x-coordinate of the voxel in the volume space (in [0, GetWidth()-1])
    /// \param y the y-coordinate of the voxel in the volume space (in [0, GetHeight()-1])
    /// \param z the y-coordinate of the voxel in the volume space (in [0, GetImageNum()-1])
    /// \param c the channel of the specified voxel (in [0, GetChannelNum()-1])
    /// \return Return the value of the specified voxel's channel in double data type.
    /// \note It is a safe but slow function. Use it carefully if you are
    ///       concerned about the efficiency.
    ///////////////////////////////////////////////////////////////////////////
    double GetData(int x, int y, int z, int c = 0);

    ///////////////////////////////////////////////////////////////////////////
    /// Useless. Obsolete.
    ///////////////////////////////////////////////////////////////////////////
    void GetPointGradient(int i, int j, int k, float g[3]);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the minimum value of the data type of this volume.
    /// \return Return the minimum value of the data type of this volume.
    ///////////////////////////////////////////////////////////////////////////
    double GetDataTypeMin() const { return m_DataTypeMin; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the maximum value of the data type of this volume.
    /// \return Return the maximum value of the data type of this volume.
    ///////////////////////////////////////////////////////////////////////////
    double GetDataTypeMax() const { return m_DataTypeMax; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the window width for display in mitkImageScene.
    /// \param wWidth The window width. For some image files, they contain
    /// the window width/center information in file header, for example, 
    /// DICOM files. In this situation, the window width/center is got directly
    /// from the file header. In other situations, the window width/center
    /// is calculate from the data of the volume.
    ///////////////////////////////////////////////////////////////////////////
    void SetWindowWidth(float wWidth) { m_WindowWidth = wWidth; m_HasWidthCenter = true; }    

    ///////////////////////////////////////////////////////////////////////////
    /// Set the window center for display in mitkImageScene.
    /// \param wCenter The window center. For some image files, they contain
    /// the window width/center information in file header, for example, 
    /// DICOM files. In this situation, the window width/center is got directly
    /// from the file header. In other situations, the window width/center
    /// is calculate from the data of the volume.
    ///////////////////////////////////////////////////////////////////////////
    void SetWindowCenter(float wCenter) { m_WindowCenter = wCenter; m_HasWidthCenter = true; }    

    ///////////////////////////////////////////////////////////////////////////
    /// Get the window width for display in mitkImageScene.
    /// \return Return the window width of this volume.
    ///////////////////////////////////////////////////////////////////////////
    float GetWindowWidth();

    ///////////////////////////////////////////////////////////////////////////
    /// Get the window center for display in mitkImageScene.
    /// \return Return the window center of this volume.
    ///////////////////////////////////////////////////////////////////////////
    float GetWindowCenter(); 

    ///////////////////////////////////////////////////////////////////////////
    /// Get the window width and center for display in mitkImageScene.
    /// \param wWidth Return the window width of this volume.
    /// \param wCenter Return the window center of this volume.
    ///////////////////////////////////////////////////////////////////////////
    void  GetWidthCenter(float &wWidth, float &wCenter);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the flag which indicates whether this volume has window width and center
    /// \return Return true --- This volume has window width/center
    /// Return false --- This volume has not window width/center
    ///////////////////////////////////////////////////////////////////////////
    bool HasWidthCenter() const {return m_HasWidthCenter;}    

    ///////////////////////////////////////////////////////////////////////////
    /// Get the size of the data type in bytes.
    /// \return Return the size of the data type in bytes.
    ///////////////////////////////////////////////////////////////////////////
    int GetDataTypeSize() const { return m_DataTypeSize; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume. MITK supports various data type.
    /// \param data_type Its valid value and meaning is shown as follows:\n
    /// MITK_CHAR            The data type is char \n
    /// MITK_UNSIGNED_CHAR   The data type is unsigned char \n
    /// MITK_SHORT           The data type is short \n
    /// MITK_UNSIGNED_SHORT  The data type is unsigned short \n
    /// MITK_INT             The data type is int \n
    /// MITK_UNSIGNED_INT    The data type is unsigned int \n
    /// MITK_LONG            The data type is long \n
    /// MITK_UNSIGNED_LONG   The data type is unsigned long \n
    /// MITK_FLOAT           The data type is float \n
    /// MITK_DOUBLE          The data type is double \n
    ///////////////////////////////////////////////////////////////////////////
    void SetDataType(int data_type);

    ///////////////////////////////////////////////////////////////////////////
    /// Get data type of this volume. MITK supports various data type.
    /// \return All of the return values and their meaning are shown as follows:\n
    /// MITK_CHAR            The data type is char \n
    /// MITK_UNSIGNED_CHAR   The data type is unsigned char \n
    /// MITK_SHORT           The data type is short \n
    /// MITK_UNSIGNED_SHORT  The data type is unsigned short \n
    /// MITK_INT             The data type is int \n
    /// MITK_UNSIGNED_INT    The data type is unsigned int \n
    /// MITK_LONG            The data type is long \n
    /// MITK_UNSIGNED_LONG   The data type is unsigned long \n
    /// MITK_FLOAT           The data type is float \n
    /// MITK_DOUBLE          The data type is double \n
    ///////////////////////////////////////////////////////////////////////////
    int GetDataType() const { return m_DataType; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to float.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToFloat() { this->SetDataType(MITK_FLOAT); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to double.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToDouble() { this->SetDataType(MITK_DOUBLE); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to int.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToInt() { this->SetDataType(MITK_INT); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to unsigned int.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToUnsignedInt() { this->SetDataType(MITK_UNSIGNED_INT); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to long.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToLong() { this->SetDataType(MITK_LONG); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to unsigned long.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToUnsignedLong() { this->SetDataType(MITK_UNSIGNED_LONG); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to short.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToShort() { this->SetDataType(MITK_SHORT); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to unsigned short.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToUnsignedShort() { this->SetDataType(MITK_UNSIGNED_SHORT); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to unsigned char.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToUnsignedChar() { this->SetDataType(MITK_UNSIGNED_CHAR); }

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this volume to char.
    ///////////////////////////////////////////////////////////////////////////
    void SetDataTypeToChar() { this->SetDataType(MITK_CHAR); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the minimum and maximum data value in a specified slice.
    /// \param sliceNum The specified slice number.
    /// \param minValue return the minimum data value in the specified slice.
    /// \param maxValue return the maximum data value in the specified slice.
    /// \param needRecalculate If needRecalculate=true, the minValue and maxValue
    /// need be recalculated. Otherwise, the cached value is returned directly.
    ///////////////////////////////////////////////////////////////////////////
    void GetMinMaxValue(int sliceIdx, double &minValue, double &maxValue, bool needRecalculate = false);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the minimum and maximum data value of all the volume data.
    /// \param minValue return the minimum data value
    /// \param maxValue return the maximum data value
    /// \param needRecalculate If needRecalculate=true, the minValue and maxValue
    /// need be recalculated. Otherwise, the cached value is returned directly.
    ///////////////////////////////////////////////////////////////////////////
    void GetMinMaxValue(double &minValue, double &maxValue, bool needRecalculate = false);
    
    ///////////////////////////////////////////////////////////////////////////
    /// \warning Don't call this function directly.
    ///////////////////////////////////////////////////////////////////////////
    virtual void ShallowCopy(mitkDataObject *src);

    ///////////////////////////////////////////////////////////////////////////
    /// \warning Don't call this function directly.
    ///////////////////////////////////////////////////////////////////////////
    virtual void DeepCopy(mitkDataObject *src);

    ///////////////////////////////////////////////////////////////////////////
    /// Lock the physical memory containing sliceIdx'th slice data. (only useful
    /// for out-of-core volume data (mitkOoCVolume) to avoid swapping some slice
    /// data from memory buffer to disk buffer, i.e. to keep the returned pointer
    /// of some 'Get' functions, such as GetSliceData(), GetSliceForRead() and
    /// so on, always be valid until call UnFreezeSlice().
    /// \param sliceIdx the index of the slice to freeze.
    ///////////////////////////////////////////////////////////////////////////
    virtual void FreezeSlice(int sliceIdx) {}

    ///////////////////////////////////////////////////////////////////////////
    /// Unlock the physical memory containing sliceIdx'th slice data.
    /// \param sliceIdx the index of the slice to un-freeze.
    /// \see FreezeSlice()
    ///////////////////////////////////////////////////////////////////////////
    virtual void UnFreezeSlice(int sliceIdx) {}

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of the volume data (unchangeable). 
    /// \return Return a void pointer to const data.
    /// \note The returned type is void const *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    ///////////////////////////////////////////////////////////////////////////
    virtual void const* GetData() const = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of the volume data (changeable). 
    /// \return Return a void pointer to data.
    /// \note The returned type is void *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void* GetData() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Provided for back compatibility, just the same as GetSliceForReadWrite().
    ///////////////////////////////////////////////////////////////////////////
    void* GetSliceData(int sliceIdx) { return this->GetSliceForReadWrite(sliceIdx); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of a specified slice in the volume (for read only).
    /// \param sliceIdx the index of the slice to get (in [0, GetSliceNum()-1])
    /// \return Return a const void pointer to data.
    /// \note The returned type is void const *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void const* GetSliceForRead(int sliceIdx) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of a specified slice in the volume (for write only).
    /// \param sliceIdx the index of the slice to get (in [0, GetSliceNum()-1])
    /// \return Return a const void pointer to data.
    /// \note The returned type is void *, it should be converted to some
    ///       useful data type according to the return value of GetDataType().
    ///       This function returns an empty buffer for writing the specified
    ///       slice the first time.
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void* GetSliceForWrite(int sliceIdx) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of a specified slice in the volume (for read & write).
    /// \param sliceIdx the index of the slice to get (in [0, GetSliceNum()-1])
    /// \return Return a const void pointer to data.
    /// \note The returned type is void *, it must be converted to some
    ///       useful data type according to the return value of GetDataType().
    /// \warning The memory is deleted by destructor automatically, so
    ///          clients shouldn't delete the pointer returned by this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void* GetSliceForReadWrite(int sliceIdx) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Copy slice data from the volume to a specified memory buffer.
    /// \param sliceIdx the index of the slice to read (in [0, GetSliceNum()-1])
    /// \param dst the pointer to the destination memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of destination memory buffer should be
    ///       GetWidth() * GetHeight() * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool ReadSliceData(int sliceIdx, void *dst) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Copy x-directional slice from the volume to a specified memory buffer.
    /// \param xIdx the position of the x-directional slice to read (in [0, GetWidth()-1])
    /// \param dst the pointer to the destination memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of destination memory buffer should be
    ///       GetHeight() * GetImageNum() * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool ReadYZSliceData(int xIdx, void *dst) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Copy y-directional slice from the volume to a specified memory buffer.
    /// \param yIdx the position of the y-directional slice to read (in [0, GetHeight()-1])
    /// \param dst the pointer to the destination memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of destination memory buffer should be
    ///       GetWidth() * GetImageNum() * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool ReadXZSliceData(int yIdx, void *dst) = 0;

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
    virtual bool GetArbitrarySlice(int w, int h, double o[3], double ux[3], double uy[3], void *dst) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Copy slice data from a specified memory buffer to the volume.
    /// \param sliceIdx the index of the slice to write (in [0, GetImageNum()-1])
    /// \param src the pointer to the source memory buffer
    /// \return Return true if successful, otherwise return false.
    /// \note The size of source memory buffer should be
    ///       GetWidth() * GetHeight() * GetChannelNum() * GetDataTypeSize().
    ///////////////////////////////////////////////////////////////////////////
    virtual bool WriteSliceData(int sliceIdx, void const *src) = 0;

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
    virtual bool ReadSubVolume(int x, int y, int z, int w, int h, int d, int &tw, int &th, int &td, void *dst) = 0;

    virtual bool ReadSubVolume(int x, int y, int z, int w, int h, int d,
        int dstx, int dsty, int dstz, int dstw, int dsth, int dstd,
        void *dst, bool zeropad=true) = 0;

    virtual bool ReadSubVolume(int x, int y, int z, int w, int h, int d, void *dst, bool zeropad=true) = 0;

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
    virtual bool WriteSubVolume(int x, int y, int z, int w, int h, int d, int &tw, int &th, int &td, void const *src) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Allocate necessary space for holding the image data. It calculate the
    /// memory size using current Dimensions, DataType and NumberOfChannel
    /// settings. The equation is shown as follow: \n
    /// Width * Height * SliceNum * sizeof(DataType) * NumberOfChannel \n
    /// The previous allocated data will be deleted if exists.
    /// \return Return true if successful, otherwise return false.
    /////////////////////////////////////////////////////////////////////////// 
    virtual bool Allocate() = 0;

    virtual void PrepareSlicesForRead(int startSliceIdx,int sliceNum=1,bool freeze=false){};
    virtual void PrepareSlicesForWrite(int startSliceIdx,int sliceNum=1,bool freeze=false){};

protected:
    virtual ~mitkVolume();    
    void _computeIncrements();
    void _clearMinMaxCache();

    int   m_Dimensions[3];
    int   m_Increments[3];
    float m_Spacings[3];

    int   m_DataType;
    int   m_NumberOfChannel;

    float m_WindowWidth;
    float m_WindowCenter;
    bool  m_HasWidthCenter;
    bool  m_IsFirstWidthCenter;

    double *m_MinArray;
    double *m_MaxArray;
    unsigned char *m_MinMaxFlags;

    int m_DataTypeSize;
    double m_DataTypeMin;
    double m_DataTypeMax;

    //void  *m_Data;

private:
    mitkVolume(const mitkVolume&);
    void operator=(const mitkVolume&);

};

//#define DEFINED_mitkVolume



#endif


