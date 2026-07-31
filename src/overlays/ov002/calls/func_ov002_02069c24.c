/*
 * Ov002_InitStateRecord - reset the record at root-context + 0x8c94, then chain to
 * func_ov002_02069c04. Part of the ov002 gameplay init family (siblings init records at
 * +0x8ba8/+0x8bcc/+0x8d14). Sets the leading word to -1, the +8/+0x1a/+0x50 bytes to 0xff,
 * the +0x18/+0x74 halfwords to 0xffff, and zeroes a spread of byte/half/word fields; clears
 * +0x28..+0x4f via INITi_CpuClear32, fills +0x1b..+0x1e with 0xff (MI_CpuFill8) then again
 * with 0xffff via MIi_CpuClear16, and sets the +0x77 enable byte to 1.
 *
 * THUMB. The -1 stores use signed short/int lvalues so mwcc reuses one 0xffffffff register
 * for every width; it is re-materialized after the CpuClear/CpuFill calls clobber r0-r3.
 */

typedef unsigned char u8;
typedef unsigned int  u32;

extern void INITi_CpuClear32_0x01ff86fc(int val, void *dst, int count);
extern void MI_CpuFill8(void *dst, int val, int size);
extern void MIi_CpuClear16(int val, void *dst, int size);
extern void func_ov002_02069c04(void);
extern int  data_ov002_0207fa00;

void func_ov002_02069c24(void)
{
    char *rec = (char *)(data_ov002_0207fa00 + 0x8c94);

    *(int *)(rec + 0) = -1;
    rec[4] = 0;
    rec[8] = -1;
    rec[0x1a] = -1;
    *(int *)(rec + 0xc) = 0;
    *(short *)(rec + 0x10) = 0;
    *(int *)(rec + 0x14) = 0;
    *(short *)(rec + 0x18) = -1;
    rec[0x76] = 0;
    INITi_CpuClear32_0x01ff86fc(0, rec + 0x28, 0x28);
    MI_CpuFill8(rec + 0x1b, 0xff, 4);
    MIi_CpuClear16(0xffff, rec + 0x1b, 4);
    rec[0x50] = -1;
    *(int *)(rec + 0x6c) = 0;
    *(int *)(rec + 0x70) = 0;
    rec[0x77] = 1;
    *(int *)(rec + 0x64) = 0;
    rec[0x51] = 0;
    *(short *)(rec + 0x74) = -1;
    func_ov002_02069c04();
}
