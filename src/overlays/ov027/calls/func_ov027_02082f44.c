typedef int (*Ov027Handler)(void);

typedef struct {
    char pad00[0x24];
    int f24;
} Ov027Sub;

typedef struct {
    char pad00[4];
    Ov027Sub *sub;   /* +0x04 */
} Ov027Res;

extern char *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov027_02083308(void);
extern void func_ov027_020837dc(void);
extern int *CARDi_GetRomAccessor_0x020315f4(void);
extern void func_ov027_02082ba4(Ov027Sub *p);
extern void func_02023cc0(void *p);
extern void func_02033b78(int bank, int id);
extern int func_ov027_02083068(void);

extern Ov027Res data_ov027_02084360;
extern unsigned short data_0204c190;

Ov027Handler func_ov027_02082f44(void) {
    char *root = NNSi_FndGetCurrentRootHeap();

    func_ov027_02083308();
    func_ov027_020837dc();
    if (*CARDi_GetRomAccessor_0x020315f4() != 1) {
        func_ov027_02082ba4(data_ov027_02084360.sub);
    }
    func_02023cc0(root + 0x4d8);
    if ((data_0204c190 & 1) != 0) {
        func_02033b78(0, 1);
        {
            volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;
            *reg_dispcnt = (*reg_dispcnt & 0xffffe0ff) | 0x100;
        }
        data_ov027_02084360.sub->f24 = 8;
        return func_ov027_02083068;
    }
    return 0;
}
