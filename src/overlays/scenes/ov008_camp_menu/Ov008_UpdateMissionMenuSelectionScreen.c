/* Mission selection screen: reads the menu input, requests the chosen menu state with a sound, and
 * draws the option text rows and cursor; returns the next state. */

#include "nitro/types.h"
#include "game/engine.h"

typedef void (*MissionState)(void);

typedef struct {
    void *resourceBase;
    u32 resourceValue;
    void *resourceData;
} MissionResourceRecord;

typedef struct {
    u8 pad_00[0x20];
    u32 sessionReady;
    u32 parametersReady;
    u32 singleRowMode;
    u32 menuState;
    u8 optionMask;
    u8 messageStateFlag;
    u16 messageId;
    u16 messageVariant;
    u8 pad_36[0x2a];
    MissionResourceRecord resource;
} MissionMenuContext;

extern MissionMenuContext *data_ov008_02090fa0;
extern u16 data_ov008_02090d0c[8];

extern int Ov008_IsMissionMenuExitRequested(void);
extern void Ov008_MissionMenuHookNoOp(void);
extern int Ov008_CanConfirmMissionMenu(void);
extern int Ov008_IsMissionMenuBusy(void);
extern int Ov008_ReadMissionMenuAction(void);
extern unsigned short WH_GetCurrentAid(void);
extern int Ov008_TickInputUpdate(void);
extern void Ov008_RequestMenuState(int state, int arg1, int arg2);
extern int Ov008_GetMissionScreenFlag(void);
extern void Ov008_SetTickSlotByte(int value);
extern int Ov008_IsSubMenuSceneReady(void);
extern void Ov008_Link_InstallSceneCallback(void);
extern void Ov008_ResetTextLayers(void);
extern void *Ov008_GetVarRecordByIndex(void *resource, u32 index);
extern void Ov008_ForwardSevenArgs(void *text, int x, int y, int style, int layer, int align,
                                   int visible);
extern u16 Ov008_GetMissionOptionMask(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void Ov008_CopyMissionOptionTextRows(void *destination);
extern void Ov008_MissionToggleSlotVisible(int visible);
extern void Ov008_SetMissionCursorSelection(int selection);
extern unsigned short WH_GetBitmap(void);
extern int Ov008_GetMissionMenuSelection(void);
extern void Ov008_FlushTextLayers(void);

extern void Ov008_MissionInitVideoScene(void);
extern void Ov008_MissionMenuTick(void);
extern void Ov008_MissionMenuWaitReady(void);

MissionState Ov008_UpdateMissionMenuSelectionScreen(void)
{
    MissionState nextState;
    int menuAction;
    int transitionReady;
    void *textRecord;
    u16 optionMask;
    u16 optionTextRows[44];
    u32 sourceRowIndex;
    u32 visibleRowIndex;
    u32 textId;

    nextState = 0;
    menuAction = 0;

    if (data_ov008_02090fa0->sessionReady == 0 &&
        Ov008_IsMissionMenuExitRequested() != 0) {
        Ov008_MissionMenuHookNoOp();
        return Ov008_MissionInitVideoScene;
    }

    if (Game_PollSceneAlive() == 8) {
        return Ov008_MissionMenuTick;
    }

    if (Ov008_CanConfirmMissionMenu() != 0) {
        Ov008_MissionMenuHookNoOp();
        return Ov008_MissionInitVideoScene;
    }

    if (Ov008_IsMissionMenuBusy() == 0) {
        menuAction = Ov008_ReadMissionMenuAction();
    }

    transitionReady = 1;
    if (data_ov008_02090fa0->sessionReady != 0) {
        if (WH_GetCurrentAid() != 0) {
            transitionReady = 0;
        }
        if (data_ov008_02090fa0->messageStateFlag != 0) {
            transitionReady = 0;
        }
    }

    if (transitionReady != 0 && menuAction == 1) {
        if (data_ov008_02090fa0->sessionReady != 0) {
            data_ov008_02090fa0->singleRowMode = Ov008_TickInputUpdate();
        }
        data_ov008_02090fa0->messageStateFlag = 4;
        Ov008_RequestMenuState(0xd, 1, 0);
        PlaySound(0, 0x30);
        nextState = Ov008_MissionMenuWaitReady;
    }

    switch (data_ov008_02090fa0->messageStateFlag) {
    case 0:
        if (Ov008_GetMissionScreenFlag() == 0 &&
            Game_PollSceneAlive() == 4 &&
            (data_ov008_02090fa0->sessionReady != 0 ||
             Ov008_IsMissionMenuBusy() == 0) &&
            menuAction == 3) {
            if (data_ov008_02090fa0->sessionReady == 0) {
                Ov008_SetTickSlotByte(1);
                data_ov008_02090fa0->messageStateFlag = 1;
            } else {
                PlaySound(0, 3);
                data_ov008_02090fa0->messageStateFlag = 2;
            }
        }
        break;

    case 1:
        menuAction = Ov008_GetMissionScreenFlag();
        if (menuAction != 1) {
            break;
        }
        PlaySound(0, 3);
        data_ov008_02090fa0->messageStateFlag = 2;
    case 2:
        if (Ov008_IsSubMenuSceneReady() == 0) {
            Ov008_Link_InstallSceneCallback();
        }
        data_ov008_02090fa0->messageStateFlag = 3;
        break;

    case 3:
        if (Ov008_IsSubMenuSceneReady() != 0) {
            nextState = Ov008_MissionMenuTick;
        }
        break;
    }

    Ov008_ResetTextLayers();

    if (data_ov008_02090fa0->sessionReady == 0) {
        data_ov008_02090fa0->messageVariant++;
        if (data_ov008_02090fa0->messageVariant > 0x3c) {
            data_ov008_02090fa0->messageVariant = 0;
            if (data_ov008_02090fa0->messageId == 0x34) {
                data_ov008_02090fa0->messageId = 0x40;
            } else {
                data_ov008_02090fa0->messageId = 0x34;
            }
        }
    }

    textRecord = Ov008_GetVarRecordByIndex(
        &data_ov008_02090fa0->resource,
        data_ov008_02090fa0->messageId);
    Ov008_ForwardSevenArgs(textRecord, 0xfa, 2, 1, 1, 1, 1);

    if (data_ov008_02090fa0->sessionReady != 0) {
        textId = 0x41;
    } else {
        textId = 0x42;
    }
    textRecord = Ov008_GetVarRecordByIndex(
        &data_ov008_02090fa0->resource, textId);
    Ov008_ForwardSevenArgs(textRecord, 0x80, 0x60, 1, 1, 3, 1);

    optionMask = Ov008_GetMissionOptionMask();
    MI_CpuFill8(optionTextRows, 0, 0x58);
    Ov008_CopyMissionOptionTextRows(optionTextRows);

    visibleRowIndex = 0;
    sourceRowIndex = 0;
    do {
        if ((optionMask & (1 << sourceRowIndex)) != 0 &&
            *(u16 *)((u8 *)optionTextRows + sourceRowIndex * 0x16) != 0) {
            Ov008_ForwardSevenArgs((u8 *)optionTextRows + sourceRowIndex * 0x16, 99,
                                   visibleRowIndex * 0x18 + 0x23, 1, 1, 0, 0);
            visibleRowIndex = (visibleRowIndex + 1) & 0xff;
        }
        sourceRowIndex = (sourceRowIndex + 1) & 0xff;
    } while (sourceRowIndex < 4);

    while (visibleRowIndex < 4) {
        Ov008_ForwardSevenArgs(data_ov008_02090d0c, 99, visibleRowIndex * 0x18 + 0x23, 1, 1, 0, 0);
        visibleRowIndex = (visibleRowIndex + 1) & 0xff;
    }

    if (data_ov008_02090fa0->sessionReady != 0) {
        if (Ov008_IsMissionMenuBusy() == 0) {
            textRecord = Ov008_GetVarRecordByIndex(
                &data_ov008_02090fa0->resource, 0x43);
            Ov008_ForwardSevenArgs(textRecord, 0x80, 0x98, 1, 1, 3, 0);
            Ov008_MissionToggleSlotVisible(1);
        } else {
            Ov008_MissionToggleSlotVisible(0);
            textRecord = Ov008_GetVarRecordByIndex(
                &data_ov008_02090fa0->resource, 0x43);
            Ov008_ForwardSevenArgs(textRecord, 0x80, 0x98, 1, 1, 3, 0);
        }
    }

    Ov008_SetMissionCursorSelection(-1);
    if (data_ov008_02090fa0->sessionReady != 0) {
        if (WH_GetBitmap() > 1) {
            Ov008_SetMissionCursorSelection(Ov008_GetMissionMenuSelection());
        }
    } else {
        if (WH_GetBitmap() != 0) {
            Ov008_SetMissionCursorSelection(Ov008_GetMissionMenuSelection());
        }
    }

    if (Game_PollSceneAlive() == 4 && Ov008_IsMissionMenuBusy() == 0) {
        if (data_ov008_02090fa0->sessionReady != 0) {
            textId = 0x45;
        } else {
            textId = 0x46;
        }
        textRecord = Ov008_GetVarRecordByIndex(
            &data_ov008_02090fa0->resource, textId);
        Ov008_ForwardSevenArgs(textRecord, 10, 0xb4, 1, 1, 0, 0);
    }

    Ov008_FlushTextLayers();
    return nextState;
}