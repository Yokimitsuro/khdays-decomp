/*
 * func_ov107_020c5af8 -- send a kind-7 position message.
 *
 * Only when the owner's +0x50 mode is 1. Builds an 18-byte message: the owner's
 * u16 id, kind 7, the two caller halfwords, then *pos packed into three 24-bit
 * big-endian coordinates. Bit 2 of data_0204c240 picks the route: set, send it
 * through func_02031258 on channel 4; clear, hand it straight to
 * func_ov107_020c49b8.
 *
 * Coordinates are held in a one-value wrapper type (Fx32). This is a tentative
 * reconstruction of the original's coordinate type, not a proven one: copying a
 * wrapped value is a struct copy, which mwcc never deletes, and that is what
 * keeps the unread stack copy of the position the ROM has.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 field_03;        /* +0x3 */
} MsgHeader;

typedef struct {
    MsgHeader hdr;      /* +0x0 */
    u16 field_04;       /* +0x4 */
    u16 field_06;       /* +0x6 */
    Fx24 pos[3];        /* +0x8 */
} PosMsg7;

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    char pad000[2];
    u16 id;             /* +0x002 */
    char pad004[0x4c];
    int field_50;       /* +0x050 */
};

extern u8 data_0204c240;
extern int func_02031258(int channel, u16 *msg, u16 size);
extern void func_ov107_020c49b8(struct AiState *self, PosMsg7 *msg, int size);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

void func_ov107_020c5af8(struct AiState *self, u16 a, u16 b, FxVec *pos) {
    if (self->field_50 != 1) {
        return;
    }
    {
    PosMsg7 msg = {0};
    FxVec copy;
    /* The header goes through a pointer so mwcc addresses it off the
     * initializer's base register, as the ROM does. */
    MsgHeader *hdr = (MsgHeader *)&msg;

    hdr->id = self->id;
    hdr->kind = 7;
    hdr->field_03 = 0;
    msg.field_04 = a;
    msg.field_06 = b;

    copy.x = pos->x;
    PackFx24(&msg.pos[0], copy.x.value);
    copy.y = pos->y;
    PackFx24(&msg.pos[1], copy.y.value);
    copy.z = pos->z;
    PackFx24(&msg.pos[2], copy.z.value);

    if (data_0204c240 & 4) {
        func_02031258(4, (u16 *)&msg, sizeof(PosMsg7));
    } else {
        func_ov107_020c49b8(self, &msg, sizeof(PosMsg7));
    }
    }
}
