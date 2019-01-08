/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkThreadMaster_h
#define __mitkThreadMaster_h

#include "mitkObject.h"

class mitkThreadDelegate;
/// mitkThreadWorker - encapsulates a worker of the Master/Worker model.
/// A worker can be driven by a thread of the master to fulfil the scheduled tasks. 
///////////////////////////////////////////////////////////////////////////
/// mitkThreadWorker encapsules a worker of the Master/Worker model.
/// A worker can be driven by a thread of the master to fulfil the scheduled tasks. 
/// The class can be subclassed as a specific implementation of some parallel part 
/// of an algorithm. 
class MITK_COMMON_API mitkThreadWorker :public mitkObject
{
public:
    MITK_TYPE(mitkThreadWorker,mitkObject)
    mitkThreadWorker(){}
    friend class mitkThreadMaster;
protected:
    virtual ~mitkThreadWorker(){}
    ///////////////////////////////////////////////////////////////////////////
    /// Overwrite this function when more than one task will be done in do task 
    /// function. The master use this function to decide the progress.
    /// \return Return the number of tasks done in each call to DoTask
    ///////////////////////////////////////////////////////////////////////////
    virtual int TasksPerTime() {return 1;}
    ///////////////////////////////////////////////////////////////////////////
    /// Called by the master when a group of tasks are sent to be done
    /// \param taskBag Information of the group of tasks
    ///////////////////////////////////////////////////////////////////////////
    virtual void SendTaskBag(void *taskBag) {}
    ///////////////////////////////////////////////////////////////////////////
    /// Do the scheduled task, called automatically by master
    /// \param taskID Sent by master indicating the task (or the first of the tasks)
    /// that should be done.
    /// \param taskNumber Sent by master indicating how many tasks actually should
    /// be done. It is no less than 1 and no more than the return value of 
    /// TasksPerTime
    ///////////////////////////////////////////////////////////////////////////
    virtual void DoTask(int taskID,int taskNumber)=0;
    ///////////////////////////////////////////////////////////////////////////
    /// Should be implemented. Used by master to duplicate workers from a single
    /// "sample worker".
    ///////////////////////////////////////////////////////////////////////////
    virtual mitkThreadWorker *Duplicate()=0;
private:
    mitkThreadWorker(const mitkThreadWorker&);
    void operator = (const mitkThreadWorker&);
};

/// mitkThreadWorkerCreator - An abstract class whose descendant can be used by 
/// master to create workers. Subclass it when different kind of workers should be
/// used is calculation.
///////////////////////////////////////////////////////////////////////////
/// mitkThreadWorkerCreator is an abstract class whose descendant can be used by 
/// master to create workers. Subclass it when different kind of workers should be
/// used is calculation.
class MITK_COMMON_API mitkThreadWorkerCreator : public mitkObject
{
public:
    MITK_TYPE(mitkThreadWorkerCreator,mitkObject)
    mitkThreadWorkerCreator(){}
    ///////////////////////////////////////////////////////////////////////////
    /// Called by master to decided how many workers(threads) should be created
    /// \return Return the desired number of workers
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetWorkerNum();
    ///////////////////////////////////////////////////////////////////////////
    /// Called by master to create workers. 
    /// \param WorkerID id of the worker currently being created
    /// \return Return a pointer to the created worker
    ///////////////////////////////////////////////////////////////////////////
    virtual mitkThreadWorker* CreateThreadWorker(int WorkerID)=0;
protected:
    virtual ~mitkThreadWorkerCreator(){}
private:
    mitkThreadWorkerCreator(const mitkThreadWorkerCreator&);
    void operator = (const mitkThreadWorkerCreator&);
};

class mitkThread;
class mitkConditionVariable;
#include "mitkMutex.h"
/// mitkThreadMaster - encapsulates a master of the master/worker model
///////////////////////////////////////////////////////////////////////////
/// mitkThreadMaster encapsulates a master of the master/worker model
/// It creates workers when it is initialized either by a "worker creator"
/// or by duplicating an existing "sample worker". If workers are created
/// by duplication, the "sample worker" itself will be referenced as one 
/// of the workers. And then, the master creates corresponding threads 
/// to drive the workers.
class MITK_COMMON_API mitkThreadMaster : public mitkObject
{
public:
    MITK_TYPE(mitkThreadMaster,mitkObject)
    mitkThreadMaster(mitkThreadWorkerCreator* workerCreator);
    mitkThreadMaster(mitkThreadWorker* sampleWorker);
    mitkThreadMaster(int threadNumber,mitkThreadWorker* sampleWorker);
    ///////////////////////////////////////////////////////////////////////////
    /// Get the number of threads spawned.
    /// \return Return the number of threads spawned.
    ///////////////////////////////////////////////////////////////////////////
    int GetThreadNumber() const
    {
        return m_threadNumber;
    }
    ///////////////////////////////////////////////////////////////////////////
    /// When this function is called, threads are waken up to drive the workers.
    /// Tasks are dynamically scheduled, which means a worker will receive a new 
    /// task immediately after it finishes its current one. The function won't 
    /// return until all scheduled tasks are done.
    /// \param taskNumber Specify how many tasks to be scheduled
    /// \param startID Specify where the ID of tasks starts from
    /// \param taskBag Sent to workers to describe current group of tasks
    ///////////////////////////////////////////////////////////////////////////
    void DoTasks(unsigned long taskNumber,unsigned long startID=0,void *taskBag=NULL);

protected:
    virtual ~mitkThreadMaster();

private:
    mitkThreadMaster (const mitkThreadMaster&);
    void operator = (const mitkThreadMaster&);

    int m_threadNumber;
    mitkThreadDelegate** m_threads;
    int *m_threadIDs;

    mitkThreadWorker **m_workers;

    unsigned long m_taskNumber;
    unsigned long m_taskProgress;
    unsigned long m_taskStartID;

    int m_toDoValue,m_doneValue;
    mitkConditionVariable *m_toDoCV;
    mitkConditionVariable *m_doneCV;
    mitkMutex *m_progressMutex;

    void _init(mitkThreadWorker* sampleWorker);
    unsigned long _getProgress(int step)
    {
        unsigned long prog;
        m_progressMutex->Lock();
        prog=m_taskProgress;
        m_taskProgress+=step;
        m_progressMutex->Unlock();
        return prog;
    }
    void _threadEntrance(void *param);

};

#endif

