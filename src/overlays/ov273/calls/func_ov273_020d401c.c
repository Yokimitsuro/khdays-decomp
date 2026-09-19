/* Stagger entry: clears bit 0 and raises flags 0x86 in the actor's +0x60 high byte, clears bit 0
 * in the low byte of the +0x3d4 slot's +8 word, broadcasts the +4 anchor position as a 14-byte
 * message built from the data_ov273_020d6ab4 template (three components packed as sign + 23-bit
 * magnitude split high/mid/low) through the actor's +0x24 hook, spawns effect 0 (kind 0x49) at
 * the actor's +0x74 position, resets the +0x1c7 request and dispatches null.
 *
 * Coordinates are held in a one-value wrapper type (Fx32): copying a wrapped value is a struct
 * copy, which mwcc keeps, and that is the ROM's unread stack copy of the position. */
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct Msg { unsigned short h[7]; };
struct bf { unsigned b : 8; };
extern struct Msg data_ov273_020d6ab4;
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov273_020d401c(int *node) {
    int *state = (int *)node[1];
    struct Msg m;
    FxVec v;
    FxVec *pos;
    void (*cb)(int, struct Msg *, int);

    {
        int actor = *state;
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x86;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    ((struct bf *)(*(int *)(*state + 0x3d4) + 8))->b &= ~1;

    m = data_ov273_020d6ab4;
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

    cb = *(void (**)(int, struct Msg *, int))(*state + 0x24);
    if (cb != 0) {
        cb(*state, &m, 0xe);
    }
    func_ov107_020c5af8(*state, 0, 0x49, *state + 0x74);
    *(signed char *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)(node + 8), 0);
}
