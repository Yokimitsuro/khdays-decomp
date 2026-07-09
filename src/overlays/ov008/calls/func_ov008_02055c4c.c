extern void MI_CpuFill8(void *dst, int value, unsigned int size);
extern char *func_0201ef9c(void *source, int count);

void func_ov008_02055c4c(void *object, void *source)
{
    char *block;
    int offset;

    MI_CpuFill8(object, 0, 0xc);
    block = func_0201ef9c(source, 0xe);
    *(char **)object = block;
    offset = *(int *)block;
    *(int *)((char *)object + 4) = *(int *)(block + 4);
    *(char **)((char *)object + 8) = *(char **)object + offset;
}
