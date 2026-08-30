/* Ov002_UpdatePeerAnimationsAndExit: step the selected seat's entries, stop
 * completed one-shot tracks, and broadcast a shared exit when allowed. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Ov002LinkEntry { char pad0[0x108]; u8 bActive; char pad109[3]; } Ov002LinkEntry;
typedef struct Ov002GateEffect Ov002GateEffect;
typedef struct Ov002LinkCtx Ov002LinkCtx;
typedef void (*Ov002PeerUpdateHook)(u8 *,int,Ov002LinkCtx *,int);
struct Ov002LinkCtx {
    char pad0[14]; u8 bFlags; char padf[0x49];
    Ov002GateEffect *apOwnedBlocks[8]; s8 nOwnedBlockCount; char pad79[0x97];
    s8 nEntryCount,nSeatSplit; char pad112[2]; Ov002LinkEntry aEntries[32];
    char pad2294[0x1c]; Ov002PeerUpdateHook apSecondaryHooks[4]; u8 aHookState[4][32];
};
typedef struct Ov002PeerExitCommand { u8 nKind,nSlot,nExitKey; } Ov002PeerExitCommand;
extern Ov002LinkCtx *data_ov002_0207fa10;
extern u8 data_0204be04,data_0204c240;
extern void *func_0202bfa0(u16);
extern u16 func_0202a818(void *,int);
extern int func_0202aef8(void *,u16);
extern void func_01fff774(void *,u16,int);
extern void func_0202af1c(void *);
extern int func_02023588(int);
extern u16 func_02030788(void);
extern int func_ov022_02088648(void);
extern int func_ov002_0206b7a4(void);
extern int func_ov002_0206b7f4(void);
extern int func_ov002_0206b828(void);
extern int func_ov002_02071230(void);
extern int func_ov002_0206b084(void);
extern u32 func_ov002_0206fb84(int,Ov002PeerExitCommand *);
extern void func_020208d0(int);
extern void func_02020878(int);
extern int func_ov022_020882f8(void);
extern void func_ov022_020888b8(int,int);

void func_ov002_02072364(int nSlot,int nDeltaQ12,int bAllowExit)
{
    int i,j;
    u16 nEnded;
    int nExit;
    Ov002LinkEntry *pEntry;
    Ov002PeerExitCommand command;
    Ov002LinkCtx *pCtx=data_ov002_0207fa10;
    if(pCtx->apSecondaryHooks[nSlot]) pCtx->apSecondaryHooks[nSlot](pCtx->aHookState[nSlot],nSlot,pCtx,nDeltaQ12);
    func_0202bfa0((u16)nSlot);
    if(data_0204be04==0) {
        for(i=0;i<pCtx->nSeatSplit;i++) {
            pEntry=&pCtx->aEntries[i];
            nEnded=func_0202a818(pEntry,nDeltaQ12);
            if((pEntry->bActive&2) && nEnded) {
                for(j=0;j<5;j++) {
                    if(nEnded&1) {
                        func_01fff774(pEntry,(u16)j,func_0202aef8(pEntry,(u16)j)-0x1000);
                        nEnded>>=1;
                    }
                }
                func_0202af1c(pEntry);
                pEntry->bActive|=4;
            }
        }
    } else {
        for(i=pCtx->nSeatSplit;i<pCtx->nEntryCount;i++) {
            pEntry=&pCtx->aEntries[i];
            nEnded=func_0202a818(pEntry,nDeltaQ12);
            if((pEntry->bActive&2) && nEnded) {
                for(j=0;j<5;j++) {
                    if(nEnded&1) {
                        func_01fff774(pEntry,(u16)j,func_0202aef8(pEntry,(u16)j)-0x1000);
                        nEnded>>=1;
                    }
                }
                func_0202af1c(pEntry);
                pEntry->bActive|=4;
            }
        }
    }
    if(!(data_0204c240&4)) return;
    if(func_02023588(0x2087)) return;
    for(i=0;i<pCtx->nOwnedBlockCount;i++) func_0202a818(pCtx->apOwnedBlocks[i],nDeltaQ12);
    if(func_02030788()) return;
    if(!bAllowExit) return;
    if(func_ov022_02088648()) return;
    if(pCtx->bFlags&2) return;
    if(func_ov002_0206b7a4()) return;
    if(!func_ov002_0206b7f4()) return;
    if(func_ov002_0206b828()) return;
    nExit=func_ov002_02071230();
    if(nExit<0) return;
    if(!func_ov002_0206b084()) return;
    command.nExitKey=nExit;
    command.nSlot=nSlot;
    if(func_ov002_0206fb84(5,&command)==0xffff) return;
    pCtx->bFlags|=2;
    func_020208d0(0);
    func_02020878(0);
    for(i=0;i<func_ov022_020882f8();i++) func_ov022_020888b8(i,1);
}
