/* Releases the texture banks and records the released mask plus the three slot base
 * addresses the mask maps to. */
extern int SNDi_UnlockMutex(void);
extern unsigned short data_02041428[];
extern unsigned short data_0204142a[];
extern unsigned short data_0204142c[];
extern int data_0204470c[];

void GX_BeginLoadTex(void) {
    int mask = SNDi_UnlockMutex();
    int off = mask * 6;
    unsigned short a = *(unsigned short *)((char *)data_02041428 + off);
    unsigned short b = *(unsigned short *)((char *)data_0204142a + off);
    unsigned short c = *(unsigned short *)((char *)data_0204142c + off);
    data_0204470c[5] = mask;
    data_0204470c[1] = a << 12;
    data_0204470c[6] = b << 12;
    data_0204470c[7] = c << 12;
}
