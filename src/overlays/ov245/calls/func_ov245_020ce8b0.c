/* func_ov245_020ce8b0 -- constructor of the ov245 carried object. */
typedef struct { int x, y, z; } Vec3;
typedef void (*Callback)(void);
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

struct Ov245Obj {
    int pad0[2];
    Callback tick;        /* 0x08 */
    Callback draw;        /* 0x0c */
    int pad10[3];
    Callback message;     /* 0x1c */
    int pad20;
    Callback hook24;      /* 0x24 */
    int pad28[2];
    Callback cb30;        /* 0x30 */
    int pad34[11];
    u16 flags60;          /* 0x60 */
    u16 pad62;
    Vec3 pose;            /* 0x64 */
    int scale;            /* 0x70 */
    int pad74[10];
    int pOwner;           /* 0x9c */
    char padA0[0x1ae - 0xa0];
    u16 flags1ae;         /* 0x1ae */
    char pad1b0[0x1d0 - 0x1b0];
    Callback hit;         /* 0x1d0 */
    char pad1d4[0x384 - 0x1d4];
    int pItem;            /* 0x384 */
    int *pPlacement;      /* 0x388 */
    int p38c;             /* 0x38c */
    int pool;             /* 0x390 */
    int pSub;             /* 0x394 */
};

extern void func_ov245_020cea24(void);
extern void func_ov245_020cea48(void);
extern void func_ov245_020cea80(void);
extern void func_ov245_020cebd4(void);
extern void func_ov245_020cc8ec(void);
extern void func_ov245_020ceb34(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int flag);
extern void func_0203c7ac(int item, int a);
extern void func_ov107_020c9074(struct Ov245Obj *self, int item);
extern int *func_01fffca8(void *list, int stride, int max);
extern int func_ov107_020c319c(void *pose);
extern const Vec3 data_02041dc8;

void func_ov245_020ce8b0(struct Ov245Obj *self) {
    int pool = self->pool;

    /* written three times: the repeats are dead stores dropped after scheduling that use up its
     * budget, so the rest of the constructor keeps the ROM's order (as in Ov261_EnemyConstruct) */
    self->tick = func_ov245_020cea24;
    self->tick = func_ov245_020cea24;
    self->tick = func_ov245_020cea24;
    self->draw = func_ov245_020cea48;
    self->message = func_ov245_020cea80;
    self->cb30 = func_ov245_020cebd4;
    self->hook24 = func_ov245_020cc8ec;
    self->hit = func_ov245_020ceb34;
    {
        u16 hw = self->flags60;
        self->flags60 = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x56) << 0x18) >> 0x10);
    }
    self->flags1ae |= 0xc;
    self->scale = 0x2000;
    self->pose = data_02041dc8;
    *(int *)(self->pOwner + 0x5c) |= 4;
    self->pItem = func_0203b898(func_ov107_020c9440(pool, 0x16));
    func_0203bfb4(self->pOwner, self->pItem);
    func_0203b9fc(self->pItem, 0, 0, 1);
    func_0203c7ac(self->pItem, 0);
    self->pSub = func_0203b898(func_ov107_020c9440(pool, 0x1b));
    func_ov107_020c9074(self, self->pSub);
    *(int *)(self->pSub + 0x5c) |= 2;
    self->pPlacement = func_01fffca8((char *)self + 0x22c, 0x10, 0x64);
    *self->pPlacement = func_ov107_020c319c(&self->pose);
    ((struct w8 *)(self->pPlacement + 2))->lo |= 2;
    self->p38c = 0;
}
