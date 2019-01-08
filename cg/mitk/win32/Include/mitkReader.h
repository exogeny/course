/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkReader_h
#define __mitkReader_h

#include "mitkSource.h"

//class mitkStringList;

/// mitkReader - an abstract class represents a reader
///////////////////////////////////////////////////////////////////////////
/// mitkReader defines the interface of all of the readers. To use a 
/// concrete reader, for example, mitkBMPReader, the code snippet is: 
/// \code
/// mitkBMPReader *aReader = new mitkBMPReader; 
/// aReader->AddFileName(file1); 
/// aReader->AddFileName(file2); 
/// ...  ...  ... 
/// aReader->Run(); 
/// mitkVolume *aVolume = aReader->GetOutput(); 
/// Using aVolume 
/// \endcode
class MITK_COMMON_API mitkReader : public mitkSource
{
public:
    MITK_TYPE(mitkReader,mitkSource)

    virtual void PrintSelf(ostream& os);

    ///////////////////////////////////////////////////////////////////////
    /// Add a file into the internal list for reading these files.
    /// \param inFileName C string for the file name.   
    ///////////////////////////////////////////////////////////////////////
    void AddFileName(const char *inFileName);

    ///////////////////////////////////////////////////////////////////////
    /// Sort all the file names alphabetically.
    ///////////////////////////////////////////////////////////////////////
    void SortFileNames();

protected:
    virtual ~mitkReader();
    mitkReader();    

    int _getFileCount(void);
    const char* _getFileName(int nIndex);

    mitkStringList *m_FileNames;
private:
    mitkReader(const mitkReader&);
    void operator=(const mitkReader&);
};


//#define DEFINED_mitkReader



#endif


