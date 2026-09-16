/* Constructs the ov107 status-effect node: base-init via 020c2a9c, set flag bit 2, install its
 * callbacks, look up its table entry, create two effect groups, reset three child lists, then
 * load the burn/frost/shock effect models plus one more, attach each to the second group and
 * point each back at this node. */

typedef unsigned short u16;
typedef void (*Callback)(void);

typedef struct List28 { int w[10]; } List28; /* initialised by func_01fffc24 */

typedef struct EffectNode {
    char pad00[0x5c];
    int flags;                 /* 0x5c */
    char pad60[0x6c - 0x60];
    Callback onBusy;           /* 0x6c */
    char pad70[0x84 - 0x70];
    void *owner;               /* 0x84 */
} EffectNode;

typedef struct StatusNode {
    u16 flags;                 /* 0x00 */
    char pad02[0x8 - 0x2];
    Callback field_08;         /* 0x08 */
    Callback field_0c;         /* 0x0c */
    Callback field_10;         /* 0x10 */
    Callback field_14;         /* 0x14 */
    Callback field_18;         /* 0x18 */
    Callback field_1c;         /* 0x1c */
    char pad20[0x40 - 0x20];
    int field_40;              /* 0x40 */
    char pad44[0x70 - 0x44];
    Callback field_70;         /* 0x70 */
    Callback field_74;         /* 0x74 */
    int tableIndex;            /* 0x78 */
    void *tableEntry;          /* 0x7c */
    List28 list80;             /* 0x80 */
    List28 lista8;             /* 0xa8 */
    List28 listd0;             /* 0xd0 */
    int field_f8;              /* 0xf8 */
    char padfc[0x100 - 0xfc];
    EffectNode *group100;      /* 0x100 */
    EffectNode *group104;      /* 0x104 */
    EffectNode *burnFx;        /* 0x108 */
    EffectNode *frostFx;       /* 0x10c */
    EffectNode *shockFx;       /* 0x110 */
    EffectNode *field_114;     /* 0x114 */
} StatusNode;

extern void func_ov107_020c2a9c(StatusNode *node);
extern void *func_0202bfa0(int idx);
extern EffectNode *func_0203bf44(void);
extern void func_01fffc24(List28 *list);
extern EffectNode *func_0203b898(void *modelName);
extern int func_0203bfb4(EffectNode *group, EffectNode *child);
extern void func_0203b9fc(EffectNode *node, u16 track, short blend, unsigned char value);
typedef struct Ov107Global {
    char pad00[0x88];
    int field_88;              /* 0x88 */
} Ov107Global;

extern Ov107Global *OS_IsThreadAvailable_0x020c9848(void);

extern void func_ov107_020c24f0(void);
extern void func_ov107_020c2548(void);
extern void func_ov107_020c26d8(void);
extern void func_ov107_020c26f8(void);
extern void func_ov107_020c2768(void);
extern void func_ov107_020c27e8(void);
extern void func_ov107_020c22c4(void);
extern void func_ov107_020c2364(void);
extern void func_ov107_020c2a3c(void);
extern void func_ov107_020c2a54(void);
extern void func_ov107_020c2a6c(void);
extern void func_ov107_020c2a84(void);

extern char data_ov107_020cb968[]; /* "ba/ef/s_burn.p.z" */
extern char data_ov107_020cb97c[]; /* "ba/ef/s_frost.p.z" */
extern char data_ov107_020cb990[]; /* "ba/ef/s_shock.p.z" */

void func_ov107_020c207c(StatusNode *self, int tableIndex)
{
    EffectNode *fx;

    func_ov107_020c2a9c(self);

    self->flags |= 4;
    self->field_08 = func_ov107_020c24f0;
    self->field_0c = func_ov107_020c2548;
    self->field_10 = func_ov107_020c26d8;
    self->field_14 = func_ov107_020c26f8;
    self->field_18 = func_ov107_020c2768;
    self->field_1c = func_ov107_020c27e8;
    self->field_70 = func_ov107_020c22c4;
    self->field_74 = func_ov107_020c2364;
    self->tableIndex = tableIndex;
    self->tableEntry = func_0202bfa0((u16)self->tableIndex);

    self->field_40 |= 4;

    self->group100 = func_0203bf44();
    self->group104 = func_0203bf44();
    self->group104->flags |= 2;

    self->field_f8 &= ~0xf;

    func_01fffc24(&self->list80);
    func_01fffc24(&self->lista8);
    func_01fffc24(&self->listd0);

    fx = func_0203b898(data_ov107_020cb968);
    self->burnFx = fx;
    func_0203bfb4(self->group104, fx);
    func_0203b9fc(fx, 0, 0, 1);
    func_0203b9fc(fx, 2, 0, 1);
    func_0203b9fc(fx, 3, 0, 1);
    fx->onBusy = func_ov107_020c2a3c;
    fx->owner = self;

    fx = func_0203b898(data_ov107_020cb97c);
    self->frostFx = fx;
    func_0203bfb4(self->group104, fx);
    func_0203b9fc(fx, 0, 0, 1);
    func_0203b9fc(fx, 2, 0, 1);
    fx->onBusy = func_ov107_020c2a54;
    fx->owner = self;

    fx = func_0203b898(data_ov107_020cb990);
    self->shockFx = fx;
    func_0203bfb4(self->group104, fx);
    func_0203b9fc(fx, 0, 0, 1);
    func_0203b9fc(fx, 2, 0, 1);
    fx->onBusy = func_ov107_020c2a6c;
    fx->owner = self;

    fx = func_0203b898((void *)((((OS_IsThreadAvailable_0x020c9848()->field_88 + 0x8000)
                                  & 0xfffffc) << 7) | 0x80000008));
    self->field_114 = fx;
    func_0203bfb4(self->group104, fx);
    fx->onBusy = func_ov107_020c2a84;
    fx->owner = self;
}
