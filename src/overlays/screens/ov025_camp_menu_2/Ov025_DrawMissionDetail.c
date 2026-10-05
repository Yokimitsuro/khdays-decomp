/* Ov025_DrawMissionDetail -- Ov008_DrawMissionDetail: redraw the mission menu's
 * detail panels for the listed entry of the current mission (0205b6e8 of
 * 020511e0).  Outside a page transition (02051028 == 0) the mission's name
 * node (020760a0 on the +0x548 list) is looked up; the row / info drawers
 * (02074b4c, 02074c40, 02075f70) run and the tab switches (02074a4c).  The
 * rank panel (+0xc0) formats text 02090980 with the rank (+0x6) and a glyph
 * (0x20; during a transition without transfer 0xff41, or 0xff42 in colour
 * 0xf3 when the kind (+0x18) is 2).  The unlock flag of the text slot (+0x4:
 * 0 / 4 always set, else game flag 0x3bc9 + slot) then picks the second
 * line: out of a transition or with a transfer, the slot's entry (0205b6c8
 * through 020741a8 width 0x68, text 0205b6a8) or variable text 4 when
 * locked; in a transition without transfer the reward kind (+0x2e, 0 .. 8)
 * picks variable text 0x15 .. 0x1e (0x1a skipped, 02090990 otherwise) that
 * the description format (+0x48) expands into a 256-entry buffer (width
 * 0x78).  The name panel (+0x48) draws the entry's name (+0x3c) -- or, when
 * it is empty, the name node's -- in the current colour.  The count panel
 * (+0x84) shows "set / total" (020743e4, text 02090994) outside a transition,
 * else with a transfer the count's (+0x8) variable text 0xe + count from the
 * second record set (+0x53c) when the count is not 0.  The hint panel
 * (+0xfc) draws variable text 1; all four panels are queued and slots 0x18 /
 * 0x1a marked used.  Codegen: the name node is the first local set (0);
 * the colour, glyph and unlock flag live in a block (declared in that
 * order, so they colour after the entry: r6 / r7 / r8) that opens before
 * the entry lookup; the glyph is set to 0x20 before the transition test and
 * to 0xff41 inside it, incremented for kind 2; the unlock flag is tested
 * three times (width, text, locked text) with the text slot loaded into a
 * local before the first test; the three-argument prototypes of the drawers
 * copy the node into r2.
 */

#include "nitro/types.h"

#define COLOUR_NORMAL   0xf1
#define COLOUR_ACTIVE   0xf3
#define GLYPH_SPACE     0x20
#define GLYPH_MARK_A    0xff41
#define FLAG_TEXT_SLOT_BASE 0x3bc9
#define TEXT_LOCKED     4
#define TEXT_HINT       1
#define TEXT_REWARD_FIRST 0x15
#define TEXT_COUNT_BASE 0xe
#define SLOT_A          0x18
#define SLOT_B          0x1a

typedef struct Ov008MissionListEntry {
    u16   nWord;              /* 0x00 */
    u16   missionId;          /* 0x02 */
    u16   nTextSlot;          /* 0x04 */
    u16   nRank;              /* 0x06 */
    u16   nCount;             /* 0x08 */
    u8    pad_0a[0x18 - 0xa];
    int   nKind;              /* 0x18 */
    u8    pad_1c[0x2e - 0x1c];
    u16   nRewardKind;        /* 0x2e */
    u8    pad_30[0x3c - 0x30];
    u16  *pName;              /* 0x3c */
    u8    pad_40[8];
    u16  *pDescFormat;        /* 0x48 */
} Ov008MissionListEntry;

typedef struct Ov008MissionNameNode {
    u16   nWord;              /* 0x00 */
    u8    pad_02[0x3c - 2];
    u16  *pName;              /* 0x3c */
} Ov008MissionNameNode;

typedef struct Ov008MissionMenu {
    u8  pad_000[0x48];
    u8  nameSurface[0x3c];    /* 0x048 */
    u8  countSurface[0x3c];   /* 0x084 */
    u8  rankSurface[0x3c];    /* 0x0c0 */
    u8  hintSurface[0x3c];    /* 0x0fc */
    u8  pad_138[0x150 - 0x138];
    int bTransfer;            /* 0x150 */
    u8  pad_154[0x530 - 0x154];
    u8  records[0xc];         /* 0x530: variable text records */
    u8  records2[0xc];        /* 0x53c: second record set */
    u8  nameList[0xc];        /* 0x548: mission name nodes */
} Ov008MissionMenu;

extern const u16 data_ov025_020b5464[];                                  /* "rank" format */
extern const u16 data_ov025_020b5474[];                                  /* empty reward text */
extern const u16 data_ov025_020b5478[];                                  /* "set / total" format */
extern u32   Ov025_GetCtxField967c(void);                                  /* Ov008_GetCtxField967c: current mission id */
extern Ov008MissionListEntry *Ov025_GetNextMissionEntry_5(u32 nMissionId);       /* find the listed mission */
extern int   Ov025_GetCtxObject9634(void);                                  /* Ov008_GetCtxObject9634: page transition */
extern Ov008MissionNameNode *Ov025_MissionMenu_FindEntry(Ov008MissionMenu *pMenu, u32 nWord); /* find the name node */
extern void  Ov025_MissionMenu_DrawMissionText(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry, Ov008MissionNameNode *pNode);
extern void  Ov025_MissionMenu_DrawInfo(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry, Ov008MissionNameNode *pNode);
extern void  Ov025_DrawMissionInfoText(Ov008MissionMenu *pMenu, Ov008MissionListEntry *pEntry, Ov008MissionNameNode *pNode); /* Ov008_DrawMissionInfoText */
extern void  Ov025_SwitchMenuTab(Ov008MissionMenu *pMenu, int nTab);     /* Ov008_SwitchMenuTab */
extern int   GameState_IsFlagSet(int nFlag);                                   /* GameState_IsFlagSet */
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...); /* Text_FormatUtf16 */
extern void  Ov025_BindDescriptor0B(void *pSurface);
extern void  Obj_InvokeInnerVtable4(void *pSurface);                              /* Obj_InvokeInnerVtable4 */
extern void  Text_DrawWithShadow(void *pSurface, int nX, int nY, int nColour, void *pText, int nFlag); /* Text_DrawWithShadow */
extern void *Ov025_GetVarRecordByIndex(void *pRecords, int nIndex);            /* GetVarRecordByIndex */
extern int   Ov025_GetNextMissionEntry_4(u32 nTextSlot);
extern void  Ov025_SetupAndConfigure_2(void *pSurface, int nValue, int nWidth); /* Ov008_Set_41a8 */
extern void *Ov025_GetNextMissionEntry_3(Ov008MissionListEntry *pEntry);
extern void  Ov025_BindSharedBlockB(void *pSurface);
extern void  Ov025_RunTwoPassUpdate_2(void *pSurface, void *pText, int nWidth);
extern void  Ov025_CountGroupFlagsSet2(Ov008MissionMenu *pMenu, u32 nWord, int *pnSet, u32 *pnCount); /* Ov008_CountGroupFlagsSet2 */
extern void  EnqueueObjGfxCommand(void *pSurface);                              /* EnqueueObjGfxCommand */
extern void  Ov025_MarkSlotUsed(int nSlot);                             /* Ov008_MarkSlotUsed */

void Ov025_DrawMissionDetail(Ov008MissionMenu *pMenu, int nTab)
{
    u16 aDesc[0x80];
    u16 aRank[4];
    u16 aCount[4];
    int nSet;
    u32 nTotal;
    Ov008MissionNameNode *pNode;
    Ov008MissionListEntry *pEntry;
    void *pText;
    u16 *pName;

    pNode = 0;
    {
        int nColour;
        int nGlyph;
        int bUnlocked;
        u32 nSlot;

        nColour = COLOUR_NORMAL;
        pEntry = Ov025_GetNextMissionEntry_5(Ov025_GetCtxField967c());
        if (Ov025_GetCtxObject9634() != 0) {
            pNode = Ov025_MissionMenu_FindEntry(pMenu, pEntry->nWord);
        }
        Ov025_MissionMenu_DrawMissionText(pMenu, pEntry, pNode);
        Ov025_MissionMenu_DrawInfo(pMenu, pEntry, pNode);
        Ov025_DrawMissionInfoText(pMenu, pEntry, pNode);
        Ov025_SwitchMenuTab(pMenu, nTab);
        if (pEntry->nTextSlot == 0) {
            bUnlocked = 1;
        } else if (pEntry->nTextSlot == 4) {
            bUnlocked = 1;
        } else {
            bUnlocked = GameState_IsFlagSet(pEntry->nTextSlot + FLAG_TEXT_SLOT_BASE);
        }
        nGlyph = GLYPH_SPACE;
        if (Ov025_GetCtxObject9634() != 0) {
            if (pMenu->bTransfer == 0) {
                nGlyph = GLYPH_MARK_A;
                if (pEntry->nKind == 2) {
                    nGlyph++;
                    nColour = COLOUR_ACTIVE;
                }
            }
        }
        Text_FormatUtf16(aRank, 4, data_ov025_020b5464, pEntry->nRank, nGlyph);
        Ov025_BindDescriptor0B(pMenu->rankSurface);
        Obj_InvokeInnerVtable4(pMenu->rankSurface);
        Text_DrawWithShadow(pMenu->rankSurface, 0, 6, nColour, aRank, 1);
        if (Ov025_GetCtxObject9634() == 0 || pMenu->bTransfer != 0) {
            nSlot = pEntry->nTextSlot;
            if (bUnlocked != 0) {
                Ov025_SetupAndConfigure_2(pMenu->rankSurface, Ov025_GetNextMissionEntry_4(nSlot), 0x68);
            }
            if (bUnlocked != 0) {
                Text_DrawWithShadow(pMenu->rankSurface, 0x14, 6, COLOUR_NORMAL, Ov025_GetNextMissionEntry_3(pEntry), 1);
            }
            if (bUnlocked == 0) {
                Text_DrawWithShadow(pMenu->rankSurface, 0x14, 6, COLOUR_NORMAL, Ov025_GetVarRecordByIndex(pMenu->records, TEXT_LOCKED), 1);
            }
        } else {
            pText = (void *)data_ov025_020b5474;
            switch (pEntry->nRewardKind) {
            case 0:
                pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_REWARD_FIRST);
                break;
            case 1:
                pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_REWARD_FIRST + 1);
                break;
            case 2:
                pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_REWARD_FIRST + 2);
                break;
            case 3:
                pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_REWARD_FIRST + 3);
                break;
            case 4:
                pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_REWARD_FIRST + 4);
                break;
            case 5:
                pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_REWARD_FIRST + 6);
                break;
            case 6:
                pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_REWARD_FIRST + 7);
                break;
            case 7:
                pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_REWARD_FIRST + 8);
                break;
            case 8:
                pText = Ov025_GetVarRecordByIndex(pMenu->records, TEXT_REWARD_FIRST + 9);
                break;
            }
            Text_FormatUtf16(aDesc, 0x100, pEntry->pDescFormat, pText);
            Ov025_SetupAndConfigure_2(pMenu->rankSurface, (int)aDesc, 0x78);
            Text_DrawWithShadow(pMenu->rankSurface, 0x14, 6, nColour, aDesc, 1);
        }
        Ov025_BindSharedBlockB(pMenu->nameSurface);
        pName = pEntry->pName;
        if (*pName == 0 && pNode != 0) {
            Obj_InvokeInnerVtable4(pMenu->nameSurface);
            Ov025_RunTwoPassUpdate_2(pMenu->nameSurface, pNode->pName, 0x80);
            Text_DrawWithShadow(pMenu->nameSurface, 0, 1, nColour, pNode->pName, 1);
        } else {
            Ov025_RunTwoPassUpdate_2(pMenu->nameSurface, pName, 0x80);
            Obj_InvokeInnerVtable4(pMenu->nameSurface);
            Text_DrawWithShadow(pMenu->nameSurface, 0, 1, nColour, pEntry->pName, 1);
        }
        if (Ov025_GetCtxObject9634() == 0) {
            nSet = 0;
            nTotal = 0;
            Ov025_CountGroupFlagsSet2(pMenu, pEntry->nWord, &nSet, &nTotal);
            Text_FormatUtf16(aCount, 4, data_ov025_020b5478, nSet, nTotal);
            Obj_InvokeInnerVtable4(pMenu->countSurface);
            Text_DrawWithShadow(pMenu->countSurface, 2, 7, COLOUR_NORMAL, aCount, 1);
        } else if (pMenu->bTransfer != 0) {
            pText = Ov025_GetVarRecordByIndex(pMenu->records2, pEntry->nCount + TEXT_COUNT_BASE);
            Obj_InvokeInnerVtable4(pMenu->countSurface);
            if (pEntry->nCount != 0) {
                Text_DrawWithShadow(pMenu->countSurface, 0, 5, COLOUR_NORMAL, pText, 1);
            }
        }
        Obj_InvokeInnerVtable4(pMenu->hintSurface);
        Text_DrawWithShadow(pMenu->hintSurface, 4, 2, COLOUR_NORMAL, Ov025_GetVarRecordByIndex(pMenu->records, TEXT_HINT), 0);
        EnqueueObjGfxCommand(pMenu->rankSurface);
        EnqueueObjGfxCommand(pMenu->nameSurface);
        EnqueueObjGfxCommand(pMenu->countSurface);
        EnqueueObjGfxCommand(pMenu->hintSurface);
        Ov025_MarkSlotUsed(SLOT_A);
        Ov025_MarkSlotUsed(SLOT_B);
    }
}
