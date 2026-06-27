extern void *NNSi_FndInitExpHeap(void *hh, void *end, int opt);

void *func_02010b88(unsigned int start, unsigned int size, int opt)
{
    unsigned int end = size + start;
    unsigned int aligned_start = start + 3;
    end &= ~3u;
    aligned_start &= ~3u;
    if (aligned_start > end) goto fail;
    if ((end - aligned_start) >= 0x30) goto ok;
fail:
    return (void *)0;
ok:
    return NNSi_FndInitExpHeap((void *)aligned_start, (void *)end, opt);
}
