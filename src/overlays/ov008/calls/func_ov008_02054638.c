extern void func_ov008_020543b0(void *context, void *entry);
extern void func_ov008_02053bcc(void *context, void *entry);

void func_ov008_02054638(void *context, void *entries, int count)
{
    int i;

    i = 0;
    if (count > 0) {
        char *entry = entries;

        do {
            func_ov008_020543b0(context, entry);
            entry += 0x58;
            i++;
        } while (i < count);
    }

    i = 0;
    if (count > 0) {
        do {
            func_ov008_02053bcc(context, entries);
            i++;
            entries = (char *)entries + 0x58;
        } while (i < count);
    }
}
