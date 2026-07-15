#pragma thumb on
/* func_ov023_02089274 -- set/clear sub-panel flag bit 8 (@+0x1a28) per `on`, but only
 * while the panel is enabled (bit 0), ov023. */
void func_ov023_02089274(char *obj, int on) {
    int *p = (int *)(obj + 0x1a28);
    if (*p & 1) {
        if (on != 0) {
            *p |= 8;
        } else {
            *p &= ~8;
        }
    }
}
