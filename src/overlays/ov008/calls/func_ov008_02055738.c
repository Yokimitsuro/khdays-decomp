extern void func_ov008_02055708(void *context, void *entry);

void func_ov008_02055738(void *context)
{
    int count = *(int *)((char *)context + 0x34);
    int i = 0;

    if (count > 0) {
        int offset = 0;

        do {
            char *entry = *(char **)((char *)context + 0x10) + offset;

            if ((((unsigned int)*(unsigned char *)(entry + 0x24) << 30) >> 31) == 1) {
                func_ov008_02055708(context, entry);
            }

            count = *(int *)((char *)context + 0x34);
            i++;
            offset += 0x30;
        } while (i < count);
    }
}
