/* Reaction enter, gated on the flag byte the node's third word points at. Picks a random hold
 * time between the actor's two bounds (+0x224 and +0x228, in either order -- the span is taken
 * as an absolute value), stores it in the node, promotes the reaction state from idle (-1) to 2,
 * and re-arms the slot with no handler.
 *
 * Parked as an addressing tie: the state byte is read with `ldrsb`, whose 8-bit offset cannot
 * reach 0x1c7, so the read splits into `add #0x100` + `ldrsb #0xc7`; the original then writes it
 * back with the direct 12-bit `strb [actor,#0x1c7]` while mwcc reused the split and spent an
 * extra add. Two things fix it, and both are the general lesson rather than anything about this
 * function:
 *   - reach the field through a STRUCT, not a cast of a computed address -- the same lever that
 *     stopped the strength reduction in the ov008 loops;
 *   - the -1 is a VARIABLE, not a literal. The original materialises it with `mvn r1,#0` and
 *     compares register-to-register; a literal -1 compiles to `cmn r0,#1` and no register. */
extern int func_02023eb4(int bound);
extern int func_0203c634(int self, int idx, void *handler);

struct Ov253Actor {
    char _pad0[0x1c7];
    signed char bReactState;    /* +0x1c7: -1 idle, 2 reacting */
    char _pad1[0x224 - 0x1c8];
    int nHoldMin;               /* +0x224 */
    int nHoldMax;               /* +0x228 */
};

void func_ov253_020d0938(int self) {
    int *node = *(int **)(self + 4);
    int min, span;
    int idle = -1;
    struct Ov253Actor *actor;

    if (*(unsigned char *)node[2] != 0) {
        return;
    }
    min = ((struct Ov253Actor *)*node)->nHoldMin;
    span = ((struct Ov253Actor *)*node)->nHoldMax - min;
    if (span < 0) {
        span = -span;
    }
    node[0xb] = min + func_02023eb4(span + 1);

    actor = (struct Ov253Actor *)*node;
    if (actor->bReactState == idle) {
        actor->bReactState = 2;
    }
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
