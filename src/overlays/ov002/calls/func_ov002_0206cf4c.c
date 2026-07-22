/* func_ov002_0206cf4c -- append `id` to the pending-id list at +0x8d14 of the ov002 root, unless it
 * is already there. The list is a byte count at +6 followed by shorts from +8.
 * The declaration order (tab, i, p, n) is what colours the count r6 and the cursor r5 as the ROM
 * does; tools/declperm.py picks it out (1 of the 24). */
extern int data_ov002_0207fa00;

void func_ov002_0206cf4c(int id) {
    char *tab;
    int i;
    short *p;
    int n;
    tab = (char *)(*(int *)&data_ov002_0207fa00 + 0x8d14);
    i = 0;
    n = *(unsigned char *)(tab + 6);
    if (n > 0) {
        p = (short *)tab;
        do {
            if (id == p[4]) {
                return;
            }
            i = i + 1;
            p = p + 1;
        } while (i < n);
    }
    *(short *)(tab + n * 2 + 8) = (short)id;
    *(unsigned char *)(tab + 6) = *(unsigned char *)(tab + 6) + 1;
}
