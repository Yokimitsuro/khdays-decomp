extern void *func_ov025_02084a7c(void);
extern void *func_ov025_0208843c(void *context, int arg1);
extern void *func_ov025_020884c8(void *context, void *entry);
extern void MI_CpuCopy8(void *src, void *dst, int size);

void func_ov025_0209bfcc(void *out, short value)
{
    void *context = func_ov025_02084a7c();
    void *entry;

    *(short *)out = value;
    entry = func_ov025_0208843c(context, *(short *)out);
    *(void **)((char *)out + 4) = entry;
    entry = *(void **)((char *)out + 4);
    MI_CpuCopy8(func_ov025_020884c8(context, entry), (char *)out + 8, 8);
}
