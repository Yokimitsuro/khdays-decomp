/*
 * Build a Y-rotation from a heading vector and apply it to the node's matrix (x4).
 *
 * A helper, not a state tick: takes (self, vx, vy, vz, flag) with the heading vector {vx,vy,vz}
 * in r1-r3. Optionally (when *self+0x394 is set) first records the aim heading to the target in
 * self[0xe]. Then normalises the passed vector (returning its magnitude), turns its atan2 heading
 * into a sin/cos pair, builds a Y-rotation matrix (MTX_RotY33_), multiplies it into the node's
 * orientation at self+0x10 (MTX_MultVec33 on *self+0x3b0), and -- if flag is set -- transforms
 * that by another matrix (*self+0x3c0). Returns the magnitude.
 *
 * MATCHED. Two things carried it, both catalogued:
 *  - ★ PARAMETER HOMING: the vector arrives in registers r1-r3 and its ADDRESS is taken (passed to
 *    normalise/atan2), so mwcc homes it with the opening `push {r0,r1,r2,r3}`. To reproduce the
 *    ROM's RE-READS of the homed slots (`ldr r1,[sp,#0x4c]` for vz), the vector must be accessed
 *    through a POINTER -- `int *v = &vx; ... v[0], v[2]` -- not through the `vx`/`vz` params
 *    directly. Using the params keeps mwcc's values in callee-saved registers and adds a `mov`
 *    (260 B). `&vx` + `v[i]` forces the loads mwcc's homing set up.
 *  - the reloc NAME: `func_01ff93bc` is MTX_MultVec33 (the index knew it) -- the last DIFIERE was
 *    a reloc-name mismatch, not a byte mismatch.
 *  - `mtx` declared BEFORE `aim` so the frame is aim=sp+0, mtx above it.
 */
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern int func_01ff8d18(void *a, void *d);
extern void MTX_RotY33_(void *mtx, int sin, int cos);
extern void MTX_MultVec33(void *a, void *mtx, void *d);
extern void func_0202f384(void *dst, void *mtx, void *src);
extern short data_0203d210[];

int func_ov148_020d0770(int *self, int vx, int vy, int vz, int flag) {
    int mtx[9];
    int aim[3];
    int mag;
    int idx;

    if (*(int *)(*self + 0x394) != 0) {
        VEC_Subtract((void *)(*(int *)(*self + 0x394) + 0x190), (void *)self[3], aim);
        self[0xe] = func_020050b4(aim[0], aim[2]);
    }
    {
    int *v = &vx;
    mag = func_01ff8d18(v, v);
    idx = (int)(((unsigned)(((long long)(int)(unsigned)func_020050b4(v[0], v[2]) * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    MTX_RotY33_(mtx, (int)data_0203d210[idx * 2], (int)data_0203d210[idx * 2 + 1]);
    }
    MTX_MultVec33((void *)(*self + 0x3b0), mtx, (void *)(self + 4));
    if (flag != 0) {
        func_0202f384((void *)(self + 4), (void *)(*self + 0x3c0), (void *)(self + 4));
    }
    return mag;
}
