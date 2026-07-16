/* func_ov024_020865f8 -- MobiClip: hand the fast-memory arena its backing store.
 * The arena descriptor is data_ov024_0209bb30; this points it at `base` with `size` bytes
 * (rounded down to a word) and clears the cursor and cached-block fields. This is what
 * func_ov024_02086620 and func_ov024_0208670c later carve the ITCM blob and the saturation
 * table out of. */
extern int data_ov024_0209bb30[];

void func_ov024_020865f8(int base, unsigned int size) {
    data_ov024_0209bb30[4] = base;
    data_ov024_0209bb30[3] = size & 0xfffffffc;
    data_ov024_0209bb30[1] = 0;
    data_ov024_0209bb30[0] = 0;
    data_ov024_0209bb30[8] = 0;
}
