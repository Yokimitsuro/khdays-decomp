/* func_ov245_020d12e0 = Ov245_ThrownConstruct -- constructor of the ov245 thrown object: installs the handlers (+8 tick,
 * +0xc draw, +0x1c message, +0x30 callback, +0x24 hook, +0x1dc finish), seeds the +0x64 pose
 * (y and scale 2.6) and +0x54/+0x58 (0, 0x100), builds the primary item from pool entry 0x12
 * of the +0x394 pool (+0x384, subscribed, motion halted), the +0x398 sub-item from entry 0x24
 * (attached, bit 1 of +0x5c), and from a pose 1.5 up at scale 2.6 a +0x22c placement (+0x388,
 * bit 1 of its +8 low byte) and a +0x144 placement (+0x38c); +0x390 starts empty. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int scale; } Pose;
typedef void (*Callback)(void);
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov245_020d1454(void);
extern void func_ov245_020d1478(void);
extern void func_ov245_020d14d4(void);
extern void func_ov245_020d15d4(void);
extern void func_ov245_020cc8ec(void);
extern void func_ov245_020d154c(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203c7ac(int item, int a);
struct Ov245Thrown;
extern void func_ov107_020c9074(struct Ov245Thrown *self, int item);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(void *pose);

typedef struct { int x, y, z; } VecP_;

static inline void VecSetP_(VecP_ *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

struct Ov245Thrown {
    int pad0[2];
    Callback tick;        /* 0x08 */
    Callback draw;        /* 0x0c */
    int pad10[3];
    Callback message;     /* 0x1c */
    int pad20;
    Callback hook24;      /* 0x24 */
    int pad28[2];
    Callback cb30;        /* 0x30 */
    int pad34[8];
    int f54;              /* 0x54 */
    int f58;              /* 0x58 */
    int pad5c[2];
    VecP_ pose;           /* 0x64 */
    int scale;            /* 0x70 */
    int pad74[10];
    int pOwner;           /* 0x9c */
    char padA0[0x144 - 0xa0];
    char list144[0x1dc - 0x144];   /* 0x144 */
    Callback cb1dc;       /* 0x1dc */
    char pad1e0[0x22c - 0x1e0];
    char list22c[0x384 - 0x22c];   /* 0x22c */
    int pItem;            /* 0x384 */
    int *pShape;          /* 0x388 */
    int placement;        /* 0x38c */
    int f390;             /* 0x390 */
    int pool;             /* 0x394 */
    int pSub;             /* 0x398 */
};

void func_ov245_020d12e0(struct Ov245Thrown *self) {
    int pool = self->pool;
    Pose pose;
    int *slot;

    /* written twice: the dead copy is dropped after scheduling but spends its budget, which
     * keeps the ROM's register choice for the handler stores (as in Ov245_CarriedConstruct) */
    self->tick = func_ov245_020d1454;
    self->tick = func_ov245_020d1454;
    self->draw = func_ov245_020d1478;
    self->message = func_ov245_020d14d4;
    self->cb30 = func_ov245_020d15d4;
    self->hook24 = func_ov245_020cc8ec;
    self->cb1dc = func_ov245_020d154c;
    self->scale = 0x2991;
    VecSetP_(&self->pose, 0, 0x2991, 0);   /* the constant again, not a re-read of scale */
    self->f54 = 0;
    self->f58 = 0x100;
    self->pItem = func_0203b898(func_ov107_020c9440(pool, 0x12));
    func_0203bfb4(self->pOwner, self->pItem);
    func_0203c7ac(self->pItem, 0);
    self->pSub = func_0203b898(func_ov107_020c9440(pool, 0x24));
    func_ov107_020c9074(self, self->pSub);
    *(int *)(self->pSub + 0x5c) |= 2;
    pose.pos.x = 0;
    pose.pos.y = 0x1800;
    pose.pos.z = 0;
    pose.scale = 0x2991;
    self->pShape = func_01fffca8(self->list22c, 0x10, 0x64);
    *self->pShape = func_ov107_020c319c(&pose);
    ((struct w8 *)((int)self->pShape + 8))->lo |= 2;
    slot = func_01fffca8(self->list144, 4, 0x64);
    self->placement = *slot = func_ov107_020c319c(&pose);
    self->f390 = 0;
}
