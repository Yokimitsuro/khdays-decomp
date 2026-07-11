/* ov003 scene/HUD init (2552B, largest ov003 fn). Faithful readable reconstruction
 * from Ghidra + full pool map. Dominated by MMIO BGxCNT writes + RegisterSeqAndInit
 * cell sequences + char-resource loads + per-entry HUD layout. Same MMIO/register
 * pointer-hold tie class as func_ov003_0204cba0 / ov010_0204cb3c — nonmatching by the
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
extern int data_0204f9a0;
extern unsigned short data_0204c300[];
extern unsigned int data_0204f944, data_0204f950, data_0204f958, data_0204f964, data_0204f978;
extern signed char data_0204f8f8[], data_0204f8d0[], data_0204f8bc[];
extern int func_ov003_0204e5b0;
extern void func_ov003_0204cba0(void);

extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern void func_0201e1d0(void);
extern unsigned int *func_02024ee8(unsigned int a, int b, int c, int d);
extern int func_020bd7c4(void);
extern void func_ov003_0204d74c(void);
extern void func_0202e8ec(unsigned int *p, int a);
extern void func_0202ea14(int p, int a);
extern void func_0202ea1c(int p, int a);
extern void func_02005e48(int a);
extern void func_02006020(int a);
extern void func_020058bc(int a);
extern void func_02011174(int a, int b);
extern void func_020056b4(int a, int b, int c);          /* SetDisplayControl(1,0,1) */
extern void func_0202e358(unsigned int *dst, unsigned int *src, int len, int a);
extern void func_0202a634(unsigned short *obj, unsigned int *vram, int a, int b); /* RegisterSeqAndInit */
extern void func_02001878(unsigned int *out, unsigned int tbl, unsigned int n, int idx);
extern void func_0202af3c(int obj, int anim, unsigned int *ctx);
extern void func_0202a388(unsigned int *a, int obj, unsigned int *vram, int b);
extern void func_0202accc(int obj, int slot, int a, int b);
extern void func_02006128(int a);
extern unsigned int func_0201ef9c(char *vram, int a, unsigned int b, int c);
extern int func_02024e5c(void);                          /* returns HUD-variant flag */
extern void func_ov003_0204d308(unsigned int *out, int root, int a, int b, int c); /* LoadCharResource */
extern void func_01ff86c8(int a, int dst, int len);
extern void func_02024c94(unsigned int *out, int *res, int a, int b, int c);
extern void func_ov003_0204d3b0(int i);                  /* LayoutHudPanelRow */
extern void func_02002778(int addr, int len);
extern void func_02024a6c(int a, int *b, int c);
extern void func_02024ae0(int a, int b, int c, int d);
extern void func_0202497c(int a, unsigned short *b, int c, int d);
extern void func_02024b04(int a, int b, int c, int d);
extern void func_020115b8(void);
extern void func_020249b0(int a, int b, int c, int d);
extern void func_020249e4(int a, int b, int c, int d);
extern int func_020066a4(void);
extern void func_02013484(int a, unsigned short *b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_02033500(int a, int b, int c, int d);
extern void func_0203355c(short a, int b, int c, int d);
extern void func_02024d68(void);
extern void func_02000f48(int a, unsigned int b, int cb);

int func_ov003_0204d98c(int param_1, unsigned int param_2, int param_3, int param_4) {
    unsigned short uVar1, uVar2;
    unsigned short *root, *puVar9, *puVar10, *puVar14, *puVar15, *puVar16;
    unsigned int *puVar4;
    unsigned int uVar5, uVar7, vram_mask;
    int iVar6, iVar11, iVar12, iVar13;
    unsigned int auStack_30[2];
    volatile unsigned short *reg_bg1_sub = (volatile unsigned short *)0x0400100a;
    volatile unsigned short *reg_mosaic  = (volatile unsigned short *)0x04000060;
    volatile unsigned int  *reg_dispcnt  = (volatile unsigned int *)0x04000000;
    volatile unsigned short *reg_bg1cnt  = (volatile unsigned short *)0x0400000a;
    volatile unsigned short *reg_bg2cnt  = (volatile unsigned short *)0x0400000c;
    volatile unsigned short *reg_bg3cnt  = (volatile unsigned short *)0x0400000e;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    data_0204f9a0 = (int)root;
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    func_0201e1d0();
    puVar4 = func_02024ee8(data_0204f944, 0xf, param_3, param_4);
    *(unsigned int **)(root + 0x20) = puVar4;
    if (param_1 == 0) {
        root[0xf08] = 0;
        root[0xf09] = 0;
        *(int *)(root + 0xf0a) = func_020bd7c4();
    } else {
        root[0xf08] = 1;
        root[0xf09] = 0;
        root[0xf0a] = 3;
        root[0xf0b] = 0;
    }
    /* copy 21 halfwords of default state from data_0204c300 */
    iVar6 = 10;
    puVar9 = root;
    puVar10 = data_0204c300;
    do {
        uVar1 = *puVar10;
        uVar2 = puVar10[1];
        puVar10 = puVar10 + 2;
        iVar6 = iVar6 + -1;
        *puVar9 = uVar1;
        puVar9[1] = uVar2;
        puVar9 = puVar9 + 2;
    } while (iVar6 != 0);
    *puVar9 = *puVar10;
    /* clear any 0x13 entry-type tag */
    iVar6 = 0;
    if (*root != 0) {
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
    func_02005e48(3);
    func_02006020(0x20);
    func_020058bc(0x10);
    func_02011174(0x4000, 1);
    func_020056b4(1, 0, 1);
    vram_mask = 0x00fffffc;
    reg_dispcnt[0] = *reg_dispcnt & 0xffffe0ff | 0x100;
    *reg_bg1cnt = *reg_bg1cnt & 0x43 | 0xd00;
    *reg_bg1_sub = *reg_bg1_sub & 0x43 | 0xd00;
    *reg_bg2cnt = *reg_bg2cnt & 0x43 | 0xe00;
    reg_bg1_sub[1] = reg_bg1_sub[1] & 0x43 | 0xe00;
    *reg_bg3cnt = *reg_bg3cnt & 0x43 | 0xf00;
    reg_bg1_sub[-1] = reg_bg1_sub[-1] & 0x43 | 0xf00;
    func_0202e358((unsigned int *)(root + 0x58),
                  (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & vram_mask) << 7 | 0x80000001),
                  vram_mask, (int)(reg_bg1_sub - 1));
    func_0202e358((unsigned int *)(root + 0x2c),
                  (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & vram_mask) << 7 | 0x80000002),
                  *(int *)(root + 0x20) + 0x8000, (int)(reg_bg1_sub - 1));
    func_0202a634(root + 0x84,
                  (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & vram_mask) << 7 | 0x80000008), 1, 0);
    /* per-entry actor/cell registration */
    uVar7 = (unsigned int)*root;
    iVar12 = 0;
    if (uVar7 != 0) {
        puVar15 = root + 0x950;
        puVar16 = root + 0x108;
        puVar9  = root + 0x318;
        puVar10 = root + 0x528;
        puVar4  = (unsigned int *)(root + 0xb60);
        puVar14 = root + 0x738;
        do {
            func_02001878(auStack_30, (unsigned int)data_0204f950, uVar7, iVar12 + 1);
            func_0202a634(puVar16, (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & vram_mask) << 7 |
                          0x80000000 | (iVar12 + 3U & vram_mask >> 0xf)), 1, 0);
            func_0202af3c((int)puVar16, (int)(root + 0x84), auStack_30);
            func_0202a634(puVar9, (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & vram_mask) << 7 |
                          0x80000007), 1, 0);
            func_0202af3c((int)puVar9, (int)(root + 0x84), auStack_30);
            func_0202a634(puVar10, *(unsigned int **)(&data_0204f8f8[*(char *)((int)root + iVar12 + 6) * 4]), 1, 6);
            func_0202a388(puVar4, (int)puVar10,
                          (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & vram_mask) << 7 | 0x80000000 |
                          ((int)data_0204f8d0[*(char *)((int)root + iVar12 + 6)] & vram_mask >> 0xf)), 6);
            func_0202af3c((int)puVar10, (int)(root + 0x84), auStack_30);
            func_0202accc((int)puVar10, 0, (int)puVar4, 0);
            uVar7 = (unsigned int)data_0204f8bc[*(char *)((int)root + iVar12 + 6)];
            if (uVar7 != 0xffffffff) {
                func_0202a634(puVar14, (unsigned int *)((*(int *)(root + 0x20) + 0x8000U & vram_mask) << 7 |
                              0x80000000 | (uVar7 & vram_mask >> 0xf)), 1, 6);
                func_0202af3c((int)puVar14, (int)(root + 0x84), auStack_30);
                func_0202accc((int)puVar14, 0, (int)(puVar14 + 0x70), 0);
            }
            *(unsigned int *)(root + iVar12 * 2 + 0x948) = (unsigned int)(uVar7 != 0xffffffff);
            func_0202a634(puVar15, (unsigned int *)data_0204f958, 1, 0xf);
            func_0202af3c((int)puVar15, (int)(root + 0x84), auStack_30);
            func_0202accc((int)puVar15, 0, (int)(puVar15 + 0x70), 0);
            func_0202accc((int)puVar15, 4, (int)(puVar15 + 0x70), 0);
            func_0202accc((int)puVar15, 2, (int)(puVar15 + 0x70), 0);
            (root + iVar12 * 2 + 0xbc6)[0] = 0;
            (root + iVar12 * 2 + 0xbc6)[1] = 0;
            uVar7 = (unsigned int)*root;
            iVar12 = iVar12 + 1;
            puVar16 = puVar16 + 0x84;
            puVar9  = puVar9 + 0x84;
            puVar10 = puVar10 + 0x84;
            puVar4  = puVar4 + 9;
            puVar14 = puVar14 + 0x84;
            puVar15 = puVar15 + 0x84;
        } while (iVar12 < (int)uVar7);
    }
    iVar6 = 0;
    func_02006128(4);
    uVar5 = func_0201ef9c((char *)((*(int *)(root + 0x20) + 0x8000U & vram_mask) << 7 | 0x80000000),
                          0xe, uVar7, iVar6);
    *(unsigned int *)(root + 0xedc) = uVar5;
    if (func_02024e5c() == 1) {
        root[0xede] = 0;
        root[0xedf] = 0;
    } else {
        uVar7 = func_0201ef9c((char *)data_0204f964, 0xe, uVar7, iVar6);
        *(unsigned int *)(root + 0xede) = uVar7;
    }
    func_ov003_0204d308((unsigned int *)(root + 0xee0), (int)root, 0, 0, 0);
    func_01ff86c8(0, (int)(root + 0xbdc), 0x600);
    func_02024c94((unsigned int *)(root + 0xee6), *(int **)(root + 0xedc), 1, -1, -1);
    iVar6 = 0;
    if (*root != 0) {
        do {
            func_ov003_0204d3b0(iVar6);
            iVar6 = iVar6 + 1;
        } while (iVar6 < (int)(unsigned int)*root);
    }
    func_02002778(data_0204f9a0 + 0x17b8, 0x600);
    func_02024a6c(1, *(int **)(root + 0xee4), *(int *)(root + 0xee0));
    func_02024ae0(1, *(int *)(root + 0xee2), 0, *(int *)(*(int *)(root + 0xee2) + 0x10));
    func_0202497c(1, root + 0xbdc, 0, 0x600);
    func_02024a6c(5, *(int **)(root + 0xee4), *(int *)(root + 0xee0));
    func_02024ae0(5, *(int *)(root + 0xee2), 0, *(int *)(*(int *)(root + 0xee2) + 0x10));
    func_0202497c(5, root + 0xbdc, 0, 0x600);
    func_ov003_0204d308((unsigned int *)(root + 0xeec), (int)root, 3, 2, 0);
    iVar6 = 0;
    do {
        iVar12 = iVar6 * 2;
        iVar6 = iVar6 + 1;
        *(short *)(*(int *)(root + 0xeec) + 0xc + iVar12) =
            *(short *)(*(int *)(root + 0xeec) + 0xc + iVar12) + 0x60;
    } while (iVar6 < 0x40);
    func_02024ae0(2, *(int *)(root + 0xeee), 0xc00, *(int *)(*(int *)(root + 0xeee) + 0x10));
    func_02024b04(2, *(int *)(root + 0xeec), 0, *(int *)(*(int *)(root + 0xeec) + 8));
    func_02024ae0(6, *(int *)(root + 0xeee), 0xc00, *(int *)(*(int *)(root + 0xeee) + 0x10));
    func_02024b04(6, *(int *)(root + 0xeec), 0, *(int *)(*(int *)(root + 0xeec) + 8));
    func_ov003_0204d308((unsigned int *)(root + 0xef2), (int)root, 2, 1, 0);
    iVar6 = 0;
    do {
        iVar12 = iVar6 * 2;
        iVar6 = iVar6 + 1;
        *(short *)(*(int *)(root + 0xef2) + 0xc + iVar12) =
            *(short *)(*(int *)(root + 0xef2) + 0xc + iVar12) + 0x80;
    } while (iVar6 < 0x20);
    func_02024ae0(3, *(int *)(root + 0xef4), 0x1000, *(int *)(*(int *)(root + 0xef4) + 0x10));
    func_02024ae0(4, *(int *)(root + 0xef4), 0x1000, *(int *)(*(int *)(root + 0xef4) + 0x10));
    func_020115b8();
    func_02024c94((unsigned int *)(root + 0xef8), *(int **)(root + 0xedc), -1, 3, 1);
    func_02024c94((unsigned int *)(root + 0xefe), *(int **)(root + 0xedc), -1, 4, 2);
    iVar6 = 0;
    if (*root != 0) {
        iVar12 = 0x100;
        do {
            iVar11 = (int)*(char *)((int)root + iVar6 + 6);
            if (iVar11 < 0x10) {
                iVar13 = *(int *)(*(int *)(root + 0xefa) + 0x14) + iVar11 * 0x480;
                iVar11 = *(int *)(*(int *)(root + 0xefc) + 0xc) + iVar11 * 0x20;
            } else {
                iVar13 = *(int *)(*(int *)(root + 0xf00) + 0x14) + (iVar11 + -0x10) * 0x480;
                iVar11 = *(int *)(*(int *)(root + 0xf02) + 0xc) + (iVar11 + -0x10) * 0x20;
            }
            func_020249b0(1, iVar13, iVar12 << 5, 0x480);
            func_020249b0(5, iVar13, iVar12 << 5, 0x480);
            iVar13 = (iVar6 + 1) * 0x20;
            func_020249e4(1, iVar11, iVar13, 0x20);
            func_020249e4(5, iVar11, iVar13, 0x20);
            iVar6 = iVar6 + 1;
            iVar12 = iVar12 + 0x24;
        } while (iVar6 < (int)(unsigned int)*root);
    }
    func_02006128(0x180);
    func_02024ae0(6, *(int *)(root + 0xeee), 0xc00, *(int *)(*(int *)(root + 0xeee) + 0x10));
    func_02024b04(6, *(int *)(root + 0xeec), 0, *(int *)(*(int *)(root + 0xeec) + 8));
    func_02024ae0(4, *(int *)(root + 0xef4), 0x1000, *(int *)(*(int *)(root + 0xef4) + 0x10));
    iVar6 = func_020066a4();
    func_02013484(iVar6, *(unsigned short **)(root + 0xef2), 0, 0, 8, 0x16, 0x20, 0x18, 0x10, 2);
    func_020115b8();
    func_02033500(0, 0, 0, 0);
    func_0203355c((short)0x182, 0, 0, 0);
    iVar6 = 0;
    if (*root != 0) {
        do {
            (root + iVar6 * 2 + 0xba8)[0] = 0;
            (root + iVar6 * 2 + 0xba8)[1] = 0;
            (root + iVar6 * 2 + 0xbb2)[0] = 0;
            (root + iVar6 * 2 + 0xbb2)[1] = 0;
            iVar6 = iVar6 + 1;
        } while (iVar6 < (int)(unsigned int)*root);
    }
    root[0xbb0] = 0;
    root[0xbb1] = 0;
    root[0xbd6] = 0;
    root[0xbd7] = 0;
    root[0xbd8] = 0;
    root[0xbd9] = 0;
    root[0xf04] = 0;
    root[0xf05] = 0;
    root[0xf06] = 0;
    root[0xf07] = 0;
    root[0xbba] = 0;
    root[0xbbb] = 0;
    *reg_mosaic = *reg_mosaic & 0xcfff | 0x10;
    func_02024d68();
    func_02000f48(1, data_0204f978, (int)&func_ov003_0204cba0);
    return (int)&func_ov003_0204e5b0;
}
