extern int func_0203c634(void *obj, int slot, void *cb);
extern void func_ov301_020cc748(void);

int func_ov301_020cc6fc(void *obj) {
    int *p = *(int **)((char *)obj + 4);
    char *a = (char *)*p + 0x100;
    *(unsigned short *)(a + 0xae) |= 3;
    {
        short s = *(short *)((char *)*p + 0x218);
        *(unsigned short *)((char *)*p + 0x21a) = (s >= 0) ? 0 : s;
    }
    return func_0203c634(obj, *(signed char *)((char *)obj + 0x20), (void *)func_ov301_020cc748);
}
