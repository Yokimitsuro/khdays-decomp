/* Constructor of the ov260 actor. +0x474 takes bit 2 of the game flags (0204c240, the alternate
 * voice); installs the handlers (+8, +0xc, +0x1c message, +0x30, +0x28, +0x2c, +0x34, +0x1d0, +0x1dc
 * set pose), sets +0x1c9 = 2, the +0x64 pose (scale 1.0) and the +0x1fc bounds. Builds the +0x384
 * body (kit 1 / 0x21 for the variant, else 0 / 0x20 with the +0x390 part), the hit volume (020cc078),
 * the +0x394 bank (clip 2), the +0x410 / +0x414 nodes, the +0x390 part (stance track, +0x424 tag
 * node), the +0x388 shell (0x22) and the +0x38c part (0x37, bit 2), the +0x428 part (0x23), the
 * twelve +0x478 hidden parts (kits of data_ov260_020d2a3c), two placements (+0x418 on the +0x22c
 * pool, +0x41c on the +0x144 pool), the +0x42c / +0x430 helpers and the fifteen +0x434 shards, and
 * loads sound bank 0x17c or 0x174. */
typedef unsigned char u8;
typedef void (*Callback)(void);
typedef struct { int id[12]; } PartKits;
typedef struct { int min[3]; int max[3]; } Bounds;
struct Parts { char pad[0x478]; struct { int obj; int pad; } part[12]; };
struct Ov260Shards { char pad[0x434]; int shards[15]; };

extern void func_ov260_020cc440(void);
extern void func_ov260_020cc4a8(void);
extern void func_ov260_020cc5c4(void);
extern void func_ov260_020ccb90(void);
extern void func_ov260_020cc51c(void);
extern void func_ov260_020cc570(void);
extern void func_ov260_020cc808(void);
extern void func_ov260_020ccbec(void);
extern void func_ov260_020cc8fc(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern void func_ov260_020cc078(char *self);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0202a388(void *list, int b, void *c, int d);
extern void func_0203b9ac(int a, void *list);
extern int func_0203bdfc(int item, const char *name);
extern void func_0203b9fc(int model, int track, int pose, int flag);
extern void func_0203c7ac(int item, int a);
extern int func_0203bee8(int item, int kind, void *name);
extern int func_ov107_020c9e50(void *item, void *name);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *placement);
extern int func_ov260_020d1824(char *self);
extern int func_ov260_020d0a24(char *self);
extern int func_ov260_020d2424(char *self);
extern void func_0203355c(int resourceId);
extern u8 data_0204c240;
extern const PartKits data_ov260_020d2a3c;
extern char data_ov260_020d2aac[];
extern char data_ov260_020d2ab4[];
extern char data_ov260_020d2ac4[];
extern char data_ov260_020d2ac8[];

void func_ov260_020cc0b4(char *self)
{
    PartKits kits = data_ov260_020d2a3c;
    Bounds bounds;
    int i;
    int *slot;

    *(int *)(self + 0x474) = data_0204c240 & 4;
    bounds.min[0] = -0xeea;
    bounds.min[1] = 0x17;
    bounds.min[2] = -0x858;
    bounds.max[0] = bounds.min[0] + 0x1dd3;
    bounds.max[1] = bounds.min[1] + 0x1c27;
    bounds.max[2] = bounds.min[2] + 0xd64;
    *(Callback *)(self + 0x8) = func_ov260_020cc440;
    *(Callback *)(self + 0xc) = func_ov260_020cc4a8;
    *(Callback *)(self + 0x1c) = func_ov260_020cc5c4;
    *(Callback *)(self + 0x30) = func_ov260_020ccb90;
    *(Callback *)(self + 0x28) = func_ov260_020cc51c;
    *(Callback *)(self + 0x2c) = func_ov260_020cc570;
    *(Callback *)(self + 0x34) = func_ov260_020cc808;
    *(Callback *)(self + 0x1d0) = func_ov260_020ccbec;
    *(Callback *)(self + 0x1dc) = func_ov260_020cc8fc;
    *(u8 *)(self + 0x1c9) = 2;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1000;
    *(int *)(self + 0x6c) = 0;
    *(Bounds *)(self + 0x1fc) = bounds;
    if (*(int *)(self + 0x474) != 0) {
        *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 1));
        *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(self, 0x21));
    } else {
        *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
        *(int *)(self + 0x390) = func_0203b898(func_ov107_020c9440(self, 0x20));
    }
    func_ov260_020cc078(self);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0202a388(self + 0x394, *(int *)(*(int *)(self + 0x384) + 0x88), func_ov107_020c9440(self, 2), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), self + 0x394);
    *(int *)(self + 0x410) = func_0203bdfc(*(int *)(self + 0x384), data_ov260_020d2aac);
    *(int *)(self + 0x414) = func_0203bdfc(*(int *)(self + 0x384), data_ov260_020d2ab4);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x390));
    func_0203b9fc(*(int *)(self + 0x390), 1, 0, 0);
    func_0203c7ac(*(int *)(self + 0x390), 0);
    *(int *)(self + 0x424) = func_0203bee8(*(int *)(self + 0x390), 3, data_ov260_020d2ac4);
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(self, 0x22));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(self, 0x37));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    *(int *)(*(int *)(self + 0x38c) + 0x5c) |= 4;
    *(int *)(self + 0x428) = func_ov107_020c9e50(func_ov107_020c9440(self, 0x23), data_ov260_020d2ac8);
    for (i = 0; i < 12; i++) {
        ((struct Parts *)self)->part[i].obj = func_0203b898(func_ov107_020c9440(self, kits.id[i]));
        func_ov107_020c9074(self, ((struct Parts *)self)->part[i].obj);
        *(int *)(((struct Parts *)self)->part[i].obj + 0x5c) |= 2;
    }
    *(int *)(self + 0x418) = (int)func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x418) = func_ov107_020c319c(self + 0x64);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x41c) = *slot = func_ov107_020c319c(self + 0x64);
    *(int *)(self + 0x42c) = func_ov260_020d1824(self);
    *(int *)(self + 0x430) = func_ov260_020d0a24(self);
    for (i = 0; i < 15; i++) {
        ((struct Ov260Shards *)self)->shards[i] = func_ov260_020d2424(self);
    }
    func_0203355c(*(int *)(self + 0x474) != 0 ? 0x17c : 0x174);
}
