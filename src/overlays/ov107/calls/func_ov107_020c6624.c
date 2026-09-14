/* Constructs an AiState on top of the base actor node (func_ov107_020c3c74): sets flag 0x40,
 * installs this subclass's callbacks, binds the state data table `data` at +0x1a0, seeds the
 * scale/timer fields, initialises the two lists at +0x22c/+0x260, attaches the +0x3c object and
 * the +0x1a8 item, then runs the record-load callbacks at +0x1ec/+0x1f0 and the +0x18c hook.
 * With a table bound, it creates attachment slot 6 for an entry of kind 4, slots 5 and 7 for an
 * entry of kind 8, and otherwise slot 7 when any field_24 value exceeds 0x100; every created
 * item gets func_ov107_020c65d8 at +0x6c, and slot 7's item points back at this state at +0x84.
 *
 * Partial layouts: only offsets this function and the landed callbacks establish.
 * field_310 is signed: the ROM stores it as -1, derived from the preceding constant 2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct { int x, y, z; } Vec3;

typedef struct AiState AiState;
typedef struct CreatedItem CreatedItem;

struct CreatedItem {
    char pad000[0x5c];
    u32 flags_5c;
    char pad060[0xc];
    void (*field_6c)(CreatedItem *self, int region);
    char pad070[0x14];
    AiState *field_84;
};

typedef struct {
    unsigned int kind:4;
    Vec3 pos;
    int field_10;
    CreatedItem *item;
} Slot;

typedef struct {
    s16 field_00;
    u8 field_02_low : 2;
    u8 field_02_high : 4;
    u8 field_02_top : 2;
    u8 field_03;
} StateEntry;

typedef struct {
    s16 field_00;
    char pad002[2];
    StateEntry field_04[8];
    s16 field_24[8];
} StateData;

typedef struct { u8 flag : 1; u8 count : 7; } ModeByte;

typedef struct {
    char pad000[0x88];
    u32 spriteSet_88;
} ActorManager;

struct AiState {
    u16 flags00;
    char pad002[6];
    void (*field_08)(AiState *);
    void (*field_0c)(AiState *, int);
    char pad010[0xc];
    void (*field_1c)(AiState *, void *, int);
    void (*field_20)(AiState *);
    void (*field_24)(AiState *, void *, int);
    void (*field_28)(AiState *, void *);
    void (*field_2c)(AiState *, void *);
    char pad030[4];
    void (*field_34)(AiState *);
    char pad038[4];
    void *field_3c;
    u32 flags40;
    char pad044[8];
    int (*field_4c)(AiState *, AiState *);
    char pad050[0x13c];
    void (*field_18c)(AiState *);
    char pad190[0x10];
    StateData *field_1a0;
    char pad1a4[4];
    CreatedItem *field_1a8;
    char pad1ac[0x1a];
    signed char currentAction;
    char pad1c7[2];
    u8 field_1c9;
    char pad1ca[2];
    int (*field_1cc)(AiState *, int);
    int field_1d0;
    void (*field_1d4)(AiState *);
    void (*field_1d8)(AiState *, int, int);
    void *field_1dc;
    int (*field_1e0)(AiState *);
    void (*field_1e4)(AiState *);
    void (*field_1e8)(AiState *);
    void (*field_1ec)(AiState *, int);
    void (*field_1f0)(AiState *, u8);
    void (*field_1f4)(AiState *, int, int);
    void (*field_1f8)(AiState *);
    char pad1fc[0x18];
    int field_214;
    char pad218[8];
    int field_220;
    char pad224[8];
    char list_22c[0x34];
    char list_260[0x70];
    int field_2d0;
    char pad2d4[4];
    int field_2d8;
    char pad2dc[0x10];
    int field_2ec;
    char pad2f0[8];
    int field_2f8;
    char pad2fc[0x10];
    int field_30c;
    signed char field_310;
    ModeByte field_311;
    char pad312[0x3e];
    Slot *slots[8];
};

extern void func_ov107_020c3c74(u16 *node);
extern void func_01fffc24(void *list);
extern void *func_0203c400(void);
extern ActorManager *OS_IsThreadAvailable_0x020c9848(void);
extern CreatedItem *func_0203b898(u32 handle);
extern void func_ov107_020c92b0(AiState *self, int slot, unsigned int kind, Vec3 *pos, int field10);

extern void func_ov107_020c68ec(AiState *self);
extern void func_ov107_020c6980(AiState *self, int delta);
extern void func_ov107_020c7500(AiState *self, void *msg, int size);
extern void func_ov107_020c7a2c(AiState *self);
extern void func_ov107_020c7a90(AiState *self, void *msg, int size);
extern void func_ov107_020c7b70(AiState *self, void *region);
extern void func_ov107_020c7c1c(AiState *self, void *param);
extern void func_ov107_020c7ca4(AiState *self);
extern int func_ov107_020c8014(AiState *a, AiState *b);
extern int func_ov107_020c73a0(AiState *self, int event);
extern void func_ov107_020c8500(AiState *self, int recordIndex);
extern void func_ov107_020c887c(AiState *self, u8 recordIndex);
extern void func_ov107_020c88dc(AiState *self, int a, int b);
extern void func_ov107_020c88fc(AiState *self);
extern void func_ov107_020c7da4(AiState *self);
extern void func_ov107_020c8000(AiState *self, int a, int b);
extern void func_ov107_020c65d8(CreatedItem *self, int region);

extern u8 data_0204252c;
extern u8 data_02042530;

void func_ov107_020c6624(AiState *self, StateData *data)
{
    int i;

    func_ov107_020c3c74((u16 *)self);
    self->flags00 |= 0x40;
    self->field_08 = func_ov107_020c68ec;
    self->field_0c = func_ov107_020c6980;
    self->field_1c = func_ov107_020c7500;
    self->field_20 = func_ov107_020c7a2c;
    self->field_24 = func_ov107_020c7a90;
    self->field_28 = func_ov107_020c7b70;
    self->field_2c = func_ov107_020c7c1c;
    self->field_34 = func_ov107_020c7ca4;
    self->flags40 |= 4;
    self->field_4c = func_ov107_020c8014;
    self->field_1cc = func_ov107_020c73a0;
    self->field_1ec = func_ov107_020c8500;
    self->field_1f0 = func_ov107_020c887c;
    self->field_1f4 = func_ov107_020c88dc;
    self->field_1f8 = func_ov107_020c88fc;
    self->field_1d0 = 0;
    self->field_1e0 = 0;
    self->field_1e4 = 0;
    self->field_1d4 = func_ov107_020c7da4;
    self->field_1d8 = func_ov107_020c8000;
    self->field_1dc = 0;
    self->field_1e8 = 0;
    self->field_1c9 = 1;
    self->currentAction = -1;
    self->field_1a0 = data;
    self->field_2d8 = 0x1000;
    self->field_2d0 = -1;
    self->field_220 = 0x1000;
    self->field_2f8 = 0x1000;
    self->field_2ec = 0;
    func_01fffc24(self->list_22c);
    func_01fffc24(self->list_260);
    self->field_3c = func_0203c400();
    self->field_1a8 = func_0203b898((((OS_IsThreadAvailable_0x020c9848()->spriteSet_88 + 0x8000)
                                      & 0xfffffc) << 7) | 0x80000000 | 6);
    self->field_1a8->flags_5c |= 2;
    self->field_310 = -1;
    self->field_311.flag = 0;
    self->field_311.count = 0;
    self->field_214 = 0;
    self->field_30c = 1;

    {
        u8 recordIndex = data_0204252c;
        if (self->field_1ec != 0) {
            self->field_1ec(self, recordIndex);
        }
    }
    {
        u8 recordIndex = data_02042530;
        if (self->field_1f0 != 0) {
            self->field_1f0(self, recordIndex);
        }
    }
    if (self->field_18c != 0) {
        self->field_18c(self);
    }

    if (self->field_1a0 != 0) {
        for (i = 0; i < 8; i++) {
            if (self->field_1a0->field_04[i].field_02_high == 4 &&
                self->field_1a0->field_04[i].field_03 != 0) {
                func_ov107_020c92b0(self, 6, 1, 0, 0x1000);
                self->slots[6]->item->field_6c = func_ov107_020c65d8;
                break;
            }
        }
        for (i = 0; i < 8; i++) {
            if (self->field_1a0->field_04[i].field_02_high == 8 &&
                self->field_1a0->field_04[i].field_03 != 0) {
                func_ov107_020c92b0(self, 5, 1, 0, 0x1000);
                self->slots[5]->item->field_6c = func_ov107_020c65d8;
                func_ov107_020c92b0(self, 7, 1, 0, 0x1000);
                self->slots[7]->item->field_6c = func_ov107_020c65d8;
                self->slots[7]->item->field_84 = self;
                break;
            }
        }
        if (self->slots[7] == 0) {
            for (i = 0; i < 8; i++) {
                if (self->field_1a0->field_24[i] > 0x100) {
                    func_ov107_020c92b0(self, 7, 1, 0, 0x1000);
                    self->slots[7]->item->field_6c = func_ov107_020c65d8;
                    self->slots[7]->item->field_84 = self;
                    break;
                }
            }
        }
    }
}
