/*
-----------------------------------------------------------------------
This source file is part of "cgcourse-examples"
(Examples for Computer Graphics Course of CCCE GUCAS.)
Copyright (C) 2011 Xue Jian (jian.xue.cn@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------
*/

#ifndef __cpucounter_h
#define __cpucounter_h

// system dependent, for accurate calculation of cpu counts
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

class CPUCounter
{
public:
    CPUCounter() : counts(0) {}

    void CounterStart()
    {
#ifdef WIN32
        LARGE_INTEGER li;
        ::QueryPerformanceCounter(&li);
        counts = (double)(li.QuadPart);
#else
        counts = static_cast<double>(clock());
#endif
    }

    double GetCounts()
    {
#ifdef WIN32
        LARGE_INTEGER li;
        ::QueryPerformanceCounter(&li);
        return (static_cast<double>(li.QuadPart) - counts);
#else
        return (static_cast<double>(clock()) - counts);
#endif
    }

    double GetFrequence()
    {
#ifdef WIN32
        LARGE_INTEGER li;
        ::QueryPerformanceFrequency(&li);
        return static_cast<double>(li.QuadPart);
#else
        return static_cast<double>(CLOCKS_PER_SEC);
#endif
    }

protected:
    double counts;

};

#endif
