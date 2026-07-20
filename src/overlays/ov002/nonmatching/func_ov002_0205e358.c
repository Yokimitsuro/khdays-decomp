/* UNFINISHED. 144 vs 140 -- one `movs r1,#6` we emit and the ROM does not.
 *
 * ov002 scene step: refresh, read the current mode, and act on it.  Mode 2 draws
 * one counter; mode 3 runs the fuller path (mark 0xe, optional 0x79 sound, then
 * the same counter draw offset by ctx[0x4ac], a 02020400 update and a 0205b7dc
 * refresh).  Anything else does nothing.  Returns the 0205cda8 handle.
 *
 * ★ THE DISPATCH IS A SWITCH, NOT AN IF-CHAIN -- and that part is now right.
 * The ROM does `cmp #2 / beq case2 / cmp #3 / beq case3 / b end`, i.e. it JUMPS
 * TO each case rather than falling into the first.  Written as `if/else if`,
 * mwcc inlines case 2 where it is tested and the branch polarity inverts
 * (`bne skip` instead of `beq case`).  Written as a switch, every branch and
 * every case body matches byte for byte.
 *
 * WHAT REMAINS: the last two calls in case 3.
 *   ROM   ldrb r0,[r4,#4] ; movs r1,#6 ; bl 02020400
 *         ldrb r0,[r4,#1] ;             ; movs r2,#1 ; bl 0205b7dc
 * The ROM passes r1 to the SECOND call without setting it -- it relies on r1
 * still holding 6 across the intervening `bl`, which the ABI does not guarantee.
 * mwcc will not reproduce that, and it is hard to see what source form would:
 * it looks like the original either had a latent bug (an uninitialised second
 * argument) or its compiler knew something about 02020400 that ours cannot.
 *
 * RULED OUT: passing an uninitialised local as that argument, and hoisting the 6
 * into a shared variable used by both calls.  Both still emit the movs (+4).
 */
extern int func_ov002_0205cda8(void);
extern void func_ov002_0205cc44(void);
extern int func_ov002_0205a3f0(int *out, int a);
extern void func_ov002_0205a924(int a, int b, int c, int d);
extern void func_ov002_020536bc(int a);
extern int func_ov002_0205374c(void);
extern int func_ov002_02053558(int a);
extern void func_ov002_020535f0(void);
extern void func_ov002_0205c87c(int a);
extern void func_02020400(int a, int b);
extern void func_ov002_0205b7dc(int a, int b, int c);

extern unsigned char *data_ov002_0207f620;

int func_ov002_0205e358(void) {
    unsigned char *ctx = data_ov002_0207f620;
    int r;
    int mode;
    int v;

    r = func_ov002_0205cda8();
    func_ov002_0205cc44();
    mode = func_ov002_0205a3f0(&v, ctx[1]);
    switch (mode) {
    case 2:
        func_ov002_0205a924(v + 1, ctx[0x4ac] + ctx[0x4ad], 7, 0xb);
        break;
    case 3:
        func_ov002_020536bc(0xe);
        if (func_ov002_0205374c() == 0) {
            func_ov002_02053558(0x79);
            func_ov002_020535f0();
        }
        func_ov002_0205c87c(v);
        func_ov002_0205a924(ctx[0x4ac] + v + 1, ctx[0x4ac] + ctx[0x4ad], 7, 0xb);
        func_02020400(ctx[4], 6);
        func_ov002_0205b7dc(ctx[1], 6, 1);
        break;
    }
    return r;
}
