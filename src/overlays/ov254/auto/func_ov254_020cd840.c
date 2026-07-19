/* Returns the Y coordinate the panel should sit at for the given phase; a negative phase means
 * "use the owner's current one". */
int func_ov254_020cd840(int *self, int phase) {
    if (phase < 0) {
        phase = *(signed char *)(*self + 0x100 + 0xc6);
    }
    switch (phase) {
    case 5:
        return *(int *)(*self + 0x4d4);
    case 0xb:
        return *(int *)(*self + 0x4d4) + (int)0xffff1904;
    case 0xa: {
        int span = self[0x1e] != 0 ? 0xa00 : 0x800;
        return (*(int *)(*self + 0x4d4) + 0x7b31)
               - (int)(((long long)span * 0xf662 + 0x800) >> 12);
    }
    default:
        if (self[0x1e] != 0) {
            return *(int *)(*self + 0x4d4) + (int)0xffffcebc;
        }
        {
            int y = *(int *)(*self + 0x4d4) + 0x7b31;
            if (y < 0xf000) {
                y = 0xf000;
            }
            return y;
        }
    }
}
