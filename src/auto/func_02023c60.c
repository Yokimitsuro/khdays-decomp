/* func_02023c60 -- load the default projection/clipping constants into a 14-word state block.
 * Fixed point .12: 0x1000 == 1.0, so 0x800 == 0.5, 0xddb ~= 0.866 (sqrt(3)/2), 0x1555 ~= 4/3
 * (the DS 256x192 aspect), 0x3e8000 == 1000.0 and 0x64000 == 100.0 (the far/near pair).
 *
 * The zeroed fields are written as chained assignments, which is both why they store in
 * descending order and what keeps the first pool load below `str r1,[r0]`: writing the
 * fourteen stores as fourteen separate statements makes mwcc hoist the 0xddb literal load
 * one slot higher to widen the load-use gap. */
void func_02023c60(unsigned int *p) {
    p[0]  = 0x800;
    p[1]  = 0xddb;
    p[2]  = 0x1555;
    p[3]  = 0x1000;
    p[4]  = 0x3e8000;
    p[5]  = p[6] = p[7] = 0;
    p[8]  = p[9] = 0;
    p[10] = 0x64000;
    p[11] = p[13] = 0;
    p[12] = 0x1000;
}
