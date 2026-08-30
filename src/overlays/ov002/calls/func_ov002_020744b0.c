/* Ov002_FlushPendingObjectCommands: clear queued commands only after submission. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct VecFx32 {int x,y,z;} VecFx32;
typedef struct Ov002PartRetireCmd {u8 nKind,nEntryIndex,nGroupIndex;} Ov002PartRetireCmd;
typedef struct Ov002SessionSlotCmd {u8 nKind,nSlot;} Ov002SessionSlotCmd;
typedef struct Ov002SessionSpawnCmd {u8 nKind;u8 nSlot:2,nStyle:6;u8 nEntry;s8 nKeyIndex;u8 nSeed,pad5[3];VecFx32 vPos;} Ov002SessionSpawnCmd;
typedef struct Ov002PendingObjectSpawn {short x,y,z;u8 nSlot:2,nStyle:6;u8 nEntry;s8 nKeyIndex;s8 bGuaranteed:1;} Ov002PendingObjectSpawn;
typedef struct Ov002ObjectContext {char pad0[0x55];u8 aPendingSlots[8];char pad5d;u16 aPendingRetireTags[8];Ov002PendingObjectSpawn aPendingSpawns[4];} Ov002ObjectContext;
extern Ov002ObjectContext *data_ov002_0207fa14;
extern u8 data_0204c240;
extern u32 func_ov002_0206fb84(int,void *);
void func_ov002_020744b0(void)
{
    Ov002PartRetireCmd retireCmd;
    Ov002SessionSlotCmd slotCmd;
    Ov002SessionSpawnCmd spawnCmd;
    Ov002ObjectContext *pCtx=data_ov002_0207fa14;
    int i;
    if(!(data_0204c240&4))return;
    for(i=0;i<8;i++){
        if(pCtx->aPendingRetireTags[i]!=0xffff){
            retireCmd.nEntryIndex=pCtx->aPendingRetireTags[i]>>8;
            retireCmd.nGroupIndex=pCtx->aPendingRetireTags[i];
            if(func_ov002_0206fb84(0xc,&retireCmd)==0xffff)return;
            pCtx->aPendingRetireTags[i]=0xffff;
        }
    }
    for(i=0;i<8;i++){
        if(pCtx->aPendingSlots[i]!=0xff){
            slotCmd.nSlot=pCtx->aPendingSlots[i];
            if(func_ov002_0206fb84(0xd,&slotCmd)==0xffff)return;
            pCtx->aPendingSlots[i]=0xff;
        }
    }
    for(i=0;i<4;i++){
        if(pCtx->aPendingSpawns[i].nKeyIndex!=-1){
            spawnCmd.nSlot=pCtx->aPendingSpawns[i].nSlot;
            spawnCmd.nStyle=pCtx->aPendingSpawns[i].nStyle;
            spawnCmd.nEntry=pCtx->aPendingSpawns[i].nEntry;
            spawnCmd.nKeyIndex=pCtx->aPendingSpawns[i].nKeyIndex;
            spawnCmd.vPos.x=(u16)pCtx->aPendingSpawns[i].x<<4;
            spawnCmd.vPos.y=(u16)pCtx->aPendingSpawns[i].y<<4;
            spawnCmd.vPos.z=(u16)pCtx->aPendingSpawns[i].z<<4;
            if(func_ov002_0206fb84(0x10,&spawnCmd)==0xffff)return;
            pCtx->aPendingSpawns[i].nKeyIndex=-1;
        }
    }
}
