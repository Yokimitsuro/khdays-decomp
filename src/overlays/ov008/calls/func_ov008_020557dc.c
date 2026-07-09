extern void func_ov008_020557b0(void *context, void *entry);

void func_ov008_020557dc(void *context)
{
    int count = *(int *)((char *)context + 0x38);
    int i = 0;

    if (count > 0) {
        int offset = 0;

        do {
            char *entry = *(char **)((char *)context + 0x14) + offset;

            if (*(int *)(entry + 0xc) != 0) {
                func_ov008_020557b0(context, entry);
            }

            count = *(int *)((char *)context + 0x38);
            i++;
            offset += 0x10;
        } while (i < count);
    }
}
