/* Constructor of the ov262 enemy (byte-identical twin of ov261): raises bit 8 of the +0 flag
 * halfword, installs the handlers (+8 tick, +0xc draw, +0x34/+0x30/+0x10/+0x14/+0x38 callbacks,
 * +0x1dc finish), clears bit 2 of +0x40, raises bit 2 of the +0x9c parent's +0x5c, bit 6 of the
 * +0x60 high byte and bit 4 of +0x1ae, seeds the +0x64 pose (scale 0xa00, zero vector); builds the
 * primary item from pool entry 0 (+0x384, subscribed) and resolves the two named handles into
 * +0x390/+0x394, then two kind-1/2 sub-items (+0x388/+0x38c: subscribed, bit 0, channels 0 and 2
 * bound), a placement on the +0x144 list (+0x398) from the +0x64 pose, clears bit 0 of the +0x60
 * high byte, loads sound 0x179 and finally sends the +0x38 hook a 60-byte notice (+0x14 = 1, bit 16
 * of +0x18 clear, +0x2c..+0x34 zero, +0x38..+0x3b = -1) that is freed right after. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*Callback)(void);

struct Bit0 {
    unsigned bit0 : 1;
};
struct hw60 { unsigned short lo : 8, hi : 8; };

struct Notice {
    char pad00[0x14];
    int nKind;
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    char pad1c[0x10];
    int a2c;
    int a30;
    int a34;
    signed char b38;
    signed char b39;
    signed char b3a;
    signed char b3b;
};

extern void func_ov262_020d3aec(void);
extern void func_ov262_020d3b80(void);
extern void func_ov262_020d3d00(void);
extern void func_ov262_020d3f3c(void);
extern void func_ov262_020d3c00(void);
extern void func_ov262_020d3c60(void);
extern void func_ov262_020d3e4c(void);
extern void func_ov262_020d3bd0(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bee8(int item, int kind, const char *name);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *pose);
extern void func_0203355c(int resourceId);
extern struct Notice *func_0203d15c(int size);
extern void func_0203d194(struct Notice *p);
extern const char data_ov262_020d51cc[];
extern const char data_ov262_020d51dc[];

void func_ov262_020d3844(char *self)
{
    volatile int *p;
    struct Notice *notice;

    *(u16 *)self |= 0x100;
    /* the first handler is written five times: the repeats are dead stores the compiler drops
     * after scheduling, and they use up its scheduling budget so the rest of the constructor keeps
     * the ROM's order (the same lever as the repeated +0x60 clear in ov146) */
    *(Callback *)(self + 0x8) = func_ov262_020d3aec;
    *(Callback *)(self + 0x8) = func_ov262_020d3aec;
    *(Callback *)(self + 0x8) = func_ov262_020d3aec;
    *(Callback *)(self + 0x8) = func_ov262_020d3aec;
    *(Callback *)(self + 0x8) = func_ov262_020d3aec;
    *(Callback *)(self + 0xc) = func_ov262_020d3b80;
    *(Callback *)(self + 0x34) = func_ov262_020d3d00;
    *(Callback *)(self + 0x30) = func_ov262_020d3f3c;
    *(Callback *)(self + 0x10) = func_ov262_020d3c00;
    *(Callback *)(self + 0x14) = func_ov262_020d3c60;
    *(Callback *)(self + 0x38) = func_ov262_020d3e4c;
    *(Callback *)(self + 0x1dc) = func_ov262_020d3bd0;
    *(int *)(self + 0x40) &= ~4;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 0x10;
    *(int *)(self + 0x70) = 0xa00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x390) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov262_020d51cc);
    *(int *)(self + 0x394) = func_0203bee8(*(int *)(self + 0x384), 1, data_ov262_020d51dc);
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(self, 1));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    ((struct Bit0 *)(*(int *)(self + 0x388) + 0x5c))->bit0 = 1;
    func_0203b9fc(*(int *)(self + 0x388), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x388), 2, 0, 1);
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(self, 2));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    ((struct Bit0 *)(*(int *)(self + 0x38c) + 0x5c))->bit0 = 1;
    func_0203b9fc(*(int *)(self + 0x38c), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x38c), 2, 0, 1);
    p = func_01fffca8(self + 0x144, 4, 100);
    *p = func_ov107_020c319c(self + 0x64);
    *(int *)(self + 0x398) = *p;
    ((struct hw60 *)(self + 0x60))->hi &= ~1;
    func_0203355c(0x179);
    notice = func_0203d15c(0x3c);
    notice->nKind = 1;
    notice->uFlagsLo = 0;
    notice->a2c = 0;
    notice->a30 = 0;
    notice->a34 = 0;
    notice->b38 = -1;
    notice->b39 = -1;
    notice->b3a = -1;
    notice->b3b = -1;
    if (*(void (**)(char *, int, struct Notice *))(self + 0x38) != 0) {
        (*(void (**)(char *, int, struct Notice *))(self + 0x38))(self, 0x3c, notice);
    }
    func_0203d194(notice);
}
