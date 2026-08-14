typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    char pad_0000[0x5c];
    u32 flags_005c;
} Ov169Subitem;

typedef struct {
    int value;
    int pad_0004;
    u32 flags : 8;
} Ov169PoolEntry;

typedef struct {
    char pad_0000[0x08];
    void (*callback_0008)(void);
    void (*callback_000c)(void);
    char pad_0010[0x0c];
    void (*callback_001c)(void);
    char pad_0020[0x10];
    void (*callback_0030)(void);
    char pad_0034[0x20];
    int field_0054;
    int field_0058;
    char pad_005c[0x04];
    u16 flags_0060;
    char pad_0062[0x02];
    int field_0064;
    char pad_0068[0x08];
    int field_0070;
    char pad_0074[0x28];
    Ov169Subitem *subscriber_009c;
    char pad_00a0[0x10e];
    u16 flags_01ae;
    char pad_01b0[0x20];
    void (*callback_01d0)(void);
    char pad_01d4[0x58];
    char pool_022c[0x158];
    Ov169Subitem *subitem_0384;
    Ov169PoolEntry *poolEntry_0388;
    int owner_038c;
} Ov169Object;

extern void *func_ov107_020c9440(int owner, int index);
extern Ov169Subitem *func_0203b898(void *item);
extern void func_0203bfb4(Ov169Subitem *subscriber, Ov169Subitem *item);
extern void func_0203b9fc(Ov169Subitem *item, int state, int zero, int enabled);
extern void func_0203c7ac(Ov169Subitem *item, int value);
extern Ov169PoolEntry *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *field);
extern void func_ov176_020d1fe4(void);
extern void func_ov176_020d2000(void);
extern void WM_EndKeySharing_0x020d2038(void);
extern void func_ov176_020d20cc(void);
extern void func_ov176_020d2044(void);

void func_ov176_020d1e84(Ov169Object *self) {
    int owner = self->owner_038c;
    u16 v;

    self->callback_0008 = func_ov176_020d1fe4;
    self->callback_000c = func_ov176_020d2000;
    self->callback_001c = WM_EndKeySharing_0x020d2038;
    self->callback_0030 = func_ov176_020d20cc;
    self->callback_01d0 = func_ov176_020d2044;
    v = self->flags_0060;
    self->flags_0060 =
        (u16)((v & ~0xff00) | (((((u32)v << 0x10) >> 0x18 | 0x4e) << 0x18) >> 0x10));
    self->flags_01ae |= 4;
    self->field_0070 = 0x600;
    self->field_0054 = 0;
    self->field_0058 = 0;
    self->subscriber_009c->flags_005c |= 4;
    self->subitem_0384 = func_0203b898(func_ov107_020c9440(owner, 3));
    func_0203bfb4(self->subscriber_009c, self->subitem_0384);
    func_0203b9fc(self->subitem_0384, 0, 0, 1);
    func_0203b9fc(self->subitem_0384, 2, 0, 1);
    func_0203b9fc(self->subitem_0384, 4, 0, 1);
    func_0203b9fc(self->subitem_0384, 1, 0, 1);
    func_0203c7ac(self->subitem_0384, 0);
    self->poolEntry_0388 = func_01fffca8(self->pool_022c, 0x10, 100);
    self->poolEntry_0388->value = func_ov107_020c319c(&self->field_0064);
    self->poolEntry_0388->flags |= 2;
}
