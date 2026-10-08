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

extern MissionMenuContext *data_ov006_02056660;
extern u16 data_ov006_0205651c[8];

extern int Ov006_IsMissionMenuExitRequested(void);
extern void Ov006_BlankScreensAndTeardownText(void);
extern int Ov006_CanConfirmMissionMenu(void);
extern int Ov006_IsMissionMenuBusy(void);
extern int Ov006_ReadMissionMenuAction(void);
extern unsigned short WH_GetCurrentAid(void);
extern int Ov006_TickInputUpdate(void);
extern void Ov006_RequestMenuState(int state, int arg1, int arg2);
extern int Ov006_GetMissionScreenFlag(void);
extern void Ov006_SetTickSlotByte(u8 value);
extern int Ov006_IsSubMenuSceneReady(void);
extern void Ov006_MissionLeaveSubMenu_Ov105(void);
extern void Ov006_ResetTextLayers(void);
extern void *Ov006_GetVarRecordByIndex(void *resource, u32 index);
extern void Ov006_MissionDrawTextRunFwd(void *text, int x, int y, int style, int layer, int align,
                                        int visible);
extern u16 Ov006_GetMissionOptionMask(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void Ov006_CopyMissionOptionTextRows(void *destination);
extern void Ov006_MissionToggleSlotVisible(int visible);
extern void Ov006_SetMissionCursorSelection(int selection);
extern unsigned short WH_GetBitmap(void);
extern int Ov006_GetMissionMenuSelection(void);
extern void Ov006_FlushTextLayers(void);

extern void Ov006_MissionInitVideoScene(void);
extern void Ov006_MissionMenuTick(void);
extern void Ov006_MissionBuildOptionRows(void);

MissionState Ov006_UpdateMissionMenuSelectionScreen(void)
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

    if (data_ov006_02056660->sessionReady == 0 &&
        Ov006_IsMissionMenuExitRequested() != 0) {
        Ov006_BlankScreensAndTeardownText();
        return Ov006_MissionInitVideoScene;
    }

    if (Game_PollSceneAlive() == 8) {
        return Ov006_MissionMenuTick;
    }

    if (Ov006_CanConfirmMissionMenu() != 0) {
        Ov006_BlankScreensAndTeardownText();
        return Ov006_MissionInitVideoScene;
    }

    if (Ov006_IsMissionMenuBusy() == 0) {
        menuAction = Ov006_ReadMissionMenuAction();
    }

    transitionReady = 1;
    if (data_ov006_02056660->sessionReady != 0) {
        if (WH_GetCurrentAid() != 0) {
            transitionReady = 0;
        }
        if (data_ov006_02056660->messageStateFlag != 0) {
            transitionReady = 0;
        }
    }

    if (transitionReady != 0 && menuAction == 1) {
        if (data_ov006_02056660->sessionReady != 0) {
            data_ov006_02056660->singleRowMode = Ov006_TickInputUpdate();
        }
        data_ov006_02056660->messageStateFlag = 4;
        Ov006_RequestMenuState(0xd, 1, 0);
        PlaySound(0, 0x30);
        nextState = Ov006_MissionBuildOptionRows;
    }

    switch (data_ov006_02056660->messageStateFlag) {
    case 0:
        if (Ov006_GetMissionScreenFlag() == 0 &&
            Game_PollSceneAlive() == 4 &&
            (data_ov006_02056660->sessionReady != 0 ||
             Ov006_IsMissionMenuBusy() == 0) &&
            menuAction == 3) {
            if (data_ov006_02056660->sessionReady == 0) {
                Ov006_SetTickSlotByte(1);
                data_ov006_02056660->messageStateFlag = 1;
            } else {
                PlaySound(0, 3);
                data_ov006_02056660->messageStateFlag = 2;
            }
        }
        break;

    case 1:
        menuAction = Ov006_GetMissionScreenFlag();
        if (menuAction != 1) {
            break;
        }
        PlaySound(0, 3);
        data_ov006_02056660->messageStateFlag = 2;
    case 2:
        if (Ov006_IsSubMenuSceneReady() == 0) {
            Ov006_MissionLeaveSubMenu_Ov105();
        }
        data_ov006_02056660->messageStateFlag = 3;
        break;

    case 3:
        if (Ov006_IsSubMenuSceneReady() != 0) {
            nextState = Ov006_MissionMenuTick;
        }
        break;
    }

    Ov006_ResetTextLayers();

    if (data_ov006_02056660->sessionReady == 0) {
        data_ov006_02056660->messageVariant++;
        if (data_ov006_02056660->messageVariant > 0x3c) {
            data_ov006_02056660->messageVariant = 0;
            if (data_ov006_02056660->messageId == 0x34) {
                data_ov006_02056660->messageId = 0x40;
            } else {
                data_ov006_02056660->messageId = 0x34;
            }
        }
    }

    textRecord = Ov006_GetVarRecordByIndex(
        &data_ov006_02056660->resource,
        data_ov006_02056660->messageId);
    Ov006_MissionDrawTextRunFwd(textRecord, 0xfa, 2, 1, 1, 1, 1);

    if (data_ov006_02056660->sessionReady != 0) {
        textId = 0x41;
    } else {
        textId = 0x42;
    }
    textRecord = Ov006_GetVarRecordByIndex(
        &data_ov006_02056660->resource, textId);
    Ov006_MissionDrawTextRunFwd(textRecord, 0x80, 0x60, 1, 1, 3, 1);

    optionMask = Ov006_GetMissionOptionMask();
    MI_CpuFill8(optionTextRows, 0, 0x58);
    Ov006_CopyMissionOptionTextRows(optionTextRows);

    visibleRowIndex = 0;
    sourceRowIndex = 0;
    do {
        if ((optionMask & (1 << sourceRowIndex)) != 0 &&
            *(u16 *)((u8 *)optionTextRows + sourceRowIndex * 0x16) != 0) {
            Ov006_MissionDrawTextRunFwd((u8 *)optionTextRows + sourceRowIndex * 0x16, 99,
                                        visibleRowIndex * 0x18 + 0x23, 1, 1, 0, 0);
            visibleRowIndex = (visibleRowIndex + 1) & 0xff;
        }
        sourceRowIndex = (sourceRowIndex + 1) & 0xff;
    } while (sourceRowIndex < 4);

    while (visibleRowIndex < 4) {
        Ov006_MissionDrawTextRunFwd(data_ov006_0205651c, 99, visibleRowIndex * 0x18 + 0x23, 1, 1, 0,
                                    0);
        visibleRowIndex = (visibleRowIndex + 1) & 0xff;
    }

    if (data_ov006_02056660->sessionReady != 0) {
        if (Ov006_IsMissionMenuBusy() == 0) {
            textRecord = Ov006_GetVarRecordByIndex(
                &data_ov006_02056660->resource, 0x43);
            Ov006_MissionDrawTextRunFwd(textRecord, 0x80, 0x98, 1, 1, 3, 0);
            Ov006_MissionToggleSlotVisible(1);
        } else {
            Ov006_MissionToggleSlotVisible(0);
            textRecord = Ov006_GetVarRecordByIndex(
                &data_ov006_02056660->resource, 0x43);
            Ov006_MissionDrawTextRunFwd(textRecord, 0x80, 0x98, 1, 1, 3, 0);
        }
    }

    Ov006_SetMissionCursorSelection(-1);
    if (data_ov006_02056660->sessionReady != 0) {
        if (WH_GetBitmap() > 1) {
            Ov006_SetMissionCursorSelection(Ov006_GetMissionMenuSelection());
        }
    } else {
        if (WH_GetBitmap() != 0) {
            Ov006_SetMissionCursorSelection(Ov006_GetMissionMenuSelection());
        }
    }

    if (Game_PollSceneAlive() == 4 && Ov006_IsMissionMenuBusy() == 0) {
        if (data_ov006_02056660->sessionReady != 0) {
            textId = 0x45;
        } else {
            textId = 0x46;
        }
        textRecord = Ov006_GetVarRecordByIndex(
            &data_ov006_02056660->resource, textId);
        Ov006_MissionDrawTextRunFwd(textRecord, 10, 0xb4, 1, 1, 0, 0);
    }

    Ov006_FlushTextLayers();
    return nextState;
}