extern void GXS_BeginLoadBGExtPltt(void);
extern void GXS_LoadBGExtPltt(void *src, unsigned offset, unsigned size);
extern void GXS_EndLoadBGExtPltt(void);

void func_02011480(void *src, unsigned offset, unsigned size) {
    GXS_BeginLoadBGExtPltt();
    GXS_LoadBGExtPltt(src, offset, size);
    GXS_EndLoadBGExtPltt();
}
