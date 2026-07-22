/* Reads back the vector matrix, but only while the geometry engine is idle; -1 otherwise. */
extern void MI_Copy36B(const void *src, void *dst);

int G3X_GetVectorMtx(void *dst) {
    volatile unsigned int *gxstat = (volatile unsigned int *)0x4000600;
    if (*gxstat & 0x8000000) {
        return -1;
    }
    MI_Copy36B((const void *)(gxstat + 0x20), dst);
    return 0;
}
