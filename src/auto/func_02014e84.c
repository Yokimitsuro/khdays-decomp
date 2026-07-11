/* Detach up to two resources from obj: for each non-null out-pointer, clear the
 * ready bit (bit0 of the u16 at +0x10 / +0x20), hand out the held value
 * (obj[8] / obj[0x18]) and zero the slot. */
void func_02014e84(int *obj, int *arg1, int *arg2) {
    if (arg1 != 0) {
        *(unsigned short *)((char *)obj + 0x10) &= ~1;
        *arg1 = obj[2];
        obj[2] = 0;
    }
    if (arg2 != 0) {
        *(unsigned short *)((char *)obj + 0x20) &= ~1;
        *arg2 = obj[6];
        obj[6] = 0;
    }
}
