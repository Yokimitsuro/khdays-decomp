#include "nitro/types.h"

#include "game/ov006_mission_mode_select.h"

/* Starts the mission link as parent: resolves the session id, picks the next group id, sets the
 * receive buffer, connects and installs the receiver and packet filter; marks the transition
 * requested. */

#define MISSION_CONTEXT (*(MissionContext *volatile *)&data_ov006_020565e4.pContext)
extern char data_ov006_02056600[];

extern unsigned short Ov105_WH_GetMeasureChannel(void);
extern unsigned short Ov105_WM_GetNextTgid(void);
extern void Ov105_WH_SetUserGameInfo(void *resource, int size);
extern int Ov105_WH_ParentConnect(int mode, int selection, int value, int count, int option);
extern void Ov105_WH_SetReceiver(void (*callback)(void));
extern void Ov105_WH_SetJudgeAcceptFunc(void (*callback)(void));
extern void Ov006_UpdateSlotCache(void);
extern void Ov006_MatchMissionStartPacket(void);

void Ov006_MissionStartTransition(void) {
    int value = Ov105_WH_GetMeasureChannel();

    MISSION_CONTEXT->active.record.selection = (u16)Ov105_WM_GetNextTgid();
    Ov105_WH_SetUserGameInfo(data_ov006_02056600, 0x18);

    if (Ov105_WH_ParentConnect(0, MISSION_CONTEXT->active.record.selection, value, 2,
                            MISSION_CONTEXT->active.record.option) == 0) {
        return;
    }

    Ov105_WH_SetReceiver(Ov006_UpdateSlotCache);
    Ov105_WH_SetJudgeAcceptFunc(Ov006_MatchMissionStartPacket);
    MISSION_CONTEXT->transitionRequested = 1;
}
