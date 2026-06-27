extern void GXS_BeginLoadOBJExtPltt(void);
extern void GXS_LoadOBJExtPltt(void *src, unsigned offset, unsigned size);
extern void GXS_EndLoadOBJExtPltt(void);

void func_02011454(void *src, unsigned offset, unsigned size) {
    GXS_BeginLoadOBJExtPltt();
    GXS_LoadOBJExtPltt(src, offset, size);
    GXS_EndLoadOBJExtPltt();
}
