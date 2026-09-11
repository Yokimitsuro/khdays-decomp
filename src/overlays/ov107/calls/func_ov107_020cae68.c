typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int x, y, z; } VecFx32;

typedef struct Node {
    unsigned char pad0[0x60];
    u16 flags;
    unsigned char pad62[0x18c - 0x62];
    char *source;
    VecFx32 anchor;
} Node;

extern void func_ov107_020c4e9c(Node *node, int region);
extern void func_ov107_020c5c54(Node *node, VecFx32 *anchor);

void func_ov107_020cae68(Node *node, int region) {
    node->flags = (u16)((node->flags & 0xffff00ff) |
                  ((((u32)node->flags << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
    func_ov107_020c4e9c(node, region);
    if (node->source != 0) {
        node->anchor = *(VecFx32 *)(node->source + 0x48c);
        func_ov107_020c5c54(node, &node->anchor);
    }
}
