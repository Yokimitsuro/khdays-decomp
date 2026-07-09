extern void *data_ov008_02090f14;
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void *func_ov008_02055dcc(void *dst)
{
    if (data_ov008_02090f14 == 0) {
        return 0;
    }

    MI_CpuCopy8(data_ov008_02090f14, dst, 8);
    return dst;
}
