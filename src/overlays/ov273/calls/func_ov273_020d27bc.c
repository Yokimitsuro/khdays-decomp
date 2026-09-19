/* Regroup tick: once the +0x3dc partner raises bit 2 of its +0x394 word, the +4 anchor position
 * is broadcast as a 14-byte message built from the data_ov273_020d6afa template (byte 4 = 1;
 * three components packed as sign + 23-bit magnitude split high/mid/low) through the actor's
 * +0x24 hook, the +0x1c timer clears and the node moves to 020cecfc. Until then the lock-on
 * target is re-acquired into +0x24 and, when present, the +0xc velocity is the direction to it
 * scaled by the distance capped at 4.0.
 *
 * Coordinates are held in a one-value wrapper type (Fx32): copying a wrapped value is a struct
 * copy, which mwcc keeps, and that is the ROM's unread stack copy of the position. */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct v3 { int x, y, z; };
struct Msg { unsigned short h[7]; };
struct Flags394 { int b0 : 1; int b1 : 1; int b2 : 1; };
extern struct Msg data_ov273_020d6afa;
extern void func_0203c634(void *obj, int idx, void *value);
extern int  func_ov107_020cab14(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *v, void *out);
extern void func_01ffa724(int s, void *v, void *d);
extern void func_ov273_020d293c(void);

void func_ov273_020d27bc(int *node) {
    int *state = (int *)node[1];
    struct Msg m;
    struct v3 dir;
    FxVec v;
    FxVec *pos;
    void (*cb)(int, struct Msg *, int);
    int target;
    int dist;

    if (((struct Flags394 *)(*(int *)(*state + 0x3dc) + 0x394))->b2 != 0) {
        m = data_ov273_020d6afa;
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
        state[7] = 0;
        func_0203c634(node, *(signed char *)(node + 8), func_ov273_020d293c);
        return;
    }
    target = state[9] = func_ov107_020cab14(*state, 0);
    if (target == 0) return;
    VEC_Subtract((void *)(target + 0x74), (void *)state[1], &dir);
    dist = func_01ff8d18(&dir, &dir);
    if (dist > 0x4000) dist = 0x4000;
    func_01ffa724(dist, &dir, state + 3);
}
