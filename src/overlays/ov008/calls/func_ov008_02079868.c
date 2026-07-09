extern void MI_CpuCopy8(void *src, void *dst, int size);
extern char *data_ov008_02090f24[];

void func_ov008_02079868(int index, void *dst, int size)
{
    if (dst != 0) {
        MI_CpuCopy8(*(void **)(data_ov008_02090f24[0] + index * 8 + 8), dst, size);
    }

    *(int *)(data_ov008_02090f24[0] + index * 4 + 0x30) = 0;
}
