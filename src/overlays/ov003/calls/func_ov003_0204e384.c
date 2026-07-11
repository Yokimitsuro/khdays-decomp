extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_02000fb4(int a, void *b);
extern void func_0200c5fc(void);
extern void func_0200ca50(int a);
extern void func_0200ca68(int a);
extern void func_02033500(int a);
extern void NNSi_FndFreeFromDefaultHeap(int a);
extern void func_0202a440(int p);
extern void func_0202a7dc(int p);
extern void func_0202e3c4(void *p);
extern void func_0202e944(void *p);
extern void func_02024fd4(void *p);
extern int data_ov003_0204f978;

void func_ov003_0204e384(void) {
    unsigned short *root;
    int base;
    int i108;
    int iVar3;
    int puVar4;
    int puVar5;
    int puVar6;
    int puVar7;
    int puVar8;
    int puVar9;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    func_02000fb4(1, &data_ov003_0204f978);
    func_0200c5fc();
    func_0200ca50(4);
    func_0200ca68(4);
    func_02033500(0);
    if (*(int *)(root + 0xede) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(root + 0xede));
    }
    NNSi_FndFreeFromDefaultHeap(*(int *)(root + 0xedc));
    iVar3 = *root - 1;
    if (iVar3 >= 0) {
        base = (int)root;
        puVar4 = base + 0x16c0 + iVar3 * 0x24;
        i108 = iVar3 * 0x108;
        puVar5 = base + 0x12a0 + i108;
        puVar6 = base + 0xe70 + i108;
        puVar7 = base + 0xa50 + i108;
        puVar8 = base + 0x210 + i108;
        puVar9 = base + 0x630 + i108;
        do {
            func_0202a440(puVar4);
            func_0202a7dc(puVar5);
            if (((int *)root)[iVar3 + 0x4a4] != 0) {
                func_0202a7dc(puVar6);
            }
            func_0202a7dc(puVar7);
            func_0202a7dc(puVar8);
            func_0202a7dc(puVar9);
            puVar4 = puVar4 - 0x24;
            puVar5 = puVar5 - 0x108;
            puVar6 = puVar6 - 0x108;
            puVar7 = puVar7 - 0x108;
            puVar8 = puVar8 - 0x108;
            puVar9 = puVar9 - 0x108;
            iVar3 = iVar3 - 1;
        } while (iVar3 >= 0);
    }
    func_0202a7dc((int)(root + 0x84));
    func_0202e3c4(root + 0x58);
    func_0202e3c4(root + 0x2c);
    func_0202e944(root + 0x22);
    func_02024fd4(*(void **)(root + 0x20));
}
