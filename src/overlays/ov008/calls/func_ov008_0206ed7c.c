typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct { u16 h0, h1, h2, h3, h4, h5; u32 w; } Ov008WeaponStat;
typedef struct { int a[22]; } Ov008StatColTable;

extern int               data_ov008_02090f20;
extern u8                data_0204c678[];
extern u16               data_0204c680[];
extern u8               *data_0204be18;
extern Ov008StatColTable data_ov008_0208f7f8;

extern int   func_ov008_02050cec(void);
extern void  func_02035a58(int obj, void *state);
extern void  func_02035730(int a, int b, void *out);
extern void  func_ov008_0206f6e4(int id, int flag);
extern int   func_ov008_0206eb64(int id, int a, ...);
extern void  func_ov008_0206e044(int a, int b, int idx);
extern int  *func_02010154(void *list, int key);
extern void  func_ov008_0206e1b4(int self);
extern int   func_ov008_0206b6e4(void);
extern int   func_ov008_02055c84(int base, int id);
extern void  func_ov008_0206e410(int p1, int a, int b, int c, int d, int e, int f, int g, int h, int i);
extern void  func_020342e8(int *rec, int a, int b, int c);
extern void  func_020343cc(int *rec);
extern int   NNS_FndGetNextListObject(void *list, int prev);
extern void  func_ov008_0206e4cc(int root, int *self, int idx, int val);
extern void  func_ov008_0206c29c(void *p);
extern int   func_ov008_0206c90c(int a, int b, int c, int d);
extern void  func_ov008_0206f334(void);
extern void  func_ov008_0206f35c(void);

#pragma opt_lifetimes off

void func_ov008_0206ed7c(int *self)
{
    Ov008StatColTable tbl;
    Ov008WeaponStat sbuf;
    int local_90, local_94, local_98;
    int root = func_ov008_02050cec();
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
    if (data_ov008_02090f20 == 0)
        return;
    func_02035a58(0, self);
    puVar2 = data_0204c680;
    func_02035730(data_0204c678[3], data_0204c678[2], &sbuf);
    func_ov008_0206f6e4(self[0xb] != 0 ? -1 : (int)data_0204c678[4], self[0xc]);
    func_ov008_0206eb64(2, 0, idxData[2] + 1);
    if (self[0xd] != 0)
        func_ov008_0206eb64(3, 0, 1);
    else
        func_ov008_0206eb64(3, 0, puVar2[3]);
    iVar12 = data_0204be18[0x811] + 0xf;
    func_ov008_0206eb64(0x11, 0, self[1], iVar12);
    func_ov008_0206e044(sbuf.h0, puVar2[0], 7);
    func_ov008_0206e044(sbuf.h1, puVar2[1], 9);
    func_ov008_0206e044(sbuf.h2, puVar2[2], 0xb);
    func_ov008_0206e044(sbuf.w, *(int *)(puVar2 + 6), 0xc);
    func_ov008_0206e044(sbuf.h4, puVar2[4], 0xd);
    func_ov008_0206eb64(6, 0, self[0]);

    puVar7 = func_02010154((void *)(root + 0x1cc), *(int *)(root + 0x50) & 0xffff);
    if (puVar7 != 0) {
        iVar16 = puVar7[0];
        iVar17 = puVar7[2];
    }
    func_ov008_0206e1b4(root);
    uVar4 = func_ov008_0206b6e4();
    if (uVar4 == 10 && self[0xb] != 0) {
        func_ov008_0206e410(root, 0xff, 4, -1, -1, 0, 0, 1, func_ov008_02055c84(root + 0x58, 0x36), 0);
        func_ov008_0206e410(root, 0xfe, 4, -1, -1, 0, 0, 1, func_ov008_02055c84(root + 0x58, 0x85), 0);
    } else {
        func_020342e8(&local_98, uVar4, self[0x1d], 0xe);
        func_ov008_0206e410(root, self[0x1d], 4, -1, -1, 0, 0, 1, *(int *)(local_98 + 0xc), 0);
        func_020343cc(&local_98);
    }

    node = (int *)NNS_FndGetNextListObject((void *)(self + 2), 0);
    while (node != 0) {
        func_020342e8(&local_90, 0x13, node[0], 0xe);
        func_ov008_0206e410(root, node[0], 1, node[4], node[5], node[2], node[3], 1, *(int *)(local_90 + 0xc), 0);
        func_020343cc(&local_90);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 2), (int)node);
    }
    node = (int *)NNS_FndGetNextListObject((void *)(self + 5), 0);
    while (node != 0) {
        func_020342e8(&local_90, 0x13, node[0], 0xe);
        func_ov008_0206e410(root, node[0], 5, node[1], node[2], node[3], node[4], node[5], *(int *)(local_90 + 0xc), 0);
        func_020343cc(&local_90);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 5), (int)node);
    }
    node = (int *)NNS_FndGetNextListObject((void *)(self + 8), 0);
    while (node != 0) {
        func_020342e8(&local_94, 0x15, node[0], 0xe);
        func_ov008_0206e410(root, node[0], 0, -1, node[1], node[2], node[3], 1, *(int *)(local_94 + 0xc), 0);
        func_020343cc(&local_94);
        node = (int *)NNS_FndGetNextListObject((void *)(self + 8), (int)node);
    }

    tbl = data_ov008_0208f7f8;
    bVar1 = idxData[3];
    iVar9 = tbl.a[bVar1];
    for (iVar12 = 0; iVar12 < 0xe; iVar12++) {
        if (iVar12 == iVar9)
            func_ov008_0206e4cc(root, self, iVar12, 0);
        else
            func_ov008_0206e4cc(root, self, iVar12, self[iVar12 + 0xe]);
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
    func_ov008_0206c29c((void *)root);
    func_ov008_0206c90c(root, *(int *)(root + 0x50), 0, 1);
    func_ov008_0206f334();
    func_ov008_0206f35c();
}
