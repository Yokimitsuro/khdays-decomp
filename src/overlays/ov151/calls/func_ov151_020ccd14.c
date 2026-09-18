/* func_ov151_020ccd14 -- broadcast this node's position. When the caller's flag word has both
 * bit 0 and bit 4 set, build the 14-byte message from the template at data_ov151_020cec18, pack
 * the node's position vector into bytes 5..13 (three components, each as sign + 23-bit magnitude
 * split high/mid/low), hand it to the object's message hook with length 0xe, clear the pending
 * byte at +0x1c7 and report success. Head of a 5-member family.
 *
 * Two codegen cracks were needed; both are counter-intuitive enough to be worth recording.
 *
 * 1. THE UNREAD STACK COPY.
 *    The ROM also stores the vector into a stack copy that nothing ever reads. Coordinates are
 *    held in a one-value wrapper type (Fx32), a tentative reconstruction of the original's
 *    coordinate type: copying a wrapped value is a struct copy, which mwcc keeps, and that is the
 *    ROM's unread stack copy. A plain int copy is dead-store-eliminated (12 bytes short); copying
 *    the whole vector at once emits a block `ldm`/`stm` and costs registers. Copying one
 *    component at a time gives one load per component, packed from that register, then stored.
 *
 * 2. DO NOT CACHE A POINTER TO THE MESSAGE BUFFER.
 *    With `p = (unsigned char *)&m;` mwcc keeps `p` in a register and addresses the bytes as
 *    `[p, #5]`. Indexing `m` directly at every use lets it fold the whole thing into the frame
 *    pointer, `[sp, #0x11]`, which is what the ROM does and what frees the last register.
 */
struct Msg { unsigned short h[7]; };
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
extern struct Msg data_ov151_020cec18;

int func_ov151_020ccd14(int self, int a, unsigned int *flags, int d) {
    int *node = *(int **)(self + 0x214);
    struct Msg m;
    FxVec v;
    FxVec *s;
    void (*cb)(int, struct Msg *, int);

    if (((unsigned short)*flags & 1) != 0) {
        m = data_ov151_020cec18;
        s = (FxVec *)node[2];

        v.x = s->x;
        ((unsigned char *)&m)[5]  = (unsigned char)(((unsigned int)v.x.value >> 0x10 & 0x7f) | ((unsigned int)v.x.value >> 0x18 & 0x80));
        ((unsigned char *)&m)[6]  = (unsigned char)((unsigned int)v.x.value >> 8);
        ((unsigned char *)&m)[7]  = (unsigned char)v.x.value;

        v.y = s->y;
        ((unsigned char *)&m)[8]  = (unsigned char)(((unsigned int)v.y.value >> 0x10 & 0x7f) | ((unsigned int)v.y.value >> 0x18 & 0x80));
        ((unsigned char *)&m)[9]  = (unsigned char)((unsigned int)v.y.value >> 8);
        ((unsigned char *)&m)[10] = (unsigned char)v.y.value;

        v.z = s->z;
        ((unsigned char *)&m)[11] = (unsigned char)(((unsigned int)v.z.value >> 0x10 & 0x7f) | ((unsigned int)v.z.value >> 0x18 & 0x80));
        ((unsigned char *)&m)[12] = (unsigned char)((unsigned int)v.z.value >> 8);
        ((unsigned char *)&m)[13] = (unsigned char)v.z.value;

        cb = *(void (**)(int, struct Msg *, int))(*node + 0x24);
        if (cb != 0) {
            cb(*node, &m, 0xe);
        }
        *(signed char *)(*node + 0x1c7) = 0;
        return 1;
    }
    return 0;
}
