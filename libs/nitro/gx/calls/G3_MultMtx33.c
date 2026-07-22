/* Geometry command 0x1a (MTX_MULT_3x3); the 36 bytes go through MI_Copy36B. */
extern void *MI_Copy36B();

void *G3_MultMtx33(void *m) {
    *(volatile unsigned int *)0x4000400 = 0x1a;
    return MI_Copy36B(m);
}
