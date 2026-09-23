/* Page refresh of ov025, the twin of ov008 0206ed7c: when the page is active (020b575c) the stat
 * block of the selected entry (02035730 on data_0204c678) is shown through 020a4cd0 / 020a41f0 /
 * 020a36d8, the row list is rebuilt (the +0x74 record as kind 4, then the +0x8, +0x14 and +0x20 lists
 * as kinds 1, 5 and 0, each resolved through 020342e8 / 020343cc), the fourteen +0x38 column values
 * are applied (the entry's own column from data_ov025_020b4520 forced to 0) and the cursor (+0x50)
 * is put back on the row it was on, or clamped to the last row. The ov008 copy's page-10 special
 * case is absent here. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct { u16 h0, h1, h2, h3, h4, h5; u32 w; } Ov025WeaponStat;
typedef struct { int a[22]; } Ov025StatColTable;

extern int               data_ov025_020b575c;
extern u8                data_0204c678[];
extern u16               data_0204c680[];
extern u8               *data_0204be18;
extern Ov025StatColTable data_ov025_020b4520;

extern int   func_ov025_02084b14(void);
extern void  func_02035a58(int obj, void *state);
extern void  func_02035730(int a, int b, void *out);
extern void  func_ov025_020a4cd0(int id, int flag);
extern int   func_ov025_020a41f0(int id, int a, ...);
extern void  func_ov025_020a36d8(int a, int b, int idx);
extern int  *func_02010154(void *list, int key);
extern void  func_ov025_020a3848(int self);
extern int   func_ov025_020a0f28(void);
extern void  func_ov025_020a3aa4(int p1, int a, int b, int c, int d, int e, int f, int g, int h, int i);
extern void  func_020342e8(int *rec, int a, int b, int c);
extern void  func_020343cc(int *rec);
extern int   NNS_FndGetNextListObject(void *list, int prev);
extern void  func_ov025_020a3b60(int root, int *self, int idx, int val);
extern void  func_ov025_020a1930(void *p);
extern int   func_ov025_020a1fa0(int a, int b, int c, int d);
extern void  func_ov025_020a4920(void);
extern void  func_ov025_020a4948(void);

#pragma opt_lifetimes off

void func_ov025_020a4408(int *self)
{
    Ov025StatColTable tbl;
    Ov025WeaponStat sbuf;
    int local_90, local_94, local_98;
    int root = func_ov025_02084b14();
    int *node = 0;
    int iVar16 = 0;
    int iVar17 = iVar16;
    int finalIndex;
    int uVar4, iVar12, bVar1, iVar9;
    u16 *puVar2;
    int *puVar7;
    u8 *idxData;
    idxData=data_0204c678;
    local_98 = local_94 = local_90 = 0;
    if (data_ov025_020b575c == 0)
        return;
    func_02035a58(0, self);
    puVar2 = data_0204c680;
    func_02035730(data_0204c678[3], data_0204c678[2], &sbuf);
    func_ov025_020a4cd0(data_0204c678[4], self[0xc]);
    func_ov025_020a41f0(2, 0, idxData[2] + 1);
    if (self[0xd] != 0)
        func_ov025_020a41f0(3, 0, 1);
    else
        func_ov025_020a41f0(3, 0, puVar2[3]);
    iVar12 = data_0204be18[0x811] + 0xf;
    func_ov025_020a41f0(0x11, 0, self[1], iVar12);
    func_ov025_020a36d8(sbuf.h0, puVar2[0], 7);
    func_ov025_020a36d8(sbuf.h1, puVar2[1], 9);
    func_ov025_020a36d8(sbuf.h2, puVar2[2], 0xb);
    func_ov025_020a36d8(sbuf.w, *(int *)(puVar2 + 6), 0xc);
    func_ov025_020a36d8(sbuf.h4, puVar2[4], 0xd);
    func_ov025_020a41f0(6, 0, self[0]);

    puVar7 = func_02010154((void *)(root + 0x1cc), *(int *)(root + 0x50) & 0xffff);
    if (puVar7 != 0) {
        iVar16 = puVar7[0];
        iVar17 = puVar7[2];
    }
    func_ov025_020a3848(root);
    uVar4 = func_ov025_020a0f28();
    func_020342e8(&local_98, uVar4, self[0x1d], 0xe);
    func_ov025_020a3aa4(root, self[0x1d], 4, -1, -1, 0, 0, 1, *(int *)(local_98 + 0xc), 0);
    func_020343cc(&local_98);

    node = (int *)NNS_FndGetNextListObject((void *)(self + 2), 0);
    while (node != 0) {
        func_020342e8(&local_90, 0x13, node[0], 0xe);
        func_ov025_020a3aa4(root, node[0], 1, node[4], node[5], node[2], node[3], 1, *(int *)(local_90 + 0xc), 0);
        func_020343cc(&local_90);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 2), (int)node);
    }
    node = (int *)NNS_FndGetNextListObject((void *)(self + 5), 0);
    while (node != 0) {
        func_020342e8(&local_90, 0x13, node[0], 0xe);
        func_ov025_020a3aa4(root, node[0], 5, node[1], node[2], node[3], node[4], node[5], *(int *)(local_90 + 0xc), 0);
        func_020343cc(&local_90);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 5), (int)node);
    }
    node = (int *)NNS_FndGetNextListObject((void *)(self + 8), 0);
    while (node != 0) {
        func_020342e8(&local_94, 0x15, node[0], 0xe);
        func_ov025_020a3aa4(root, node[0], 0, -1, node[1], node[2], node[3], 1, *(int *)(local_94 + 0xc), 0);
        func_020343cc(&local_94);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 8), (int)node);
    }

    tbl = data_ov025_020b4520;
    bVar1 = idxData[3];
    iVar9 = tbl.a[bVar1];
    for (iVar12 = 0; iVar12 < 0xe; iVar12++) {
        if (iVar12 == iVar9)
            func_ov025_020a3b60(root, self, iVar12, 0);
        else
            func_ov025_020a3b60(root, self, iVar12, self[iVar12 + 0xe]);
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
    func_ov025_020a1930((void *)root);
    func_ov025_020a1fa0(root, *(int *)(root + 0x50), 0, 1);
    func_ov025_020a4920();
    func_ov025_020a4948();
}
