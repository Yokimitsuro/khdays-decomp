typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int func_ov107_020c5c54();

struct Vec3 {
    u32 x, y, z;
};

union F {
    u16 w;
    struct {
        u16 lo : 8;
        u16 hi : 8;
    } bf;
};

struct Obj {
    u8 pad0[0x60];
    union F f60;
    u8 pad62[0x394 - 0x62];
    struct Vec3 field_0x394;
};

void func_ov138_020d2530(struct Obj *a, int b, struct Vec3 *src) {
    func_ov107_020c5c54(a, b);
    a->field_0x394 = *src;
    a->f60.w = (u16)((a->f60.w & ~0xff00) | (((a->f60.bf.hi | 1) & 0xff) << 8));
}
