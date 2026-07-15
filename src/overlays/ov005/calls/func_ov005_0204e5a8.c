/* Allocate a 0x58-byte record node, zero it, and copy ~25 fields from the source record
 * (param_1) with their native widths (several u16/u8 values widened into u32 slots, two
 * u16 reads truncated to bytes). node[4] is a bool (source field 0xc == 1). Finally parse
 * four sub-values out of param_2 via func_ov005_0204e564, threading the cursor. */
typedef unsigned short u16;
typedef unsigned char u8;
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void MI_CpuFill8(void *dst, int val, unsigned int size);
extern short *func_ov005_0204e564(short **cursor, short *in);
unsigned int *func_ov005_0204e5a8(int param_1, short *param_2) {
    short *cur;
    unsigned int *n = (unsigned int *)NNSi_FndAllocFromDefaultExpHeap(0x58);
    MI_CpuFill8(n, 0, 0x58);
    *(u16 *)((char *)n + 0x00) = *(u16 *)(param_1 + 2);
    *(u16 *)((char *)n + 0x02) = *(u16 *)(param_1 + 4);
    *(u16 *)((char *)n + 0x04) = *(u16 *)(param_1 + 0xa);
    *(u16 *)((char *)n + 0x06) = *(u16 *)(param_1 + 0xe);
    *(u16 *)((char *)n + 0x08) = *(u16 *)(param_1 + 0x10);
    *(u16 *)((char *)n + 0x0a) = *(u16 *)(param_1 + 0x12);
    *(u8 *)((char *)n + 0x0c) = *(u8 *)(param_1 + 0x14);
    *(int *)((char *)n + 0x10) = (*(u16 *)(param_1 + 0xc) == 1);
    *(u8 *)((char *)n + 0x14) = *(u8 *)(param_1 + 0x16);
    *(u8 *)((char *)n + 0x0d) = *(u8 *)(param_1 + 0x15);
    *(u8 *)((char *)n + 0x15) = *(u8 *)(param_1 + 0x17);
    *(int *)((char *)n + 0x1c) = *(u16 *)(param_1 + 6);
    *(int *)((char *)n + 0x18) = *(u8 *)(param_1 + 0x23);
    *(u16 *)((char *)n + 0x20) = *(u16 *)(param_1 + 0x18);
    *(u16 *)((char *)n + 0x22) = *(u16 *)(param_1 + 0x1a);
    *(u16 *)((char *)n + 0x24) = *(u16 *)(param_1 + 0x1c);
    *(u8 *)((char *)n + 0x26) = (u8)*(u16 *)(param_1 + 0x1e);
    *(u8 *)((char *)n + 0x27) = (u8)*(u16 *)(param_1 + 0x20);
    *(u8 *)((char *)n + 0x28) = *(u8 *)(param_1 + 0x22);
    *(u16 *)((char *)n + 0x2a) = *(u16 *)(param_1 + 0x24);
    *(u16 *)((char *)n + 0x2c) = *(u16 *)(param_1 + 0x26);
    *(u16 *)((char *)n + 0x2e) = *(u16 *)(param_1 + 0x28);
    *(int *)((char *)n + 0x30) = *(u16 *)(param_1 + 0x2a);
    *(int *)((char *)n + 0x34) = *(u16 *)(param_1 + 0x2c);
    *(int *)((char *)n + 0x38) = *(u16 *)(param_1 + 0x2e);
    n[0xf] = (unsigned int)func_ov005_0204e564(&cur, param_2);
    n[0x10] = (unsigned int)func_ov005_0204e564(&cur, cur);
    n[0x11] = (unsigned int)func_ov005_0204e564(&cur, cur);
    n[0x12] = (unsigned int)func_ov005_0204e564(0, cur);
    return n;
}
