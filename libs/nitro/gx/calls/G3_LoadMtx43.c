/* Geometry command 0x17 (MTX_LOAD_4x3) followed by the 48-byte FIFO push. */
extern void *GX_SendFifo48B();

void *G3_LoadMtx43(void *m) {
    *(volatile unsigned int *)0x4000400 = 0x17;
    return GX_SendFifo48B(m);
}
