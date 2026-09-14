/*
 * Throttles creature updates by distance and update phase, advances timers and
 * owner callbacks, applies hit/motion updates, and refreshes the attached transform.
 *
 * HitPacket's halfword bitfields preserve the ROM's word-wide read/modify/write
 * accesses. Block-local aggregate initializers determine the stack layout.
 * TimedHitAmount captures its inputs before clamping; expanding its arithmetic at
 * the call site changes address reuse and scheduling in mwccarm.
 * Both external vector constants are in their modules' .rodata sections.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int w;
    int x;
    int y;
    int z;
} Quat;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    u8 pad000[2];
    u16 field_002;                 /* 0x002 */
    void *field_004;               /* 0x004 */
    u8 pad008[0x34];
    void *field_03c;               /* 0x03c */
    u8 pad040[0x10];
    int field_050;                 /* 0x050 */
    int field_054;                 /* 0x054 */
    int field_058;                 /* 0x058 */
    int flags5c;                   /* 0x05c */
    u16 flags60;                   /* 0x060 */
    u8 pad062[0x12];
    VecFx32 field_074;             /* 0x074 */
    int field_80;                  /* 0x080 */
    u8 pad084[0x18];
    void *field_09c;               /* 0x09c */
    u8 pad0a0[0x44];
    VecFx32 field_0e4;             /* 0x0e4 */
    VecFx32 field_0f0;             /* 0x0f0 */
    u8 pad0fc[0x18];
    VecFx32 field_114;             /* 0x114 */
    u8 pad120[0x04];
    int field_124;                 /* 0x124 */
    int field_128;                 /* 0x128 */
    int field_12c;                 /* 0x12c */
    u8 pad130[0x0c];
    int field_13c;                 /* 0x13c */
    u8 pad140[0x3a];
    u8 field_17a;                  /* 0x17a */
    u8 pad17b[0x2d];
    void *field_1a8;               /* 0x1a8 */
    u16 field_1ac;                 /* 0x1ac */
    u8 pad1ae[0x16];
    u8 field_1c4;                  /* 0x1c4 */
    u8 field_1c5;                  /* 0x1c5 */
    signed char currentAction;     /* 0x1c6 */
    signed char field_1c7;         /* 0x1c7 */
    signed char field_1c8;          /* 0x1c8 */
    u8 pad1c9[0x07];
    int field_1d0;                 /* 0x1d0 */
    u8 pad1d4[0x44];
    short field_218;               /* 0x218 */
    u8 pad21a[0x42];
    void *field_25c;               /* 0x25c */
    u8 pad260[0x7c];
    short field_2dc;               /* 0x2dc */
    short field_2de;               /* 0x2de */
    int field_2e0;                 /* 0x2e0 */
    int field_2e4;                 /* 0x2e4 */
    u8 pad2e8[4];
    int field_2ec;                 /* 0x2ec */
    int field_2f0;                 /* 0x2f0 */
    u8 pad2f4[8];
    VecFx32 field_2fc;
    int field_308;                 /* 0x308 */
    int field_30c;                 /* 0x30c */
    u8 field_310;                  /* 0x310 */
    u8 field_311;                  /* 0x311 */
    u8 pad312[0x3e];
    void *field_350;               /* 0x350 */
    u8 pad354[4];
    void *field_358;               /* 0x358 */
    void *field_35c;               /* 0x35c */
};

struct ThreadState {
    void *field_000;
    u8 pad004[0x40];
    int field_044;
};

struct HitPacket {
    unsigned int flags00 : 16;
    unsigned int flags02 : 16;
    VecFx32 normal;
    signed int amount : 16;
    unsigned int field12 : 16;
    signed int field14 : 16;
    unsigned int field16 : 16;
    void *field18;
    int field1c;
    int field20;
    int field24;
    int field28;
};

struct FlagBytes { u16 low : 8; u16 high : 8; };
struct FlagByte { u8 bit0 : 1; u8 bit1 : 1; u8 remaining : 6; };
struct ModeByte { u8 flag : 1; u8 count : 7; };
struct ModePacket { u16 index; u8 kind; u8 mode; };

extern char *func_ov107_020cab14(struct AiState *self, int *distance);
extern int FX_Sqrt(int value);
extern struct ThreadState *OS_IsThreadAvailable_0x020c9848(void);
extern int func_ov107_020c9568(void *context, VecFx32 *position);
extern void func_ov107_020c5cfc(struct AiState *self, void *arg, void *data);
extern void func_0203c4a8(void *owner, int tick);
extern void func_ov107_020c9474(struct AiState *self, void *node);
extern void func_ov107_020c41e4(struct AiState *self, int tick);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(VecFx32 *source, VecFx32 *destination);
extern void func_01ffa724(int factor, VecFx32 *source, VecFx32 *destination);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int func_02031258(int type, u16 *data, u16 size);
extern void func_0202ed60(Quat *out, VecFx32 *forward, VecFx32 *direction);
extern void func_0203ca14(int *out, int a, int b, int c);
extern int func_0203c9d0(void *out, void *in);
extern void func_0203ca50(void *out, int a, int b, int c);

extern u8 data_0204c240;
extern const VecFx32 data_ov107_020cb658;
extern const VecFx32 data_02042264;

static inline int TimedHitAmount(short baseAmount, int remaining)
{
    int fraction = 0xc000 - remaining;
    if (fraction > 0xc000) fraction = 0xc000;
    return fraction * (baseAmount * 18 / 100) / 0xc000;
}

void func_ov107_020c6980(struct AiState *self, int delta)
{
    int distance;
    struct ModePacket packet;
    char *target;
    int other;
    struct ThreadState *thread;

    if ((data_0204c240 & 4) != 0) {
        if (self->field_004 != 0 && (self->field_1c4 & 0xf) == 0 &&
            (self->field_1ac & 8) == 0) {
            target = func_ov107_020cab14(self, &distance);
            distance = FX_Sqrt(distance);

            /* The explicit target tests preserve the two short-circuit paths. */
            if (self->field_30c < 4 &&
                (target == 0 || (target != 0 && distance > 0x1e000))) {
                thread = OS_IsThreadAvailable_0x020c9848();
                other = thread != 0 ? thread->field_044 : 0;
                if ((self->field_002 % 4) != (other % 4)) {
                    self->field_30c++;
                    return;
                }
            } else if (self->field_30c < 3 &&
                       (target == 0 || (target != 0 && distance > 0x14000))) {
                thread = OS_IsThreadAvailable_0x020c9848();
                other = thread != 0 ? thread->field_044 : 0;
                if ((self->field_002 % 3) != (other % 3)) {
                    self->field_30c++;
                    return;
                }
            } else if (self->field_30c < 3 && (((struct FlagBytes *)&self->flags60)->low & 1) == 0) {
                thread = OS_IsThreadAvailable_0x020c9848();
                other = thread != 0 ? thread->field_044 : 0;
                if ((self->field_002 % 3) != (other % 3)) {
                    self->field_30c++;
                    return;
                }
            } else if (self->field_30c < 2 && (((struct FlagBytes *)&self->flags60)->low & 0x80) != 0) {
                thread = OS_IsThreadAvailable_0x020c9848();
                other = thread != 0 ? thread->field_044 : 0;
                if ((self->field_002 % 2) != (other % 2)) {
                    self->field_30c++;
                    return;
                }
            } else if (self->field_30c < 2 && target != 0 && distance > 0xa000) {
                thread = OS_IsThreadAvailable_0x020c9848();
                other = thread != 0 ? thread->field_044 : 0;
                if ((self->field_002 % 2) == (other % 2)) {
                    self->field_30c++;
                    return;
                }
            }
        }
    } else if (self->field_004 != 0 && (self->field_1c4 & 0xf) == 0 &&
               (self->field_1ac & 8) == 0 && self->field_30c < 3 &&
               func_ov107_020c9568(OS_IsThreadAvailable_0x020c9848()->field_000,
                                   &self->field_074) != 0) {
        thread = OS_IsThreadAvailable_0x020c9848();
        other = thread != 0 ? thread->field_044 : 0;
        if ((self->field_002 % 3) == (other % 3)) {
            self->field_30c++;
            return;
        }
    }

    if (self->field_050 == 1) {
        if ((self->field_1c4 & 1) != 0 && (self->field_1ac & 7) == 0) {
            int step = delta / 30;
            self->field_2dc -= step;
            if (self->field_2dc <= 0 ||
                (self->field_2e0 > 0 && self->field_2e0 <= step)) {
                int amount;
                struct HitPacket timedHit = {0};
                amount = TimedHitAmount(self->field_218, self->field_2e0 - step);
                timedHit.flags00 = 0x88;
                timedHit.flags02 = 0x80;
                timedHit.amount = amount - self->field_2de;
                if (timedHit.amount < 1) timedHit.amount = 1;
                func_ov107_020c5cfc(self, self->field_25c, &timedHit);
                self->field_2dc += 0x800;
                self->field_2de = amount;
            }
        }
        if (self->field_2e4 > 0) {
            self->field_2e4 -= delta / 30;
            if (self->field_2e4 <= 0) self->field_2e4 = 0;
        }
        if (self->field_2e0 > 0) {
            self->field_2e0 -= delta / 30;
            if (self->field_2e0 <= 0) {
                self->field_2e0 = 0;
                self->field_1c5 &= ~0xf;
            }
        }
        if (self->field_2f0 > 0) {
            self->field_2f0 -= delta / 30;
            if (self->field_2f0 <= 0) self->field_2f0 = 0;
        }
    }
    if (self->field_03c != 0) {
        if (self->field_050 == 1) self->field_1c8 = self->currentAction;
        if (((self->field_1c4 & 2) != 0 || (self->field_1c4 & 8) != 0) &&
            (self->field_1ac & 7) == 0) {
            func_0203c4a8(self->field_03c, 0);
        } else {
            func_0203c4a8(self->field_03c, delta * self->field_30c);
        }
    }
    if (self->field_1c8 != 1 && self->currentAction == 1) {
        if (self->field_350 != 0) func_ov107_020c9474(self, self->field_350);
    } else if (self->field_1c8 != 3 && self->currentAction == 3) {
        if (self->field_358 != 0) func_ov107_020c9474(self, self->field_358);
        if (self->field_35c != 0) func_ov107_020c9474(self, self->field_35c);
    }
    if ((((struct FlagBytes *)&self->flags60)->low & 1) != 0) {
        int tick = 0;
        self->flags5c = 0x1000;
        if ((self->field_1ac & 7) == 0) {
            if ((self->field_1c4 & 8) != 0) {
                VecFx32 zeroVector = {0};
                self->flags5c = 0;
                zeroVector.y = self->field_2ec;
                {
                    int fallStep = (int)(((long long)self->field_058 * 0x555 + 0x800) >> 12);
                    self->field_2ec += -(fallStep + self->field_2ec) / 15;
                }
                self->field_0f0 = zeroVector;
            } else if ((self->field_1c4 & 2) == 0) {
                tick = delta * self->field_30c;
            } else {
                self->field_0f0 = data_ov107_020cb658;
            }
        } else {
            tick = delta * self->field_30c;
        }
        func_ov107_020c41e4(self, tick);
    }
    self->field_30c = 1;
    if (self->field_050 == 1) {
        if (self->field_308 > 0) {
            VecFx32 direction;
            int length;
            VEC_Subtract(&self->field_2fc, &self->field_074, &direction);
            direction.y = 0;
            length = func_01ff8d18(&direction, &direction);
            if (self->field_308 - length <= self->field_80) {
                func_01ffa724(self->field_80 - (self->field_308 - length),
                              &direction, &direction);
                VEC_Add(&self->field_0e4, &direction, &self->field_0e4);
            }
        }
        if (((struct FlagByte *)&self->field_17a)->bit0 != 0) {
            if (self->field_2ec < 0) self->field_1c5 &= ~8;
        }
        if (self->field_2f0 == 0 && self->field_1d0 != 0 &&
            (self->field_1c4 & 4) != 0 &&
            ((struct FlagByte *)&self->field_17a)->bit1 != 0) {
            struct HitPacket effect = {0};
            VecFx32 scaled;
            func_01ffa724(0x1000, &self->field_114, &scaled);
            effect.flags00 = 0x2004;
            effect.flags02 = 0;
            effect.normal = scaled;
            effect.field12 = 0;
            effect.field14 = -1;
            effect.field18 = 0;
            func_ov107_020c5cfc(self, 0, &effect);
            self->field_1c5 &= ~4;
        }
        if (((struct ModeByte *)&self->field_311)->count != 0) {
            u16 index = self->field_002;
            u8 count;
            packet.kind = 6;
            packet.index = index;
            /* Narrow the source bit before moving it into the packet's high bit. */
            packet.mode = (self->field_310 & 0x7f) |
                (((u32)((struct ModeByte *)&self->field_311)->flag << 31) >> 24);
            func_02031258(4, (u16 *)&packet, sizeof(packet));
            count = ((struct ModeByte *)&self->field_311)->count;
            count += (u8)-1;
            ((struct ModeByte *)&self->field_311)->count = count;
        }
    }
    if (self->field_004 != 0 && (self->field_1ac & 0x10) == 0 &&
        (((*(int *)((char *)self->field_09c + 0x5c) << 30) >> 31) == 0) &&
        (self->field_124 != 0 || self->field_128 != 0 || self->field_12c != 0)) {
        VecFx32 position;
        Quat quat;
        int scale;
        int height = self->field_13c;
        func_0202ed60(&quat, (VecFx32 *)&data_02042264,
                      (VecFx32 *)&self->field_124);
        scale = 0x1000 - height / 20;
        if (scale < 0x200) scale = 0x200;
        scale = (int)(((long long)scale * (self->field_80 * 2) + 0x800) >> 12);
        position = self->field_074;
        position.y -= height;
        func_0203ca14((int *)((char *)self->field_1a8 + 4), position.x,
                      position.y + 0x200, position.z);
        func_0203c9d0((char *)self->field_1a8 + 4, &quat);
        func_0203ca50((char *)self->field_1a8 + 4, scale, 0x1000, scale);
        *(int *)((char *)self->field_1a8 + 0x5c) &= ~2;
    } else {
        *(int *)((char *)self->field_1a8 + 0x5c) |= 2;
    }
}
