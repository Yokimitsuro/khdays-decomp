/* Slot-event relay of the mission enemy: when the actor's +0x694 bit 0 is set and the node is
 * of kind 2, 3 or 4, samples the actor's anchor position, raises it 0x800, faces the node the
 * model's way (heading +0x80 flipped by 0x8000), flags it 0x20 and stores the position at +0xb4
 * before re-registering the node. Then the 2 requests at +0x12c (stride 0x240) are stepped
 * through func_ov043_020b50f8. */
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

typedef struct {
    char pad0[0x10];
    u16 flags;
    char pad12[0x7a];
    u16 angle;
    char pad8e[0x26];
    Vec3 vec;
    char padc0[0x11c - 0xc0];
    int kind;
} Node;

struct b1 { u8 b0 : 1; };

extern void func_ov022_020ad44c(Vec3 *out, char *self);
extern void func_0202aa9c(void *node);
extern void func_ov043_020b50f8(char *req);

void func_ov043_020b4a68(char *self, Node *node)
{
    Vec3 pos;
    int i;
    char *req;

    if (((struct b1 *)(self + 0x694))->b0 == 0) {
        return;
    }
    if (!(node->kind != 2 && node->kind != 3 && node->kind != 4)) {
        func_ov022_020ad44c(&pos, self);
        pos.y += 0x800;
        node->angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
        node->flags |= 0x20;
        node->vec = pos;
        func_0202aa9c(&node->flags);
    }
    req = (char *)node + 0x12c;
    for (i = 0; i < 2; i++) {
        func_ov043_020b50f8(req);
        req += 0x240;
    }
}
