/*
 * func_ov002_02074460 - linear search of a stride-0x18 entry array for a key (ARM).
 *
 * Scans the base[0x48]-length entry array at base[0x44] (base = *(int*)&data_ov002_0207fa14) for
 * the first entry whose signed key byte at +0x14 equals param_1, returning its index or -1.
 * `entry` is declared before `base` so the count and the running entry pointer land in the
 * registers the ROM uses.
 */
extern int data_ov002_0207fa14;

int func_ov002_02074460(int param_1)
{
    int result = -1;
    int i = 0;
    char *entry;
    int base = *(int *)&data_ov002_0207fa14;
    int count = *(unsigned char *)(base + 0x48);
    if (count > 0) {
        entry = *(char **)(base + 0x44);
        do {
            if (param_1 == *(signed char *)(entry + 0x14)) { result = i; break; }
            entry += 0x18;
            i++;
        } while (i < count);
    }
    return result;
}
