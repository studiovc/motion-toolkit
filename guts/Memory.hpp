/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_MEMORY_HPP
#define GUTS_MEMORY_HPP

#include <consolid/consolid.h>

#ifndef NDEBUG
#include "MemAllocLog.hpp"

#define REPORT_LEAKS() guts::MemAllocLog::instance().logLeaks()
#define ALLOCATE(T) static_cast<T*>(guts::MemAllocLog::instance().alloc(sizeof(T), __FILE__, __LINE__))
#define ALLOCATE_ARRAY(T, n) static_cast<T*>(guts::MemAllocLog::instance().alloc((n) * sizeof(T), __FILE__, __LINE__))
#define DEALLOCATE(p) guts::MemAllocLog::instance().free(p)

#else

#include "MemAlloc.hpp"

#define REPORT_LEAKS() ((void)0)
#define ALLOCATE(T) static_cast<T*>(guts::MemAlloc::instance().alloc(sizeof(T)))
#define ALLOCATE_ARRAY(T, n) static_cast<T*>(guts::MemAlloc::instance().alloc((n) * sizeof(T)))
#define DEALLOCATE(p) guts::MemAlloc::instance().free(p)

#endif

#define CREATE(T) new(ALLOCATE(T)) T
#define DESTROY(p) guts::destroy(p)

#define CREATE_ARRAY(T, n) guts::createArray(ALLOCATE_ARRAY(T, n), n)
#define DESTROY_ARRAY(p, n) guts::destroyArray(p, n)

namespace guts
{
    template <typename T>
    FORCEINLINE
    void destroy(T* p)
    {
        if (p)
        {
            p->~T();
        }
        DEALLOCATE(p);
    }

    template <typename T>
    FORCEINLINE
    T* createArray(T* p, size_t n)
    {
        for (size_t i = 0; i != n; ++i)
        {
            new (&p[i]) T();
        }

        return p;
    }

    
    template <typename T>
    FORCEINLINE
    void destroyArray(T* p, size_t n)
    {
        if (p)
        {
            for (size_t i = 0; i != n; ++i)
            {
                p[i].~T();
            }
        }

        DEALLOCATE(p);
    }
}
  
#endif

