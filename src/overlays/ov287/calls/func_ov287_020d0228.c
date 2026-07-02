struct v3 { int a, b, c; };
extern void func_01fffc5c(void *p);
extern void func_01fffc24(void *p);
extern void *func_01fffca8(int a, int b, int c);
void func_ov287_020d0228(int obj, int size, int *entries) {
    struct v3 *src;
    int count, i;
    *(int *)(obj + 0x390) = entries[0];
    src = (struct v3 *)(entries + 1);
    func_01fffc5c((void *)(obj + 0x398));
    func_01fffc24((void *)(obj + 0x398));
    count = (int)((unsigned int)(size - 4) / 12);
    for (i = 0; i < count; i++) {
        struct v3 *slot = (struct v3 *)func_01fffca8(obj + 0x398, 0xc, 0x64);
        *slot = *src;
        src++;
    }
}
