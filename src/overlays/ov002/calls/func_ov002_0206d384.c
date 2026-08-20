typedef struct {
    char pad0000[0x24];
    signed char nFlags;             /* +0x24 */
    unsigned char nPhase;           /* +0x25 */
    unsigned char nKind;            /* +0x26 */
    char pad0027;
    int nTimer;                     /* +0x28 */
    char pad002c[4];
    unsigned char aState[4];        /* +0x30 */
    char pad0034[0x10];
} Ov002Track;                       /* 0x44 */

extern Ov002Track data_0204c3d8[4];
extern signed char data_0204c4d8[];

/* Reset every track to its idle state and mark the selection as none. */
void func_ov002_0206d384(void)
{
    int i;

    data_0204c4d8[0x10] = -1;

    for (i = 0; i < 4; i++) {
        data_0204c3d8[i].nKind = 0xe;
        data_0204c3d8[i].nTimer = 0;
        data_0204c3d8[i].nFlags &= ~1;
        data_0204c3d8[i].nFlags &= ~2;
        data_0204c3d8[i].nPhase = 0;
        data_0204c3d8[i].aState[0] = 0;
        data_0204c3d8[i].aState[1] = 0;
        data_0204c3d8[i].aState[2] = 0;
        data_0204c3d8[i].aState[3] = 0;
    }
}
