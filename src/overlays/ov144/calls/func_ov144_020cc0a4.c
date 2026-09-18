/* Constructor of the ov144 enemy (and its byte-identical twin): installs the handlers (+8 tick,
 * +0xc draw, +0x30/+0x38 hit callbacks, +0x1c message, +0x20/+0x24 callbacks, +0x1dc finish,
 * +0x1e0 callback), sets +0x1c9 to 2, seeds the +0x1fc bounding box, the +0x64 pose (scale
 * 0x1000, y 0x1000), bit 3 of +0x1ae and bit 5 of the +0x60 high byte; builds the primary item
 * from pool entry 0 (subscribed, back-linked into its render object's +0x4c, its named joint
 * resolved into +0x3a0 and the node matrix callback armed with mode 6/3), runs the finish
 * handler once, keeps the named motion handle (+0x394), creates the kind-7 sub-item (+0x388,
 * attached, bits 0/1, channel 2 bound), an effect node (+0x398, subscribed, bit 0) hosting the
 * pool entry 2 item (+0x38c, bit 1), the kind-0 sub-item (+0x3f8, attached, bit 1), a placement
 * on the +0x144 list (+0x390) and loads sound 0x123.
 *
 * MATCH NOTE: the bounding box is assigned field by field before the handlers (max = min +
 * size keeps the ROM's add chains; folded constants become pool loads) and copied as a whole
 * after the sub-state byte; the sub-item/list tail goes through the typed actor view, which
 * keeps the `orr r1` flag store ahead of the list call's argument setup. */
typedef unsigned short u16;

struct Bit0 {
    unsigned bit0 : 1;
};

struct Subitem {
    char pad000[0x5c];
    unsigned int flags5c;
};

struct Ov144Actor {
    char pad000[0x64];
    int camera[4];
    char pad074[0x144 - 0x74];
    char pool144[0x390 - 0x144];
    int poolValue390;
    char pad394[0x3f8 - 0x394];
    struct Subitem *subitem3f8;
};

struct Box {
    int xmin, ymin, zmin;
    int xmax, ymax, zmax;
};

extern void func_ov144_020cc39c(void);
extern void func_ov144_020cc3f8(void);
extern void func_ov144_020ccabc(void);
extern void func_ov144_020cc490(void);
extern void func_ov144_020cc600(void);
extern void func_ov144_020cc570(void);
extern void func_ov144_020cc5cc(void);
extern void func_ov144_020cc440(void);
extern void func_ov144_020ccb08(void);
extern void func_ov144_020cbfc4(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bdfc(int item, const char *name);
extern void func_02014e18(int renderObj, void *cb, int ptr, int timing, int opt);
extern int func_ov107_020c9e50(void *item, const char *name);
extern int *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(int self, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern int func_0203bf44(void);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern void func_0203355c(int id);
extern const char data_ov144_020cdcec[];
extern const char data_ov144_020cdcf8[];

void func_ov144_020cc0a4(char *self)
{
    struct Box box;
    int *p;
    struct Subitem *item;
    struct Ov144Actor *actor = (struct Ov144Actor *)self;
    int pose;

    box.xmin = -0x122d;
    box.ymin = -0xb;
    box.zmin = -0x742;
    box.xmax = box.xmin + 0x23ec;
    box.ymax = box.ymin + 0x1b60;
    box.zmax = box.zmin + 0x2014;
    *(void **)(self + 0x8) = func_ov144_020cc39c;
    *(void **)(self + 0xc) = func_ov144_020cc3f8;
    *(void **)(self + 0x30) = func_ov144_020ccabc;
    *(void **)(self + 0x38) = func_ov144_020cc490;
    *(void **)(self + 0x1c) = func_ov144_020cc600;
    *(void **)(self + 0x20) = func_ov144_020cc570;
    *(void **)(self + 0x24) = func_ov144_020cc5cc;
    *(void **)(self + 0x1dc) = func_ov144_020cc440;
    *(void **)(self + 0x1e0) = func_ov144_020ccb08;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(struct Box *)(self + 0x1fc) = box;
    *(int *)(self + 0x70) = 0x1000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1000;
    *(int *)(self + 0x6c) = 0;
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(char **)(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x4c) = self;
    *(u16 *)(self + 0x3a0) = func_0203bdfc(*(int *)(self + 0x384), data_ov144_020cdcec);
    func_02014e18(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x20, func_ov144_020cbfc4, 0, 6, 3);
    (*(void (**)(char *, int, int))(self + 0x1dc))(self, 0, 1);
    *(int *)(self + 0x394) = func_ov107_020c9e50(func_ov107_020c9440((int)self, 1), data_ov144_020cdcf8);
    *(int *)(self + 0x388) = func_0203b898((void *)((((OS_IsThreadAvailable_0x020c9848()[0x22] + 0x8000) & 0xfffffc) << 7) | 0x80000007));
    ((struct Bit0 *)(*(int *)(self + 0x388) + 0x5c))->bit0 = 1;
    func_ov107_020c9074((int)self, *(int *)(self + 0x388));
    *(int *)(*(int *)(self + 0x388) + 0x5c) |= 2;
    func_0203b9fc(*(int *)(self + 0x388), 2, 0, 1);
    *(int *)(self + 0x398) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x398));
    ((struct Bit0 *)(*(int *)(self + 0x398) + 0x5c))->bit0 = 1;
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440((int)self, 2));
    func_0203bfb4(*(int *)(self + 0x398), *(int *)(self + 0x38c));
    *(int *)(*(int *)(self + 0x38c) + 0x5c) |= 2;
    item = actor->subitem3f8 = (struct Subitem *)func_0203b898((void *)((((OS_IsThreadAvailable_0x020c9848()[0x22] + 0x8000) & 0xfffffc) << 7) | 0x80000000));
    func_ov107_020c9074((int)self, (int)item);
    item->flags5c |= 2;
    p = func_01fffca8(actor->pool144, 4, 0x64);
    pose = func_ov107_020c319c((char *)actor->camera);
    *p = pose;
    actor->poolValue390 = pose;
    func_0203355c(0x123);
}
