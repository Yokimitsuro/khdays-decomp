/*
 * func_ov107_020c73a0 -- event handler for an AiState node, dispatched on `event`.
 *  0: raise hw60 high-byte bits 0-1, clear bit 1 of flags1ae, zero +0x25c, copy the
 *     3-word vector at +0xb0 into +0x190.
 *  1: set pendingAction = 3.
 *  2: if the node is active (hw60 low bit) and its +0x1e0 callback reports done, clear
 *     hw60 high-byte bit 0, clear the low nibble of +0x1c5, set +0x2e8 = 0x800, and if
 *     +0x360 is set notify through the +0x24 callback with a 2-halfword record from the
 *     rodata table. Returns 0 when the node is inactive or the callback is not done.
 *  3: run the +0x1e4 callback if present.
 * Returns 1 otherwise.
 *
 * The record is filled through a pointer to the destination, high halfword first, with the
 * table declared as an incomplete array (same shape as func_ov117_020cd494). A struct
 * assignment reads +0xc first; a sized `[4]` declaration stores the first halfword before
 * loading the second.
 */
struct flags16 { unsigned short lo : 8, hi : 8; };

typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned short a, b; } HalfPair;

struct AiState;
typedef void (*NotifyFn)(struct AiState *self, void *rec, int size);
typedef int (*StepFn)(struct AiState *self);
typedef void (*ExitFn)(struct AiState *self);

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    unsigned char pad000[0x24];
    NotifyFn field_24;            /* 0x024 */
    unsigned char pad028[0x38];
    struct flags16 flags60;       /* 0x060 */
    unsigned char pad062[0x4e];
    Vec3 field_b0;                /* 0x0b0 */
    unsigned char pad0bc[0xd4];
    Vec3 field_190;               /* 0x190 */
    unsigned char pad19c[0x12];
    unsigned short flags1ae;      /* 0x1ae */
    unsigned char pad1b0[0x15];
    unsigned char field_1c5;      /* 0x1c5 */
    unsigned char pad1c6;
    signed char pendingAction;    /* 0x1c7 */
    unsigned char pad1c8[0x18];
    StepFn field_1e0;             /* 0x1e0 */
    ExitFn field_1e4;             /* 0x1e4 */
    unsigned char pad1e8[0x74];
    int field_25c;                /* 0x25c */
    unsigned char pad260[0x88];
    int field_2e8;                /* 0x2e8 */
    unsigned char pad2ec[0x74];
    int field_360;                /* 0x360 */
};

extern const HalfPair data_ov107_020cb628[];

int func_ov107_020c73a0(struct AiState *self, int event) {
    HalfPair rec;

    switch (event) {
    case 0:
        {
            unsigned short hw = *(unsigned short *)&self->flags60;
            *(unsigned short *)&self->flags60 = (hw & ~0xff00) |
                (((((unsigned int)hw << 0x10) >> 0x18) | 3) << 0x18 >> 0x10);
        }
        self->flags1ae &= ~2;
        self->field_25c = 0;
        self->field_190 = self->field_b0;
        break;
    case 1:
        self->pendingAction = 3;
        break;
    case 2: {
        int done;
        if (self->flags60.lo & 1) {
            done = (self->field_1e0 != 0) ? self->field_1e0(self) : 0;
            if (done != 0) {
                self->flags60.hi &= ~1;
                self->field_1c5 &= ~0xf;
                self->field_2e8 = 0x800;
                if (self->field_360 != 0) {
                    HalfPair *msg = &rec;
                    msg->b = data_ov107_020cb628[3].b;
                    msg->a = data_ov107_020cb628[3].a;
                    if (self->field_24 != 0) {
                        self->field_24(self, msg, 4);
                    }
                }
                return 1;
            }
        }
        return 0;
    }
    case 3:
        if (self->field_1e4 != 0) {
            self->field_1e4(self);
        }
        break;
    }
    return 1;
}
