struct v3 { int a, b, c; };
extern void NNSi_FndDestroyDoubleList(void *p);
extern void func_01fffc24(void *p);
extern void *func_01fffca8(int a, int b, int c);
void func_ov292_020d3b64(int obj, int size, int *entries) {
    struct v3 *src;
    int i;
    src = (struct v3 *)entries;
    NNSi_FndDestroyDoubleList((void *)(obj + 0x394));
    func_01fffc24((void *)(obj + 0x394));
    size = (int)((unsigned int)size / 12);
    for (i = 0; i < size; i++) {
        struct v3 *slot = (struct v3 *)func_01fffca8(obj + 0x394, 0xc, 0x64);
        *slot = *src;
        src++;
    }
}
