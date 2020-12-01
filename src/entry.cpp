#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <whb/proc.h>
#include <whb/log_udp.h>
#include <whb/log.h>

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
#include "screen.h"

#include <iosuhax.h>
#include "wupserver_bin.h"
#include "IOSU.h"

void ExceptionHandler(const char *type, OSContext *context)
{

	char *symbolname = (char*)OSAllocFromSystem(129, 4);
	memset(symbolname, 0, 129);

	if(OSIsAddressValid(context->srr0) == true)
		OSGetSymbolName(context->srr0, symbolname, 128);
	

	char buffer[0x800];
	__os_snprintf(buffer, 2048,	"Exception: %s - in %s\n"
								"Title ID: %016llX | Core: %d | UPID: %d\n\n"
								""
								"An error has occured.\n"
								"Press the POWER button for 4 seconds to shutdown.\n\n"
								""
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | r%-2d: 0x%08X\n"
								"r%-2d: 0x%08X | r%-2d: 0x%08X | LR : 0x%08X\n"
								"PC : 0x%08X | DAR: 0x%08X | DSISR: 0x%08X\n",
								type, symbolname,
								OSGetTitleID(), OSGetCoreId(), OSGetUPID(),
								0, context->gpr[0], 11, context->gpr[11], 22, context->gpr[22],
								1, context->gpr[1], 12, context->gpr[12], 23, context->gpr[23],
								2, context->gpr[2], 13, context->gpr[13], 24, context->gpr[24],
								3, context->gpr[3], 14, context->gpr[14], 25, context->gpr[25],
								4, context->gpr[4], 15, context->gpr[15], 26, context->gpr[26],
								5, context->gpr[5], 16, context->gpr[16], 27, context->gpr[27],
								6, context->gpr[6], 17, context->gpr[17], 28, context->gpr[28],
								7, context->gpr[7], 18, context->gpr[18], 29, context->gpr[29],
								8, context->gpr[8], 19, context->gpr[19], 30, context->gpr[30],
								9, context->gpr[9], 20, context->gpr[20], 31, context->gpr[31],
								10, context->gpr[10], 21, context->gpr[21], context->lr,
								context->srr0, context->dar, context->dsisr);

	WHBLogPrintf(buffer);
	OSFatal(buffer);

}

BOOL ExcDSI(OSContext *ctx)
{
	ExceptionHandler("DSI", ctx);
	return TRUE;
}

BOOL ExcISI(OSContext *ctx)
{
	ExceptionHandler("ISI", ctx);
	return TRUE;
}

BOOL ExcProgram(OSContext *ctx)
{
	ExceptionHandler("Program", ctx);
	return TRUE;
}

typedef struct FST_Header {
	uint32_t magic; // "FST\0" in ascii
	uint32_t fileOffsetMultiplier;
	int32_t numSecondaryHeaders;
	char unknown[20]; // mostly padding
} FST_Header;

typedef struct FST_SecondaryHeader {

	uint32_t offset;
	uint32_t size;
	uint64_t ownerTitleID;
	uint32_t groupID;
	uint16_t flags;
	char unknown[10];
} FST_SecondaryHeader;

typedef struct FST_FileDirEntry {

	char type;
	char nameOffset[3]; // uint24_t
	uint32_t offset;
	uint32_t size;
	uint16_t flags;
	uint16_t secondaryHeaderIndex;

} FST_FileDirEntry;

int patchFST(WiiUScreen *screen, char *data) {

	int ret = 0;

	FST_Header *fst = (FST_Header*)data;
	FST_SecondaryHeader *fstSndHeaders = (FST_SecondaryHeader*)(data + 0x20);
	FST_FileDirEntry *mainInfoProvider = (FST_FileDirEntry*)(data + 0x20 + (fst->numSecondaryHeaders * 0x20));
	int numFileDirEntries = mainInfoProvider->size - 1;
	mainInfoProvider++;

	if(fst->magic != 0x46535400) {
		return -1;
	}

	int validIdx = -1;
	for(int i = 0; i < fst->numSecondaryHeaders; i++) {
		if(fstSndHeaders[i].flags == 0x0200) {
			validIdx = i;
		}
	}

	if(validIdx >= 0) {
		int numPatch = 0;
		for(int i = 0; i < numFileDirEntries; i++) {
			uint16_t sndIdx = mainInfoProvider[i].secondaryHeaderIndex;
			uint16_t fileDirEntryFlags = fstSndHeaders[sndIdx].flags;
			if(fileDirEntryFlags != 0x0200) {
				numPatch += 1;
				mainInfoProvider[i].secondaryHeaderIndex = validIdx;
			}
		}
		screen->DrawTextf("Patched %d entries.\n", numPatch);
	} else {
		screen->DrawTextf("Couldn't patch the FST. No valid secondary headers found.. (0x0200)\n");
		ret = -1;
	}
	
	return ret;

}

int pageNum = 0;
int totalPageCount = 0;

typedef struct Title {
	bool hovered;
	bool used;
	uint64_t titleId;
	char *appName;
	MCPTitleListType *entry;

} Title;

typedef struct Page {
	Title titles[12];
} Page;

Page pages[0xff]; // up to 3060 titles could be made

void addEntryIntoPages(uint64_t titleId, char *name, MCPTitleListType *entry) {
	
	int counter = 0;
	while(counter != 12) {
		if(!pages[totalPageCount].titles[counter].used) {
			pages[totalPageCount].titles[counter].used = true;
			pages[totalPageCount].titles[counter].titleId = titleId;
			pages[totalPageCount].titles[counter].entry = entry;
			char * appname = (char*)malloc(strlen(name) + 1);
			memcpy(appname, name, strlen(name)+1);
			pages[totalPageCount].titles[counter].appName = appname;
			return;
		}
		counter += 1;
		if(counter == 12) {
			totalPageCount+=1;
			pages[totalPageCount].titles[0].used = true;
			pages[totalPageCount].titles[0].titleId = titleId;
			char * appname = (char*)malloc(strlen(name) + 1);
			memcpy(appname, name, strlen(name)+1);
			pages[totalPageCount].titles[0].appName = appname;
			pages[totalPageCount].titles[0].entry = entry;
			return;
		}
	}

}

bool inWhiteList(uint32_t lowTid) {

	if(lowTid == 0x1004C000) { return true; }
	if(lowTid == 0x1004C100) { return true; }
	if(lowTid == 0x1004C200) { return true; }

	if(lowTid == 0x1004E000) { return true; }
	if(lowTid == 0x1004E100) { return true; }
	if(lowTid == 0x1004E200) { return true; }

	if(lowTid == 0x1005A000) { return true; }
	if(lowTid == 0x1005A100) { return true; }
	if(lowTid == 0x1005A200) { return true; }

	if(lowTid == 0x1005A000) { return true; }
	if(lowTid == 0x1005A100) { return true; }
	if(lowTid == 0x1005A200) { return true; }

	return false;

}

void someFunc(void *arg) {
	return;
}

static int mcp_hook_fd = -1;
int MCPHookOpen() {
	//take over mcp thread
	mcp_hook_fd = MCP_Open();
	if(mcp_hook_fd < 0) {
		return -1;
	}
	IOS_IoctlAsync(mcp_hook_fd, 0x62, (void*)0, 0, (void*)0, 0, (IOSAsyncCallbackFn)someFunc, (void*)0);
	OSSleepTicks(OSSecondsToTicks(1));
	if(IOSUHAX_Open("/dev/mcp") < 0) {
		return -1;
	}

	return 0;
}

void MCPHookClose()
{
	if(mcp_hook_fd < 0)
		return;
	//close down wupserver, return control to mcp
	IOSUHAX_Close();
	//wait for mcp to return
	OSSleepTicks(OSSecondsToTicks(1));
	MCP_Close(mcp_hook_fd);
	mcp_hook_fd = -1;
}

int fsa_read(int fsa_fd, int fd, void *buf, int len)
{
	int done = 0;
	uint8_t *buf_u8 = (uint8_t*)buf;
	while(done < len)
	{
		size_t read_size = len - done;
		int result = IOSUHAX_FSA_ReadFile(fsa_fd, buf_u8 + done, 0x01, read_size, fd, 0);
		if(result < 0)
			return result;
		else
			done += result;
	}
	return done;
}

int fsa_write(int fsa_fd, int fd, void *buf, int len)
{
	int done = 0;
	uint8_t *buf_u8 = (uint8_t*)buf;
	while(done < len)
	{
		size_t write_size = len - done;
		int result = IOSUHAX_FSA_WriteFile(fsa_fd, buf_u8 + done, 0x01, write_size, fd, 0);
		if(result < 0)
			return result;
		else
			done += result;
	}
	return done;
}

int main(int argc, char *argv[]) {

	WHBProcInit();
	WHBLogUdpInit();

	/* Online check + render loop */
	WiiUScreen *screen = new WiiUScreen();

	memset(pages, 0, sizeof(pages));

	int fd = (int)MCP_Open();
	int numTitle = MCP_TitleCount(fd);
	uint32_t tempTitleCount;
	MCPTitleListType *titleList = (MCPTitleListType*)malloc(sizeof(MCPTitleListType) * numTitle);
	MCP_TitleList(fd, &tempTitleCount, titleList, sizeof(MCPTitleListType) * numTitle);

	for(int i = 0; i < numTitle; i++) {
		if(((titleList[i].titleId >> 32) == 0x00050000) || (((titleList[i].titleId >> 32) == 0x00050010) && inWhiteList(titleList[i].titleId & 0xFFFFFFFF))) {
			ACPMetaXml *metaXml = (ACPMetaXml*)malloc(sizeof(ACPMetaXml));
			ACPGetTitleMetaXml(titleList[i].titleId, metaXml);
			addEntryIntoPages(titleList[i].titleId, &metaXml->shortname_en[0], &titleList[i]);
		}
	}
	
	pages[0].titles[0].hovered = true;
	int currentHover = 0;
	bool afterWarning = false;
	MCPTitleListType *selectedApp = NULL;

	while(WHBProcIsRunning()) {
			
		VPADReadError err;
		VPADStatus vpad;

		/* Handle VPAD inputs */
		VPADRead(VPAD_CHAN_0, &vpad, 1, &err);
		uint32_t btn = vpad.hold | vpad.trigger;

		if(btn & VPAD_BUTTON_ZR) {
			if(pageNum < totalPageCount) {
				pageNum++;
			}
			OSSleepTicks(OSMillisecondsToTicks(200));
		}

		if(btn & VPAD_BUTTON_ZL) {
			if(pageNum > 0) {
				pageNum--;
			}
			OSSleepTicks(OSMillisecondsToTicks(200));
		}

		if(btn & VPAD_BUTTON_DOWN) {
			if(currentHover < 12) {
				currentHover++;
			}
			OSSleepTicks(OSMillisecondsToTicks(150));
		}

		if(btn & VPAD_BUTTON_UP) {
			if(currentHover > 0) {
				currentHover--;
			}
			OSSleepTicks(OSMillisecondsToTicks(100));
		}

		if(btn & VPAD_BUTTON_A) {

			OSSleepTicks(OSMillisecondsToTicks(200));
			if(pages[pageNum].titles[currentHover].titleId != 0) {
				
				screen->EndFrame();

				while(WHBProcIsRunning()) {

					VPADRead(VPAD_CHAN_0, &vpad, 1, &err);
					uint32_t btn = vpad.hold | vpad.trigger;

					if(btn & VPAD_BUTTON_X) {
						selectedApp = pages[pageNum].titles[currentHover].entry;
						afterWarning = true;
						break;
					}

					if(btn & VPAD_BUTTON_Y) {
						break;
					}

					screen->StartFrame();

					screen->DrawText("Warning !!!!");
					screen->Y_Position++;
					screen->DrawTextf("This will install FailST into the following title:");
					screen->Y_Position++;
					screen->Y_Position++;
					screen->DrawTextf("   TitleID: %016llx", pages[pageNum].titles[currentHover].titleId);
					screen->DrawTextf("Title Name: %s", pages[pageNum].titles[currentHover].appName);
					screen->Y_Position++;
					screen->Y_Position++;
					screen->Y_Position++;
					screen->Y_Position++;
					screen->Y_Position++;
					screen->DrawText("Press X to install, or press Y to quit");
					
					screen->EndFrame();

				}

				if(afterWarning) {
					break;
				}

			}
		}

		screen->StartFrame();

		screen->DrawText("Press ZL for previous page, Press ZR for next page");
		screen->DrawText("Press UP or DOWN to move in the menu then A to select the title");
		screen->DrawTextf("Total of %d pages! (%d / %d)", totalPageCount, pageNum, totalPageCount);
		screen->Y_Position++;
		screen->Y_Position++;

		for (int i = 0; i < 12; i++) {
			if(pages[pageNum].titles[i].used) {
				screen->DrawTextf("%s %016llx: %s", (currentHover == i) ? "> " : "  ", pages[pageNum].titles[i].titleId, pages[pageNum].titles[i].appName);
			}
		}
		

		screen->EndFrame();

	}

	screen->EndFrame();
	screen->StartFrame();
	screen->EndFrame();
	screen->StartFrame();

	if(afterWarning) {

		int fsaFd = - 1;
		
		char *titleFst_Data = NULL;
		int titleFst_R = - 1;
		int titleFst_W = - 1;

		screen->FlushEveryDraw = true;
		screen->Y_Position = 0;
		screen->DrawText("Doing IOSU Exploit and triggering mcp hook..");

		int res = IOSUHAX_Open(NULL);
		if(res < 0) {
			res = MCPHookOpen();
		}
		if(res < 0) {
			*(volatile unsigned int*)0xF5E70000 = wupserver_bin_len;
			memcpy((void*)0xF5E70020, &wupserver_bin, wupserver_bin_len);
			DCStoreRange((void*)0xF5E70000, wupserver_bin_len + 0x40);
			IOSUExploit();
			if(MCPHookOpen() < 0) {
				screen->DrawText("Didn't work D: exiting in 5...");
				OSSleepTicks(OSSecondsToTicks(5));
				goto end;
			}
		}

		screen->DrawText("Success Hooking our wupserver!");

		fsaFd = IOSUHAX_FSA_Open();
		if(fsaFd < 0) {
			screen->DrawText("Couldn't open FSA, exiting in 5...");
			OSSleepTicks(OSSecondsToTicks(5));
			goto end;
		}

		char *fileName = (char*)malloc(256);
		__os_snprintf(fileName, 256, "%s/code/title.fst", selectedApp->path);
		WHBLogPrintf("Path: %s", fileName);
		if(IOSUHAX_FSA_OpenFile(fsaFd, fileName, "rb", &titleFst_R) >= 0) {
			fileStat_s stats;
			IOSUHAX_FSA_StatFile(fsaFd, titleFst_R, &stats);
			size_t titleFstSize = stats.size;
			WHBLogPrintf("Size: %d", titleFstSize);
			titleFst_Data = (char*)malloc(titleFstSize);
			fsa_read(fsaFd, titleFst_R, titleFst_Data, titleFstSize);
			IOSUHAX_FSA_CloseFile(fsaFd, titleFst_R);

			if(patchFST(screen, titleFst_Data) < 0) {
				screen->DrawText("Couldn't patch title.fst, exiting in 5...");
				OSSleepTicks(OSSecondsToTicks(5));
				goto end;
			}

			if(IOSUHAX_FSA_OpenFile(fsaFd, fileName, "wb", &titleFst_W) < 0) {
				screen->DrawText("Couldn't open title.fst (write), exiting in 5...");
				OSSleepTicks(OSSecondsToTicks(5));
				goto end;
			}

			fsa_write(fsaFd, titleFst_W, titleFst_Data, titleFstSize);
			IOSUHAX_FSA_CloseFile(fsaFd, titleFst_W);

		} else {
			screen->DrawText("Couldn't open title.fst (read), exiting in 5...");
			OSSleepTicks(OSSecondsToTicks(5));
			goto end;
		}

		if((mcp_hook_fd >= 0) && (IOSUHAX_FSA_FlushVolume(fsaFd, "/vol/storage_mlc01") == 0)) {
			screen->DrawText("Flushed MLC !");
		} else {
			screen->DrawText("Couldn't flush MLC .. restart console from the WiiU Menu cleanly.");
		}

		screen->DrawText("Done! Exiting in 3 seconds..");
		OSSleepTicks(OSSecondsToTicks(3));
	}

end:

	if(mcp_hook_fd >= 0)
		MCPHookClose();
	else
		IOSUHAX_Close();

	WHBProcShutdown();
	return 0;

}