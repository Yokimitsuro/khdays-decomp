/* func_ov009_02054d08 -- x3 (ov008/...). Does the cursor at tag `tag` overlap any of the first
 * three cells once shifted by (dx, dy)? Resolve the reference rect p3 for tag+1, then for i in
 * 0..2 resolve rect p5 for tag i+1 and test an AABB overlap with margins (0x2000/0xc4000 in X,
 * 0x2000/0x24000 in Y). An overlap with a cell that is not our own tag means the placement
 * collides -> 0; if none of the three collide -> 1.
 *
 * Parked as a "homed-struct register-allocation tie" after modelling the second argument as a
 * by-value {tag, dx, dy}. The `stmdb sp!,{r0,r1,r2,r3}` at entry is the VARIADIC prologue, not a
 * struct home: `tag` is the last named argument and dx/dy are varargs, which is why the ROM keeps
 * tag in its argument register and reads the other two out of the block at fixed offsets.
 * Naming the varargs (`a2`, `a3`) and reading them through their own addresses reproduces that.
 *
 * Two more things were load-bearing:
 *  - the ROM RE-READS p5[1] for the fourth comparison instead of reusing the load from the third,
 *    and it BRANCHES where mwcc predicates (`addlt/sublt/cmplt`). One `volatile` read on the
 *    fourth comparison buys both at once -- it is the same access, so nothing changes semantically,
 *    and denying the CSE is what makes the block too long to predicate. Those were the 8 bytes.
 *  - the loop test is `i >= 3`, not `i > 2` (`cmp #3 ; blt` vs `cmp #2 ; ble`).
 * The declaration order below is the one that colours dy->r8, dx->r4, i->r5 as the ROM does.
 */
extern int func_ov009_0204e440(void);
extern int func_ov009_020518fc(int ctx, int tag);
extern int *func_ov009_02051978(int ctx, int slot);

int func_ov009_02054d08(int param1, int tag, int a2, int a3, ...) {
    int dx;
    int i;
    int ctx;
    int *p3;
    int dy;
    dy = *(int *)&a3;
    ctx = func_ov009_0204e440();
    p3 = func_ov009_02051978(ctx, func_ov009_020518fc(ctx, tag + 1));
    i = 0;
    dx = *(int *)&a2;

    while (1) {
        int *p5 = func_ov009_02051978(ctx, func_ov009_020518fc(ctx, i + 1));
        if ((*p3 - 0x2000) - dx < *p5 + 0xc4000 &&
            *p5 - 0x2000 < (*p3 + 0xc4000) - dx &&
            (p3[1] + 0x2000) - dy < p5[1] + 0x24000 &&
            ((volatile int *)p5)[1] < (p3[1] + 0x24000) - dy &&
            i != tag) {
            return 0;
        }
        i++;
        if (i >= 3) {
            return 1;
        }
    }
}
