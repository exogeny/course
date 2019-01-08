/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkDICOMDIRTree_h
#define __mitkDICOMDIRTree_h

#include "mitkDataObject.h"

class DcmDirectoryModel;

/// mitkDICOMDIRTree - Data Object that stores the DICOMDIR structure of a data base
///////////////////////////////////////////////////////////////////////////
/// mitkDICOMDIRTree is a data Object class that stores the DICOMDIR structure of a data base
class MITK_COMMON_API mitkDICOMDIRTree : public mitkDataObject
{
public:
    MITK_TYPE(mitkDICOMDIRTree,mitkDataObject);
    mitkDICOMDIRTree();
      ///////////////////////////////////////////////////////////////////////////
    /// Delete the allocated memory (if any) and initialize to default status.
    ///////////////////////////////////////////////////////////////////////////
    virtual void Initialize();
    ///////////////////////////////////////////////////////////////////////////
    /// \warning Don't call this function directly.
    ///////////////////////////////////////////////////////////////////////////
    virtual void DeepCopy(mitkDataObject *src);
    ///////////////////////////////////////////////////////////////////////////
    /// \warning Don't call this function directly.
    ///////////////////////////////////////////////////////////////////////////
    virtual void ShallowCopy(mitkDataObject *src);
    ///////////////////////////////////////////////////////////////////////////
    /// Return the actual memory size occupied by the volume data. The unit is BYTE.
    /// \return Return the actual memory size occupied by this volume. The unit is BYTE.
    ///////////////////////////////////////////////////////////////////////////
    virtual unsigned long long GetActualMemorySize()const;
    ///////////////////////////////////////////////////////////////////////////
    /// Called internally by the reader to setup the data
    ///////////////////////////////////////////////////////////////////////////
    void SetTreeData(DcmDirectoryModel* data);

    string GetFileSetID();
    void SetFileSetID(string &ID);
    
    string GetRootRecID(int row);
    string GetRecID(int num);
    string GetRecID(int row,int parentnum);
    string GetRecID(int row,int parentrow,int grandparentnum);
    string GetRecID(int row,int parentrow,int grandparentnum,int rootnum);

    string GetPatientRecID(int num);
    string GetStudyID(int row,int parentnum);
    string GetSeriesID(int row,int parentrow,int grandparentnum);
    string GetReferencedFileID(int row,int parentrow,int grandparentnum,int rootnum);
    int GetChildrenCount(int ParentNum);
    int GetChildrenCount(int Parentrow,int grandparentNum);
    int GetChildrenCount(int Parentrow,int grandparentNum,int rootNum);
    int GetRootCount();
    int GetRecCount();
protected:
    virtual ~mitkDICOMDIRTree();
private:
    void _clear();
    DcmDirectoryModel* m_Tree;
    string FileSetID;
};

#endif