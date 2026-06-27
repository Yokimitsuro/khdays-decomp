extern void GX_BeginLoadBGExtPltt(void);
extern void GX_LoadBGExtPltt(void *src, unsigned offset, unsigned size);
extern void GX_EndLoadBGExtPltt(void);

void func_02011428(void *src, unsigned offset, unsigned size) {
    GX_BeginLoadBGExtPltt();
    GX_LoadBGExtPltt(src, offset, size);
    GX_EndLoadBGExtPltt();
}
