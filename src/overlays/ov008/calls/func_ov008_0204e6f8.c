typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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
extern Ov002MissionMember data_0204c678[4];
extern Ov002DayClock data_0204c240;
extern u16 data_0204c23c;
extern Ov002PanelThresholds data_0204c254;
extern Ov002TallyRules data_0204c248;

extern int func_ov008_0204cac0(void);
extern void func_ov008_0204da6c(void);
extern int func_ov008_0207baf8(void);
extern int func_ov008_0204ed3c(void);
extern void func_ov008_0204cadc(u8 messageType);
extern int func_02031440(u32 handle);
extern int func_020315c0(int slot);
extern void func_ov008_0204d6a8(int slot);

int func_ov008_0204e6f8(void)
{
    int slot;
    Ov008MenuContext *context;

    func_ov008_0204cac0();
    data_ov008_02090f00->sessionState = 7;
    func_ov008_0204da6c();

    if (func_ov008_0207baf8() == 0) {
        if (func_ov008_0204ed3c() == 0) {
            context = data_ov008_02090f00;

            if (context->messageHandle == 0xffff) {
                func_ov008_0204cadc(10);
                return 0;
            }
            if (func_02031440(context->messageHandle) != 0) {
                return 0;
            }
        }

        slot = 0;
        do {
            if (func_020315c0(slot) != 0) {
                func_ov008_0204d6a8(slot);
                data_0204c678[slot] =
                    data_ov008_02090f00->sharedSnapshot.missionMembers[slot];
                ((u8 *)&data_0204c678[slot])[0] = (u8)slot;
                ((u8 *)&data_0204c678[slot])[1] = (u8)slot;
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
