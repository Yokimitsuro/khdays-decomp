/* Decode drop requests and received state, update mode/reaction resources,
 * then forward every message to the base handler with its original size.
 * Packed coordinates use the upper three bytes of an integer scratch word;
 * the unspecified low byte is discarded by the arithmetic right shift.
 */
#pragma opt_propagation off
#pragma opt_common_subs off

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed long long s64;

typedef struct {
    u8 pad000[2];
    u8 type;
    u8 subtype;
    u8 field_04;
    u8 field_05;
    u8 field_06;
    u8 field_07;
    u8 field_08;
    u8 field_09;
    u8 field_0a;
    u8 field_0b;
    u8 field_0c;
    u8 field_0d;
    u8 pad00e[0xf];
    u8 field_1d;
    u16 field_1e;
    u8 field_20;
    u8 field_21;
    s16 field_22;
} Message;

/* Type 8 uses aligned halfword/word payload reads; other types use bytes. */
typedef struct {
    u8 pad000[4];
    u16 handlerId;
    u8 pad006[2];
    int adjustment;
} ReactionMessage;


typedef struct {
    int field_00;
    int field_04;
    u32 flags08 : 8;
    u32 field_08_upper : 24;
} ListNode;

typedef union {
    u8 value;
    struct {
        u8 modeFlag:1;
        u8 modePhase:7;
    } bits;
} Flags311;

typedef struct {
    u8 pad000[0x51];
    u8 field_51;
    u8 field_52;
} Parameter;

typedef struct {
    u8 pad000[0x78];
    int field_78;
} Context;

/* Partial reaction resource and its descriptor; their full sizes are unknown. */
typedef struct {
    u8 pad000[0x84];
    int field_84;
} ReactionData;

typedef struct {
    u8 pad000[0x14];
    ReactionData *field_14;
    u8 field_18;
} SubObject;

/* Partial AiState; currentAction follows the shared object vocabulary. */
typedef struct {
    u8 pad000[4];
    Context *field_04;
    u8 pad008[0x48];
    int field_50;
    u8 pad054[0x14c];
    Parameter *field_1a0;
    u8 pad1a4[8];
    u16 field_1ac;
    u8 pad1ae[0x16];
    u8 field_1c4;
    u8 pad1c5;
    s8 currentAction;
    u8 pad1c7;
    u8 field_1c8;
    u8 pad1c9[0xb];
    void (*field_1d4)(void *self);
    u8 pad1d8[4];
    void (*field_1dc)(void *self, int mode, int flag);
    u8 pad1e0[0x38];
    s16 field_218;
    s16 field_21a;
    u8 pad21c[4];
    int field_220;
    u8 pad224[8];
    u8 list_22c[0x34];
    u8 pad260[0xb0];
    s8 field_310;
    Flags311 field_311;
    u8 pad312[0x42];
    SubObject *field_354;
    void *field_358;
    void *field_35c;
    SubObject *field_360;
    SubObject *field_364;
    SubObject *field_368;
    SubObject *field_36c;
} AiState;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    int raw9[3];
    int raw11[3];
    u8 amount9[6];
    u8 amount11[6];
    Vec3 place9;
    Vec3 place11;
} PacketLocals;

extern int func_ov002_02072754(int value);
extern void func_ov002_02077cec(const u8 *amount, int context,
                                const Vec3 *place);
extern int func_01fffd70(void *list);
extern int func_01fffd8c(void *list);
extern int func_ov107_020c9b68(unsigned int id);
extern void func_ov107_020c9474(void *self, void *entry);
extern void func_ov107_020c49b8(void *self, u8 *msg, int size);

/* Both message paths clamp the new value to [0, field_218]. */
static inline void SetBoundedValue(AiState *self, int value)
{
    int bounded;
    if (value < 0) {
        bounded = 0;
    } else {
        int limit = self->field_218;
        bounded = value > limit ? limit : value;
    }
    self->field_21a = bounded;
}

void func_ov107_020c7500(AiState *self, Message *msg, int size)
{
    Context *context = self->field_04;
    PacketLocals locals;

    if (msg->type == 0xb) {
        u8 *amount = locals.amount11;
        amount[0] = 0;
        amount[1] = 0;
        amount[2] = 0;
        amount[3] = 0;
        amount[4] = 0;
        amount[5] = 0;
        locals.amount11[0] = msg->field_04;
        {
            u8 hi = msg->field_05;
            u8 mid = msg->field_06;
            u8 lo = msg->field_07;
            ((u8 *)&locals.raw11[0])[1] = lo;
            ((u8 *)&locals.raw11[0])[3] = hi;
            ((u8 *)&locals.raw11[0])[2] = mid;
        }
        locals.place11.x = locals.raw11[0] >> 8;
        {
            u8 hi = msg->field_08;
            u8 mid = msg->field_09;
            u8 lo = msg->field_0a;
            ((u8 *)&locals.raw11[1])[1] = lo;
            ((u8 *)&locals.raw11[1])[3] = hi;
            ((u8 *)&locals.raw11[1])[2] = mid;
        }
        locals.place11.y = locals.raw11[1] >> 8;
        {
            u8 hi = msg->field_0b;
            u8 mid = msg->field_0c;
            u8 lo = msg->field_0d;
            ((u8 *)&locals.raw11[2])[1] = lo;
            ((u8 *)&locals.raw11[2])[3] = hi;
            ((u8 *)&locals.raw11[2])[2] = mid;
        }
        locals.place11.z = locals.raw11[2] >> 8;
        func_ov002_02077cec(locals.amount11,
                            (u16)func_ov002_02072754(context->field_78),
                            &locals.place11);
    } else if (msg->type == 9) {
        u8 *amount = locals.amount9;
        amount[0] = 0;
        amount[1] = 0;
        amount[2] = 0;
        amount[3] = 0;
        amount[4] = 0;
        amount[5] = 0;

        if (self->field_1a0 != 0) {
            s64 value = self->field_1a0->field_51 * self->field_220;
            if (value > 0 && value < 0x1000) {
                value = 0x1000;
            }
            locals.amount9[2] = (u8)((value + 0xfff) >> 12);

            value = self->field_1a0->field_52 * self->field_220;
            if (value > 0 && value < 0x1000) {
                value = 0x1000;
            }
            locals.amount9[3] = (u8)((value + 0xfff) >> 12);
        }

        {
            u8 hi = msg->field_05;
            u8 mid = msg->field_06;
            u8 lo = msg->field_07;
            ((u8 *)&locals.raw9[0])[1] = lo;
            ((u8 *)&locals.raw9[0])[3] = hi;
            ((u8 *)&locals.raw9[0])[2] = mid;
        }
        locals.place9.x = locals.raw9[0] >> 8;
        {
            u8 hi = msg->field_08;
            u8 mid = msg->field_09;
            u8 lo = msg->field_0a;
            ((u8 *)&locals.raw9[1])[1] = lo;
            ((u8 *)&locals.raw9[1])[3] = hi;
            ((u8 *)&locals.raw9[1])[2] = mid;
        }
        locals.place9.y = locals.raw9[1] >> 8;
        {
            u8 hi = msg->field_0b;
            u8 mid = msg->field_0c;
            u8 lo = msg->field_0d;
            ((u8 *)&locals.raw9[2])[1] = lo;
            ((u8 *)&locals.raw9[2])[3] = hi;
            ((u8 *)&locals.raw9[2])[2] = mid;
        }
        locals.place9.z = locals.raw9[2] >> 8;
        func_ov002_02077cec(locals.amount9,
                            (u16)func_ov002_02072754(context->field_78),
                            &locals.place9);
    } else if (msg->type == 6) {
        if (self->field_50 == 2) {
            u8 requested = msg->subtype;
            u8 value = requested & 0x7f;
            u8 mode = (requested & 0x80) != 0;
            if (!self->field_311.bits.modePhase ||
                self->field_310 != value ||
                self->field_311.bits.modeFlag != mode) {
                self->field_310 = value;
                self->field_311.bits.modeFlag = mode;
                self->field_311.bits.modePhase = 3;
                if (self->field_1dc != 0) {
                    self->field_1dc(self, value, mode);
                }
            }
        }
    } else if (msg->type == 0) {
        if (self->field_50 == 2) {
            int index = 0;
            ListNode *node = (ListNode *)func_01fffd70(self->list_22c);
            if (node != 0) {
                do {
                    node->flags08 = 0;
                    node->flags08 |= ((msg->field_20 >> index) & 1) ? 1 : 0;
                    node->flags08 |= ((msg->field_21 >> index) & 1) ? 2 : 0;
                    index++;
                    node = (ListNode *)func_01fffd8c(self->list_22c);
                } while (node != 0);
            }
        }

        self->field_21a = msg->field_22;
        if ((msg->field_1e & 2) != 0 && (self->field_1ac & 2) == 0) {
            SetBoundedValue(self, self->field_218);
            if (self->field_1d4 != 0) {
                self->field_1d4(self);
            }
        }
        self->field_1ac = msg->field_1e;
        self->field_1c4 = msg->field_1d;
        if (self->field_50 == 2) {
            self->field_1c8 = self->currentAction;
        }
        self->currentAction = msg->field_05;
    } else if (msg->type == 8) {
        ReactionMessage *reaction = (ReactionMessage *)msg;
        int handler = func_ov107_020c9b68(reaction->handlerId);
        if (msg->subtype == 6) {
            if (handler != 0) {
                SubObject *outer = self->field_368;
                outer->field_14->field_84 = handler;
                func_ov107_020c9474(self, outer);
            }
        } else if (msg->subtype == 5) {
            if (handler != 0) {
                SubObject *outer = self->field_364;
                outer->field_14->field_84 = handler;
                func_ov107_020c9474(self, outer);
                func_ov107_020c9474(self, self->field_36c);
                if (self->field_50 == 1) {
                    SetBoundedValue(self, reaction->adjustment + self->field_21a);
                }
            }
        } else if (msg->subtype == 4) {
            func_ov107_020c9474(self, self->field_360);
        } else if (msg->subtype == 7) {
            func_ov107_020c9474(self, self->field_36c);
        } else if ((u8)(msg->subtype + 0xf8) <= 1U) {
            SubObject *entry = self->field_354;
            u8 old = entry->field_18;
            entry->field_18 = (u8)(old + (msg->subtype - 8));
            func_ov107_020c9474(self, entry);
            entry->field_18 = old;
        }
    }

    func_ov107_020c49b8(self, (u8 *)msg, size);
}
