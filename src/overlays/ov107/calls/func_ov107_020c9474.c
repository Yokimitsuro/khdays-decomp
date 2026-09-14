/*
 * func_ov107_020c9474 -- place an attachment at the owner's position.
 *
 * Adds the node's offset to the owner's vec74, packs the sum into three 24-bit
 * big-endian coordinates and hands them to func_ov107_020c08cc together with the
 * node's four parameters. Does nothing without a node or without its +0x14 item.
 *
 * Coordinates are held in a one-value wrapper type (Fx32). This is a tentative
 * reconstruction of the original's coordinate type, not a proven one: copying a
 * wrapped value is a struct copy, which mwcc never deletes, and that is what
 * keeps the unread stack copy of the position the ROM has. About 24 other
 * functions in the game carry the same unread copy.
 */
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

struct AttachNode {
    char pad00[4];
    FxVec offset;       /* +0x04 */
    int field_10;       /* +0x10 */
    void *field_14;     /* +0x14 */
    u8 field_18;        /* +0x18 */
    u8 field_19;        /* +0x19 */
};

/* Partial AiState, fields from STRUCTS.md; pads are not claims about the object. */
struct AiState {
    char pad000[0x3c];
    void *field_3c;     /* +0x03c */
    char pad040[0x34];
    FxVec vec74;        /* +0x074 */
};

extern void VEC_Add(FxVec *a, FxVec *b, FxVec *out);
extern void *func_ov107_020c08cc(void *taskList, void *subitem, int mode, int blend,
                                 int weight, Fx24 *payload);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

void func_ov107_020c9474(struct AiState *self, struct AttachNode *node) {
    FxVec sum;
    Fx24 packed[3];
    FxVec pos;

    if (node == 0 || node->field_14 == 0) {
        return;
    }

    VEC_Add(&self->vec74, &node->offset, &sum);
    pos.x = sum.x;
    PackFx24(&packed[0], pos.x.value);
    pos.y = sum.y;
    PackFx24(&packed[1], pos.y.value);
    pos.z = sum.z;
    PackFx24(&packed[2], pos.z.value);

    func_ov107_020c08cc(self->field_3c, node->field_14, node->field_19, node->field_18,
                        node->field_10, packed);
}
