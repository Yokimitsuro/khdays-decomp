/* Runs the opening-scene script and display loop, handles skip input and thread-count changes,
 * waits for the brightness transition, then resets the script/display state and selects the next
 * scene. */

#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int VBlank_GetCount(void);
extern void OS_WaitVBlankIntr(void);
extern void GX_DispOff(void);
extern void DispCnt_ApplyPendingMode(void);
extern int PM_SetLCDPower(int mode);
extern void SetMasterBrightnessMain(int brightness);
extern void SetMasterBrightnessSub(int brightness);
extern int GetMasterBrightnessMain(void);
extern int GetMasterBrightnessSub(void);
extern void Obj_ResetBothSubBlocksAndArm(void *script);
extern int Game_RunActionScript(void *script);
extern void ActionScript_RequestSkip(void *script);
extern void Session_SetMoviePlaying(int value);
extern void MsgQueue_SetMoviePlaying(int value);
extern int Ov012_IsCounterAt16(void);
extern void Ov012_ProcessOpeningTimeline(void *context, int delta);
extern void Ov012_SetHeapFlag8CheckFlag10(void);
extern void Ov024_MobiClip_StopPlayback(void);
extern int Ov024_TickStreamSlots(void);

void *Ov012_RunOpeningScene(void) {
    char *context;
    int exitSceneId;

    context = (char *)NNSi_FndGetCurrentRootHeap();
    if ((*(u16 *)(context + 2) & 2) == 0) {
        if (*(int *)(context + 0x8bd8) == 2 ||
            *(int *)(context + 0x8bdc) == 2) {
            int previousThreadCount;
            int initialThreadCount;
            int currentThreadCount;
            int loopStatus;
            u32 pressedKeys;
            u16 normalizedKeys;
            u16 *rawKeys;
            u16 *systemFlags;
            u32 keyMask;

            previousThreadCount = VBlank_GetCount();
            initialThreadCount = previousThreadCount;
            loopStatus = Ov024_TickStreamSlots();
            if (loopStatus == 0) {
                rawKeys = (u16 *)0x04000130;
                systemFlags = (u16 *)0x027fffa8;
                keyMask = 0x2fff;
                do {
                    if ((*(u16 *)(context + 2) & 4) != 0) {
                        if (Ov012_IsCounterAt16() != 0) {
                            if ((*(u16 *)(context + 2) & 1) != 0) {
                                ActionScript_RequestSkip(context + 4);
                            }
                            break;
                        }
                    } else if (*(u8 *)(context + 0x8be0) == 0) {
                        normalizedKeys = ((*rawKeys | *systemFlags) ^ keyMask) & keyMask;
                        pressedKeys = normalizedKeys & 8;
                        if (*(u32 *)(context + 0x8bec) == 0 && pressedKeys != 0) {
                            *(int *)(context + 0x8be8) = 0;
                            *(u16 *)(context + 2) |= 4;
                        }
                        *(u32 *)(context + 0x8bec) = pressedKeys;
                    }

                    if ((*(u16 *)(context + 2) & 1) != 0 &&
                        Game_RunActionScript(context + 4) == 0) {
                        *(u16 *)(context + 2) &= ~1;
                    }

                    currentThreadCount = VBlank_GetCount();
                    if (previousThreadCount != currentThreadCount) {
                        Ov012_ProcessOpeningTimeline(context,
                                            currentThreadCount - initialThreadCount);
                        previousThreadCount = currentThreadCount;
                    }

                    if (*(u8 *)(context + 0x8be0) == 0 &&
                        ((int)(*systemFlags & 0x8000) >> 15) != 0) {
                        GX_DispOff();
                        PM_SetLCDPower(0);
                        *(u8 *)(context + 0x8be0) = 1;
                    } else if (*(u8 *)(context + 0x8be0) != 0 &&
                               ((int)(*systemFlags & 0x8000) >> 15) == 0 &&
                               PM_SetLCDPower(1) != 0) {
                        *(u8 *)(context + 0x8be0) = 0;
                        SetMasterBrightnessMain(GetMasterBrightnessMain());
                        SetMasterBrightnessSub(GetMasterBrightnessSub());
                        DispCnt_ApplyPendingMode();
                    }
                } while (Ov024_TickStreamSlots() == 0);
            }

            if ((*(u16 *)(context + 2) & 4) != 0) {
                while (Ov012_IsCounterAt16() == 0) {
                    OS_WaitVBlankIntr();
                }
                if ((*(u16 *)(context + 2) & 1) != 0) {
                    ActionScript_RequestSkip(context + 4);
                }
            }
            Ov024_MobiClip_StopPlayback();
            *(int *)(context + 0x8bd8) = *(int *)(context + 0x8bdc) = 3;
            if ((*(u16 *)(context + 2) & 1) != 0) {
                goto brightness_only;
            }
            goto cleanup;
        }
    }

    if (Game_RunActionScript(context + 4) == 0) {
        goto cleanup;
    }

brightness_only:
    SetMasterBrightnessMain(-16);
    SetMasterBrightnessSub(-16);
    return 0;

cleanup:
    Obj_ResetBothSubBlocksAndArm(context + 4);
    MsgQueue_SetMoviePlaying(0);
    Session_SetMoviePlaying(0);
    exitSceneId = *(int *)(context + 0x130);
    if (exitSceneId == 0 || (exitSceneId != 1 && exitSceneId == 2)) {
        *(u16 *)context = 2;
    }
    SetMasterBrightnessMain(-16);
    SetMasterBrightnessSub(-16);
    return (void *)Ov012_SetHeapFlag8CheckFlag10;
}