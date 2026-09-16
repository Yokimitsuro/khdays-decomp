typedef unsigned short u16;

typedef struct { int x, y, z; } VecFx32;
typedef struct { int w[11]; } Blk44;

typedef struct Heading {
    unsigned char pad0[0x80];
    u16 angle;                   /* +0x80, indexes the sin/cos table */
} Heading;

typedef struct Source {
    unsigned char pad0[0x20];
    Heading *field_20;           /* +0x20 */
} Source;

typedef struct Shape {
    unsigned char pad0[0x10];
    Blk44 field_10;              /* +0x10 */
} Shape;

typedef struct Node {
    unsigned char pad0[0x60];
    u16 flagsLo : 8;             /* +0x60 */
    u16 flagsHi : 8;             /* +0x61 */
    unsigned char pad62[0xa0 - 0x62];
    Blk44 field_a0;              /* +0xa0 */
    unsigned char padcc[0xfc - 0xcc];
    VecFx32 field_fc;            /* +0xfc */
    unsigned char pad108[0x18c - 0x108];
    Source *source;              /* +0x18c */
    VecFx32 anchor;              /* +0x190 */
    VecFx32 direction;           /* +0x19c */
    VecFx32 field_1a8;           /* +0x1a8 */
    unsigned char pad1b4[0x1d8 - 0x1b4];
    Shape *shape;                /* +0x1d8 */
} Node;

extern const short data_0203d210[];    /* sin, cos pairs by angle >> 4 (rodata) */
extern const VecFx32 data_02041dc8;    /* zero vector (rodata) */

/* Copies the high flag byte into the low one; if there is a source, sets direction
 * to (sin, 0, cos) of the source heading turned 180 degrees; pushes field_a0 into the
 * shape; moves field_fc into field_1a8 and resets field_fc to zero. */
void func_ov107_020cada8(Node *node)
{
    node->flagsLo = node->flagsHi;
    if (node->source != 0) {
        int idx = (u16)(node->source->field_20->angle - 0x8000) >> 4;
        node->direction.x = data_0203d210[idx * 2];
        node->direction.y = 0;
        node->direction.z = data_0203d210[idx * 2 + 1];
    }
    node->shape->field_10 = node->field_a0;
    node->field_1a8 = node->field_fc;
    node->field_fc = data_02041dc8;
}
