extern void func_ov008_02055a34(void *context, int arg1);
extern void func_ov008_020555dc(void *context, void *entry, int arg2);

void func_ov008_02055608(void *context, int arg1)
{
    int count;
    int i;

    func_ov008_02055a34(context, arg1);
    count = *(int *)((char *)context + 0x30);
    i = 0;

    if (count > 0) {
        int offset = 0;

        do {
            char *entry = *(char **)((char *)context + 0xc) + offset;

            if (*(int *)(entry + 0x14) != 0) {
                func_ov008_020555dc(context, entry, arg1);
            }

            count = *(int *)((char *)context + 0x30);
            i++;
            offset += 0x38;
        } while (i < count);
    }
}
