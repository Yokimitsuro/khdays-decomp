/* func_ov245_020cc078 -- constructor of the ov245 boss: installs the handlers (+8 tick, +0xc
 * draw, +0x1c message, +0x30 / +0x28 / +0x2c / +0x20 callbacks, +0x24 hook, +0x1d0 hit, +0x1dc
 * finish), kind byte 2 at +0x1c9, the +0x64 pose at scale 4.75, bit 5 of the +0x60 high byte and
 * bits 3-4 of +0x1ae; builds the primary item from pool entry 0 (+0x384, callback 020cbfc8 at
 * +0x74, owner at +0x84, subscribed), binds entry 1 as its motion (+0x390 track, slot 0xc) and
 * four named joints (+0x448..+0x454), the two +0x388 items from entries 0xb / 0xc (subscribed,
 * bit 0 of +0x5c), the +0x4dc sub-item from entry 0x20 (attached, bit 1), the named motions of
 * entries 0xd / 0xe (+0x4c8 / +0x4cc), a +0x3bc query block (origin, the three axes, 8.0 and
 * 4.75 x 2) shaping two placements (+0x3b4 on the +0x22c list, +0x3b8 on +0x144), registers
 * the +0x458 spawner (kind 4), nine +0x3fc slots (020ce87c), three +0x420 parts (020cf284), three
 * +0x43c riders (020d54f0), the four +0x42c..+0x438 helpers and loads sound 0x15a. */
typedef struct { int x, y, z; } Vec3;
typedef void (*Callback)(void);
typedef unsigned short u16;
struct Flags5c { int bit0 : 1; };
struct Ov245Track { char pad[0x88]; int track; };
struct Ov245Query { Vec3 pos; Vec3 a; Vec3 b; Vec3 c; int w0; int w1; int w2; };
struct Ov245Boss {
    char pad[0x388];
    int items[2];          /* 0x388 */
    char pad390[0x3fc - 0x390];
    int slots[9];          /* 0x3fc */
    int parts[3];          /* 0x420 */
    int helpers[4];        /* 0x42c */
    int riders[3];         /* 0x43c */
};

extern void func_ov245_020cc434(void);
extern void func_ov245_020cc494(void);
extern void func_ov245_020cc6e4(void);
extern void func_ov245_020cc918(void);
extern void func_ov245_020cc54c(void);
extern void func_ov245_020cc638(void);
extern void func_ov245_020cc810(void);
extern void func_ov245_020cc86c(void);
extern void func_ov245_020cc974(void);
extern void func_ov245_020cc794(void);
extern void func_ov245_020cbfc8(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0202a388(void *track, int model, void *resource, int slot);
extern void func_0203b9ac(int item, void *track);
extern int func_0203bee8(int item, int kind, const char *name);
extern void func_ov107_020c9074(int self, int item);
extern int func_ov107_020c9e50(void *item, const char *name);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c32b8(struct Ov245Query *query);
extern void func_ov107_020c2f94(int kind, void *spawner);
extern int func_ov245_020ce87c(int self);
extern int func_ov245_020cf284(int self, int index);
extern int func_ov245_020d54f0(int self, void *spawner);
extern int func_ov245_020d12ac(int self);
extern int func_ov245_020d1e1c(int self);
extern int func_ov245_020d3804(int self);
extern int func_ov245_020d48c0(int self);
extern void func_0203355c(int id);
extern const char data_ov245_020d71ec[];
extern const char data_ov245_020d71f4[];
extern const char data_ov245_020d7200[];
extern const char data_ov245_020d720c[];
extern const char data_ov245_020d7218[];
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;

void func_ov245_020cc078(int selfArg) {
    char *self = (char *)selfArg;   /* codegen: the local copy keeps the query-block copies and address temps in ROM order */
    int *slot;
    int item;
    int i;

    *(Callback *)(self + 0x8) = func_ov245_020cc434;
    *(Callback *)(self + 0xc) = func_ov245_020cc494;
    *(Callback *)(self + 0x1c) = func_ov245_020cc6e4;
    *(Callback *)(self + 0x30) = func_ov245_020cc918;
    *(Callback *)(self + 0x28) = func_ov245_020cc54c;
    *(Callback *)(self + 0x2c) = func_ov245_020cc638;
    *(Callback *)(self + 0x20) = func_ov245_020cc810;
    *(Callback *)(self + 0x24) = func_ov245_020cc86c;
    *(Callback *)(self + 0x1d0) = func_ov245_020cc974;
    *(Callback *)(self + 0x1dc) = func_ov245_020cc794;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(int *)(self + 0x70) = 0x4c00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x4c00;
    *(int *)(self + 0x6c) = 0;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    *(Callback *)(*(int *)(self + 0x384) + 0x74) = func_ov245_020cbfc8;
    *(int *)(*(int *)(self + 0x384) + 0x84) = self;
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0202a388((void *)(self + 0x390), ((struct Ov245Track *)*(int *)(self + 0x384))->track,
                  func_ov107_020c9440(self, 1), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), (void *)(self + 0x390));
    *(int *)(self + 0x448) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov245_020d71ec);
    *(int *)(self + 0x44c) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov245_020d71f4);
    *(int *)(self + 0x450) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov245_020d7200);
    *(int *)(self + 0x454) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov245_020d720c);
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(self, 0xb));
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(self, 0xc));
    for (i = 0; i < 2; i++) {
        func_0203bfb4(*(int *)(self + 0x9c), ((struct Ov245Boss *)self)->items[i]);
        ((struct Flags5c *)(((struct Ov245Boss *)self)->items[i] + 0x5c))->bit0 = 1;
    }
    item = *(int *)(self + 0x4dc) = func_0203b898(func_ov107_020c9440(self, 0x20));
    func_ov107_020c9074(self, item);
    *(int *)(item + 0x5c) |= 2;
    *(int *)(self + 0x4c8) = func_ov107_020c9e50(func_ov107_020c9440(self, 0xd), data_ov245_020d7218);
    *(int *)(self + 0x4cc) = func_ov107_020c9e50(func_ov107_020c9440(self, 0xe), data_ov245_020d7218);
    *(Vec3 *)(self + 0x3bc) = data_02041dc8;
    *(Vec3 *)(self + 0x3c8) = data_02042270;
    *(Vec3 *)(self + 0x3d4) = data_02042264;
    *(Vec3 *)(self + 0x3e0) = data_02042258;
    *(int *)(self + 0x3ec) = 0x8000;
    *(int *)(self + 0x3f0) = 0x4c00;
    *(int *)(self + 0x3f4) = 0x4c00;
    *(int **)(self + 0x3b4) = func_01fffca8((void *)(self + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x3b4) = func_ov107_020c32b8((struct Ov245Query *)(self + 0x3bc));
    slot = func_01fffca8((void *)(self + 0x144), 4, 0x64);
    *(int *)(self + 0x3b8) = *slot = func_ov107_020c32b8((struct Ov245Query *)(self + 0x3bc));
    func_ov107_020c2f94(4, (void *)(self + 0x58 + 0x400));
    for (i = 0; i < 9; i++) {
        ((struct Ov245Boss *)self)->slots[i] = func_ov245_020ce87c(self);
    }
    for (i = 0; i < 3; i++) {
        ((struct Ov245Boss *)self)->parts[i] = func_ov245_020cf284(self, i);
    }
    for (i = 0; i < 3; i++) {
        ((struct Ov245Boss *)self)->riders[i] = func_ov245_020d54f0(self, (void *)(self + 0x58 + 0x400));
    }
    *(int *)(self + 0x42c) = func_ov245_020d12ac(self);
    *(int *)(self + 0x430) = func_ov245_020d1e1c(self);
    *(int *)(self + 0x434) = func_ov245_020d3804(self);
    *(int *)(self + 0x438) = func_ov245_020d48c0(self);
    func_0203355c(0x15a);
}
