/*
 * Ov002_InitContextRecord - reset the gameplay record block at root-context + 0x8bcc,
 * called from the ov002 gameplay scene tick. Sets the leading id word and a second marker
 * word to -1, stores the data_0204c3d8 table pointer at +4, zeroes the +0xc0 word and the
 * +0xb0-byte middle region (INITi_CpuClear32), sets the +0xc4 marker word to -1, and fills
 * the +0xb9..+0xbd bytes with 0xff.
 *
 * THUMB. The -1/0 fields at aligned offsets are word stores (Ghidra renders them as byte
 * runs); the single-byte fields (+0xbe/+0xb8/+0xbf) are byte stores.
 */

typedef unsigned char u8;
typedef unsigned int  u32;

extern void INITi_CpuClear32_0x01ff86fc(int val, void *dst, int count);
extern void MI_CpuFill8(void *dst, int val, int size);
extern int  data_ov002_0207fa00;
extern char data_0204c3d8[];

void func_ov002_020697e8(void)
{
    int ctx = data_ov002_0207fa00;
    int p = ctx + 0x8bcc;

    *(u32 *)p = 0xffffffff;
    *(int *)(p + 4) = (int)data_0204c3d8;
    *(u32 *)(p + 0xc0) = 0;
    *(u32 *)(p + 0xc4) = 0xffffffff;
    *(u8 *)(p + 0xbe) = 0;
    INITi_CpuClear32_0x01ff86fc(0, (void *)(p + 8), 0xb0);
    *(u8 *)(p + 0xb8) = 0;
    *(u8 *)(p + 0xbf) = 0;
    MI_CpuFill8((void *)(p + 0xb9), 0xff, 5);
}
