extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void *func_ov008_02054e74(void *src, void *dst)
{
    MI_CpuCopy8((char *)src + 0x4a44, dst, 8);
    return dst;
}
