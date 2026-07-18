/*
 * func_ov025_02099eec -- x3 (ov008/...). Render a time value into its menu digit cells.
 * Grab the UI context (02050c28), find the container tag 0x1e, and split the time into H/M/S
 * (020678d4 -> local_1e = the count to format digit-by-digit, local_1f/local_20 = the two fixed
 * fields). Publish the two fixed fields (02067a7c cells 9 and 6) and restore two template rows
 * (020558b8 tags 7 and 4). Then peel decimal digits off local_1e low-to-high: each digit picks the
 * glyph tag (digit + 0x14) and restores template row sVar4 (3,2,1), dividing by 10 until exhausted.
 */
extern int func_ov025_02084a50(void);
extern int func_ov025_020894b0(int ctx, unsigned int tag);
extern void func_ov025_02099cb4(unsigned int t, unsigned short *hi, unsigned char *mid, unsigned char *lo);
extern void func_ov025_02089560(int ctx, int entry, int tag, int flags);
extern void func_ov025_02099e5c(int cell, unsigned int value);

void func_ov025_02099eec(unsigned int param_1) {
    unsigned char local_1f, local_20;
    unsigned short local_1e;
    int ctx = func_ov025_02084a50();
    int entry = func_ov025_020894b0(ctx, 0x1e);
    int sVar4;

    func_ov025_02099cb4(param_1, &local_1e, &local_1f, &local_20);
    func_ov025_02089560(ctx, entry, 7, 0x16);
    func_ov025_02089560(ctx, entry, 4, 0x16);
    func_ov025_02099e5c(9, local_20);
    func_ov025_02099e5c(6, local_1f);

    sVar4 = 3;
    do {
        int entry2 = func_ov025_020894b0(ctx, (local_1e % 10 + 0x14) & 0xffff);
        func_ov025_02089560(ctx, entry2, (short)sVar4--, 0x16);
        local_1e = local_1e / 10;
    } while (local_1e != 0);
}
