/* Constructs the 0x1ec-byte node func_ov107_020ca900 allocates: run the shared
 * base constructor, set flag bit 7, replace or add nine behaviour callbacks
 * (clearing the one at +0x10), zero +0x1bc..+0x1c8, seed +0x1e0 and +0x1dc to
 * 0x2000, clear bit 7 of the +0x60 high byte, set bits 1 and 2 of +0x40, reset
 * +0x54/+0x58, store the caller's value at +0x70 and as the Y of the +0x64
 * vector, set bits 2-4 of the +0x60 high byte, then build a shape record from a
 * 32-byte request (zero position, the data_02042264 axis, 0x800, the caller's
 * value), link it into the child list at +0x144 under key 100 and keep it at
 * +0x1d8.
 *
 * The +0x60 high byte is cleared through the bitfield and set through the raw
 * halfword: the bitfield form narrows the new byte to u16 before inserting it
 * (the ROM's first update) and the raw form does not (the second). The +0x64
 * vector goes through a named pointer, which keeps its address in a register
 * for the Y and Z stores as the ROM does. */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int x, y, z; } VecFx32;

/* the 32-byte block func_ov107_020c3210 copies into its new record */
typedef struct ShapeRequest {
    VecFx32 pos;                 /* 0x00 */
    VecFx32 axis;                /* 0x0c */
    int field_18;                /* 0x18 */
    int field_1c;                /* 0x1c */
} ShapeRequest;

/* the halfword at +0x60: its two bytes are read and written separately */
typedef union Flags60 {
    u16 raw;
    struct {
        u16 lo : 8;
        u16 hi : 8;
    } bytes;
} Flags60;

/* Partial layout of the 0x1ec-byte node func_ov107_020ca900 allocates. */
typedef struct Node {
    u16 flags;                   /* 0x000 */
    unsigned char pad002[0xc - 0x2];
    void *field_0c;              /* 0x00c */
    void *field_10;              /* 0x010 */
    unsigned char pad014[0x1c - 0x14];
    void *field_1c;              /* 0x01c */
    void *field_20;              /* 0x020 */
    void *field_24;              /* 0x024 */
    void *field_28;              /* 0x028 */
    void *field_2c;              /* 0x02c */
    unsigned char pad030[0x34 - 0x30];
    void *field_34;              /* 0x034 */
    unsigned char pad038[0x40 - 0x38];
    unsigned int field_40;       /* 0x040 */
    void *field_44;              /* 0x044 */
    unsigned char pad048[0x54 - 0x48];
    int field_54;                /* 0x054 */
    int field_58;                /* 0x058 */
    unsigned char pad05c[0x60 - 0x5c];
    Flags60 flags60;             /* 0x060 */
    unsigned char pad062[0x64 - 0x62];
    VecFx32 vec64;               /* 0x064 */
    int field_70;                /* 0x070 */
    unsigned char pad074[0x144 - 0x74];
    unsigned char children[0x18c - 0x144]; /* 0x144, child list */
    void *source;                /* 0x18c */
    unsigned char pad190[0x1bc - 0x190];
    int field_1bc;               /* 0x1bc */
    int field_1c0;               /* 0x1c0 */
    int field_1c4;               /* 0x1c4 */
    int field_1c8;               /* 0x1c8 */
    unsigned char pad1cc[0x1d8 - 0x1cc];
    void *shape;                 /* 0x1d8 */
    int field_1dc;               /* 0x1dc */
    int field_1e0;               /* 0x1e0 */
    int field_1e4;               /* 0x1e4 */
    unsigned char pad1e8[0x1ec - 0x1e8];
} Node;

extern void func_ov107_020c3c74(Node *node);
extern void **func_01fffca8(void *list, int payloadSize, unsigned int key);
extern void *func_ov107_020c3210(ShapeRequest *req);
extern void func_ov107_020cada8(void);
extern void func_ov107_020caf24(void);
extern void func_ov107_020cafb4(void);
extern void func_ov107_020caf64(void);
extern void func_ov107_020cae68(void);
extern void func_ov107_020caebc(void);
extern void func_ov107_020cafd8(void);
extern void func_ov107_020cad48(void);
extern const VecFx32 data_02042264;

static inline void VEC_Set(VecFx32 *vec, int x, int y, int z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void func_ov107_020cac24(Node *node, int value)
{
    ShapeRequest req;
    void **slot;
    VecFx32 *center;

    func_ov107_020c3c74(node);
    node->flags |= 0x80;
    node->field_0c = (void *)func_ov107_020cada8;
    node->field_10 = 0;
    node->field_20 = (void *)func_ov107_020caf24;
    node->field_1c = (void *)func_ov107_020cafb4;
    node->field_24 = (void *)func_ov107_020caf64;
    node->field_28 = (void *)func_ov107_020cae68;
    node->field_2c = (void *)func_ov107_020caebc;
    node->field_34 = (void *)func_ov107_020cafd8;
    node->field_44 = (void *)func_ov107_020cad48;
    node->field_1bc = 0;
    node->field_1c0 = 0;
    node->field_1c4 = 0;
    node->field_1c8 = 0;
    node->field_1dc = node->field_1e0 = 0x2000;
    node->flags60.bytes.hi &= ~0x80;
    node->field_40 |= 2;
    node->field_40 |= 4;
    node->field_54 = 0x1000;
    node->field_58 = 0;
    node->field_70 = value;
    center = &node->vec64;
    VEC_Set(center, 0, node->field_70, 0);
    node->flags60.raw = (u16)((node->flags60.raw & 0xffff00ff) |
                        ((((u32)node->flags60.raw << 0x10) >> 0x18 | 0x1c) << 0x18) >> 0x10);
    VEC_Set(&req.pos, 0, 0, 0);
    req.axis = data_02042264;
    req.field_18 = 0x800;
    req.field_1c = value;
    slot = func_01fffca8(node->children, 4, 100);
    node->shape = *slot = func_ov107_020c3210(&req);
}
