/* Rebuilds the 0x10-byte request record in data_ov023_0208a790 for `a` and submits it
 * against the sub-object at +0x40 of the block held at +0x24; -1 when there is none.
 *
 * The `p != 0 ? p + 0x40 : 0` has to be a TERNARY (or an explicit else branch): written as
 * a bare `if (p != 0) p = p + 0x40;` mwcc drops the ROM's redundant `moveq r0,#0`. */
extern void INITi_CpuClear32_0x01ff86fc(int val, void *dst, int len);
extern void func_0201f924(void *dst, int a);
extern int func_02016f10(char *p, void *q);
extern char data_ov023_0208a790[];

int func_ov023_02087510(char *self, int a) {
    char *p;
    INITi_CpuClear32_0x01ff86fc(0, data_ov023_0208a790, 0x10);
    func_0201f924(data_ov023_0208a790, a);
    p = *(char **)(self + 0x24);
    p = p != 0 ? p + 0x40 : 0;
    if (p == 0) {
        return -1;
    }
    return func_02016f10(p, data_ov023_0208a790);
}
