/*
 * Ov002_InitHandleRecord - reset the handle record at root-context + 0x8d14, a sibling of
 * Ov002_InitContextRecord (+0x8bcc). Zeroes the leading word (+0), the byte at +5 and +6,
 * clears the +8..+0x37 region to 0xffff (invalid handles) via MIi_CpuClear16, zeroes the
 * +0x38..+0x47 region via INITi_CpuClear32, sets the +0x48 halfword to -1, and zeroes +0x4c.
 *
 * THUMB. The root context pointer is held at data_ov002_0207fa00; typing the base as char *
 * (not int) is what lands ctx in r4 and the record base in r5, matching the original.
 */

extern void MI_CpuFill8(void *dst, int val, int size);
extern void MIi_CpuClear16(int val, void *dst, int size);
extern void INITi_CpuClear32_0x01ff86fc(int val, void *dst, int count);
extern int  data_ov002_0207fa00;

void func_ov002_0206a230(void)
{
    char *ctx = (char *)data_ov002_0207fa00;
    char *rec = ctx + 0x8d14;

    MI_CpuFill8(rec + 6, 0, 1);
    MIi_CpuClear16(0xffff, rec + 8, 0x30);
    INITi_CpuClear32_0x01ff86fc(0, rec + 0x38, 0x10);
    rec[5] = 0;
    *(int *)(ctx + 0x8d14) = 0;
    *(short *)(rec + 0x48) = -1;
    *(int *)(rec + 0x4c) = 0;
}
