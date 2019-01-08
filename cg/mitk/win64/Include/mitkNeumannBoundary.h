/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef _mitkNeumannBoundary_h
#define _mitkNeumannBoundary_h

#include "mitkVolumeToVolumeFilter.h"

/** \class mitkNeumannBoundary
* \brief
* A function object that determines a neighborhood of values at an
* image boundary according to a Neumann boundary condition where first,
* upwind derivatives on the boundary are zero.  This is a useful condition 
* in solving some classes of differential equations. 
*
* For example, invoking this function object on a 7x5 iterator that masks
* a region at an image corner (iterator is centered on the 2):
* \code
*               * * * * * * * 
*               * * * * * * *
*               * * 1 2 3 4 5  (where * denotes pixels that lie 
*               * * 3 3 5 5 6          outside of the image boundary)
*               * * 4 4 6 7 8
* \endcode
* returns the following neighborhood of values:
* \code
*               1 1 1 2 3 4 5
*               1 1 1 2 3 4 5
*               1 1 1 2 3 4 5
*               3 3 3 3 5 5 6   (note the corner values)
*               4 4 4 4 6 7 8
* \endcode
* 
*/
//  [8/19/2010 Xiuli Li]

class MITK_COMMON_API mitkNeumannBoundary : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkNeumannBoundary,mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////
    mitkNeumannBoundary() {}

protected:
    virtual ~mitkNeumannBoundary() {}
    virtual bool Execute();
private:
    mitkNeumannBoundary(const mitkNeumannBoundary&);
    void operator = (const mitkNeumannBoundary&);
};

#endif
