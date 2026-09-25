/* func_ov245_020cf2f0 -- constructor of the ov245 carrier actor: installs the handlers (+8 tick,
 * +0xc draw, +0x1c message, +0x30 / +0x28 / +0x2c / +0x34 / +0x20 callbacks, +0x24 hook, +0x1d0
 * hit, +0x1dc finish), raises bits 1-3 of the +0x60 high byte and bits 2, 3, 7 and 11 of +0x1b0,
 * seeds the +0x64 pose at scale 1.0, builds the primary item from pool entry 0x10 of the +0x3dc
 * pool (+0x384, subscribed, motion halted) and its named joint (+0x3a0, kind 3), two items from
 * the shared +0x88 model base (kinds 0 and 3, +0x3e0 / +0x3e8) and one from entry 0x1a (+0x3f0),
 * all three attached (bit 1 of +0x5c), two placements from the +0x64 pose (+0x388 on the +0x22c
 * list with bit 1 of its +8 low byte, +0x38c on the +0x144 list) and three +0x394 slots (020d07f0). */
typedef void (*Callback)(void);
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };
struct Ov245Slot { int pItem; int pad4; };
struct Ov245Self { char pad[0x3e0]; struct Ov245Slot slots[3]; };
struct Ov245Nodes { char pad[0x394]; int nodes[3]; };

extern void func_ov245_020cf534(void);
extern void func_ov245_020cf574(void);
extern void func_ov245_020cf698(void);
extern void func_ov245_020cf9b8(void);
extern void func_ov245_020cf620(void);
extern void func_ov245_020cf65c(void);
extern void func_ov245_020cf7f4(void);
extern void func_ov245_020cf870(void);
extern void func_ov245_020cf8cc(void);
extern void func_ov245_020cfa14(void);
extern void func_ov245_020cf838(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203c7ac(int item, int a);
extern int func_0203bee8(int item, int kind, const char *name);
extern void *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9074(int self, int item);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(void *pose);
extern int func_ov245_020d07f0(int self);
extern const char data_ov245_020d7220[];

typedef struct { int x, y, z; } Vec3;

static inline void VEC_Set(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov245_020cf2f0(int selfArg) {
    char *self = (char *)selfArg;
    int pool = *(int *)(self + 0x3dc);
    int *slot;
    int i;
    void *os;

    *(Callback *)(self + 0x8) = func_ov245_020cf534;
    *(Callback *)(self + 0xc) = func_ov245_020cf574;
    *(Callback *)(self + 0x1c) = func_ov245_020cf698;
    *(Callback *)(self + 0x30) = func_ov245_020cf9b8;
    *(Callback *)(self + 0x28) = func_ov245_020cf620;
    *(Callback *)(self + 0x2c) = func_ov245_020cf65c;
    *(Callback *)(self + 0x34) = func_ov245_020cf7f4;
    *(Callback *)(self + 0x20) = func_ov245_020cf870;
    *(Callback *)(self + 0x24) = func_ov245_020cf8cc;
    *(Callback *)(self + 0x1d0) = func_ov245_020cfa14;
    *(Callback *)(self + 0x1dc) = func_ov245_020cf838;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0xe) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xb0) |= 0x88c;
    *(int *)(self + 0x70) = 0x1000;
    VEC_Set((Vec3 *)(self + 0x64), 0, *(int *)(self + 0x70), 0);
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 0x10));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x3a0) = func_0203bee8(*(int *)(self + 0x384), 3, data_ov245_020d7220);
    os = OS_IsThreadAvailable_0x020c9848();
    ((struct Ov245Self *)self)->slots[0].pItem =
        func_0203b898((void *)((((*(int *)((char *)os + 0x88) + 0x8000) & 0x00fffffc) << 7) | 0x80000000));
    os = OS_IsThreadAvailable_0x020c9848();
    ((struct Ov245Self *)self)->slots[1].pItem =
        func_0203b898((void *)((((*(int *)((char *)os + 0x88) + 0x8000) & 0x00fffffc) << 7) | 0x80000003));
    ((struct Ov245Self *)self)->slots[2].pItem = func_0203b898(func_ov107_020c9440(pool, 0x1a));
    for (i = 0; i < 3; i++) {
        func_ov107_020c9074(self, ((struct Ov245Self *)self)->slots[i].pItem);
        *(int *)(((struct Ov245Self *)self)->slots[i].pItem + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = func_01fffca8((void *)(self + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c((void *)(self + 0x64));
    ((struct w8 *)(*(int *)(self + 0x388) + 8))->lo |= 2;
    slot = func_01fffca8((void *)(self + 0x144), 4, 0x64);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c319c((void *)(self + 0x64));
    for (i = 0; i < 3; i++) {
        ((struct Ov245Nodes *)self)->nodes[i] = func_ov245_020d07f0(self);
    }
}
