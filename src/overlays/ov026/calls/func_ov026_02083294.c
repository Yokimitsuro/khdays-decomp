/* Build a record via ov000_02056010, zero it (0x38 bytes), fill its fields from the args, attach
 * the ov000_02055fc0 result at +0x18, mark it active (+0x14=1) and return it. */
extern int func_ov026_02082d28(int a);
extern void MI_CpuFill8(void *dst, int val, int size);
extern int func_ov026_02082cd8(int a, int b);
int func_ov026_02083294(int a, int b, unsigned short c, unsigned short d, unsigned short e,
                        short f, short g, int h) {
    int obj = func_ov026_02082d28(a);
    MI_CpuFill8((void *)obj, 0, 0x38);
    *(unsigned short *)(obj) = c;
    *(unsigned short *)(obj + 6) = d;
    *(unsigned short *)(obj + 8) = e;
    *(int *)(obj + 0x10) = h;
    *(short *)(obj + 0xa) = f;
    *(short *)(obj + 0xc) = g;
    *(int *)(obj + 0x18) = func_ov026_02082cd8(a, b);
    *(int *)(obj + 0x14) = 1;
    return obj;
}
