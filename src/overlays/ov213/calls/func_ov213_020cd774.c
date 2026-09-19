/* Retreat entry: broadcasts the +4 anchor position as a 14-byte message built from the
 * data_ov213_020d2ed6 template (byte 4 = 1; three components packed as sign + 23-bit magnitude
 * split high/mid/low) through the actor's +0x24 hook, raises flags 0x82 in the +0x60 high byte
 * and bit 0 of +0x1ae, clears bit 0 in the low byte of the +0x3d4 slot's +8 word, resets the
 * +0x1c timer and moves the node to 020cd8ec.
 *
 * Coordinates are held in a one-value wrapper type (Fx32): copying a wrapped value is a struct
 * copy, which mwcc keeps, and that is the ROM's unread stack copy of the position. The message
 * buffer is indexed directly at every use (a cached byte pointer would take a register). */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

struct Msg { unsigned short h[7]; };
struct bf { unsigned b : 8; };
extern struct Msg data_ov213_020d2ed6;
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov213_020cd8ec(void);

void func_ov213_020cd774(int *node) {
    int *state = (int *)node[1];
    struct Msg m;
    FxVec v;
    FxVec *pos;
    void (*cb)(int, struct Msg *, int);

    m = data_ov213_020d2ed6;
    pos = (FxVec *)state[1];

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
    ((unsigned char *)&m)[4] = 1;

    cb = *(void (**)(int, struct Msg *, int))(*state + 0x24);
    if (cb != 0) {
        cb(*state, &m, 0xe);
    }
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x82;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    *(unsigned short *)(*state + 0x100 + 0xae) |= 1;
    ((struct bf *)(*(int *)(*state + 0x3d4) + 8))->b &= ~1;
    state[7] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov213_020cd8ec);
}
