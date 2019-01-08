/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkHalfEdgeStructures_h
#define __mitkHalfEdgeStructures_h

#include "mitkGeometryTypes.h"

#define MITK_FLAG_DELETED 0x00000001

typedef struct _vertex    HEVertex,   *HEVertexPtr;
typedef struct _half_edge HEHalfEdge, *HEHalfEdgePtr;
typedef struct _edge      HEEdge,     *HEEdgePtr;
typedef struct _face      HEFace,     *HEFacePtr;

template <typename T> class HandleT;

template <typename T> inline bool operator==(HandleT<T> const &lhs, index_type rhs) { return (lhs._index==rhs); }
template <typename T> inline bool operator==(index_type lhs, HandleT<T> const &rhs) { return (lhs==rhs._index); }
template <typename T> inline bool operator!=(HandleT<T> const &lhs, index_type rhs) { return (lhs._index!=rhs); }
template <typename T> inline bool operator!=(index_type lhs, HandleT<T> const &rhs) { return (lhs!=rhs._index); }
template <typename T> inline bool operator<(HandleT<T> const &lhs, index_type rhs) { return (lhs._index<rhs); }
template <typename T> inline bool operator<(index_type lhs, HandleT<T> const &rhs) { return (lhs<rhs._index); }
template <typename T> inline bool operator<=(HandleT<T> const &lhs, index_type rhs) { return (lhs._index<=rhs); }
template <typename T> inline bool operator<=(index_type lhs, HandleT<T> const &rhs) { return (lhs<=rhs._index); }
template <typename T> inline bool operator>(HandleT<T> const &lhs, index_type rhs) { return (lhs._index>rhs); }
template <typename T> inline bool operator>(index_type lhs, HandleT<T> const &rhs) { return (lhs>rhs._index); }
template <typename T> inline bool operator>=(HandleT<T> const &lhs, index_type rhs) { return (lhs._index>=rhs); }
template <typename T> inline bool operator>=(index_type lhs, HandleT<T> const &rhs) { return (lhs>=rhs._index); }

#ifdef _MSC_VER
#   if _MSC_VER >= 1310 
#       define _TEMP_ <>
#   else
#       define _TEMP_
#   endif
#else
#   define _TEMP_ <>
#endif

template <typename T> class HandleT
{
    friend bool operator==_TEMP_(HandleT const &lhs, index_type rhs);
    friend bool operator==_TEMP_(index_type lhs, HandleT const &rhs);
    friend bool operator!=_TEMP_(HandleT const &lhs, index_type rhs);
    friend bool operator!=_TEMP_(index_type lhs, HandleT const &rhs);
    friend bool operator< _TEMP_(HandleT const &lhs, index_type rhs);
    friend bool operator< _TEMP_(index_type lhs, HandleT const &rhs);
    friend bool operator<=_TEMP_(HandleT const &lhs, index_type rhs);
    friend bool operator<=_TEMP_(index_type lhs, HandleT const &rhs);
    friend bool operator>_TEMP_(HandleT const &lhs, index_type rhs);
    friend bool operator>_TEMP_(index_type lhs, HandleT const &rhs);
    friend bool operator>=_TEMP_(HandleT const &lhs, index_type rhs);
    friend bool operator>=_TEMP_(index_type lhs, HandleT const &rhs);
public:
    HandleT(index_type idx = INVALID_INDEX) : _index(idx) {}
    ~HandleT() {}

    HandleT(HandleT const &h) { _index = h._index; }
    HandleT& operator=(HandleT const &rhs) { _index = rhs._index; return *this; }
    HandleT& operator=(index_type rhs) { _index = rhs; return *this; }

    bool operator==(HandleT const &rhs) const { return (_index==rhs._index); }
    bool operator!=(HandleT const &rhs) const { return (_index!=rhs._index); }
    bool operator<(HandleT const &rhs) const { return (_index<rhs._index); }
    bool operator<=(HandleT const &rhs) const { return (_index<=rhs._index); }
    bool operator>(HandleT const &rhs) const { return (_index>rhs._index); }
    bool operator>=(HandleT const &rhs) const { return (_index>=rhs._index); }
    

    index_type Idx() { return _index; }
    bool IsValid() const { return (_index!=INVALID_INDEX); }

    operator index_type() { return _index; }
    operator bool() { return (_index!=INVALID_INDEX); }

private:
    typedef T PrivateType;
    index_type _index;
};



typedef HandleT<HEVertex> HEVertexHandle;
typedef HandleT<HEHalfEdge> HEHalfEdgeHandle;
typedef HandleT<HEFace> HEFaceHandle;
typedef HandleT<HEEdge> HEEdgeHandle;

struct _flag_base
{
public:
    enum FLAGS
    {
        flag0=1, flag1,  flag2,  flag3,  flag4,  flag5,  flag6,  flag7,
        flag8,   flag9,  flag10, flag11, flag12, flag13, flag14, flag15,
        flag16,  flag17, flag18, flag19, flag20, flag21, flag22, flag23,
        flag24,  flag25, flag26, flag27, flag28, flag29, flag30
    };

    friend class mitkHEMesh;

    _flag_base() : _flags(0) {}
    bool IsDeleted() const { return (_flags & MITK_FLAG_DELETED) != 0; }
    void SetFlag(FLAGS const f, bool const flag) { if (flag) _flags |= (1<<f); else _flags &= ~(1<<f); }
    void SetFlag(FLAGS const f) { _flags |= (1<<f); }
    void UnSetFlag(FLAGS const f) { _flags &= ~(1<<f); }
    bool GetFlag(FLAGS const f) const { return (_flags & (1<<f)) != 0; }
    void SetFlags(unsigned int const fs) { _flags = (_flags & MITK_FLAG_DELETED) | (fs & (~MITK_FLAG_DELETED)); }
    void ClearFlags() { _flags &= MITK_FLAG_DELETED; }  

private:
    void SetDeleted(bool del=true) { if (del) _flags |= MITK_FLAG_DELETED; else _flags &= (~MITK_FLAG_DELETED); }
    unsigned int _flags;
};

struct _vertex : public _flag_base
{
    union
    {
        Vertex3f vert;
        struct 
        {
            Point3f point;
            Point3f normal;
        };
    };
    HEHalfEdgeHandle outHalfEdge;   
};

struct _half_edge
{
    HEVertexHandle endVertex;
    HEHalfEdgeHandle pairHalfEdge;
    HEHalfEdgeHandle nextHalfEdge;
    HEHalfEdgeHandle prevHalfEdge;
    HEFaceHandle face;
};

struct _edge : public _flag_base
{
    HEHalfEdge halfEdge[2];
};

struct _face : public _flag_base
{
    HEHalfEdgeHandle oneHalfEdge;
};


#endif

