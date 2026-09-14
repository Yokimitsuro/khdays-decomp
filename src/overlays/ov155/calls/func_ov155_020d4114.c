/* func_ov155_020d4114 -- broadcast this node's position. When the caller's flag word has both
 * bit 0 and bit 4 set, build the 14-byte message from the template at data_ov155_020d58c4, pack
 * the node's position vector into bytes 5..13 (three components, each as sign + 23-bit magnitude
 * split high/mid/low), hand it to the object's message hook with length 0xe, clear the pending
 * byte at +0x1c7 and report success. Head of a 5-member family.
 *
 * Coordinates are held in a one-value wrapper type (Fx32). This is a tentative reconstruction
 * of the original's coordinate type, not a proven one: copying a wrapped value is a struct copy,
 * which mwcc keeps, and that is the ROM's unread stack copy of the position.
 *
 * DO NOT CACHE A POINTER TO THE MESSAGE BUFFER.
 * With `p = (unsigned char *)&m;` mwcc keeps `p` in a register and addresses the bytes as
 * `[p, #5]`. Indexing `m` directly at every use lets it fold the whole thing into the frame
 * pointer, `[sp, #0x11]`, which is what the ROM does and what frees the last register.
 */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

struct Msg { unsigned short h[7]; };
extern struct Msg data_ov155_020d58c4;

int func_ov155_020d4114(int self, int a, unsigned int *flags, int d) {
    int *node = *(int **)(self + 0x214);
    struct Msg m;
    FxVec v;
    FxVec *pos;
    void (*cb)(int, struct Msg *, int);

    if (((unsigned short)*flags & 1) != 0 && ((unsigned short)*flags & 0x10) != 0) {
        m = data_ov155_020d58c4;
        pos = (FxVec *)node[1];

        v.x = pos->x;
        ((unsigned char *)&m)[5]  = (unsigned char)(((unsigned int)v.x.value >> 0x10 & 0x7f) | ((unsigned int)v.x.value >> 0x18 & 0x80));
        ((unsigned char *)&m)[6]  = (unsigned char)((unsigned int)v.x.value >> 8);
        ((unsigned char *)&m)[7]  = (unsigned char)v.x.value;

        v.y = pos->y;
        ((unsigned char *)&m)[8]  = (unsigned char)(((unsigned int)v.y.value >> 0x10 & 0x7f) | ((unsigned int)v.y.value >> 0x18 & 0x80));
        ((unsigned char *)&m)[9]  = (unsigned char)((unsigned int)v.y.value >> 8);
        ((unsigned char *)&m)[10] = (unsigned char)v.y.value;

        v.z = pos->z;
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
