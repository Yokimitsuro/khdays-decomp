extern void GX_BeginLoadOBJExtPltt(void);
extern void GX_LoadOBJExtPltt(void *src, unsigned offset, unsigned size);
extern void GX_EndLoadOBJExtPltt(void);

void func_020113fc(void *src, unsigned offset, unsigned size) {
    GX_BeginLoadOBJExtPltt();
    GX_LoadOBJExtPltt(src, offset, size);
    GX_EndLoadOBJExtPltt();
}
