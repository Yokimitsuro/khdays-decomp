/*
 * func_ov002_02070384 - test whether a point lies within a centred 2D box (ARM, reloc-free).
 *
 * The object at param_1 defines a box by centre (param_1[0x2c], param_1[0x34]) and half-extents
 * (param_1[0x20], param_1[0x24]); the point is (param_2[0], param_2[2]). Returns 1 when the point
 * is inside the box on both axes, 0 otherwise. A negative x half-extent (sign bit set) is a
 * wildcard that always passes.
 *
 * All three failure exits share one `return 0` via goto so mwcc emits branches to a single tail;
 * the upper-bound sum (centre + half-extent) is precomputed into a local so mwcc schedules the
 * add into the slot after the lower-bound compare, ahead of the branch, as the ROM does.
 */
int func_ov002_02070384(int param_1, int *param_2)
{
    int w = *(int *)(param_1 + 0x20);
    int cx, cy, h, s;
    if (w & 0x80000000) return 1;
    cx = *(int *)(param_1 + 0x2c);
    s = cx + w;
    if (cx - w > param_2[0]) goto ret0;
    if (s < param_2[0]) goto ret0;
    h  = *(int *)(param_1 + 0x24);
    cy = *(int *)(param_1 + 0x34);
    s = cy + h;
    if (cy - h > param_2[2]) goto ret0;
    if (s >= param_2[2]) return 1;
ret0:
    return 0;
}
