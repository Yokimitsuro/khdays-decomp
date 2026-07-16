/* NONMATCHING: 164B vs 168B -- one instruction. Structure, all five re-derefs of the global,
 * both shift-pair bit extractions and the ldrsb icon read all match. The ROM materialises the
 * stride and multiplies (`mov r0,#6 ; mul r0,r5,r0`); mwcc strength-reduces `row * 6` into
 * shift/add. Not steerable from C -- the operand is a variable, so there is no array-subscript
 * form to hang it on (contrast ov006 55e04, where a full-size struct made the subscript work).
 *
 * func_ov006_0204fbd0 -- title: fill in the description block for menu row `row`.
 * Each row's record is 6 bytes at OBJ+0x4ac: the id at +4, two flag bits packed in the byte
 * at +1 and the icon at +2. The flags are unpacked into their own bytes and the icon is
 * mapped through func_ov006_0204d610 to the sprite the caption uses. */
extern void MI_CpuFill8(void *dst, int data, unsigned int size);
extern int  func_ov006_0204d610(int icon);
extern int  data_ov006_020565e4;

#define OBJ (*(char **)&data_ov006_020565e4)

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
    out->flag0 = (unsigned char)(((unsigned int)*(unsigned char *)(OBJ + off + 0x4ad) << 0x1f) >> 0x1f);
    out->flag1 = (unsigned char)(((unsigned int)*(unsigned char *)(OBJ + off + 0x4ad) << 0x1e) >> 0x1f);
    out->icon = *(signed char *)(OBJ + off + 0x4ae);
    out->sprite = (signed char)func_ov006_0204d610(*(signed char *)(OBJ + off + 0x4ae));
    out->pad6 = 0;
}
