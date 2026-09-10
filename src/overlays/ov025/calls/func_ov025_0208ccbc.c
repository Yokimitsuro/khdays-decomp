typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    const u8 *resourcePath;
    int selector;
    int listKind;
} Ov008MissionResourceDescriptor;

typedef struct {
    u8 data[0x24];
} Ov008MissionListState;

typedef struct Ov008MissionListEntry {
    u8 pad00[2];
    u16 missionId;
    u8 pad04[0x14];
    u32 statusFlags;
} Ov008MissionListEntry;

extern Ov008MissionResourceDescriptor data_ov025_020b3940;
extern void func_ov025_0208a13c(Ov008MissionListState *list,
                                Ov008MissionResourceDescriptor *descriptor);
extern Ov008MissionListEntry *func_ov025_0208a1cc(Ov008MissionListState *list,
                                                  Ov008MissionListEntry *entry);
extern void func_ov025_0208a19c(Ov008MissionListState *list);
extern int func_020235d0(int field, int selector);
extern int func_02020400(int numerator, int denominator);

u16 func_ov025_0208ccbc(void *menuState)
{
    Ov008MissionResourceDescriptor resourceDescriptor = data_ov025_020b3940;
    Ov008MissionListState missionList;
    u16 qualifyingCount = 0;
    u16 progressTotal = 0;
    Ov008MissionListEntry *missionEntry;

    func_ov025_0208a13c(&missionList, &resourceDescriptor);
    for (missionEntry = func_ov025_0208a1cc(&missionList, 0);
         missionEntry != 0;
         missionEntry = func_ov025_0208a1cc(&missionList, missionEntry)) {
        if ((missionEntry->statusFlags & 3) != 0) {
            qualifyingCount++;
            progressTotal += func_020235d0(missionEntry->missionId * 3 + 0x2a4c, 3);
        }
    }
    func_ov025_0208a19c(&missionList);
    if (qualifyingCount != 0) {
        return (u16)func_02020400(progressTotal * 100, qualifyingCount * 3);
    }
    return 0;
}
