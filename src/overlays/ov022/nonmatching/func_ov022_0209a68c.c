/*
 * [nonmatching: dead self-store — repeated `field[1] = field[1]`]
 *
 * Sets or clears bit 0x200 in arg0[0] (via arg1) after notifying func_0202beb8,
 * and re-writes arg0[1] = arg0[1] (a no-op, from an OR/AND with a build-time
 * 0-valued flag). mwcc's -O4 dead-store elimination drops the identical store;
 * not reproducible without the original header's 0 flag macro. Left uncarved.
 */
extern void func_0202beb8(int arg0);

void func_ov022_0209a68c(unsigned int *arg0, int arg1) {
    if (arg1 != 0) {
        func_0202beb8((int)*(char *)((int)arg0 + 0x12f * 4));
        *arg0 |= 0x200;
        arg0[1] = arg0[1];
        return;
    }
    func_0202beb8((int)*(char *)((int)arg0 + 0x12f * 4));
    *arg0 &= 0xfffffdff;
    arg0[1] = arg0[1];
}
