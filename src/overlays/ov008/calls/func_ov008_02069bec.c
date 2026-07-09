extern void *func_ov008_02050c54(void);
extern void *func_ov008_02054788(void *context, int arg1);
extern void *func_ov008_02054820(void *context, void *entry);
extern void MI_CpuCopy8(void *src, void *dst, int size);

void func_ov008_02069bec(void *out, short value)
{
    void *context = func_ov008_02050c54();
    void *entry;

    *(short *)out = value;
    entry = func_ov008_02054788(context, *(short *)out);
    *(void **)((char *)out + 4) = entry;
    entry = *(void **)((char *)out + 4);
    MI_CpuCopy8(func_ov008_02054820(context, entry), (char *)out + 8, 8);
}
