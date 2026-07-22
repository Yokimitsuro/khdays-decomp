/* Reads back the clip matrix, but only while the geometry engine is idle; -1 otherwise. */
extern void MI_Copy64B(const void *src, void *dst);

int G3X_GetClipMtx(void *dst) {
    volatile unsigned int *gxstat = (volatile unsigned int *)0x4000600;
    if (*gxstat & 0x8000000) {
        return -1;
    }
    MI_Copy64B((const void *)(gxstat + 0x10), dst);
    return 0;
}
