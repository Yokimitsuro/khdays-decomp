/* func_ov008_0207f18c -- upload the title text/logo cell graphics per sub-state, ov006.
 * Loads sub-resource 0 of the localized title pack (res_&.p2 container at base[0], entry
 * (container+0x8000 & 0xfffffc)<<7 | 0x8000000N where N is the sub-resource index) via
 * Archive_LoadFile, builds cells with func_02024c94(&info, arch, -1, idx, param) and uploads
 * their palette (pPltt->[8]/[0xc]) and BG3 char data (pChar->[0x10]/[0x14]) to the sub engine.
 *   Normal title states {0,1,2,3,10,11,13,14}: main-pack cells idx 1 then idx 0; when
 *     func_02024e5c()!=1 also overlays language pack sub-resource 3 (idx 0 cell).
 *   Attract states {4,5,6,7}: main-pack cells idx 3, then idx 4, then idx 2; language variant
 *     uses sub-resource 4. Other states do nothing but free the pack. */
struct Src { int a[6]; };                    /* [2]=+8 [3]=+0xc palette; [4]=+0x10 [5]=+0x14 char */
struct Cell { int f0; struct Src *pChar; struct Src *pPltt; };

extern int  *data_ov008_02090fa4;
extern void *func_0201ef9c(unsigned int entry, int mode, int a);      /* Archive_LoadFile */
extern void  func_02024c94(struct Cell *info, void *arch, int a, int idx, int param);
extern void  GX_LoadBGPltt(unsigned int src, int off, unsigned int len);     /* func_02007154 */
extern void  GX_LoadBG1Char(void *src, int off, unsigned int len);
extern void  GXS_LoadBG1Char(void *src, int off, unsigned int len);
extern void  GX_LoadBG2Char(void *src, int off, unsigned int len);
extern void  GXS_LoadBG2Char(void *src, int off, unsigned int len);
extern void  GX_LoadBG0Char(void *src, int off, unsigned int len);          /* func_0200770c */
extern void  GXS_LoadBGPltt(unsigned int src, int off, unsigned int len);
extern int   func_02024e5c(void);
extern void  NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov008_0207f18c(int state, int p2, int p3, int param4) {
    struct Cell info1;
    struct Cell info2;
    struct Cell *piVar1;
    struct Cell *piVar3;
    int iVar2;
    unsigned int base0 = (unsigned int)*data_ov008_02090fa4;

    piVar1 = (struct Cell *)func_0201ef9c(((base0 + 0x8000 & 0xfffffc) << 7) | 0x80000000,
                                          0xe, 0xfffffc);
    switch (state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 10:
    case 11:
    case 13:
    case 14:
        func_02024c94(&info1, piVar1, -1, 1, 1);
        GX_LoadBGPltt(info1.pPltt->a[3], 0, info1.pPltt->a[2]);
        iVar2 = func_02024e5c() == 1;
        if (iVar2) {
            GX_LoadBG1Char(info1.pChar->a[5], 0, info1.pChar->a[4]);
        } else {
            unsigned int b = (unsigned int)data_ov008_02090fa4[1] + 0x8000;
            piVar3 = (struct Cell *)func_0201ef9c(((b & 0xfffffc) << 7) | 0x80000003, 0xe, b);
            func_02024c94(&info2, piVar3, -1, 0, -1);
            GX_LoadBG1Char(info2.pChar->a[5], 0, info2.pChar->a[4]);
            if (piVar3 != 0) {
                NNSi_FndFreeFromDefaultHeap(piVar3);
            }
        }
        func_02024c94(&info1, piVar1, -1, 0, 0);
        GXS_LoadBGPltt(info1.pPltt->a[3], 0, info1.pPltt->a[2]);
        GXS_LoadBG1Char(info1.pChar->a[5], 0, info1.pChar->a[4]);
        goto done;
    case 4:
    case 5:
    case 6:
    case 7:
        func_02024c94(&info1, piVar1, -1, 3, 3);
        GX_LoadBGPltt(info1.pPltt->a[3], 0, info1.pPltt->a[2]);
        iVar2 = func_02024e5c() == 1;
        if (iVar2) {
            GX_LoadBG1Char(info1.pChar->a[5], 0, info1.pChar->a[4]);
            GX_LoadBG2Char(info1.pChar->a[5], 0, info1.pChar->a[4]);
        } else {
            unsigned int b = (unsigned int)data_ov008_02090fa4[1] + 0x8000;
            piVar3 = (struct Cell *)func_0201ef9c(((b & 0xfffffc) << 7) | 0x80000004, 0xe, b);
            func_02024c94(&info2, piVar3, -1, 0, -1);
            GX_LoadBG1Char(info2.pChar->a[5], 0, info2.pChar->a[4]);
            GX_LoadBG2Char(info2.pChar->a[5], 0, info2.pChar->a[4]);
            if (piVar3 != 0) {
                NNSi_FndFreeFromDefaultHeap(piVar3);
            }
        }
        func_02024c94(&info1, piVar1, -1, 4, -1);
        GX_LoadBG0Char(info1.pChar->a[5], 0, info1.pChar->a[4]);
        func_02024c94(&info1, piVar1, -1, 2, 2);
        GXS_LoadBGPltt(info1.pPltt->a[3], 0, info1.pPltt->a[2]);
        GXS_LoadBG1Char(info1.pChar->a[5], 0, info1.pChar->a[4]);
        GXS_LoadBG2Char(info1.pChar->a[5], 0, info1.pChar->a[4]);
        goto done;
    default:
        break;
    }
done:
    if (piVar1 != 0) {
        NNSi_FndFreeFromDefaultHeap(piVar1);
    }
}
