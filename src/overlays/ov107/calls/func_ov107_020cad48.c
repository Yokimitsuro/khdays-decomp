/* Update the attached shape from the source's vertical reach, clamp to 0xb33,
 * and use half the result for the node's +0x70 value and +0x64 vector's Y.
 * The source reach and shape height follow the uses in func_ov022_0209a3a4.
 */
typedef struct { int x, y, z; } VecFx32;

/* Partial layouts for the node, its source, and its attached shape. */
typedef struct Source {
    unsigned char pad0[0x26b8];
    int nReach;                   /* +0x26b8 */
} Source;

typedef struct Shape {
    unsigned char pad0[0x70];
    int nHeight;                  /* +0x70 */
    int field_74;
} Shape;

typedef struct Node {
    unsigned char pad0[0x64];
    VecFx32 vec64;
    int field_70;
    unsigned char pad74[0x18c - 0x74];
    Source *source;
    unsigned char pad190[0x1d8 - 0x190];
    Shape *shape;
} Node;

extern void func_ov107_020c3dc8(int self);

/* Keep the vector setter: argument evaluation captures Y before any component
 * is written. This also preserves mwcc's register allocation (VEC_Set pattern).
 */
static inline void VEC_Set(VecFx32 *vec, int x, int y, int z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void func_ov107_020cad48(Node *node)
{
    if (node->source != 0) {
        Shape *shape = node->shape;
        int height;
        shape->nHeight = node->source->nReach - shape->field_74;
        height = shape->nHeight;
        if (height < 0xb33)
            height = 0xb33;
        shape->nHeight = height;
        node->field_70 = shape->nHeight / 2;
        VEC_Set(&node->vec64, 0, node->field_70, 0);
    }
    func_ov107_020c3dc8((int)node);
}
