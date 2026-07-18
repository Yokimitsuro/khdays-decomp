/*
 * func_ov235_020d1a34 -- x3 (ov235/...). Spawn a 0xc-byte registry object wired to two callbacks.
 * Create it via 0203c5c0(*(self+0x3c), 100, 0xc, cb=020d1b54, cb2=020d1a88, &out); then stash the two
 * incoming words into out[0]=a and out[1]=b.
 *
 * NON-MATCHING: size-exact (84B) and byte-exact EXCEPT the two `ldr` that reload the out-pointer after
 * the spawn call use r1 in the ROM (ldr r1,[sp,#8]; str r5,[r1] ; ldr r1,[sp,#8]; str r4,[r1,#4]) and
 * r0 in mwcc 3.0/139 (ldr r0,...). The reload COUNT matches (out is address-taken -> reloaded per
 * store); only the register colour differs. The ROM keeps r0 reserved as func_0203c5c0's (discarded)
 * return value and colours the reloaded pointer r1; 3.0/139 frees r0 and grabs it. Tried: int*/struct*
 * out, cast stores, out=0 init, non-void callee return, temp-pointer copy (which collapses to one
 * reload, wrong count). This is the retail-build (likely mwcc 3.0 >=140) caller-return-reservation tie;
 * result identical. Blocks the ov235 x3 family (dedupprop can't propagate a nonmatching rep).
 */
extern void func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_ov235_020d1b54(void);
extern void func_ov235_020d1a88(void);

void func_ov235_020d1a34(int self, int a, int b) {
    int *out;

    func_0203c5c0(*(int *)(self + 0x3c), 100, 0xc, func_ov235_020d1b54, func_ov235_020d1a88, &out);
    out[0] = a;
    out[1] = b;
}
