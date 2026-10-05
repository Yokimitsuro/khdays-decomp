/* Redraws the equipment panel: the level and stats of the current character, the equipped weapon,
 * the stat bars and the item list, then uploads the page's surfaces. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct { u16 h0, h1, h2, h3, h4, h5; u32 w; } Ov008WeaponStat;
typedef struct { int a[22]; } Ov008StatColTable;

extern int               data_ov008_02090f20;
extern u8                gPartyMembers[];
extern u16               data_0204c680[];
extern u8               *gGameState;
extern Ov008StatColTable data_ov008_0208f7f8;

extern int   Ov008_GetPageB(void);
extern void  PlayRecord_FoldFrame(int obj, void *state);
extern void  LevelTable_ReadEntry(int a, int b, void *out);
extern void  Ov008_LoadWeaponStats(int id, int flag);
extern int Ov008_DrawPageBElement(int param_1, int param_2, ...);
extern void  Ov008_DrawPageBElementAt(int a, int b, int idx);
extern int  *NNS_FndGetNthListObject(void *list, int key);
extern void  Ov008_ForEachNode(int self);
extern int   Ov008_GetLocalPlayerStatB(void);
extern int   Ov008_GetVarRecordByIndex(int base, int id);
extern void  Ov008_AddListEntry(int p1, int a, int b, int c, int d, int e, int f, int g, int h, int i);
extern int   NNS_FndGetNextListObject(void *list, int prev);
extern void  Ov008_DrawStatBar(int root, int *self, int idx, int val);
extern void  Ov008_UpdateScrollGauge(void *p);
extern int   Ov008_ScrollMenuMoveTo(int a, int b, int c, int d);
extern void  Ov008_PageB_UploadSurface118(void);
extern void  Ov008_PageB_UploadSurfaceDC(void);

#pragma opt_lifetimes off

void Ov008_RefreshEquipPanel(int *self)
{
    Ov008StatColTable tbl;
    Ov008WeaponStat sbuf;
    int local_90, local_94, local_98;
    int root = Ov008_GetPageB();
    int *node = 0;
    int iVar16 = 0;
    int iVar17 = iVar16;
    int finalIndex;
    int uVar4, iVar12, bVar1, iVar9;
    u16 *puVar2;
    int *puVar7;
    u8 *idxData;
    idxData=gPartyMembers;
    local_98 = local_94 = local_90 = 0;
    if (data_ov008_02090f20 == 0)
        return;
    PlayRecord_FoldFrame(0, self);
    puVar2 = data_0204c680;
    LevelTable_ReadEntry(gPartyMembers[3], gPartyMembers[2], &sbuf);
    Ov008_LoadWeaponStats(self[0xb] != 0 ? -1 : (int)gPartyMembers[4], self[0xc]);
    Ov008_DrawPageBElement(2, 0, idxData[2] + 1);
    if (self[0xd] != 0)
        Ov008_DrawPageBElement(3, 0, 1);
    else
        Ov008_DrawPageBElement(3, 0, puVar2[3]);
    iVar12 = gGameState[0x811] + 0xf;
    Ov008_DrawPageBElement(0x11, 0, self[1], iVar12);
    Ov008_DrawPageBElementAt(sbuf.h0, puVar2[0], 7);
    Ov008_DrawPageBElementAt(sbuf.h1, puVar2[1], 9);
    Ov008_DrawPageBElementAt(sbuf.h2, puVar2[2], 0xb);
    Ov008_DrawPageBElementAt(sbuf.w, *(int *)(puVar2 + 6), 0xc);
    Ov008_DrawPageBElementAt(sbuf.h4, puVar2[4], 0xd);
    Ov008_DrawPageBElement(6, 0, self[0]);

    puVar7 = NNS_FndGetNthListObject((void *)(root + 0x1cc), *(int *)(root + 0x50) & 0xffff);
    if (puVar7 != 0) {
        iVar16 = puVar7[0];
        iVar17 = puVar7[2];
    }
    Ov008_ForEachNode(root);
    uVar4 = Ov008_GetLocalPlayerStatB();
    if (uVar4 == 10 && self[0xb] != 0) {
        Ov008_AddListEntry(root, 0xff, 4, -1, -1, 0, 0, 1, Ov008_GetVarRecordByIndex(root + 0x58, 0x36), 0);
        Ov008_AddListEntry(root, 0xfe, 4, -1, -1, 0, 0, 1, Ov008_GetVarRecordByIndex(root + 0x58, 0x85), 0);
    } else {
        MsgDb_FetchRecord(&local_98, uVar4, self[0x1d], 0xe);
        Ov008_AddListEntry(root, self[0x1d], 4, -1, -1, 0, 0, 1, *(int *)(local_98 + 0xc), 0);
        DispatchByNodeKind(&local_98);
    }

    node = (int *)NNS_FndGetNextListObject((void *)(self + 2), 0);
    while (node != 0) {
        MsgDb_FetchRecord(&local_90, 0x13, node[0], 0xe);
        Ov008_AddListEntry(root, node[0], 1, node[4], node[5], node[2], node[3], 1, *(int *)(local_90 + 0xc), 0);
        DispatchByNodeKind(&local_90);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 2), (int)node);
    }
    node = (int *)NNS_FndGetNextListObject((void *)(self + 5), 0);
    while (node != 0) {
        MsgDb_FetchRecord(&local_90, 0x13, node[0], 0xe);
        Ov008_AddListEntry(root, node[0], 5, node[1], node[2], node[3], node[4], node[5], *(int *)(local_90 + 0xc), 0);
        DispatchByNodeKind(&local_90);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 5), (int)node);
    }
    node = (int *)NNS_FndGetNextListObject((void *)(self + 8), 0);
    while (node != 0) {
        MsgDb_FetchRecord(&local_94, 0x15, node[0], 0xe);
        Ov008_AddListEntry(root, node[0], 0, -1, node[1], node[2], node[3], 1, *(int *)(local_94 + 0xc), 0);
        DispatchByNodeKind(&local_94);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 8), (int)node);
    }

    tbl = data_ov008_0208f7f8;
    bVar1 = idxData[3];
    iVar9 = tbl.a[bVar1];
    for (iVar12 = 0; iVar12 < 0xe; iVar12++) {
        if (iVar12 == iVar9)
            Ov008_DrawStatBar(root, self, iVar12, 0);
        else
            Ov008_DrawStatBar(root, self, iVar12, self[iVar12 + 0xe]);
    }

    finalIndex = 0;
    puVar7 = (int *)NNS_FndGetNextListObject((void *)(root + 0x1cc), 0);
    while (puVar7 != 0) {
        if (puVar7[0] == iVar16 && puVar7[2] == iVar17) {
            *(int *)(root + 0x50) = finalIndex;
            break;
        }
        finalIndex++;
        puVar7 = (int *)NNS_FndGetNextListObject((void *)(root + 0x1cc), (int)puVar7);
    }
    if (puVar7 == 0 && *(int *)(root + 0x50) >= finalIndex)
        *(int *)(root + 0x50) = finalIndex - 1;
    Ov008_UpdateScrollGauge((void *)root);
    Ov008_ScrollMenuMoveTo(root, *(int *)(root + 0x50), 0, 1);
    Ov008_PageB_UploadSurface118();
    Ov008_PageB_UploadSurfaceDC();
}
