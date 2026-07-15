#pragma thumb on
/* func_ov023_02088ee8 -- set/clear sub-panel flag bit 0x4 (@+0x1a28), ov023, per `on`. */
void func_ov023_02088ee8(char *obj, int on) {
    if (on != 0) {
        *(int *)(obj + 0x1a28) |= 0x4;
    } else {
        *(int *)(obj + 0x1a28) &= ~0x4;
    }
}
