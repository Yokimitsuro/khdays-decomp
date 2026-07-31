/*
 * Ov002_InitPlayRecord - reset the play record at root-context + 0x8ba8 (a sibling of
 * Ov002_InitContextRecord/+0x8bcc and Ov002_InitHandleRecord/+0x8d14), clear a 0xc0-byte
 * GameState sub-buffer, seed one GameState field from another, and clear a global flag.
 *
 * Record @ +0x8ba8: sets the +0/+2 halfwords and the +8/+0xc words to -1, the +4 byte to
 * 0xff, the +5/+6 bytes and the +0x1c word and +0x20 halfword to 0. Then MemSets 0xc0 bytes
 * at (*data_0204be18)+0x420, copies GameState field 0x40a into field 0x20ea (low 16 bits),
 * and clears data_0204c4d8[0x11].
 *
 * THUMB. The -1 stores use SIGNED short/int lvalues so mwcc materializes 0xffffffff once and
 * strh/str/strb's it to every field (signed truncation makes the high bits don't-care);
 * unsigned lvalues would force a separate 0xffff constant and add instructions.
 */

typedef unsigned char u8;
typedef unsigned int  u32;

extern void MI_CpuFill8(void *dst, int val, int size);
extern u32  func_020235d0(int field, int a);
extern void func_020235e8(int field, int a, u32 val);
extern int  data_ov002_0207fa00;
extern int  data_0204be18;
extern char data_0204c4d8[];

void func_ov002_02069240(void)
{
    char *rec = (char *)(data_ov002_0207fa00 + 0x8ba8);
    int gs;
    u32 v;

    *(short *)(rec + 0)    = -1;
    *(short *)(rec + 2)    = -1;
    *(int *)(rec + 8)      = -1;
    *(int *)(rec + 0xc)    = -1;
    rec[5] = 0;
    rec[6] = 0;
    rec[4] = -1;
    *(int *)(rec + 0x1c)   = 0;
    *(short *)(rec + 0x20) = 0;

    gs = data_0204be18;
    MI_CpuFill8((void *)(gs + 0x420), 0, 0xc0);

    v = func_020235d0(0x40a, 2);
    func_020235e8(0x20ea, 2, v & 0xffff);

    data_0204c4d8[0x11] = 0;
}
