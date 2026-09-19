typedef unsigned short u16;

struct Box {
    int xmin;
    int ymin;
    int zmin;
    int xmax;
    int ymax;
    int zmax;
};

struct Ov299Actor {
    char pad000[0x28];
    void *fn28;
    void *fn2c;
    void *fn30;
    char pad034[4];
    void *fn38;
    char pad03c[0x24];
    u16 flags60;
    char pad062[2];
    int field64;
    int scale68;
    int field6c;
    int scale70;
    char pad074[0x13a];
    u16 flags1ae;
    char pad1b0[0x19];
    unsigned char state1c9;
    char pad1ca[0x32];
    struct Box box;
    char pad214[0x170];
    int children[3];
    int scale390;
};

extern void func_ov299_020d3960(void);
extern void func_ov299_020d399c(void);
extern void func_ov299_020d39d8(void);
extern void func_ov299_020d39e4(void);
extern int func_ov299_020d3d9c(struct Ov299Actor *self);
extern void func_0203355c(int id);

void func_ov299_020d3844(struct Ov299Actor *self)
{
    struct Box box;
    u16 *hw;
    unsigned int field;
    unsigned int result;
    register int minX;
    int scale;
    int i;

    self->fn30 = func_ov299_020d39e4;
    self->fn28 = func_ov299_020d3960;
    self->fn2c = func_ov299_020d399c;
    self->fn38 = func_ov299_020d39d8;
    self->state1c9 = 2;

    hw = &self->flags60;
    field = *hw;
    result = field & ~0xff00 |
        (((((unsigned int)field << 16) >> 24 | 0xce) << 24) >> 16);

    minX = -0xeea;
    box.xmin = -0xeea;
    box.ymin = 0x17;
    box.zmin = -0x858;
    box.xmax = box.xmin + 0x1dd3;
    box.ymax = box.ymin + 0x1c27;
    box.zmax = box.zmin + 0xd64;

    *hw = result;
    self->flags1ae |= 0x11;
    scale = self->scale70 = 0x1000;
    self->field64 = 0;
    self->scale68 = scale;
    self->field6c = 0;
    self->box = box;

    for (i = 0; i < 3; i++)
        self->children[i] = func_ov299_020d3d9c(self);

    func_0203355c(0x170);
    self->scale390 = 0x1000;
}
