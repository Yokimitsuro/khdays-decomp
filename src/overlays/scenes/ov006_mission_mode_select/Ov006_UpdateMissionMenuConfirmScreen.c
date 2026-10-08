/* Mission confirmation screen: leaves when asked, follows the scene state, and draws the
 * confirmation text and cursor; returns the next state. */

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
    u8 pad_24[0x0d];
    u8 messageStateFlag;
    u16 messageId;
    u16 messageVariant;
    u8 pad_36[0x2a];
    MissionResourceRecord resource;
} MissionMenuContext;

extern MissionMenuContext *data_ov006_02056660;
extern u16 data_ov006_0205651c[8];

extern int Ov006_SetMissionCursorSelection(int selection);
extern int Ov006_IsMissionMenuExitRequested(void);
extern void Ov006_BlankScreensAndTeardownText(void);
extern unsigned short WH_GetBitmap(void);
extern int Ov006_GetMissionMenuSelection(void);
extern void Ov006_ResetTextLayers(void);
extern void *Ov006_GetVarRecordByIndex(void *resource, u32 index);
extern void Ov006_MissionDrawTextRunFwd(void *text, int x, int y, int style, int layer, int align,
                                        int visible);
extern void Ov006_MissionToggleSlotVisible(int visible);
extern void Ov006_FlushTextLayers(void);

extern void Ov006_UpdateMissionMenuSelectionScreen(void);
extern void Ov006_MissionInitVideoScene(void);
extern void Ov006_MissionMenuTick(void);

MissionState Ov006_UpdateMissionMenuConfirmScreen(void)
{
    MissionState nextState = Ov006_UpdateMissionMenuSelectionScreen;
    u32 textSelector;
    u8 lineIndex;

    Ov006_SetMissionCursorSelection(-1);

    if (data_ov006_02056660->sessionReady == 0 &&
        Ov006_IsMissionMenuExitRequested() != 0) {
        Ov006_BlankScreensAndTeardownText();
        return Ov006_MissionInitVideoScene;
    }

    switch (Game_PollSceneAlive()) {
    case 8:
        return Ov006_MissionMenuTick;
    case 0:
    case 9:
    case 10:
        Ov006_BlankScreensAndTeardownText();
        return Ov006_MissionInitVideoScene;
    case 3:
        nextState = 0;
        goto draw_screen;
    case 4:
        if (data_ov006_02056660->sessionReady != 0) {
            if (WH_GetBitmap() != 1) {
                nextState = 0;
            }
        } else {
            if (WH_GetBitmap() == 0) {
                nextState = 0;
            }
        }
        goto draw_screen;
    default:
        break;
    }

    nextState = 0;

draw_screen:
    if (nextState != 0) {
        if (Ov006_GetMissionMenuSelection() > 0) {
            Ov006_SetMissionCursorSelection(Ov006_GetMissionMenuSelection());
        }
        data_ov006_02056660->messageStateFlag = 0;
        data_ov006_02056660->messageId = 0x40;
        data_ov006_02056660->messageVariant = 0;
    }

    Ov006_ResetTextLayers();
    data_ov006_02056660->messageId = 0x40;
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

    Ov006_MissionDrawTextRunFwd(Ov006_GetVarRecordByIndex(&data_ov006_02056660->resource,
                            data_ov006_02056660->messageId), 0xfa, 2, 1, 1, 1, 1);

    if (data_ov006_02056660->sessionReady != 0) {
        textSelector = 0x41;
    } else {
        textSelector = 0x42;
    }
    Ov006_MissionDrawTextRunFwd(
                                Ov006_GetVarRecordByIndex(&data_ov006_02056660->resource, textSelector),
                                0x80, 0x60, 1, 1, 3, 1);

    for (lineIndex = 0; lineIndex < 4; lineIndex++) {
        Ov006_MissionDrawTextRunFwd(data_ov006_0205651c, 99, lineIndex * 0x18 + 0x23, 1, 1, 0, 0);
    }

    if (data_ov006_02056660->sessionReady != 0) {
        Ov006_MissionToggleSlotVisible(0);
        Ov006_MissionDrawTextRunFwd(Ov006_GetVarRecordByIndex(&data_ov006_02056660->resource, 0x43),
                                    0x80, 0x98, 1, 1, 3, 0);
    }

    Ov006_FlushTextLayers();
    return nextState;
}
