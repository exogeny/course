/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkNode_h
#define __mitkNode_h

#include "mitkCommonIncludes.h"
#include "mitkObject.h"

typedef int Index[3];

/// mitkNode - a class that define NodeType used by mitkFastMarchingImageFilter
///////////////////////////////////////////////////////////////////////////
/// mitkNode defines several node types that represent the nodes' positions. 
class  MITK_COMMON_API mitkNode : public mitkObject
{
public:
    MITK_TYPE(mitkNode,mitkObject)
    
    mitkNode(){};

    ///////////////////////////////////////////////////////////////////////////
    /// Set the x, y, z coordinates of the node.
    /// \param x                   Represent the x coor of the node.
    /// \param y                   Represent the y coor of the node.
    /// \param z                   Represent the z coor of the node.
    ///////////////////////////////////////////////////////////////////////////
    void SetIndex(int x, int y, int z)
    {
        m_index[0] = x;
        m_index[1] = y;
        m_index[2] = z;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the x, y, z coordinates of the node.
    /// \param index[0]            Represent the x coor of the node.
    /// \param index[1]            Represent the y coor of the node.
    /// \param index[2]            Represent the z coor of the node.
    /////////////////////////////////////////////////////////////////////////// 
    void SetIndex(Index index)
    {
        SetIndex(index[0], index[1], index[2]);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the x, y, z coordinates of the node.
    /// \return index[0]            Return the x coor of the node.
    /// \return index[1]            Return the y coor of the node.
    /// \return index[2]            Return the z coor of the node.
    ///////////////////////////////////////////////////////////////////////////     
    void GetIndex(Index index) const
    {
        index[0] = m_index[0];
        index[1] = m_index[1];
        index[2] = m_index[2];
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the pix value of the node.
    /// \param value                 Represent the pix value of the node.
    ///////////////////////////////////////////////////////////////////////////
    void SetValue(double value){m_value = value;}

    ///////////////////////////////////////////////////////////////////////////
    /// Get the pix value of the node.
    /// \return                     Return the pix value of the node.
    /////////////////////////////////////////////////////////////////////////// 
    double GetValue() const{return this->m_value;}

    ///////////////////////////////////////////////////////////////////////////
    /// Over load operator > for this class
    /// \param right                Represent the right side of the operator
    /// \return                     Return true if the left side > the right side,
    ///                             otherwize return false.
    ///////////////////////////////////////////////////////////////////////////
    bool operator>(const mitkNode &right)
    {
        return this->m_value > right.GetValue();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Over load operator < for this class
    /// \param right                Represent the right side of the operator
    /// \return                     Return true if the left side < the right side,
    ///                             otherwize return false.
    ///////////////////////////////////////////////////////////////////////////
    bool operator<(const mitkNode &right)
    {
        return this->m_value < right.GetValue();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Over load operator = for this class
    /// \param right                Represent the right side of the operator
    /// \return                     Return an object equal to the right side.
    /////////////////////////////////////////////////////////////////////////// 
    mitkNode& operator=(const mitkNode& right)
    {
        Index index;
        right.GetIndex(index);
        this->SetIndex(index);
        this->SetValue(right.GetValue());
        return *this;
    }
    
    virtual ~mitkNode(){};

    ///////////////////////////////////////////////////////////////////////////
    /// Constructor of this class
    /// \param node                The object according which to construct this class
    ///////////////////////////////////////////////////////////////////////////
    mitkNode(const mitkNode& node)
    {
        Index index;
        node.GetIndex(index);
        SetIndex(index);
        SetValue(node.GetValue());
    }

    
private:
    Index m_index;
    double m_value;
};

class  MITK_COMMON_API mitkIntNode : public mitkObject
{
public:
    MITK_TYPE(mitkIntNode,mitkObject)
    
    mitkIntNode(){};
    void SetIndex(int x, int y, int z)
    {
        m_index[0] = x;
        m_index[1] = y;
        m_index[2] = z;
    }
    void SetIndex(Index index)
    {
        SetIndex(index[0], index[1], index[2]);
    }
    void GetIndex(Index index) const
    {
        index[0] = m_index[0];
        index[1] = m_index[1];
        index[2] = m_index[2];
    }
    void SetValue(int value){m_value = value;}
    int GetValue() const{return this->m_value;}
    bool operator>(const mitkIntNode &right)
    {
        return this->m_value > right.m_value;
    }
    bool operator<(const mitkIntNode &right)
    {
        return this->m_value < right.GetValue();
    }
    mitkIntNode& operator=(mitkIntNode& right)
    {
        Index index;
        right.GetIndex(index);
        this->SetIndex(index);
        this->SetValue(right.GetValue());
        return *this;
    }
    virtual ~mitkIntNode(){};
    mitkIntNode(const mitkIntNode& node)
    {
        Index index;
        node.GetIndex(index);
        SetIndex(index);
        SetValue(node.GetValue());
    }
private:
    Index m_index;
    int m_value;
};


#endif

