/* Geometry command 0x19 (MTX_MULT_4x3) followed by the 48-byte FIFO push. */
extern void *GX_SendFifo48B();

void *G3_MultMtx43(void *m) {
    *(volatile unsigned int *)0x4000400 = 0x19;
    return GX_SendFifo48B(m);
}
