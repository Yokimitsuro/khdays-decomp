/* Memory-backed archive read: a plain copy that always succeeds. */
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);

int FSi_ReadMemoryCore(void *arc, void *dst, const void *src, unsigned int len) {
    MI_CpuCopy8(src, dst, len);
    return 0;
}
