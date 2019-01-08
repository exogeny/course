/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkTIFFReader_h
#define __mitkTIFFReader_h

#include "mitkVolumeReader.h"

/// mitkTIFFReader - a concrete reader for reading TIFF image files
///////////////////////////////////////////////////////////////////////////
/// mitkTIFFReader reads a set of TIFF image files to a volume. Because TIFF
/// file doesn't have the spacing information, you must set them using the
/// SetSpacingX, SetSpacingY, SetSpacingZ functions. To use this reader,
/// the code snippet is: 
/// \code
/// mitkTIFFReader *aReader = new mitkTIFFReader; 
/// aReader->SetSpacingX(sx); 
/// aReader->SetSpacingY(sy); 
/// aReader->SetSpacingZ(sz); 
/// aReader->AddFileName(file1); 
/// aReader->AddFileName(file2); 
/// ...  ...  ... 
/// if (aReader->Run())
/// { 
///     mitkVolume *aVolume = aReader->GetOutput(); 
///     Using aVolume
/// }
/// \endcode
/// \warning All of the images must have equal width and height. Otherwise
/// they can't form a volume. Now MITK only supports single frame TIFF file.
class MITK_COMMON_API mitkTIFFReader : public mitkVolumeReader
{
public:
    MITK_TYPE(mitkTIFFReader,mitkVolumeReader)
    
    virtual void PrintSelf(ostream& os);
    
    mitkTIFFReader();    

    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in x axis, the unit is mm.
    /// \param px the spacing (mm) in two adjacent voxels in x axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacingX(float px){ m_Spacings[0] = px; }
    
    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in y axis, the unit is mm.
    /// \param py the spacing (mm) in two adjacent voxels in y axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacingY(float py){ m_Spacings[1] = py; }
    
    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in z axis, the unit is mm.
    /// \param pz the spacing (mm) in two adjacent voxels in z axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacingZ(float pz){ m_Spacings[2] = pz; }

    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in x, y, z axis, the unit is mm.
    /// \param px the spacing (mm) in two adjacent voxels in x axis.
    /// \param py the spacing (mm) in two adjacent voxels in y axis.
    /// \param pz the spacing (mm) in two adjacent voxels in z axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacings(float s[3])
    {
        m_Spacings[0] = s[0];
        m_Spacings[1] = s[1];
        m_Spacings[2] = s[2];
    }
    
protected:
    virtual ~mitkTIFFReader();    
    
    virtual bool Execute();
    
    float m_Spacings[3];
    
private:
    mitkTIFFReader(const mitkTIFFReader&){};
    void operator=(const mitkTIFFReader&){};

};


//#define DEFINED_mitkTIFFReader



#endif


