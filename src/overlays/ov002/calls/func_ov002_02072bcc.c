/* Work out the object's effective height: its base height plus the signed
 * adjustment at +4, plus the extra row the wide-layout flag asks for. Capped at
 * 0x78 and floored at 1 -- nothing may end up with no height at all. */
extern int func_ov002_0206e6e8(void *self);

typedef struct {
    unsigned char bFlags;       /* +0 */
} Ov002LayoutFlags;

typedef struct {
    char pad0000[8];
    unsigned char bExtraRow;    /* +8 */
} Ov002LayoutMetrics;

extern Ov002LayoutFlags data_0204c240;
extern Ov002LayoutMetrics data_0204c254;

int func_ov002_02072bcc(char *self) {
    int height = func_ov002_0206e6e8(self) + *(signed char *)(self + 4);

    if ((data_0204c240.bFlags & 2) != 0) {
        height += data_0204c254.bExtraRow;
    }

    if (height > 0x78) {
        height = 0x78;
    }

    if (height > 0) {
        return height;
    }

    return 1;
}
