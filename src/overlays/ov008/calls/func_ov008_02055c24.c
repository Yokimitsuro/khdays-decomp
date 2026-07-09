extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void *func_ov008_02055c24(void *src, void *dst)
{
    MI_CpuCopy8((char *)src + 0x1c, dst, 8);
    return dst;
}
