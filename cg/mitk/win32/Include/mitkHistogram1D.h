/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkHistogram1D_h
#define __mitkHistogram1D_h

#include "mitkObject.h"
#include "mitkRCPtr.h"
#include "mitkVolume.h"

/// mitkHistogram1D - a tool to generate a 1D histogram from a volume
///////////////////////////////////////////////////////////////////////////
/// mitkHistogram1D is a tool to generate a 1D histogram from a volume
class MITK_COMMON_API mitkHistogram1D:public mitkObject
{
public:
    MITK_TYPE(mitkHistogram1D, mitkObject)
    
    mitkHistogram1D();
    
    ///////////////////////////////////////////////////////////////////////
    /// Set the volume whose histogram is to be generated
    /// \param vol Specify pointer to the volume
    /// \param chIdx Specify the channel of the the histogram, if the value
    /// is greater or equal than the number of channel present or smaller than zero, 
    /// an average of all channels will be genrated.
    /// \param extent Specify (optionally) the region of the volume to generate
    /// the histogram. NULL means to take the whole volume into consideration.
    ///////////////////////////////////////////////////////////////////////
    void SetSourceVolume(mitkVolume *vol, int chIdx=-1,unsigned int *extent=NULL,mitkVolume* mask=NULL);
    ///////////////////////////////////////////////////// //////////////////
    /// Set the value range and interval where to calculate statistics,
    /// this will allocate memory for statistics
    /// \param min Specify the min value of histogram
    /// \param max Specify the max value of histogram
    /// \param intervalNum Specify number of intervals between min and max
    ///////////////////////////////////////////////////////////////////////
    void SetRange(double min,double max,unsigned int intervalNum);
    ///////////////////////////////////////////////////// //////////////////
    /// Get the value range and interval where statistics are calculated,
    /// \param min Recieve the min value of histogram
    /// \param max Recieve the max value of histogram
    /// \param intervalNum Recieve number of intervals between min and max
    ///////////////////////////////////////////////////////////////////////
    void GetRange(double &min,double &max,unsigned int &intervalNum) const
    {
        min=m_min;
        max=m_max;
        intervalNum=m_intervalNum;
    }
    ///////////////////////////////////////////////////////////////////////
    /// Get the maximum pixel value within the specified extent
    /// \return Return the maximum pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetMaxPixVal() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the minimum pixel value within the specified extent
    /// this will trigger the calculation
    /// \return Return the minimum pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetMinPixVal() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the average pixel value within the specified extent,
    /// this will trigger the calculation
    /// \return Return the average pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetMeanPixVal() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the standard deviation of pixel value within the specified extent,
    /// this will trigger the calculation
    /// \return Return the standard deviation of pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetStandardDeviation() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the total number of pixels within the specified extent
    /// \return Return the total number of pixels within the specified extent
    ///////////////////////////////////////////////////////////////////////
    unsigned long GetTotalPixels() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get histogram statistics, this will trigger the calculation
    /// \return Return the histogram statistics, the array is as large as 
    /// intervalNum
    ///////////////////////////////////////////////////////////////////////
    unsigned long* GetStatistics();

    ///////////////////////////////////////////////////////////////////////
    /// Get the modified status of the histogram
    /// \return whether the histogram is modified after last call to 
    /// SetUnmodified()
    ///////////////////////////////////////////////////////////////////////
    bool IsModified();
    ///////////////////////////////////////////////////////////////////////
    /// Set the modified status the false
    ///////////////////////////////////////////////////////////////////////
    void SetUnmodified();
    ///////////////////////////////////////////////////////////////////////
    /// Get the volume whose histogram is generated
    /// \return Return the volume whose histogram is generated
    ///////////////////////////////////////////////////////////////////////
    mitkVolume *GetSourceVolume() { return m_volume; }

protected:
    virtual ~mitkHistogram1D();
    void _calculateHist();

    mitkRCPtr<mitkVolume> m_volume;
    mitkRCPtr<mitkVolume> m_mask;
    int m_chIdx;
    unsigned int m_extent[6];

    double m_min;  // range min
    double m_max;  // range max
    unsigned int m_intervalNum; 

    bool m_calculated;
    bool m_modified;

    unsigned long* m_statistics;

    double m_MaxPixVal; // min value within extent
    double m_MinPixVal; // max value within extent
    double m_MeanPixVal; 
    double m_StdDev; 
    
    unsigned long m_TotalPixels;
    
};


#endif

