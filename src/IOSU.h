#ifndef _EXPLOIT_H_
#define _EXPLOIT_H_

void IOSUExploit();
void uhs_exploit_init(void);
int uhs_write32(int, int);

#include <coreinit/memory.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/screen.h>
#include <coreinit/memheap.h>
#include <coreinit/cache.h>
#include <coreinit/memfrmheap.h>
#include <coreinit/memory.h>
#include <coreinit/ios.h>
#include <coreinit/mcp.h>
#include <coreinit/systeminfo.h>
#include <coreinit/thread.h>
#include <coreinit/time.h>
#include <coreinit/context.h>
#include <coreinit/exception.h>
#include <coreinit/internal.h>
#include <coreinit/core.h>
#include <coreinit/title.h>
#include <coreinit/debug.h>
#include <coreinit/memorymap.h>
#include <coreinit/dynload.h>
#include <vpad/input.h>
#include <nn/acp/title.h>

#endif