/* Commits the synchronized snapshot: when the session is ready (or local), copies the shared
 * mission members, thresholds, rules and day clock into the game state and acknowledges it. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov002MissionMemberHeader {
    u8 memberId;
    u8 headerByte1;
    u8 tally;
    u8 memberKind;
    u16 head4;
    u16 head6;
} Ov002MissionMemberHeader;

typedef struct Ov002MissionMemberBody {
    u8 pad_0000[6];
    u16 recordedValue;
} Ov002MissionMemberBody;

typedef struct Ov002MissionMemberFields {
    Ov002MissionMemberHeader header;
    Ov002MissionMemberBody body;
    u8 pad_0010[0xf4];
} Ov002MissionMemberFields;

typedef union Ov002MissionMember {
    Ov002MissionMemberFields fields;
    u32 words[65];
} Ov002MissionMember;

typedef struct Ov002PanelThresholds {
    u32 words[7];
} Ov002PanelThresholds;

typedef struct Ov002TallyRules {
    u8 bytes[12];
} Ov002TallyRules;

typedef struct Ov002DayClock {
    u16 values[4];
} Ov002DayClock;

typedef struct Ov008SharedSnapshot {
    Ov002MissionMember missionMembers[4];
    Ov002PanelThresholds panelThresholds;
    Ov002TallyRules tallyRules;
    Ov002DayClock dayClock;
    u16 sessionValue;
    u16 pad_0442;
} Ov008SharedSnapshot;

typedef struct Ov008MenuContext {
    u8 pad_0000[0x18];
    u32 sessionState;
    u8 pad_001c[0x15c];
    Ov008SharedSnapshot sharedSnapshot;
    u8 pad_05bc[0x4a90];
    u16 messageHandle;
} Ov008MenuContext;

extern Ov008MenuContext *data_ov008_02090f00;
extern Ov002MissionMember gPartyMembers[4];
extern Ov002DayClock data_0204c240;
extern u16 data_0204c23c;
extern Ov002PanelThresholds data_0204c254;
extern Ov002TallyRules data_0204c248;

extern int Ov008_GetPlayerMask(void);
extern void Ov008_UpdateCursorSprite(void);
extern int Ov008_Link_IsLocal(void);
extern int Ov008_IsSessionReady(void);
extern void Ov008_SendMenuMessage(u8 messageType);
extern int Slot4_GetIfOccupied(int slot);
extern void Ov008_RefreshSeatCharacter(int slot);

int Ov008_CommitSynchronizedSnapshotState(void)
{
    int slot;
    Ov008MenuContext *context;

    Ov008_GetPlayerMask();
    data_ov008_02090f00->sessionState = 7;
    Ov008_UpdateCursorSprite();

    if (Ov008_Link_IsLocal() == 0) {
        if (Ov008_IsSessionReady() == 0) {
            context = data_ov008_02090f00;

            if (context->messageHandle == 0xffff) {
                Ov008_SendMenuMessage(10);
                return 0;
            }
            if (MsgQueue_Contains(context->messageHandle) != 0) {
                return 0;
            }
        }

        slot = 0;
        do {
            if (Slot4_GetIfOccupied(slot) != 0) {
                Ov008_RefreshSeatCharacter(slot);
                gPartyMembers[slot] =
                    data_ov008_02090f00->sharedSnapshot.missionMembers[slot];
                ((u8 *)&gPartyMembers[slot])[0] = (u8)slot;
                ((u8 *)&gPartyMembers[slot])[1] = (u8)slot;
            }
            slot++;
        } while (slot < 4);

        {
            context = data_ov008_02090f00;

            data_0204c240 = context->sharedSnapshot.dayClock;
            data_0204c240.values[2] = 0;
            ((u8 *)&data_0204c240)[0] = 7;
            data_0204c23c = context->sharedSnapshot.sessionValue;
            data_0204c254 = context->sharedSnapshot.panelThresholds;
            data_0204c248 = context->sharedSnapshot.tallyRules;
        }
    } else {
        ((u8 *)&data_0204c240)[0] = 0xf;
    }

    return -2;
}
