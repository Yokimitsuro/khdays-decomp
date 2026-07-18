/* flag0/flag1 are read through a 1-bit BITFIELD, not `(x << 31) >> 31`. The explicit
 * shift form folds to `and r1,r1,#1` because the destination is an 8-bit field, which
 * makes the shifts redundant; the bitfield read keeps the ROM's lsl#31/lsr#31 pair
 * (and lsl#30/lsr#31 for bit 1). Same crack as ov022 0208868c. */
extern void MI_CpuFill8(void *dst, int data, unsigned int size);
extern int  func_ov006_0204d610(int icon);
extern int  data_ov006_020565e4;
#define OBJ (*(char **)&data_ov006_020565e4)
struct Ov006RowFlags { unsigned char b0 : 1, b1 : 1; };
struct Ov006RowInfo {
    unsigned short id;
    unsigned char flag0;
    unsigned char flag1;
    signed char icon;
    signed char sprite;
    unsigned char pad6;
};
void func_ov006_0204fbd0(int row, struct Ov006RowInfo *out) {
    int off = row * 6;
    MI_CpuFill8(out, 0, 8);
    out->id = *(unsigned short *)(OBJ + off + 0x4b0);
    out->flag0 = ((struct Ov006RowFlags *)(OBJ + off + 0x4ad))->b0;
    out->flag1 = ((struct Ov006RowFlags *)(OBJ + off + 0x4ad))->b1;
    out->icon = *(signed char *)(OBJ + off + 0x4ae);
    out->sprite = (signed char)func_ov006_0204d610(*(signed char *)(OBJ + off + 0x4ae));
    out->pad6 = 0;
}
