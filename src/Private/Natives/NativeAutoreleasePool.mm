#include <KYEngine/Private/Natives/NativeAutoreleasePool.h>

#import <Foundation/Foundation.h>

NativeAutoreleasePool::NativeAutoreleasePool()
{
    m_pool = [[NSAutoreleasePool alloc] init];
}

NativeAutoreleasePool::~NativeAutoreleasePool()
{
    NSAutoreleasePool* pool = (NSAutoreleasePool*) m_pool;
    [pool drain];
}