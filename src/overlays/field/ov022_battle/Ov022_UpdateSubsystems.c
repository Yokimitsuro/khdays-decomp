/* ov022: run everything the actor's frame still owes.
 *
 * The per-frame tick's catch-all step. For the local player it drives the two
 * ambient sound channels and the chip gauge, then for every actor it walks the
 * subsystem blocks in order -- reaction, effect slots, timers, trails, the
 * slot mask and the state block -- feeding each the frame delta, the facing
 * vector and the node's angle. It finishes by calling whatever update hook the
 * actor carries, and then, only for the local player, consumes a one-shot flag
 * that asks for a menu sound.
 *
 * The two ambient channels are routed differently in one area, which is why
 * the area id is fetched three times rather than cached.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"

#include "game/config.h"
struct Node {
    u8 pad00[0x80];
    u16 nAngle;                   /* 0x80 */
};

struct Actor;
typedef void (*PfnUpdate)(struct Actor *pActor);

struct Actor {
    unsigned long long nFlags;    /* 0x0000 */
    u8 nOwner;                    /* 0x0008 */
    u8 nId;                       /* 0x0009 */
    u8 pad00a[8];
    u16 nHp;                      /* 0x0012 */
    u8 pad014[0xc];
    struct Node *pNode;           /* 0x0020 */
    u32 nInputMask;               /* 0x0024 */
    u8 pad028[0x3e];
    short nSlotIndex;             /* 0x0066 */
    u8 collMain;                  /* 0x0068 */
    u8 pad069[0x3fb];
    unsigned long long nFlags2;   /* 0x0464 */
    u8 pad46c[0x20];
    VecFx32 vecPos;           /* 0x048c */
    u8 pad498[0x1d4];
    PfnUpdate pfnUpdate;          /* 0x066c */
    u8 pad670[0x4c];
    int nHitReaction;             /* 0x06bc */
    u8 pad6c0[0xf8];
    int nEffectA;                 /* 0x07b8 */
    int nEffectB;                 /* 0x07bc */
    u8 pad7c0[0x8b0];
    u8 slotBlk;                   /* 0x1070 */
    u8 pad1071[0x127];
    u8 reactBlk;                  /* 0x1198 */
    u8 pad1199[0x17f];
    u8 comboBlk;                  /* 0x1318 */
    u8 pad1319[0x973];
    u8 timerBlk;                  /* 0x1c8c */
    u8 pad1c8d[0x11b];
    u8 reactionBlk;               /* 0x1da8 */
    u8 pad1da9[0x4df];
    u8 slotMask;                  /* 0x2288 */
    u8 pad2289[0x6f];
    u8 chipBlk;                   /* 0x22f8 */
    u8 pad22f9[0x7c0];
    short nAnimStep;             /* 0x2aba */
    u8 pad2abc[0x134];
    int nWrapA;                   /* 0x2bf0 */
    u8 pad2bf4[4];
    int nWrapB;                   /* 0x2bf8 */
};

extern u8 data_0204c240;
extern u16 gPadHeld;

extern void func_ov022_020ad44c(VecFx32 *pOut, struct Actor *pActor);
extern int Session_GetLocalPlayerIndex(void);
extern int LoadGlobalU16At0(void);
extern void Ov106_SetSceneAnimEnabled(int bOn);
extern void Ov002_SetWidgetFullOrZero(int bOn);
extern void Ov106_SetField8CCC(int bOn);
extern void Ov002_HudWidgets_SetFieldE0(int bOn);
extern int Ov022_ComputeChipGauge(u8 *pBlk);
extern int Ov002_IsMissionClearFinished(int nWhich);
extern int Ov002_GetStateWord(void);
extern void Ov002_SetPanelMode_2(int bOn);
extern void Ov002_SetScrollPosition(int nWhich, int nValue);
extern int Ov022_IsHoldingItem(struct Actor *pActor, int nKind);
extern int Ov022_GetMarkerState(int nId);
extern void func_ov022_020ad2e4(struct Actor *pActor, int nMode);
extern void func_ov022_02093f24(u8 *pBlk, int nBit);
extern void Ov022_PlayEntityVoice(struct Actor *pActor, int nSeqArc, int nSeq);
extern void Ov022_StepEffectTowardCamera(struct Actor *pActor);
extern void Ov022_MoveEffectTowardCamera(struct Actor *pActor);
extern void Ov022_StepReactionPhase(u8 *pBlk);
extern void Ov022_StepSpinEffect(u8 *pBlk, VecFx32 *pVec, int nAngle, int bReact, int nFrame);
extern void Ov022_ResetFields135_168_174(u8 *pBlk);
extern void Ov022_StartSlotEffect(u8 *pBlk, VecFx32 *pPos, int nAngle, int nScale);
extern void func_ov022_02092808(u8 *pBlk, int nFrame);
extern void func_ov022_02094224(u8 *pBlk, VecFx32 *pPos, int nFrame);
extern int Ov022_GetGlobal34(void);
extern void Ov022_StepDustEmitter(u8 *pBlk, VecFx32 *pPos, VecFx32 *pVec, int nDelta, int nReaction,
                                  int nAngle, u8 *pColl);
extern void func_ov022_0209d0b0(struct Actor *pActor, int *pCounter, int nDelta);
extern void Ov022_TickChargeTimer(struct Actor *pActor, int nDelta);
extern void func_ov022_02097b78(struct Actor *pActor);
extern int Ov002_GetSlotTableByte(int nSlot);
extern void Ov013_UpdateSpawnGroups(struct Actor *pActor);
extern void Ov022_PlayHitFeedback(struct Actor *pActor, int nDelta);
extern void Ov022_StepReactionState(u8 *pMask, int nDelta);
extern void Ov022_StepRun(u8 *pBlk, int nDelta);
extern void Ov022_StepChargeEntries(struct Actor *pActor, int nDelta);
extern void Ov022_StepLocalActorCues(struct Actor *pActor);
extern int GameState_GetField(int nFlag, int nWhich);
extern void Ov002_RefreshMemberPanel(void);
extern int Ov002_Panel_IsMode9(void);
extern int Ov002_Panel_GetField10(void);
extern void Ov002_AcceptRequestAndNotify(int nWhich);

void Ov022_UpdateSubsystems(struct Actor *pActor)
{
    VecFx32 vecFacing;
    int bLoud;
    int nGauge;
    int bBlocked;
    int nDelta;
    int nMask;

    func_ov022_020ad44c(&vecFacing, pActor);
    if (pActor->nOwner == Session_GetLocalPlayerIndex()
        && (bLoud = 0, (u32)pActor->nFlags & 0x10000) == 0) {
        if ((pActor->nFlags2 & (1ULL << 53)) != 0) {
            bLoud = 1;
        }
        if (LoadGlobalU16At0() == 0x2a) {
            Ov106_SetSceneAnimEnabled(bLoud);
        } else {
            Ov002_SetWidgetFullOrZero(bLoud);
        }
        if ((pActor->nFlags2 & (1ULL << 61)) != 0) {
            if (LoadGlobalU16At0() == 0x2a) {
                Ov106_SetField8CCC(1);
            } else {
                Ov002_HudWidgets_SetFieldE0(1);
            }
        } else {
            if (LoadGlobalU16At0() == 0x2a) {
                Ov106_SetField8CCC(0);
            } else {
                Ov002_HudWidgets_SetFieldE0(0);
            }
        }
    }

    if (pActor->nOwner == Session_GetLocalPlayerIndex()
        && ((u32)pActor->nFlags & 0x10000) == 0) {
        nGauge = Ov022_ComputeChipGauge(&pActor->chipBlk);
        bBlocked = 0;
        if (Ov002_IsMissionClearFinished(bBlocked) != 0) {
            bBlocked = 1;
        }
        if (Ov002_GetStateWord() == 0x6c && (data_0204c240 & 4) == 0) {
            bBlocked = 1;
        }
        if (nGauge > 0) {
            if (nGauge >= pActor->nHp && bBlocked == 0) {
                Ov002_SetPanelMode_2(1);
            } else {
                Ov002_SetPanelMode_2(0);
            }
            Ov002_SetScrollPosition(1, (u16)nGauge);
        }
    }

    if (Ov022_IsHoldingItem(pActor, 0xc) != 0) {
        nGauge = Ov022_GetMarkerState(pActor->nId);
        if (nGauge == -1 || nGauge == 2) {
            func_ov022_020ad2e4(pActor, 2);
        }
    }
    if ((pActor->nFlags2 & (1ULL << 59)) != 0) {
        func_ov022_02093f24(&pActor->reactionBlk, 8);
        Ov022_PlayEntityVoice(pActor, 0, 0x5b);
    }
    if (((pActor->nFlags2 & (1ULL << 40)) != 0
         || (pActor->nFlags2 & (1ULL << 41)) != 0)
        && pActor->nEffectA != 0) {
        Ov022_StepEffectTowardCamera(pActor);
    }
    if (pActor->nEffectB != -1) {
        Ov022_MoveEffectTowardCamera(pActor);
    }
    Ov022_StepReactionPhase(&pActor->reactionBlk);
    Ov022_StepSpinEffect(&pActor->reactBlk, &vecFacing, (u16)(pActor->pNode->nAngle - 0x8000),
                         pActor->nHitReaction == 0x13, pActor->nAnimStep);
    if ((pActor->nFlags2 & (1ULL << 27)) != 0
        || (pActor->nFlags2 & (1ULL << 28)) != 0) {
        Ov022_ResetFields135_168_174(&pActor->reactBlk);
    }
    if ((pActor->nFlags2 & (1ULL << 45)) != 0
        || (pActor->nFlags2 & (1ULL << 44)) != 0) {
        Ov022_StartSlotEffect(&pActor->slotBlk, &pActor->vecPos,
                              (u16)(pActor->pNode->nAngle - 0x8000), 0x1000);
    }
    func_ov022_02092808(&pActor->slotBlk, pActor->nAnimStep);
    func_ov022_02094224(&pActor->timerBlk, &pActor->vecPos, pActor->nAnimStep);
    nDelta = Ov022_GetGlobal34();
    Ov022_StepDustEmitter(&pActor->comboBlk, &pActor->vecPos, &vecFacing, nDelta,
                          pActor->nHitReaction, (u16)(pActor->pNode->nAngle - 0x8000),
                          &pActor->collMain);
    if (Session_GetLocalPlayerIndex() == 0) {
        if ((data_0204c240 & 2) != 0) {
            if ((pActor->nInputMask & 4) != 0
                && (pActor->nFlags2 & (1ULL << 7)) == 0) {
                func_ov022_0209d0b0(pActor, &pActor->nWrapB,
                                    Ov022_GetGlobal34());
            } else {
                pActor->nWrapB = 0;
            }
            func_ov022_0209d0b0(pActor, &pActor->nWrapA,
                                Ov022_GetGlobal34());
        }
        Ov022_TickChargeTimer(pActor, Ov022_GetGlobal34());
    }
    if (((u32)pActor->nFlags & 0x10000) != 0) {
        func_ov022_02097b78(pActor);
    }
    if (Ov002_GetSlotTableByte(pActor->nSlotIndex) == 0xf) {
        Ov013_UpdateSpawnGroups(pActor);
    }
    Ov022_PlayHitFeedback(pActor, Ov022_GetGlobal34());
    Ov022_StepReactionState(&pActor->slotMask, Ov022_GetGlobal34());
    Ov022_StepRun(&pActor->chipBlk, Ov022_GetGlobal34());
    Ov022_StepChargeEntries(pActor, Ov022_GetGlobal34());
    Ov022_StepLocalActorCues(pActor);
    pActor->pfnUpdate(pActor);

    if (pActor->nOwner != Session_GetLocalPlayerIndex()) {
        return;
    }
    if ((pActor->nFlags & (1ULL << 16)) != 0) {
        return;
    }
    if ((pActor->nFlags & (1ULL << 20)) == 0) {
        return;
    }
    if (GameState_GetField(CONFIG_CURSOR_POSITION, 1) == 0) {
        if (GameState_GetField(CONFIG_CONTROLS, 1) == 0) {
            nMask = 0x200;
        } else {
            nMask = 0x100;
        }
        if ((gPadHeld & (u16)nMask) == 0
            || ((Ov002_Panel_IsMode9() != 0 || Ov002_Panel_GetField10() != 0) ? 1 : 0) == 0) {
            Ov002_AcceptRequestAndNotify(0);
        }
    } else {
        Ov002_RefreshMemberPanel();
    }
    pActor->nFlags &= ~(1ULL << 20);
}
