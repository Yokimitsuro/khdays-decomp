/*
 * func_ov119_020cf7b0 -- x3 (ov119/...). Spawn a 0x10-byte registry object wired to two callbacks and
 * back-linked to its owner. Create it via 0203c5c0(*(self+0x3c), 100, 0x10, cb=020cf800, cb2=020cf7fc,
 * &out); then out[0]=self and out[3]=arg.
 *
 * NON-MATCHING: same caller-return-reservation reload-coloring tie as func_ov235_020d1a34 (see its
 * note and deferred-ties.md). Size-exact (84B), byte-exact except the two `ldr` reloads of the
 * out-pointer: ROM r1, mwcc 3.0/139 r0. The tie tracks the 2-saved-param spawn shape; the matched
 * 1-saved-param sibling func_ov124_020d14b0 colours r0 in BOTH, which is why it matches. Blocks the
 * ov119 x3 family.
 */
extern void func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_ov119_020cf7fc(void);
extern void func_ov119_020cf800(void);

void func_ov119_020cf7b0(int self, int arg) {
    int *out;

    func_0203c5c0(*(int *)(self + 0x3c), 100, 0x10, func_ov119_020cf800, func_ov119_020cf7fc, &out);
    out[0] = self;
    out[3] = arg;
}
