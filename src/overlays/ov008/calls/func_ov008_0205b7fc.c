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

extern Ov008MenuContext *func_ov008_02050cd4(void);
extern u32 func_020235d0(u32 field, int selector);
extern int func_ov008_02050ff8(void);
extern int func_ov008_02051028(void);
extern u32 func_ov008_02051064(void);
extern Ov008MissionListEntry *func_ov008_0205b650(Ov008MissionListEntry *entry);
extern u8 data_ov008_0208ee84[];
extern u8 data_ov008_0208ee88[];
extern u8 data_ov008_0208ee89[];
extern u8 data_ov008_0208ee8a[];

void func_ov008_0205b7fc(void)
{
    Ov008MenuContext *menuContext = func_ov008_02050cd4();
    u16 dayValue = (u16)func_020235d0(0, 9);
    u16 tierIndex;
    int rowOffset;
    Ov008MissionListEntry *missionEntry;
    int isCompleted;

    if (func_ov008_02050ff8() != 0 && func_ov008_02051028() == 0) {
        dayValue = (u16)func_ov008_02051064();
    }

    menuContext->missionSummaryTiers[0] = 4;
    menuContext->missionSummaryTiers[1] = 4;
    menuContext->missionSummaryTiers[2] = 4;

    tierIndex = 0;
    do {
        rowOffset = tierIndex * 8;
        if (dayValue < *(u16 *)(data_ov008_0208ee84 + tierIndex * 8 + 8)) {
            menuContext->missionSummaryTiers[0] = data_ov008_0208ee88[rowOffset];
            menuContext->missionSummaryTiers[1] = data_ov008_0208ee89[rowOffset];
            menuContext->missionSummaryTiers[2] = data_ov008_0208ee8a[rowOffset];
            break;
        }
        tierIndex++;
    } while (tierIndex < 0x37);

    menuContext->completedMissionWeight = 0;
    missionEntry = func_ov008_0205b650(0);
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
        missionEntry = func_ov008_0205b650(missionEntry);
    } while (missionEntry != 0);
}
