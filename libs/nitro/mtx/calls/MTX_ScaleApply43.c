/* Scales the 3x3 part through MTX_ScaleApply33 and copies the translation row across. */
extern void MTX_ScaleApply33(const int *src, int *dst, int sx, int sy, int sz);

void MTX_ScaleApply43(const int *src, int *dst, int sx, int sy, int sz) {
    MTX_ScaleApply33(src, dst, sx, sy, sz);
    dst[9] = src[9];
    dst[10] = src[10];
    dst[11] = src[11];
}
