/* While a target is in reach, run the countdown down; when it expires, request state 4.
 *
 * func_ov107_020cab14 acquires the target and writes the SQUARED distance into the out
 * parameter, so the gap is `sqrt(d2) - (targetRadius + ownerRadius)` -- surface to
 * surface, not centre to centre.  Out of range, or with the countdown still positive,
 * the function simply returns and is run again next frame.
 *
 * PARKED at 0x19 with three externs declared `f()`, though the arities happened to be
 * right.  Two spellings were wrong instead:
 *
 *  - the acquired node must be read BACK OUT of the field, not stored from a temporary:
 *        target = func(...); ctx->target = target;   <- str reads the copy
 *        ctx->target = func(...); target = ctx->target; <- str reads r0, the ROM's shape
 *    mwcc keeps the call's own r0 live for the store in the second form.  Dropping the
 *    temporary entirely instead costs 24 bytes, so the temporary is required -- it is
 *    which side of the assignment it sits on that matters.
 *  - the two radii are summed target-first.  Writing `owner + target` swaps the two
 *    loads and nothing else; it is the last byte in the function to come right.
 */
extern int *func_ov107_020cab14(int *owner, int *outDistSq);
extern int FX_Sqrt(int x);
extern void func_0203c634(int *self, int action, void (*cb)(void));

void func_ov141_020cce98(int *self)
{
    int distSq;
    int *ctx;
    int *owner;
    int *target;
    int dist;

    ctx = (int *)self[1];
    ctx[1] = (int)func_ov107_020cab14(((int **)ctx)[0], &distSq);
    target = (int *)ctx[1];
    if (target == 0)
        return;

    owner = ((int **)ctx)[0];
    dist = FX_Sqrt(distSq);
    distSq = dist - (target[0x20] + owner[0x20]);
    if (distSq > ((int **)ctx)[0][0xb6])
        return;

    ctx[0xd] = ctx[0xd] - ((int *)self[0])[0xb];
    if (ctx[0xd] >= 0)
        return;

    *((char *)((int **)ctx)[0] + 0x1c7) = 4;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
}
