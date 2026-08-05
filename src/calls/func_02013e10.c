extern void MIi_CpuClearFast(unsigned int data, void *dest, unsigned int size);

typedef struct TileSurface {
    void *pixels;
    int widthTiles;
    int heightTiles;
    unsigned char bpp;
} TileSurface;

void func_02013e10(TileSurface *surf, unsigned int value) {
    int bpp = surf->bpp;
    unsigned int pattern;
    int w;
    int area;
    if (bpp == 4) {
        pattern = value | (value << 4);
        pattern = pattern | (pattern << 8);
        value = pattern | (pattern << 16);
    } else {
        pattern = value | (value << 8);
        value = pattern | (pattern << 16);
    }
    w = surf->widthTiles;
    area = w * surf->heightTiles;
    MIi_CpuClearFast(value, surf->pixels, area * (bpp * 64 / 8));
}
