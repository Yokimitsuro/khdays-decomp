#include "nitro/types.h"

#include "game/ov008_camp_menu.h"
#define MISSION_CONTEXT (*(MissionContext * volatile *)&data_ov008_02090f24.pContext)
extern char data_ov008_02090f40[];

extern unsigned short Ov105_WH_GetMeasureChannel(void);
extern unsigned short Ov105_WM_GetNextTgid(void);
extern void Ov105_WH_SetUserGameInfo(void *resource, int size);
extern int Ov105_WH_ParentConnect(int mode, int selection, int value, int count, int option);
extern void Ov105_WH_SetReceiver(void (*callback)(void));
extern void Ov105_WH_SetJudgeAcceptFunc(void (*callback)(void));
extern void Ov008_UpdateSlotCache(void);
extern void Ov008_MatchMissionStartPacket(void);

void Ov008_MissionStartTransition(void) {
    int value = Ov105_WH_GetMeasureChannel();

    MISSION_CONTEXT->active.record.selection = (u16)Ov105_WM_GetNextTgid();
    Ov105_WH_SetUserGameInfo(data_ov008_02090f40, 0x18);

    if (Ov105_WH_ParentConnect(0, MISSION_CONTEXT->active.record.selection, value, 2,
                            MISSION_CONTEXT->active.record.option) == 0) {
        return;
    }

    Ov105_WH_SetReceiver(Ov008_UpdateSlotCache);
    Ov105_WH_SetJudgeAcceptFunc(Ov008_MatchMissionStartPacket);
    MISSION_CONTEXT->transitionRequested = 1;
}
