/* Memory-archive read callback: copies from the base pointer at +0x28. */
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);

int FSi_ReadMemCallback(char **arc, void *dst, unsigned int off, unsigned int len) {
    MI_CpuCopy8(arc[10] + off, dst, len);
    return 0;
}
