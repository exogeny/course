/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkWriter_h
#define __mitkWriter_h

#include "mitkTarget.h"

//class mitkStringList1;

/// mitkWriter - an abstract class represents a writer
///////////////////////////////////////////////////////////////////////////
/// mitkWriter defines the interface of all of the writers. To use a 
/// concrete writer, for example, mitkBMPWriter, the code snippet is: 
/// \code
/// mitkBMPWriter *aWriter = new mitkBMPWriter; 
/// aWriter->SetInput(aVolume); 
/// int imageNum = aVolume->GetImageNum(); 
/// Gerenate file names into files[imageNum]; 
/// for(int i = 0; i < imageNum; i++) 
///     aWriter->AddFileName(files[i]); 
/// aWriter->Run(); 
/// \endcode
class MITK_COMMON_API mitkWriter : public mitkTarget
{
public:
    MITK_TYPE(mitkWriter,mitkTarget)

    virtual void PrintSelf(ostream& os);

    ///////////////////////////////////////////////////////////////////////
    /// Add a file into the internal list for writing these files.
    /// \param inFileName C string for the file name.   
    ///////////////////////////////////////////////////////////////////////
    void AddFileName(const char *inFileName);

    ///////////////////////////////////////////////////////////////////////
    /// Sort all the file names alphabetically.
    ///////////////////////////////////////////////////////////////////////
    void SortFileNames();


protected:
    virtual ~mitkWriter();
    mitkWriter();    

    int _getFileCount(void);
    const char* _getFileName(int nIndex);
    mitkStringList *m_FileNames;
private:
    mitkWriter(const mitkWriter&);
    void operator=(const mitkWriter&);
};


//#define DEFINED_mitkWriter



#endif

