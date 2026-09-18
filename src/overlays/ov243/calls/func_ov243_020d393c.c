/* Constructor of the ov243 enemy (variant of the ov241/242 constructor): installs the handlers
 * (+8 tick, +0xc draw, +0x30/+0x38 hit callbacks, +0x1dc finish), sets +0x1c9 to 2, seeds the
 * +0x64 pose (scale 0x800, y 0x800), bit 3 of +0x1ae and bit 5 of the +0x60 high byte; builds
 * the primary item from pool entry 0, resolves the "Bone_head" joint into the +0x3a0 id triple,
 * back-links the actor into the render object's +0x4c and arms the joint callback (020d3844,
 * mode 0/6/3), translates the item's +4 placement by (0, 0x200, 0), keeps the "move" motion
 * handle (+0x390), creates an effect node (+0x394, subscribed, bit 0) hosting the kind-2 item
 * (+0x388), a placement on the +0x144 list (+0x38c) and loads sound 0x13b. */
typedef unsigned short u16;

struct Bit0 {
    unsigned bit0 : 1;
};

struct Names {
    const char *a;
    const char *b;
    const char *c;
};

extern void func_ov243_020d3b18(void);
extern void func_ov243_020d3b64(void);
extern void func_ov243_020d3c48(void);
extern void func_ov243_020d3bdc(void);
extern void func_ov243_020d3bac(void);
extern void func_ov243_020d3844(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bdfc(int item, const char *name);
extern void func_02014e18(int renderObj, void *cb, int ptr, int timing, int opt);
extern void func_0203ca14(void *placement, int x, int y, int z);
extern int func_ov107_020c9e50(void *item, const char *name);
extern int func_0203bf44(void);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern void func_0203355c(int id);
extern struct Names data_ov243_020d4748;
extern const char data_ov243_020d4778[];

void func_ov243_020d393c(char *self)
{
    struct Names names;
    int i;
    int *p;

    *(void **)(self + 0x8) = func_ov243_020d3b18;
    *(void **)(self + 0xc) = func_ov243_020d3b64;
    *(void **)(self + 0x30) = func_ov243_020d3c48;
    *(void **)(self + 0x38) = func_ov243_020d3bdc;
    *(void **)(self + 0x1dc) = func_ov243_020d3bac;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(int *)(self + 0x70) = 0x800;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x800;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    names = data_ov243_020d4748;
    for (i = 0; i < 3; i++) {
        if (((const char **)&names)[i] != 0) {
            ((u16 *)self)[0x1d0 + i] = func_0203bdfc(*(int *)(self + 0x384), ((const char **)&names)[i]);
        }
    }
    *(char **)(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x4c) = self;
    func_02014e18(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x20, func_ov243_020d3844, 0, 6, 3);
    func_0203ca14((void *)(*(int *)(self + 0x384) + 4), 0, 0x200, 0);
    *(int *)(self + 0x390) = func_ov107_020c9e50(func_ov107_020c9440((int)self, 1), data_ov243_020d4778);
    *(int *)(self + 0x394) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x394));
    ((struct Bit0 *)(*(int *)(self + 0x394) + 0x5c))->bit0 = 1;
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440((int)self, 2));
    func_0203bfb4(*(int *)(self + 0x394), *(int *)(self + 0x388));
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *p = func_ov107_020c319c(self + 0x64);
    *(int *)(self + 0x38c) = *p;
    func_0203355c(0x13b);
}
