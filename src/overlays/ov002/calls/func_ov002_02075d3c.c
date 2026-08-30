/* Ov002_InitLoadingScreen: configure loading graphics and register the blink tick. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct Ov002BlinkState {u64 nLastTick;int nPhase,bHoldsPanel;u8 *pTileData;} Ov002BlinkState;
typedef struct Ov002PageChars {u8 pad0[0x10];int nCharSize;u8 *pCharData;} Ov002PageChars;
typedef struct BgPlttSrc {int nFormat,n_pad;u32 dwSize;void *pData;} BgPlttSrc;
typedef struct SpriteResSet {void *pScreen;Ov002PageChars *pChar;BgPlttSrc *pPalette;} SpriteResSet;
typedef int (*Ov002LoadingScreenNextState)(void);
extern Ov002BlinkState *data_ov002_0207fa18;
extern char data_ov002_0207f420[],data_ov002_0207f434[],data_ov002_0207f444[];
extern u8 data_0204c240;
extern Ov002BlinkState *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *,int,u32);
extern int func_ov002_0206b864(void);
extern void func_ov002_02056fb8(int,int);
extern void func_ov002_02053d94(int);
extern void func_ov002_02075fd4(int);
extern void *func_0201ef9c(char *,int);
extern void func_02024c94(SpriteResSet *,void *,int,int,int);
extern void DC_FlushRange(void *,u32);
extern void GX_LoadBG3Char(void *,u32,u32);
extern void GX_LoadBGPltt(void *,u32,u32);
extern void NNSi_FndFreeFromDefaultHeap(void *);
extern u16 *G2_GetBG3ScrPtr(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG3CharPtr(void);
extern void MIi_CpuClearFast(u32,void *,u32);
extern void func_ov002_02075c64(int);
extern u8 *NNSi_FndAllocFromDefaultExpHeap(u32);
extern void MIi_CpuCopyFast(void *,void *,u32);
extern u64 func_020031d4(void);
extern void func_02000f48(int,char *,void (*)(void));
extern void func_ov002_02075cd8(void);
extern void func_0201e374(int);
extern int func_ov002_02075f80(void);
Ov002LoadingScreenNextState func_ov002_02075d3c(void)
{
    SpriteResSet resources;
    Ov002BlinkState *pState;
    void *pArchive;
    u16 *pMap;
    *(volatile u16 *)0x05000000=0;
    *(volatile u16 *)0x05000400=0;
    pState=NNSi_FndGetCurrentRootHeap();
    data_ov002_0207fa18=pState;
    MI_CpuFill8(pState,0,20);
    *(volatile u32 *)0x04000000=(*(volatile u32 *)0x04000000&~0x1f00)|0x800;
    *(volatile u32 *)0x04001000&=~0x1f00;
    if(func_ov002_0206b864()){
        pState->bHoldsPanel=1;
        func_ov002_02056fb8(1,1);
        func_ov002_02053d94(1);
    }
    *(volatile u16 *)0x0400000e=(*(volatile u16 *)0x0400000e&0x43)|0x1f00;
    func_ov002_02075fd4(1);
    pArchive=func_0201ef9c(data_ov002_0207f420,14);
    func_02024c94(&resources,pArchive,0,0,0);
    DC_FlushRange(resources.pPalette->pData,0x200);
    GX_LoadBG3Char(resources.pChar->pCharData,0x13c0,0x40);
    GX_LoadBG3Char(resources.pChar->pCharData+0x40,0x17c0,0x40);
    GX_LoadBGPltt(resources.pPalette->pData,0,0x200);
    NNSi_FndFreeFromDefaultHeap(pArchive);
    pMap=G2_GetBG3ScrPtr();
    MIi_CpuClearFast(0,G2_GetBG1ScrPtr(),0x800);
    MIi_CpuClearFast(0,pMap,0x800);
    MIi_CpuClearFast(0,G2_GetBG3CharPtr(),0x20);
    func_ov002_02075c64(0);
    if((data_0204c240&12)==4){
        pMap[0]=0xe086;pMap[1]=0xe087;pMap[32]=0xe088;pMap[33]=0xe089;
        pArchive=func_0201ef9c(data_ov002_0207f434,14);
        func_02024c94(&resources,pArchive,0,0,0);
        pState->pTileData=NNSi_FndAllocFromDefaultExpHeap(resources.pChar->nCharSize);
        MIi_CpuCopyFast(resources.pChar->pCharData,pState->pTileData,resources.pChar->nCharSize);
        NNSi_FndFreeFromDefaultHeap(pArchive);
    }
    *(volatile u32 *)0x0400001c=0;
    pState->nLastTick=func_020031d4();
    pState->nPhase=0;
    func_02000f48(1,data_ov002_0207f444,func_ov002_02075cd8);
    func_0201e374(0);
    return func_ov002_02075f80;
}
