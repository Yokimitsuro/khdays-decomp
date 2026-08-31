typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Ov005MenuItemHeader {char data[0x24c];} Ov005MenuItemHeader;
typedef struct RewardRecord {char header[0x10];int missionId;char pad14[12];u32 items[5];u32 weightedTables[5];} RewardRecord;
typedef struct Ov005Config {u16 sceneId,missionIndex;char pad4[8];u16 mode;} Ov005Config;
typedef struct CompletionCounts {char pad[8];u32 goal,value;} CompletionCounts;
extern Ov005Config data_ov005_0205b85c;
extern CompletionCounts data_0204c32c;
extern u8 data_0204c240;
extern char *data_ov005_0205b80c;
extern void MI_CpuFill8(void *,u8,u32);
extern void MIi_CpuCopy16(const void *,void *,u32);
extern u32 func_020235d0(u32,u32);
extern int func_02023588(u32);
extern void func_020342e8(RewardRecord **,int,u32,int);
extern void func_020343cc(RewardRecord **);
extern void func_ov005_0205192c(Ov005MenuItemHeader *,u32,int,int);
extern void func_ov005_02051ba0(u32);
extern void func_ov005_02051be4(u32);
static inline int IsMissionCleared(u16 mission) {return func_020235d0(mission*3+0x28e4,3)>=2;}
static inline int IsMissionComplete(u16 mission) {return func_020235d0(mission*3+0x28e4,3)==3;}
void func_ov005_02051cd4(int missionId) {
    RewardRecord copy;
    RewardRecord *record=0;
    CompletionCounts *counts=&data_0204c32c;
    Ov005Config *config=&data_ov005_0205b85c;
    u8 i;
    int flags;
    MI_CpuFill8(&copy,0,0x48);
    if(config->mode!=255)return;
    if(config->sceneId==0x385 && data_0204c240==0)func_ov005_0205192c((Ov005MenuItemHeader *)(data_ov005_0205b80c+0x18990),0x8a,1,1);
    flags=0;
    if(!IsMissionCleared(config->missionIndex) && func_02023588(0x2086))flags|=1;
    if(!IsMissionComplete(config->missionIndex) && counts->value==counts->goal)flags|=2;
    for(i=0;i<103;i++) {
        func_020342e8(&record,0x19,i,0xe);
        if(record!=0 && record->missionId==missionId) {
            MIi_CpuCopy16(record,&copy,0x48);
            func_020343cc(&record);
            break;
        }
        func_020343cc(&record);
    }
    if(flags&2)func_ov005_02051ba0(copy.items[2]);
    if(flags&1)for(i=0;i<5;i++) {
        if(i!=2)func_ov005_02051ba0(copy.items[i]);
    }
    for(i=0;i<5;i++)func_ov005_02051be4(copy.weightedTables[i]);
}
