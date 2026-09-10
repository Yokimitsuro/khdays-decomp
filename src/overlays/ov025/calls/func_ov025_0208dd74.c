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
extern int func_ov025_02084e08(void);
extern int func_ov025_02084e38(void);
extern u32 func_ov025_02084e74(void);
extern Ov008MissionListEntry *func_ov025_0208dbbc(Ov008MissionListEntry *entry);
extern u8 data_ov025_020b39e4[];
extern u8 data_ov025_020b39e8[];
extern u8 data_ov025_020b39e9[];
extern u8 data_ov025_020b39ea[];

void func_ov025_0208dd74(void)
{
    Ov008MenuContext *menuContext = func_ov025_02084afc();
    u16 dayValue = (u16)func_020235d0(0, 9);
    u16 tierIndex;
    int rowOffset;
    Ov008MissionListEntry *missionEntry;
    int isCompleted;

    if (func_ov025_02084e08() != 0 && func_ov025_02084e38() == 0) {
        dayValue = (u16)func_ov025_02084e74();
    }

    menuContext->missionSummaryTiers[0] = 4;
    menuContext->missionSummaryTiers[1] = 4;
    menuContext->missionSummaryTiers[2] = 4;

    tierIndex = 0;
    do {
        rowOffset = tierIndex * 8;
        if (dayValue < *(u16 *)(data_ov025_020b39e4 + tierIndex * 8 + 8)) {
            menuContext->missionSummaryTiers[0] = data_ov025_020b39e8[rowOffset];
            menuContext->missionSummaryTiers[1] = data_ov025_020b39e9[rowOffset];
            menuContext->missionSummaryTiers[2] = data_ov025_020b39ea[rowOffset];
            break;
        }
        tierIndex++;
    } while (tierIndex < 0x37);

    menuContext->completedMissionWeight = 0;
    missionEntry = func_ov025_0208dbbc(0);
    if (missionEntry == 0) {
        return;
    }
    do {
        isCompleted =
            func_020235d0(missionEntry->missionId * 3 + 0x28e4, 3) >= 2;
        if (isCompleted != 0) {
            menuContext->completedMissionWeight += missionEntry->completionWeight;
        }
        func_020235d0(missionEntry->missionId * 3 + 0x28e4, 3);
        missionEntry = func_ov025_0208dbbc(missionEntry);
    } while (missionEntry != 0);
}
