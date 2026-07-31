/*
 * Ov002_StreamFormattedLine - format a result line and stream it into the staging buffer.
 * Called from the ov002 gameplay path. Builds a text line for param_1 via
 * func_ov002_0206d834 into a 12-byte stack scratch, encodes it with func_02024fe8 (against
 * the sub-object at ctx+4), then packs a descriptor word and hands it to func_02020c7c
 * together with the context's staging buffer (ctx+8) and its tail pointer (ctx+0x859c).
 *
 * ARM. The descriptor packs ((subLen + 0x8000) & 0xfffffc) << 7, with bit31 set and the low
 * bits of the encode result masked in via (0xfffffc >> 15). The single mask constant is kept
 * in a register and reused with lsr #15, so it is written as one literal used twice.
 */

typedef unsigned int  u32;
typedef unsigned char u8;

extern void func_ov002_0206d834(int a, char *out);
extern u32  func_02024fe8(int a, char *b);
extern void func_02020c7c(u32 *dst, u32 desc, u32 *src, u8 **staging);
extern int  data_ov002_0207fa00;

void func_ov002_0206b910(int param_1, u32 *param_2)
{
    char *ctx = (char *)data_ov002_0207fa00;
    char local[12];
    u32 v;

    func_ov002_0206d834(param_1, local);
    v = func_02024fe8(*(int *)(ctx + 4), local);
    func_02020c7c(
        (u32 *)(ctx + 8),
        (((*(int *)(ctx + 4) + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (v & (0xfffffc >> 15)),
        param_2,
        (u8 **)(ctx + 0x859c));
}
