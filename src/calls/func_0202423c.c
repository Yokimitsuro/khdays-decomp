extern void GXS_SetGraphicsMode(int mode);
/* Pick the sub-engine graphics mode for the current BG mode (DISPCNT_B & 7) from the table,
 * folding entries >= 8 back into range. */
void func_0202423c(int *table) {
    int mode = table[*(volatile unsigned int *)0x4001000 & 7];
    if (mode >= 8) {
        mode -= 8;
    }
    GXS_SetGraphicsMode(mode);
}
