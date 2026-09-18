/* Constructor of the ov297 enemy: installs the handlers (+8 tick, +0xc draw, +0x1c message,
 * +0x30 callback, +0x28/+0x2c veneers, +0x1d0 hit, +0x1dc animation switch), sets +0x1c9 to 2,
 * bit 9 of +0x1ae, the +0x64 pose (scale 0x1000, y 0x1000) and the +0x1fc bounding box; builds
 * the pool entry 0/1 items (+0x384/+0x388, subscribed), the two sub-items of the pool entries
 * listed by the overlay's +0x5690 pair (+0x398/+0x3a0, attached, bit 1), two placements on the
 * +0x22c/+0x144 lists (+0x38c/+0x390) and loads sound 0x176.
 *
 * MATCH NOTE: the pool index pair is a `const` global copied into a local array, which hoists
 * the pair load above the handler stores and parks the values on the stack for the loop. */
typedef unsigned short u16;

struct Subitem {
    char pad000[0x5c];
    unsigned int flags5c;
};

struct Box {
    int xmin, ymin, zmin;
    int xmax, ymax, zmax;
};

struct SubSlot {
    int item;
    int pad4;
};

struct Ov297Actor {
    char pad000[0x64];
    int camera[4];
    char pad074[0x144 - 0x74];
    char pool144[0x390 - 0x144];
    int poolValue390;
    char pad394[4];
    struct SubSlot subs[2];
};

extern void func_ov297_020d3a3c(void);
extern void func_ov297_020d3a7c(void);
extern void func_ov297_020d3af4(void);
extern void func_ov297_020d3d90(void);
extern void WM_EndKeySharing_0x020d3adc(void);
extern void WM_EndKeySharing_0x020d3ae8(void);
extern void func_ov297_020d3dec(void);
extern void func_ov297_020d3cb4(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_ov107_020c9074(int self, int item);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern void func_0203355c(int id);
extern const int data_ov297_020d5690[2];

void func_ov297_020d3844(char *self)
{
    struct Box box;
    int *p;
    int pools[2];
    int i;
    struct Ov297Actor *actor = (struct Ov297Actor *)self;
    int pose;

    pools[0] = data_ov297_020d5690[0];
    pools[1] = data_ov297_020d5690[1];
    box.xmin = -0xeea;
    box.ymin = 0x17;
    box.zmin = -0x858;
    box.xmax = box.xmin + 0x1dd3;
    box.ymax = box.ymin + 0x1c27;
    box.zmax = box.zmin + 0xd64;
    *(void **)(self + 0x8) = func_ov297_020d3a3c;
    *(void **)(self + 0xc) = func_ov297_020d3a7c;
    *(void **)(self + 0x1c) = func_ov297_020d3af4;
    *(void **)(self + 0x30) = func_ov297_020d3d90;
    *(void **)(self + 0x28) = WM_EndKeySharing_0x020d3adc;
    *(void **)(self + 0x2c) = WM_EndKeySharing_0x020d3ae8;
    *(void **)(self + 0x1d0) = func_ov297_020d3dec;
    *(void **)(self + 0x1dc) = func_ov297_020d3cb4;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(u16 *)(self + 0x100 + 0xae) |= 0x200;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1000;
    *(int *)(self + 0x6c) = 0;
    *(struct Box *)(self + 0x1fc) = box;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440((int)self, 1));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    for (i = 0; i < 2; i++) {
        actor->subs[i].item = func_0203b898(func_ov107_020c9440((int)self, pools[i]));
        func_ov107_020c9074((int)self, actor->subs[i].item);
        *(int *)(actor->subs[i].item + 0x5c) |= 2;
    }
    *(int **)(self + 0x38c) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x38c) = func_ov107_020c319c((char *)actor->camera);
    p = func_01fffca8(actor->pool144, 4, 0x64);
    pose = (*p = func_ov107_020c319c((char *)actor->camera));
    actor->poolValue390 = pose;
    func_0203355c(0x176);
}
