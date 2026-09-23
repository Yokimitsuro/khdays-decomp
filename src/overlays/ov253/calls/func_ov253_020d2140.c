/* func_ov253_020d2140 -- queue actor construction: installs the handlers (+8 020d2388, +0xc
 * 020d23d8, +0x20 020d2474, +0x1c 020d24f8, +0x34 020d25e4, +0x30 020d283c, +0x1dc 020d26a8),
 * seeds the +0x54..+0x70 box, raises bits 2-4, 6 of the +0x60 high byte, bits 3-4 of +0x1ae and
 * 3, 7, 11 of +0x1b0, sets the four +0x38c scales to 1.0, builds the +0x384 item from pose
 * 0x1c of the +0x388 pool (subscribed to the +0x9c parent), the +0x3a0 ring object from pose
 * 0x27 (16 entries, drawn by 020d2058, owned here, bit 1 of +0x5c cleared) and its +0x3a4
 * transform, allocates the +0x3e8 pair block whose two effects come from the
 * data_ov253_020d49e0 poses (registered, bit 1 of +0x5c raised), links a +0x144 list slot to
 * the +0x64 pose as +0x3d4, clears the +0x3d8 latch and the queue counters (+0x3e0 sequence 1)
 * and allocates the 16-entry queue table cleared to -1. */
typedef unsigned short u16;
struct Ov253Entry { signed char a; signed char b; short c; };
struct Ov253Queue { char pad[0x3dc]; signed char count; signed char head; signed char tail; char pad3df; short seq; char pad3e2[2]; struct Ov253Entry *table; };
struct Ov253Poses { int w[2]; };
struct Ov253Pair { int pEffect; int pChild; };

extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203c1b0(void *item, int count);
extern void func_ov107_020c9074(char *self, int item);
extern void func_0203c960(void *srt);
extern void *func_0203d15c(int size);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const int data_ov253_020d49e0;
extern void func_ov253_020d2388(void);
extern void func_ov253_020d23d8(void);
extern void func_ov253_020d2474(void);
extern void func_ov253_020d24f8(void);
extern void func_ov253_020d25e4(void);
extern void func_ov253_020d283c(void);
extern void func_ov253_020d26a8(void);
extern void func_ov253_020d2058(void);

void func_ov253_020d2140(char *self) {
    struct Ov253Poses poses = *(const struct Ov253Poses *)((const char *)&data_ov253_020d49e0 + 4);
    int i;
    int *p;

    *(void **)(self + 0x8) = func_ov253_020d2388;
    *(void **)(self + 0xc) = func_ov253_020d23d8;
    *(void **)(self + 0x20) = func_ov253_020d2474;
    *(void **)(self + 0x1c) = func_ov253_020d24f8;
    *(void **)(self + 0x34) = func_ov253_020d25e4;
    *(void **)(self + 0x30) = func_ov253_020d283c;
    *(void **)(self + 0x1dc) = func_ov253_020d26a8;
    /* overwritten first: the dead store is dropped after scheduling but spends the block's
     * scheduling budget (keeps the ROM's unhoisted add further down) */
    *(int *)(self + 0x54) = 0x1000;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0x1000;
    *(int *)(self + 0x70) = 0x4000;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x4000;
    *(int *)(self + 0x6c) = 0;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x5c) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 0x18;
    *(u16 *)(self + 0x100 + 0xb0) |= 0x888;
    *(int *)(self + 0x38c) = 0x1000;
    *(int *)(self + 0x390) = 0x1000;
    *(int *)(self + 0x394) = 0x1000;
    *(int *)(self + 0x398) = 0x1000;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x388), 0x1c));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x3a0) = func_0203c1b0(func_ov107_020c9440(*(int *)(self + 0x388), 0x27), 0x10);
    func_ov107_020c9074(self, *(int *)(self + 0x3a0));
    *(void **)(*(int *)(self + 0x3a0) + 0x6c) = func_ov253_020d2058;
    *(char **)(*(int *)(self + 0x3a0) + 0x84) = self;
    *(int *)(*(int *)(self + 0x3a0) + 0x5c) &= ~2;
    func_0203c960(self + 0x3a4);
    *(struct Ov253Pair **)(self + 0x3e8) = func_0203d15c(0x10);
    for (i = 0; i < 2; i++) {
        (*(struct Ov253Pair **)(self + 0x3e8))[i].pEffect =
            func_0203b898(func_ov107_020c9440(*(int *)(self + 0x388), poses.w[i]));
        func_ov107_020c9074(self, (*(struct Ov253Pair **)(self + 0x3e8))[i].pEffect);
        *(int *)((*(struct Ov253Pair **)(self + 0x3e8))[i].pEffect + 0x5c) |= 2;
    }
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *p = func_ov107_020c319c(self + 0x64);
    *(int *)(self + 0x3d4) = *p;
    *(int *)(self + 0x3d8) = 0;
    ((struct Ov253Queue *)self)->count = 0;
    ((struct Ov253Queue *)self)->head = 0;
    ((struct Ov253Queue *)self)->tail = 0;
    ((struct Ov253Queue *)self)->seq = 1;
    ((struct Ov253Queue *)self)->table = func_0203d15c(0x40);
    for (i = 0; i < 16; i++) {
        ((struct Ov253Queue *)self)->table[i].a = -1;
        ((struct Ov253Queue *)self)->table[i].b = -1;
        ((struct Ov253Queue *)self)->table[i].c = -1;
    }
}
