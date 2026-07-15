/* func_ov023_02088ec0 -- test whether `id` is the active sub-panel entry, ov023.
 * Returns 1 only when the panel is enabled (@+0x1a28 bit 3) and its current entry
 * (@+0x1a2c) equals id, else 0. */
int func_ov023_02088ec0(char *obj, int id) {
    obj += 0x1000;
    if (*(int *)(obj + 0xa28) & 8) {
        if (id == *(int *)(obj + 0xa2c)) {
            return 1;
        }
    }
    return 0;
}
