/* Ov002_UpdatePeerAnimationsAndExit: step the selected seat's entries, stop
 * completed one-shot tracks, and broadcast a shared exit when allowed. */

#include "nitro/types.h"

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
extern void *GetTrackEntryBase(int);
extern u16 Sequence_UpdateTracks(void *,int);
extern int Anim_GetLengthQ12(void *, int);
extern void Anim_SetFrameWrapped(void *,int,int);
extern void SceneNode_Enable(void *);
extern int GameState_IsFlagSet(int);
extern u16 Session_GetLocalPlayerIndex(void);
extern int func_ov022_02088648(void);
extern int Ov002_RunShutdownHook(void);
extern int Ov002_IsLeaveFinished(void);
extern int Ov002_GetRootField8b68Alt(void);
extern int Ov002_FindSharedPlayerExit(void);
extern int Ov002_RequestLeave(void);
extern u32 Ov002_BuildSessionCommand(int,Ov002PeerExitCommand *);
extern void PauseMenu_SetMode(int);
extern void PauseMenu_SetAllowed(int);
extern int func_ov022_020882f8(void);
extern void func_ov022_020888b8(int,int);

void Ov002_UpdatePeerAnimationsAndExit(int nSlot,int nDeltaQ12,int bAllowExit)
{
    int i,j;
    u16 nEnded;
    int nExit;
    Ov002LinkEntry *pEntry;
    Ov002PeerExitCommand command;
    Ov002LinkCtx *pCtx=data_ov002_0207fa10;
    if(pCtx->apSecondaryHooks[nSlot]) pCtx->apSecondaryHooks[nSlot](pCtx->aHookState[nSlot],nSlot,pCtx,nDeltaQ12);
    GetTrackEntryBase((u16)((u16)nSlot));
    if(data_0204be04==0) {
        for(i=0;i<pCtx->nSeatSplit;i++) {
            pEntry=&pCtx->aEntries[i];
            nEnded=Sequence_UpdateTracks(pEntry,nDeltaQ12);
            if((pEntry->bActive&2) && nEnded) {
                for(j=0;j<5;j++) {
                    if(nEnded&1) {
                        Anim_SetFrameWrapped(pEntry,j & 0xffff,Anim_GetLengthQ12(pEntry, (u16)((u16)j))-0x1000);
                        nEnded>>=1;
                    }
                }
                SceneNode_Enable(pEntry);
                pEntry->bActive|=4;
            }
        }
    } else {
        for(i=pCtx->nSeatSplit;i<pCtx->nEntryCount;i++) {
            pEntry=&pCtx->aEntries[i];
            nEnded=Sequence_UpdateTracks(pEntry,nDeltaQ12);
            if((pEntry->bActive&2) && nEnded) {
                for(j=0;j<5;j++) {
                    if(nEnded&1) {
                        Anim_SetFrameWrapped(pEntry,j & 0xffff,Anim_GetLengthQ12(pEntry, (u16)((u16)j))-0x1000);
                        nEnded>>=1;
                    }
                }
                SceneNode_Enable(pEntry);
                pEntry->bActive|=4;
            }
        }
    }
    if(!(data_0204c240&4)) return;
    if(GameState_IsFlagSet(0x2087)) return;
    for(i=0;i<pCtx->nOwnedBlockCount;i++) Sequence_UpdateTracks(pCtx->apOwnedBlocks[i],nDeltaQ12);
    if(Session_GetLocalPlayerIndex()) return;
    if(!bAllowExit) return;
    if(func_ov022_02088648()) return;
    if(pCtx->bFlags&2) return;
    if(Ov002_RunShutdownHook()) return;
    if(!Ov002_IsLeaveFinished()) return;
    if(Ov002_GetRootField8b68Alt()) return;
    nExit=Ov002_FindSharedPlayerExit();
    if(nExit<0) return;
    if(!Ov002_RequestLeave()) return;
    command.nExitKey=nExit;
    command.nSlot=nSlot;
    if(Ov002_BuildSessionCommand(5,&command)==0xffff) return;
    pCtx->bFlags|=2;
    PauseMenu_SetMode(0);
    PauseMenu_SetAllowed(0);
    for(i=0;i<func_ov022_020882f8();i++) func_ov022_020888b8(i,1);
}
