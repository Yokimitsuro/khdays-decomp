/* Ov008_TryApplyPageStep -- x3 (ov008/...). Does the cursor at tag `tag` overlap any of the first
 * three cells once shifted by (dx, dy)? Resolve the reference rect p3 for tag+1, then for i in
 * 0..2 resolve rect p5 for tag i+1 and test an AABB overlap with margins (0x2000/0xc4000 in X,
 * 0x2000/0x24000 in Y). An overlap with a cell that is not our own tag means the placement
 * collides -> 0; if none of the three collide -> 1.
 *
 * The step arrives by value in r2-r3 and its fields are read through their addresses, which is
 * what makes mwcc home the four argument registers (`stmdb sp!,{r0,r1,r2,r3}`) and read dx/dy
 * back out of that block at fixed offsets while `tag` stays in its register.
 *
 * Two more things were load-bearing:
 *  - the ROM RE-READS p5[1] for the fourth comparison instead of reusing the load from the third,
 *    and it BRANCHES where mwcc predicates (`addlt/sublt/cmplt`). One `volatile` read on the
 *    fourth comparison buys both at once -- it is the same access, so nothing changes semantically,
 *    and denying the CSE is what makes the block too long to predicate. Those were the 8 bytes.
 *  - the loop test is `i >= 3`, not `i > 2` (`cmp #3 ; blt` vs `cmp #2 ; ble`).
 * The declaration order below is the one that colours dy->r8, dx->r4, i->r5 as the ROM does.
 */
typedef struct Ov008Pair { int x; int y; } Ov008Pair;
extern int Ov008_GetContext(void);
extern int Ov008_FindEntryById(int ctx, int tag);
extern int *Ov008_GetEntryPos(int ctx, int slot);

int Ov008_TryApplyPageStep(void *pCtx, int tag, Ov008Pair step) {
    int dx;
    int i;
    int ctx;
    int *p3;
    int dy;
    dy = *(int *)&step.y;
    ctx = Ov008_GetContext();
    p3 = Ov008_GetEntryPos(ctx, Ov008_FindEntryById(ctx, tag + 1));
    i = 0;
    dx = *(int *)&step.x;

    while (1) {
        int *p5 = Ov008_GetEntryPos(ctx, Ov008_FindEntryById(ctx, i + 1));
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
