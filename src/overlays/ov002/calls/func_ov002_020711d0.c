/*
 * func_ov002_020711d0 - find the active entry matching a key and return its address (ARM).
 *
 * Scans the stride-0x90 entry array at *(int*)&data_ov002_0207fa0c + 4 (the count is the word at
 * +0), returning the address of the first entry whose signed key byte at +4 equals param_1, or 0 if
 * none match. The count is re-read each iteration (matching the ROM's non-hoisted loop bound), and
 * `entry` is declared before `base` so the two pointers land in the registers the ROM uses.
 */
extern int data_ov002_0207fa0c;

int func_ov002_020711d0(int param_1)
{
    int result = 0;
    int i = 0;
    char *entry;
    int base = *(int *)&data_ov002_0207fa0c;
    if (*(volatile int *)base > 0) {
        entry = (char *)base;
        do {
            if (param_1 == *(signed char *)(entry + 4)) {
                result = base + 4 + i * 0x90;
                break;
            }
            entry += 0x90;
            i++;
        } while (i < *(volatile int *)base);
    }
    return result;
}
