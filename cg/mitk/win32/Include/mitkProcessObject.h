/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkProcessObject_h
#define __mitkProcessObject_h

#include "mitkObject.h"

/// mitkProcessObject - abstract base class for source, filter(algorithm) and mapper
///////////////////////////////////////////////////////////////////////////
/// mitkProcessObject is an abstract object that specifies behavior and
/// interface of source, filter and mapper.
class MITK_COMMON_API mitkProcessObject : public mitkObject
{
public:
    MITK_TYPE(mitkProcessObject,mitkObject)

    virtual void PrintSelf(ostream& os);

    bool Run();

    void SetStartMethod(void (* f) (void *)) {m_StartMethod = f;}
    void SetEndMethod(void (* f) (void *)){m_EndMethod = f;}
    void SetProgressMethod(void (* f) (void *)){m_ProgressMethod = f;}

    ///////////////////////////////////////////////////////////////////////
    /// Get current rate of process of the running process.
    /// \return Return current rate of process.
    ///////////////////////////////////////////////////////////////////////
    unsigned long GetProgressRate() { return m_ProgressRate; }
    
    ///////////////////////////////////////////////////////////////////////
    /// Set maximum value the rate of process can reach.
    /// \param m the maximum value of the rate of process
    ///////////////////////////////////////////////////////////////////////
    void SetProgressRateMax(unsigned long m) { m_ProgressRateMax = m; }

    // For local usage. Do not use these functions out of MITK.
    void SetProgressRate(unsigned int rate) { m_ProgressRate = rate; }
    unsigned int GetProgressRateMax() { return m_ProgressRateMax; }
    void UpdateObservers() { this->_updateObservers(); }

protected:
    virtual ~mitkProcessObject();
    mitkProcessObject();    

    virtual bool Execute() { return true; }

    unsigned long m_ProgressRate;
    unsigned long m_ProgressRateMax;

private:
    void (* m_StartMethod) (void *);
    void (* m_EndMethod) (void *);
    void (* m_ProgressMethod) (void *);

    mitkProcessObject(const mitkProcessObject&);
    void operator=(const mitkProcessObject&);
};


//#define DEFINED_mitkProcessObject



#endif


