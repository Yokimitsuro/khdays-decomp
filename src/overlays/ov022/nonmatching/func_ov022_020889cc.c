/* NONMATCHING: the original emits a DEAD register copy (`mul r0,ip,r0; mov ip,r0;
 * add r0,ip,#0xff` -- ip is never read again) that mwcc will not reproduce, so the
 * function comes out 4 bytes short. The original also materializes `arg1 << 16` into
 * a register and folds the `>> 16` into the `orr` shifter operand, where mwcc folds
 * the other side. Five source forms tried (temporaries for the product, the shifted
 * high half, and an unsigned intermediate). Everything else, including the
 * divide-by-100 reciprocal magic (0x51EB851F, asr #5), matches exactly.
 *
 * Scales a percentage: (arg1 << 12) / 100 by a step derived from the byte at
 * base+0x2AB3 (clamped to 0, then 100 at >= 10, else step*5), rounds up to the next
 * 4096, and packs it with arg1 into the low/high halves of one word. */
extern int func_01fffde0(int a);
extern void func_ov002_0206bbb8(int a, int b, int c);
extern int data_0204be04;

void func_ov022_020889cc(int arg0, int arg1) {
    int base, n, x;
    if (*(unsigned char *)&data_0204be04 != 0) return;
    base = func_01fffde0(arg0);
    if (base == 0) return;
    if (arg1 <= 0) return;
    n = *(unsigned char *)(base + 0x2ab3) - 1;
    if (n < 0) n = 0;
    if (n >= 10) n = 100;
    else n = n * 5;
    x = (arg1 << 12) / 100 * n + 0xfff;
    func_ov002_0206bbb8(0, 2, (arg1 << 16) | ((unsigned int)(x << 4) >> 16));
}
