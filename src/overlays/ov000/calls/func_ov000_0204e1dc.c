extern void GFXi_EnqueueCommand(int type, int a, void *src, int size);

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov000LogoPaletteContext {
    u8 pad_0000[0x4c6c];
    u16 sourcePalette[0x100];
    u16 uploadPalette[0x100];
} Ov000LogoPaletteContext;

typedef struct SourcePaletteColor {
    u16 value;
} SourcePaletteColor;

typedef struct UploadPaletteColor {
    u16 value;
} UploadPaletteColor;

extern int NNSi_FndGetCurrentRootHeap(void);

void func_ov000_0204e1dc(int scale) {
    UploadPaletteColor *end;
    int factor;
    SourcePaletteColor *src;
    UploadPaletteColor *dst;
    Ov000LogoPaletteContext *context;

    context = (Ov000LogoPaletteContext *)NNSi_FndGetCurrentRootHeap();
    src = (SourcePaletteColor *)context->sourcePalette;
    dst = (UploadPaletteColor *)context->uploadPalette;
    end = dst;
    factor = scale;

    if ((unsigned int)src < (unsigned int)dst) {
        do {
            u16 c = (src++)->value;
            int g = (c >> 5) & 0x1f;
            int r = c & 0x1f;
            int b = (c >> 0xa) & 0x1f;
            int nr = r + (factor * (0x1f - r) >> 4);
            int ng = g + (factor * (0x1f - g) >> 4);
            int nb = b + (factor * (0x1f - b) >> 4);

            (dst++)->value = nr | (ng << 5) | (nb << 10);
        } while ((unsigned int)src < (unsigned int)end);
    }

    GFXi_EnqueueCommand(0xf, 0, context->uploadPalette, 0x200);
}
