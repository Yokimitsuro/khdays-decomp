/* Replaces the BG mode bits of the sub-engine DISPCNT. */
void GXS_SetGraphicsMode(unsigned int mode) {
    volatile unsigned int *dispcnt = (volatile unsigned int *)0x4001000;
    *dispcnt = (*dispcnt & ~7) | mode;
}
