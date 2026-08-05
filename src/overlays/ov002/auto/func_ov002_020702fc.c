/*
 * func_ov002_020702fc - test whether a point lies within a centred 3D box (ARM, reloc-free).
 *
 * The 3D counterpart of func_ov002_02070384: the object at param_1 defines a box by centre
 * (param_1[0x2c], param_1[0x30], param_1[0x34]) and half-extents (param_1[0x20], param_1[0x24],
 * param_1[0x28]); the point is (param_2[0], param_2[1], param_2[2]). Returns 1 when the point is
 * inside on all three axes, 0 otherwise. A negative x half-extent (sign bit set) is a wildcard
 * that always passes.
 *
 * Every failure exit shares one `return 0` via goto so mwcc emits branches to a single tail, and
 * each axis's upper-bound sum (centre + half-extent) is precomputed into a local so mwcc schedules
 * the add ahead of the lower-bound branch, as the ROM does.
 */
int func_ov002_020702fc(int param_1, int *param_2)
{
    int w = *(int *)(param_1 + 0x20);
    int cx, cy, cz, h, d, s;
    if (w & 0x80000000) return 1;
    cx = *(int *)(param_1 + 0x2c);
    s = cx + w;
    if (cx - w > param_2[0]) goto ret0;
    if (s < param_2[0]) goto ret0;
    h = *(int *)(param_1 + 0x24);
    cy = *(int *)(param_1 + 0x30);
    s = cy + h;
    if (cy - h > param_2[1]) goto ret0;
    if (s < param_2[1]) goto ret0;
    d = *(int *)(param_1 + 0x28);
    cz = *(int *)(param_1 + 0x34);
    s = cz + d;
    if (cz - d > param_2[2]) goto ret0;
    if (s >= param_2[2]) return 1;
ret0:
    return 0;
}
