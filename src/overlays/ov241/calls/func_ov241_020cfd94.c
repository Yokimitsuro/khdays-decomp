/* Constructor of the ov241 enemy (x3: ov241/242/243): installs the handlers (+8 tick, +0xc
 * draw, +0x30/+0x38 hit callbacks, +0x1dc finish), sets +0x1c9 to 2, seeds the +0x64 pose
 * (scale 0x4cd, y 0x4cd), bit 3 of +0x1ae and bit 5 of the +0x60 high byte; builds the primary
 * item from pool entry 0, resolves the "tag_00/01/02" joints into the +0x3ac id triple, back-links
 * the actor into the render object's +0x4c and arms the joint callback (020cfc04, mode 0/6/3),
 * translates the item's +4 placement by (0, 0x200, 0), keeps the "move" motion handle (+0x39c),
 * creates three kind-2 sub-items (+0x38c.., attached, bits 0/1 of their +0x5c, channels 0 and
 * 2 bound, subscribed), an effect node (+0x3a0, subscribed, bit 0) hosting the kind-3 item
 * (+0x388), a placement on the +0x144 list (+0x398) and loads sound 0x13a. */
typedef unsigned short u16;

struct Bit0 {
    unsigned bit0 : 1;
};

struct Names {
    const char *a;
    const char *b;
    const char *c;
};

extern void func_ov241_020d0024(void);
extern void func_ov241_020d008c(void);
extern void func_ov241_020d0170(void);
extern void func_ov241_020d0104(void);
extern void func_ov241_020d00d4(void);
extern void func_ov241_020cfc04(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bdfc(int item, const char *name);
extern void func_02014e18(int renderObj, void *cb, int ptr, int timing, int opt);
extern void func_0203ca14(void *placement, int x, int y, int z);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c9074(int self, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern int func_0203bf44(void);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern void func_0203355c(int id);
extern struct Names data_ov241_020d0c84;
extern const char data_ov241_020d0cc4[];

void func_ov241_020cfd94(char *self)
{
    struct Names names;
    int i;
    int *p;

    *(void **)(self + 0x8) = func_ov241_020d0024;
    *(void **)(self + 0xc) = func_ov241_020d008c;
    *(void **)(self + 0x30) = func_ov241_020d0170;
    *(void **)(self + 0x38) = func_ov241_020d0104;
    *(void **)(self + 0x1dc) = func_ov241_020d00d4;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(int *)(self + 0x70) = 0x4cd;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x4cd;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    names = data_ov241_020d0c84;
    for (i = 0; i < 3; i++) {
        if (((const char **)&names)[i] != 0) {
            ((u16 *)self)[0x1d6 + i] = func_0203bdfc(*(int *)(self + 0x384), ((const char **)&names)[i]);
        }
    }
    *(char **)(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x4c) = self;
    func_02014e18(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x20, func_ov241_020cfc04, 0, 6, 3);
    func_0203ca14((void *)(*(int *)(self + 0x384) + 4), 0, 0x200, 0);
    *(int *)(self + 0x39c) = func_ov107_020c9e50(func_ov107_020c9440((int)self, 1), data_ov241_020d0cc4);
    for (i = 0; i < 3; i++) {
        ((int *)self)[0xe3 + i] = func_0203b898(func_ov107_020c9440((int)self, 2));
        func_ov107_020c9074((int)self, ((int *)self)[0xe3 + i]);
        ((struct Bit0 *)(((int *)self)[0xe3 + i] + 0x5c))->bit0 = 1;
        *(int *)(((int *)self)[0xe3 + i] + 0x5c) |= 2;
        func_0203b9fc(((int *)self)[0xe3 + i], 0, 0, 1);
        func_0203b9fc(((int *)self)[0xe3 + i], 2, 0, 1);
        func_0203bfb4(*(int *)(self + 0x9c), ((int *)self)[0xe3 + i]);
    }
    *(int *)(self + 0x3a0) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x3a0));
    ((struct Bit0 *)(*(int *)(self + 0x3a0) + 0x5c))->bit0 = 1;
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440((int)self, 3));
    func_0203bfb4(*(int *)(self + 0x3a0), *(int *)(self + 0x388));
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *p = func_ov107_020c319c(self + 0x64);
    *(int *)(self + 0x398) = *p;
    func_0203355c(0x13a);
}
