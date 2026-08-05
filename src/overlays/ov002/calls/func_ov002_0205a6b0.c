/*
 * func_ov002_0205a6b0 - look up a key's slot and read its enabled bit (ARM).
 *
 * Scans up to 24 stride-0xc entries at data_ov002_0207f620's base for the one whose u16 key at
 * +0x4b8 equals param_2. When found, returns bit `i` of the mask param_3 (whether that slot is
 * enabled) and, if param_1 is non-null, writes the slot index to *param_1 (or -1 when no slot
 * matches). Returns 0 when not found.
 */
extern int data_ov002_0207f620;

int func_ov002_0205a6b0(int *param_1, int param_2, int param_3)
{
    int base = *(int *)&data_ov002_0207f620;
    int result = 0;
    int i;
    char *p = (char *)base;
    for (i = 0; i < 0x18; i++) {
        if (param_2 == *(unsigned short *)(p + 0x4b8)) {
            result = (param_3 & (1 << i)) != 0;
            break;
        }
        p += 0xc;
    }
    if (param_1 != 0) {
        *param_1 = (i == 0x18) ? -1 : i;
    }
    return result;
}
