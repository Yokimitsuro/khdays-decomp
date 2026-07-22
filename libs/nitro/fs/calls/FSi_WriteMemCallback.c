/* Memory-archive write callback: copies into the base pointer at +0x28. */
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);

int FSi_WriteMemCallback(char **arc, const void *src, unsigned int off, unsigned int len) {
    MI_CpuCopy8(src, arc[10] + off, len);
    return 0;
}
