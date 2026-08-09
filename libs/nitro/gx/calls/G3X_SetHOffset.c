/* G3X_SetHOffset: writes the 3D engine horizontal offset register (0x04000010). */

void G3X_SetHOffset(int value) {
    *(volatile int *)0x04000010 = value;
}
