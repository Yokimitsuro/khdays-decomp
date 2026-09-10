typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov008MissionListEntry {
    u8 pad00[2];
    u16 missionId;
    u8 pad04[0x11];
    u8 completionWeight;
} Ov008MissionListEntry;

typedef struct Ov008MenuContext {
    u8 pad0000[0x14f0];
    u8 missionSummaryTiers[3];
    u8 completedMissionWeight;
} Ov008MenuContext;

extern Ov008MenuContext *func_ov025_02084afc(void);
extern u32 func_020235d0(u32 field, int selector);
extern u8 data_0204c300[];

u8 func_ov025_0208df00(Ov008MissionListEntry *missionEntry)
{
    Ov008MenuContext *menuContext = func_ov025_02084afc();
    u32 missionWeight = menuContext->completedMissionWeight;
    u8 summaryTier;

    if (missionEntry != 0) {
        int isComplete =
            func_020235d0(missionEntry->missionId * 3 + 0x28e4, 3) >= 2;
        if (isComplete == 0) {
            missionWeight =
                (missionWeight + missionEntry->completionWeight) & 0xff;
        }
    }

    summaryTier = 1;
    if (missionWeight > (u32)menuContext->missionSummaryTiers[0]) {
        summaryTier++;
    }
    if ((int)missionWeight >
        (int)menuContext->missionSummaryTiers[1] +
            (int)menuContext->missionSummaryTiers[0]) {
        summaryTier++;
    }

    data_0204c300[0x4f] = summaryTier;
    return summaryTier;
}
