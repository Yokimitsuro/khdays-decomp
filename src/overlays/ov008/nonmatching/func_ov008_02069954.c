/*
 * func_ov008_02069954 -- x3 (ov008/...). Does the cursor at tag o.tag overlap any of the first three
 * cells (offset by o.dx/o.dy)? Resolve the reference rect p3 = 02054820(ctx, 02054788(ctx, o.tag+1)).
 * For i in 0..2, resolve rect p5 for tag i+1 and test an AABB overlap with margins (0x2000/0xc4000 in
 * X, 0x2000/0x24000 in Y): if it overlaps and i != o.tag, the placement collides -> return 0. If none
 * of the three collide, return 1.
 *
 * The second parameter is a by-value {tag, dx, dy} struct: that is what makes the ROM home r0-r3 at
 * entry (`stmdb sp!,{r0,r1,r2,r3}`) and reload dx/dy from the stack after the calls (a plain 4-int
 * signature keeps them in callee-saved registers -- 196B, no home).
 *
 * NON-MATCHING: with the by-value struct the size is 220 vs 224 (one instruction) and the callee-saved
 * register assignment / reload ORDER for ctx, p3, o.dx, o.dy differ throughout. The retail compiler
 * loads o.dy into r8 before the first call and colours ctx=r6/p3=r7/o.dx=r4; mwcc 3.0/139 loads them
 * after resolving p3 and colours ctx=r4/p3=r5/o.dx=r7. Re-ordering the field first-uses did not
 * reproduce the retail schedule -- a homed-struct register-allocation tie. Result is identical.
 */
extern int func_ov008_02050c54(void);
extern int func_ov008_02054788(int ctx, int tag);
extern int *func_ov008_02054820(int ctx, int slot);

struct off { int tag, dx, dy; };

int func_ov008_02069954(int param1, struct off o) {
    int ctx = func_ov008_02050c54();
    int *p3 = func_ov008_02054820(ctx, func_ov008_02054788(ctx, o.tag + 1));
    int i = 0;

    while (1) {
        int *p5 = func_ov008_02054820(ctx, func_ov008_02054788(ctx, i + 1));
        if ((*p3 - 0x2000) - o.dx < *p5 + 0xc4000 &&
            *p5 - 0x2000 < (*p3 + 0xc4000) - o.dx &&
            (p3[1] + 0x2000) - o.dy < p5[1] + 0x24000 &&
            p5[1] < (p3[1] + 0x24000) - o.dy &&
            i != o.tag) {
            return 0;
        }
        i++;
        if (i > 2) {
            return 1;
        }
    }
}
