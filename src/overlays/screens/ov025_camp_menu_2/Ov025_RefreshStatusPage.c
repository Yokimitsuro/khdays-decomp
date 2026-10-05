/* Page refresh of ov025, the twin of ov008 0206ed7c: when the page is active (020b575c) the stat
 * block of the selected entry (02035730 on gPartyMembers) is shown through 020a4cd0 / 020a41f0 /
 * 020a36d8, the row list is rebuilt (the +0x74 record as kind 4, then the +0x8, +0x14 and +0x20 lists
 * as kinds 1, 5 and 0, each resolved through 020342e8 / 020343cc), the fourteen +0x38 column values
 * are applied (the entry's own column from data_ov025_020b4520 forced to 0) and the cursor (+0x50)
 * is put back on the row it was on, or clamped to the last row. The ov008 copy's page-10 special
 * case is absent here. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct { u16 h0, h1, h2, h3, h4, h5; u32 w; } Ov025WeaponStat;
typedef struct { int a[22]; } Ov025StatColTable;

extern int               data_ov025_020b575c;
extern u8                gPartyMembers[];
extern u16               data_0204c680[];
extern u8               *gGameState;
extern Ov025StatColTable data_ov025_020b4520;

extern int   Ov025_GetPageB(void);
extern void  PlayRecord_FoldFrame(int obj, void *state);
extern void  LevelTable_ReadEntry(int a, int b, void *out);
extern void  Ov025_StatusPanel_SetWeapon(int id, int flag);
extern int Ov025_DrawPageBElement(int param_1, int param_2, ...);
extern void  Ov025_DrawPageBElementAt(int a, int b, int idx);
extern int  *NNS_FndGetNthListObject(void *list, int key);
extern void  Ov025_ProcessAllAtField1cc(int self);
extern int   Ov025_GetMenuMsgDbId(void);
extern void  Ov025_AddListEntry(int p1, int a, int b, int c, int d, int e, int f, int g, int h, int i);
extern int   NNS_FndGetNextListObject(void *list, int prev);
extern void  Ov025_DrawStatBar(int root, int *self, int idx, int val);
extern void  Ov025_UpdateScrollGauge(void *p);
extern int   Ov025_ScrollMenuMoveTo(int a, int b, int c, int d);
extern void  Ov025_PageB_UploadSurface118(void);
extern void  Ov025_PageB_UploadSurfaceDC(void);

#pragma opt_lifetimes off

void Ov025_RefreshStatusPage(int *self)
{
    Ov025StatColTable tbl;
    Ov025WeaponStat sbuf;
    int local_90, local_94, local_98;
    int root = Ov025_GetPageB();
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
    if (data_ov025_020b575c == 0)
        return;
    PlayRecord_FoldFrame(0, self);
    puVar2 = data_0204c680;
    LevelTable_ReadEntry(gPartyMembers[3], gPartyMembers[2], &sbuf);
    Ov025_StatusPanel_SetWeapon(gPartyMembers[4], self[0xc]);
    Ov025_DrawPageBElement(2, 0, idxData[2] + 1);
    if (self[0xd] != 0)
        Ov025_DrawPageBElement(3, 0, 1);
    else
        Ov025_DrawPageBElement(3, 0, puVar2[3]);
    iVar12 = gGameState[0x811] + 0xf;
    Ov025_DrawPageBElement(0x11, 0, self[1], iVar12);
    Ov025_DrawPageBElementAt(sbuf.h0, puVar2[0], 7);
    Ov025_DrawPageBElementAt(sbuf.h1, puVar2[1], 9);
    Ov025_DrawPageBElementAt(sbuf.h2, puVar2[2], 0xb);
    Ov025_DrawPageBElementAt(sbuf.w, *(int *)(puVar2 + 6), 0xc);
    Ov025_DrawPageBElementAt(sbuf.h4, puVar2[4], 0xd);
    Ov025_DrawPageBElement(6, 0, self[0]);

    puVar7 = NNS_FndGetNthListObject((void *)(root + 0x1cc), *(int *)(root + 0x50) & 0xffff);
    if (puVar7 != 0) {
        iVar16 = puVar7[0];
        iVar17 = puVar7[2];
    }
    Ov025_ProcessAllAtField1cc(root);
    uVar4 = Ov025_GetMenuMsgDbId();
    MsgDb_FetchRecord(&local_98, uVar4, self[0x1d], 0xe);
    Ov025_AddListEntry(root, self[0x1d], 4, -1, -1, 0, 0, 1, *(int *)(local_98 + 0xc), 0);
    DispatchByNodeKind(&local_98);

    node = (int *)NNS_FndGetNextListObject((void *)(self + 2), 0);
    while (node != 0) {
        MsgDb_FetchRecord(&local_90, 0x13, node[0], 0xe);
        Ov025_AddListEntry(root, node[0], 1, node[4], node[5], node[2], node[3], 1, *(int *)(local_90 + 0xc), 0);
        DispatchByNodeKind(&local_90);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 2), (int)node);
    }
    node = (int *)NNS_FndGetNextListObject((void *)(self + 5), 0);
    while (node != 0) {
        MsgDb_FetchRecord(&local_90, 0x13, node[0], 0xe);
        Ov025_AddListEntry(root, node[0], 5, node[1], node[2], node[3], node[4], node[5], *(int *)(local_90 + 0xc), 0);
        DispatchByNodeKind(&local_90);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 5), (int)node);
    }
    node = (int *)NNS_FndGetNextListObject((void *)(self + 8), 0);
    while (node != 0) {
        MsgDb_FetchRecord(&local_94, 0x15, node[0], 0xe);
        Ov025_AddListEntry(root, node[0], 0, -1, node[1], node[2], node[3], 1, *(int *)(local_94 + 0xc), 0);
        DispatchByNodeKind(&local_94);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 8), (int)node);
    }

    tbl = data_ov025_020b4520;
    bVar1 = idxData[3];
    iVar9 = tbl.a[bVar1];
    for (iVar12 = 0; iVar12 < 0xe; iVar12++) {
        if (iVar12 == iVar9)
            Ov025_DrawStatBar(root, self, iVar12, 0);
        else
            Ov025_DrawStatBar(root, self, iVar12, self[iVar12 + 0xe]);
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
    Ov025_UpdateScrollGauge((void *)root);
    Ov025_ScrollMenuMoveTo(root, *(int *)(root + 0x50), 0, 1);
    Ov025_PageB_UploadSurface118();
    Ov025_PageB_UploadSurfaceDC();
}
