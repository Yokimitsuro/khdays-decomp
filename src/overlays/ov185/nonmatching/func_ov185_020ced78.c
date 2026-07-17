/*
 * func_ov185_020ced78 -- x3 (ov185/186/187). AI-state tick: if the +0x60 ready bit is set, re-aim
 * and dispatch. Gate on bit0 of the low byte of the +0x60 hw flags (hw60.lo & 1); if clear, return.
 * Else build a target vec from *(state[0x11]) = {p[0], p[1]+0xc00, p[2]} (raise Y by 0xc00) and feed
 * it to 020c5c54. Copy the next-state byte *(s8)(state[0]+0x1c9) into *(u8)(state[0]+0x1c7), then hand
 * off via 0203c634 (cb=0).
 *
 * NON-MATCHING: ldm load-coalescing tie (+8B) -- see references/deferred-ties.md. Semantics, the
 * hw60.lo&1 gate (ldrh;lsl#24;lsr#24;tst), every value and the byte-copy tail are exact. The only diff
 * is the vec build: the ROM loads the source with one `ldm r0,{r0,r2,r3}`, patches Y in-register and
 * stores the three words individually; mwcc reuses r0 and emits three separate `ldr`. Ruled out:
 * field-by-field (both store orders), struct-copy `v=*p; v.y+=0xc00`, intermediate struct value,
 * temps-first, int[3] array, C99 compound literal -- none force the load-multiple. Checklist clean
 * (ARM, c5c54 2-arg by-pointer, c634 3-arg cb=0, all constants/offsets correct).
 */
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_ov107_020c5c54(int obj, struct vec3 *v);
extern void func_0203c634(int self, int idx, int cb);

void func_ov185_020ced78(int *self) {
    int *state = (int *)self[1];
    int *p;
    struct vec3 v;

    if ((((struct hw60 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    p = (int *)state[0x11];
    v.x = p[0];
    v.y = p[1] + 0xc00;
    v.z = p[2];
    func_ov107_020c5c54(*state, &v);
    *(char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
