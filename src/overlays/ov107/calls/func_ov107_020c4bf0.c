/*
 * func_ov107_020c4bf0 -- fill a pose message from the owner and send it.
 *
 * Only when msg->field_02 is 0: copies the high byte of flags60, packs the
 * position at +0xb0 into three 24-bit big-endian coordinates, converts the
 * rotation quaternion at +0xa0 to an axis and angle (func_0202f240), and stores
 * the sum of vecF0 and the +0xd8 vector clamped to s16. In mode 1 the owner's
 * +0x1c hook sees the message first. Always ends in func_ov107_020c0d94,
 * which stamps the owner's id and sends it.
 *
 * Coordinates are held in a one-value wrapper type (Fx32). This is a tentative
 * reconstruction of the original's coordinate type, not a proven one: copying a
 * wrapped value is a struct copy, which mwcc never deletes, and that is what
 * keeps the unread stack copy of the position the ROM has.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { int x, y, z; } VecFx32;
typedef struct { int w, x, y, z; } Quat;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

typedef struct {
    u16 id;             /* +0x00 */
    u8 field_02;        /* +0x02 */
    u8 field_03;        /* +0x03 */
    u8 field_04;        /* +0x04 */
    u8 pad05;
    s16 axis[3];        /* +0x06 */
    s16 angle;          /* +0x0c */
    s16 field_0e[3];    /* +0x0e */
    Fx24 pos[3];        /* +0x14 */
} PoseMsg;

/* func_0202f240's two outputs: rotation angle and axis. */
typedef struct {
    int angle;
    VecFx32 axis;
} AxisAngle;

struct FlagBytes { u16 low : 8; u16 high : 8; };

struct AiState;
typedef void (*PoseHook)(struct AiState *self, PoseMsg *msg, int arg);

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    char pad000[0x1c];
    PoseHook field_1c;  /* +0x01c */
    char pad020[0x30];
    int field_50;       /* +0x050 */
    char pad054[0xc];
    u16 flags60;        /* +0x060 */
    char pad062[0x3e];
    Quat field_a0;      /* +0x0a0 */
    FxVec field_b0;     /* +0x0b0 */
    char pad0bc[0x1c];
    VecFx32 field_d8;   /* +0x0d8 */
    char pad0e4[0xc];
    VecFx32 vecF0;      /* +0x0f0 */
};

extern void func_0202f240(VecFx32 *axis, int *angle, Quat *q);
extern void func_ov107_020c0d94(struct AiState *self, PoseMsg *msg, int arg);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline s16 ClampS16(int v) {
    if (v >= 0x8000) {
        v = 0x7fff;
    } else if (v < -0x8000) {
        v = -0x8000;
    }
    return v;
}

void func_ov107_020c4bf0(struct AiState *self, PoseMsg *msg, int arg) {
    AxisAngle rot;
    FxVec pos;

    if (msg->field_02 == 0) {
        msg->field_04 = ((struct FlagBytes *)&self->flags60)->high;

        pos.x = self->field_b0.x;
        PackFx24(&msg->pos[0], pos.x.value);
        pos.y = self->field_b0.y;
        PackFx24(&msg->pos[1], pos.y.value);
        pos.z = self->field_b0.z;
        PackFx24(&msg->pos[2], pos.z.value);

        func_0202f240(&rot.axis, &rot.angle, &self->field_a0);
        msg->axis[0] = rot.axis.x;
        msg->axis[1] = rot.axis.y;
        msg->axis[2] = rot.axis.z;
        msg->angle = rot.angle;

        msg->field_0e[0] = ClampS16(self->vecF0.x + self->field_d8.x);
        msg->field_0e[1] = ClampS16(self->vecF0.y + self->field_d8.y);
        msg->field_0e[2] = ClampS16(self->vecF0.z + self->field_d8.z);

        if (self->field_50 == 1 && self->field_1c != 0) {
            self->field_1c(self, msg, arg);
        }
    }
    func_ov107_020c0d94(self, msg, arg);
}
