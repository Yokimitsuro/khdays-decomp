/* Draw into one of the three sub-buffers of the layout's scratch surface: the
 * shared one at +0x280 when no variant is asked for, otherwise the wide one at
 * +0x360 or the narrow one at +0x3a0. Tail call. */
extern void func_ov002_02064e5c(void *buffer, int arg);

typedef struct {
    char pad0000[0x14];
    char *pBuffer;      /* +0x14 */
} Ov002Surface;

typedef struct {
    char pad0000[0x18];
    Ov002Surface *pSurface; /* +0x18 */
} Ov002LayoutContext;

extern Ov002LayoutContext *data_ov002_0207f638;

void func_ov002_02065204(int arg, int wide, int variant) {
    Ov002LayoutContext *ctx = data_ov002_0207f638;
    int offset;

    if (variant != 0) {
        if (wide != 0) {
            offset = 0x360;
        } else {
            offset = 0x3a0;
        }
    } else {
        offset = 0x280;
    }

    func_ov002_02064e5c(ctx->pSurface->pBuffer + offset, arg);
}
