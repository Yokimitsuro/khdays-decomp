#pragma opt_strength_reduction off
#pragma opt_loop_invariants off
#pragma opt_propagation off
#pragma opt_common_subs off

/* ov003 scene/HUD init (2552B, largest ov003 fn). Faithful readable reconstruction
 * from Ghidra + full pool map. Dominated by MMIO BGxCNT writes + RegisterSeqAndInit
 * cell sequences + char-resource loads + per-entry HUD layout. Same MMIO/register
 * pointer-hold tie class as func_ov003_0204cba0 / ov010_0204cb3c â€” nonmatching by the
 * established pattern; kept as the correct C for the PC port. Returns the next-state
 * fn ptr func_ov003_0204e5b0 (ov003 state-machine convention).
 *
 * Pool map (addr = 0x0204d98c + off):
 *  e344=&data_0204f9a0(heap root global, SET here)  e348=&data_0204f944
 *  e34c=data_0204c300(10-entry init table)          e350=0x0400100a(BG1CNT_sub, held)
 *  e354=0x00fffffc(VRAM base mask)                   e358=data_0204f950
 *  e35c=data_0204f8f8  e360=data_0204f8d0  e364=data_0204f8bc(cell/anim tables)
 *  e368=data_0204f958  e36c=data_0204f964  e370=0x182  e374=0x04000060(REG_MOSAIC, held)
 *  e378=data_0204f978  e37c=&func_ov003_0204cba0(callback)  e380=&func_ov003_0204e5b0(ret) */
typedef struct {
    unsigned int mode;
    unsigned int value;
} Ov003InitState;

typedef struct {
    unsigned short first;
    unsigned short second;
} Ov003InitPair;

typedef struct {
    unsigned short first;
    unsigned short second;
} Ov003InitTablePair;

typedef struct {
    unsigned int displayControl;
    unsigned char pad_0004[6];
    unsigned short bg1Control;
    unsigned short bg2Control;
    unsigned short bg3Control;
} Ov003MainDisplayRegs;

typedef struct {
    unsigned short bg1Control;
    unsigned short bg2Control;
} Ov003SubBgRegs;

typedef struct {
    unsigned char pad_000[0x290];
    unsigned int hasExtra;
} Ov003EntryFlags;

typedef struct {
    unsigned char pad_000[0x0c];
    unsigned short tiles[0x40];
} Ov003TileData;

extern unsigned short *data_ov003_0204f9a0;
extern unsigned short data_0204c300[];
extern unsigned char data_ov003_0204f944[];
extern unsigned char data_ov003_0204f950[];
extern unsigned char data_ov003_0204f958[];
extern unsigned char data_ov003_0204f964[];
extern unsigned char data_ov003_0204f978[];
extern signed char data_ov003_0204f8f8[], data_ov003_0204f8d0[], data_ov003_0204f8bc[];
extern int func_ov003_0204e5b0;
extern void func_ov003_0204cba0(void);

extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern void func_0201e1d0(void);
extern unsigned int *func_02024ee8(void *archive, int index);
extern int func_ov105_020bd7c4(void);
extern void func_ov003_0204d74c(void);
extern void func_0202e8ec(unsigned int *p, int a);
extern void func_0202ea14(int p, int a);
extern void func_0202ea1c(int p, int a);
extern void GX_SetBankForTex(int a);
extern void GX_BeginLoadOBJExtPltt(int a);
extern void GX_SetBankForBG(int a);
extern void func_02011174(int a, int b);
extern void func_020056b4(int a, int b, int c);          /* SetDisplayControl(1,0,1) */
extern void func_0202e358();
extern void func_0202a634(unsigned short *obj, unsigned int *vram, int a, int b); /* RegisterSeqAndInit */
extern void OS_SPrintf(unsigned int *out, unsigned int tbl, unsigned int n, int idx);
extern void func_0202af3c(int obj, int anim, unsigned int *ctx);
extern void func_0202a388(unsigned int *a, int obj, unsigned int *vram, int b);
extern void func_0202accc(int obj, int slot, int a, int b);
extern void GX_SetBankForSubBG(int a);
extern unsigned int func_0201ef9c(unsigned int vram, int heap);
extern int func_02024e5c(void);                          /* returns HUD-variant flag */
extern void func_ov003_0204d308(unsigned int *out, int root, int a, int b, int c); /* LoadCharResource */
extern void MIi_CpuClear16(int a, int dst, int len);
extern void func_02024c94(unsigned int *out, int *res, int a, int b, int c);
extern void func_ov003_0204d3b0(int i);                  /* LayoutHudPanelRow */
extern void DC_FlushRange(int addr, int len);
extern void func_02024a6c(int engine, void *resource, void *data, int offset, int size);
extern void func_02024ae0(int a, int b, int c, int d);
extern void func_0202497c(int a, unsigned short *b, int c, int d);
extern void func_02024b04(int a, int b, int c, int d);
extern void func_020115b8(void);
extern void func_020249b0(int a, int b, int c, int d);
extern void func_020249e4(int a, int b, int c, int d);
extern int G2S_GetBG0ScrPtr(void);
extern void func_02013484(int a, unsigned short *b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_02033500(int a);
extern void func_0203355c(int a);
extern void func_02024d68(void);
extern void func_02000f48(int a, unsigned int b, int cb);

int func_ov003_0204d98c(int param_1) {
    unsigned int count;
    Ov003InitPair *dst;
    Ov003InitTablePair *src;
    unsigned short *tileBase;
    int tileOffset;
    unsigned short uVar1, uVar2;
    unsigned short *root, *puVar16, *puVar9, *puVar10, *puVar4, *puVar14, *puVar15;
    unsigned int uVar5, uVar7;
    int iVar6, iVar11, iVar12, iVar13;
    unsigned int auStack_30[2];

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    data_ov003_0204f9a0 = root;
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    func_0201e1d0();
    *(unsigned int **)(root + 0x20) = func_02024ee8(data_ov003_0204f944, 0xf);
    if (param_1 != 0) {
        ((Ov003InitState *)(root + 0xf08))->mode = 1;
        ((Ov003InitState *)(root + 0xf08))->value = 3;
    } else {
        ((Ov003InitState *)(root + 0xf08))->mode = 0;
        ((Ov003InitState *)(root + 0xf08))->value = func_ov105_020bd7c4();
    }
    /* copy 21 halfwords of default state from data_0204c300 */
    {
        src = (Ov003InitTablePair *)data_0204c300;
        dst = (Ov003InitPair *)root;
        count = 10;

        do {
            *dst = *(Ov003InitPair *)src;
            src = src + 1;
            --count;
            dst = dst + 1;
        } while (count != 0);
        *(unsigned short *)dst = *(unsigned short *)src;
    }
    /* clear any 0x13 entry-type tag */
    iVar6 = 0;
    iVar11 = (unsigned int)*root;
    if (iVar11 > 0) {
        do {
            iVar12 = iVar6 + 1;
            if (*(char *)((int)root + iVar6 + 6) == '\x13') {
                *(char *)((int)root + iVar6 + 6) = 0;
            }
            iVar6 = iVar12;
        } while (iVar12 < (int)(unsigned int)*root);
    }
    func_ov003_0204d74c();
    func_0202e8ec((unsigned int *)(root + 0x22), 0);
    func_0202ea14((int)(root + 0x22), 1);
    func_0202ea1c((int)(root + 0x22), 1);
    GX_SetBankForTex(3);
    GX_BeginLoadOBJExtPltt(0x20);
    GX_SetBankForBG(0x10);
    func_02011174(0x4000, 1);
    func_020056b4(1, 0, 1);
#pragma opt_common_subs on
    {
        *(volatile unsigned int *)0x04000000 =
            *(volatile unsigned int *)0x04000000 & 0xffffe0ff | 0x100;
        *(volatile unsigned short *)0x0400000a =
            *(volatile unsigned short *)0x0400000a & 0x43 | 0xd00;
        *(volatile unsigned short *)0x0400100a =
            *(volatile unsigned short *)0x0400100a & 0x43 | 0xd00;
        *(volatile unsigned short *)0x0400000c =
            *(volatile unsigned short *)0x0400000c & 0x43 | 0xe00;
        *(volatile unsigned short *)0x0400100c =
            *(volatile unsigned short *)0x0400100c & 0x43 | 0xe00;
        *(volatile unsigned short *)0x0400000e =
            *(volatile unsigned short *)0x0400000e & 0x43 | 0xf00;
        *(volatile unsigned short *)0x04001008 =
            *(volatile unsigned short *)0x04001008 & 0x43 | 0xf00;
        func_0202e358((unsigned int *)(root + 0x58),
                      (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & 0x00fffffcU) << 7 | 0x80000001),
                      0x00fffffcU, 0x04001008);
        func_0202e358((unsigned int *)(root + 0x2c),
                      (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & 0x00fffffcU) << 7 | 0x80000002),
                      *(int *)(root + 0x20) + 0x8000);
        func_0202a634(root + 0x84,
                      (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & 0x00fffffcU) << 7 | 0x80000008), 1, 0);
    }
#pragma opt_common_subs off
    /* per-entry actor/cell registration */
    uVar7 = (unsigned int)*root;
    iVar12 = 0;
    if ((int)uVar7 > 0) {
        puVar15 = root + 0x950;
        puVar16 = root + 0x108;
        puVar9  = root + 0x318;
        puVar10 = root + 0x528;
        puVar4  = root + 0xb60;
        puVar14 = root + 0x738;
        do {
            OS_SPrintf(auStack_30, (unsigned int)data_ov003_0204f950, uVar7, iVar12 + 1);
            func_0202a634(puVar16, (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & 0x00fffffcU) << 7 |
                          0x80000000 | (iVar12 + 3U & 0x00fffffcU >> 0xf)), 1, 0);
            func_0202af3c((int)puVar16, (int)(root + 0x84), auStack_30);
            func_0202a634(puVar9, (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & 0x00fffffcU) << 7 |
                          0x80000007), 1, 0);
            func_0202af3c((int)puVar9, (int)(root + 0x84), auStack_30);
            signed char *entry = (signed char *)root + iVar12;
            func_0202a634(puVar10, *(unsigned int **)(&data_ov003_0204f8f8[entry[6] * 4]), 1, 6);
            func_0202a388((unsigned int *)puVar4, (int)puVar10,
                          (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & 0x00fffffcU) << 7 | 0x80000000 |
                          ((int)data_ov003_0204f8d0[entry[6]] & 0x00fffffcU >> 0xf)), 6);
            func_0202af3c((int)puVar10, (int)(root + 0x84), auStack_30);
            func_0202accc((int)puVar10, 0, (int)puVar4, 0);
#pragma opt_common_subs on
#pragma opt_propagation on
            uVar7 = (unsigned int)data_ov003_0204f8bc[entry[6]];
            if (uVar7 != 0xffffffff) {
                func_0202a634(puVar14, (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & 0x00fffffcU) << 7 |
                              0x80000000 | (uVar7 & 0x00fffffcU >> 0xf)), 1, 6);
                func_0202af3c((int)puVar14, (int)(root + 0x84), auStack_30);
                func_0202accc((int)puVar14, 0, (int)(puVar14 + 0x70), 0);
                ((Ov003EntryFlags *)((char *)root + iVar12 * 4 + 0x1000))->hasExtra = 1;
            } else {
                ((Ov003EntryFlags *)((char *)root + iVar12 * 4 + 0x1000))->hasExtra = 0;
            }
#pragma opt_common_subs off
#pragma opt_propagation off
            func_0202a634(puVar15, (unsigned int *)data_ov003_0204f958, 1, 0xf);
            func_0202af3c((int)puVar15, (int)(root + 0x84), auStack_30);
            func_0202accc((int)puVar15, 0, (int)(puVar15 + 0x70), 0);
            func_0202accc((int)puVar15, 4, (int)(puVar15 + 0x70), 0);
            func_0202accc((int)puVar15, 2, (int)(puVar15 + 0x70), 0);
            *(unsigned int *)(root + iVar12 * 2 + 0xbc6) = 0;
            iVar12 = iVar12 + 1;
            puVar16 = puVar16 + 0x84;
            puVar9  = puVar9 + 0x84;
            puVar10 = puVar10 + 0x84;
            puVar4  = puVar4 + 0x12;
            puVar14 = puVar14 + 0x84;
            puVar15 = puVar15 + 0x84;
            uVar7 = (unsigned int)*root;
        } while (iVar12 < (int)uVar7);
    }
    iVar6 = 0;
    GX_SetBankForSubBG(4);
    uVar5 = func_0201ef9c((*(int *)(root + 0x20) + 0x8000U & 0x00fffffcU) << 7 | 0x80000000, 0xe);
    *(unsigned int *)(root + 0xedc) = uVar5;
    iVar12 = func_02024e5c() == 1;
    if (iVar12 != 0) {
        *(unsigned int *)(root + 0xede) = 0;
    } else {
        uVar7 = func_0201ef9c((unsigned int)data_ov003_0204f964, 0xe);
        *(unsigned int *)(root + 0xede) = uVar7;
    }
    func_ov003_0204d308((unsigned int *)(root + 0xee0), (int)root, 0, 0, 0);
    MIi_CpuClear16(0, (int)(root + 0xbdc), 0x600);
    func_02024c94((unsigned int *)(root + 0xee6), *(int **)(root + 0xedc), 1, -1, -1);
    iVar6 = 0;
    if ((int)(unsigned int)*root > 0) {
        do {
            func_ov003_0204d3b0(iVar6);
            iVar6 = iVar6 + 1;
        } while (iVar6 < (int)(unsigned int)*root);
    }
    DC_FlushRange((int)((char *)data_ov003_0204f9a0 + 0x17b8), 0x600);
    {
        int *resource = *(int **)(root + 0xee4);
        func_02024a6c(1, resource, *(int **)(root + 0xee0), 0, resource[2]);
    }
    func_02024ae0(1, *(int *)(root + 0xee2), 0, *(int *)(*(int *)(root + 0xee2) + 0x10));
    func_0202497c(1, root + 0xbdc, 0, 0x600);
    {
        int *resource = *(int **)(root + 0xee4);
        func_02024a6c(5, resource, *(int **)(root + 0xee0), 0, resource[2]);
    }
    {
        int *resource = *(int **)(root + 0xee2);
        func_02024ae0(5, (int)resource, 0, resource[4]);
    }
    func_0202497c(5, root + 0xbdc, 0, 0x600);
    func_ov003_0204d308((unsigned int *)(root + 0xeec), (int)root, 3, 2, 0);
    iVar6 = 0;
    do {
        tileBase = (unsigned short *)(*(int *)(root + 0xeec) + 0xc);
        tileOffset = iVar6 * 2;
        iVar6 = iVar6 + 1;
        *(unsigned short *)((char *)tileBase + tileOffset) =
            *(unsigned short *)((char *)tileBase + tileOffset) + 0x60;
    } while (iVar6 < 0x40);
    func_02024ae0(2, *(int *)(root + 0xeee), 0xc00, *(int *)(*(int *)(root + 0xeee) + 0x10));
    func_02024b04(2, *(int *)(root + 0xeec), 0, *(int *)(*(int *)(root + 0xeec) + 8));
    func_02024ae0(6, *(int *)(root + 0xeee), 0xc00, *(int *)(*(int *)(root + 0xeee) + 0x10));
    func_02024b04(6, *(int *)(root + 0xeec), 0, *(int *)(*(int *)(root + 0xeec) + 8));
    func_ov003_0204d308((unsigned int *)(root + 0xef2), (int)root, 2, 1, 0);
    iVar6 = 0;
    do {
        tileBase = (unsigned short *)(*(int *)(root + 0xef2) + 0xc);
        tileOffset = iVar6 * 2;
        iVar6 = iVar6 + 1;
        *(unsigned short *)((char *)tileBase + tileOffset) =
            *(unsigned short *)((char *)tileBase + tileOffset) + 0x80;
    } while (iVar6 < 0x20);
    func_02024ae0(3, *(int *)(root + 0xef4), 0x1000, *(int *)(*(int *)(root + 0xef4) + 0x10));
    func_02024ae0(4, *(int *)(root + 0xef4), 0x1000, *(int *)(*(int *)(root + 0xef4) + 0x10));
    func_020115b8();
    func_02024c94((unsigned int *)(root + 0xef8), *(int **)(root + 0xedc), -1, 3, 1);
    func_02024c94((unsigned int *)(root + 0xefe), *(int **)(root + 0xedc), -1, 4, 2);
    uVar7 = 0;
    if ((int)(unsigned int)*root > 0) {
        iVar11 = 0x100;
        do {
            int entryType = (int)*(char *)((int)root + uVar7 + 6);
            if (entryType < 0x10) {
                iVar6 = *(int *)(*(int *)(root + 0xefa) + 0x14) + (entryType * 0x24 << 5);
                iVar13 = *(int *)(*(int *)(root + 0xefc) + 0xc) + entryType * 0x20;
            } else {
                iVar6 = *(int *)(*(int *)(root + 0xf00) + 0x14) + ((entryType + -0x10) * 0x24 << 5);
                iVar13 = *(int *)(*(int *)(root + 0xf02) + 0xc) + (entryType + -0x10) * 0x20;
            }
            iVar12 = iVar11 << 5;
            func_020249b0(1, iVar6, iVar12, 0x480);
            func_020249b0(5, iVar6, iVar12, 0x480);
            iVar6 = (uVar7 + 1) * 0x20;
            func_020249e4(1, iVar13, iVar6, 0x20);
            func_020249e4(5, iVar13, iVar6, 0x20);
            uVar7 = uVar7 + 1;
            iVar11 = iVar11 + 0x24;
        } while ((int)uVar7 < (int)(unsigned int)*root);
    }
    GX_SetBankForSubBG(0x180);
    func_02024ae0(6, *(int *)(root + 0xeee), 0xc00, *(int *)(*(int *)(root + 0xeee) + 0x10));
    func_02024b04(6, *(int *)(root + 0xeec), 0, *(int *)(*(int *)(root + 0xeec) + 8));
    func_02024ae0(4, *(int *)(root + 0xef4), 0x1000, *(int *)(*(int *)(root + 0xef4) + 0x10));
    iVar6 = G2S_GetBG0ScrPtr();
    func_02013484(iVar6, *(unsigned short **)(root + 0xef2), 0, 0, 8, 0x16, 0x20, 0x18, 0x10, 2);
    func_020115b8();
    func_02033500(0);
    func_0203355c(0x182);
    iVar6 = 0;
    if ((int)(unsigned int)*root > 0) {
        do {
            *(unsigned int *)(root + iVar6 * 2 + 0xba8) = 0;
            *(unsigned int *)(root + iVar6 * 2 + 0xbb2) = 0;
            iVar6 = iVar6 + 1;
        } while (iVar6 < (int)(unsigned int)*root);
    }
    *(unsigned int *)(root + 0xbb0) = 0;
    *(unsigned int *)(root + 0xbd6) = 0;
    *(unsigned int *)(root + 0xbd8) = 0;
    *(unsigned int *)(root + 0xf04) = 0;
    *(unsigned int *)(root + 0xf06) = 0;
    *(unsigned int *)(root + 0xbba) = 0;
    *(volatile unsigned short *)0x04000060 =
        *(volatile unsigned short *)0x04000060 & ~0x3000 | 0x10;
    func_02024d68();
    func_02000f48(1, (unsigned int)data_ov003_0204f978, (int)&func_ov003_0204cba0);
    return (int)&func_ov003_0204e5b0;
}

