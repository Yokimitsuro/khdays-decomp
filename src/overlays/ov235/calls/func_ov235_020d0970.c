/* Gust tick of an ov235 state: the +0x54 timer accumulates the frame rate and at 1.77 reaction
 * +0x3c8 mode 0xe fires once at the +4 point (+0x65). The +0x44 timer accumulates it too, and
 * from 1.625 on every live, solid object of the world's +0xa8 list within 6.0 of the owner (the
 * gap between their +0x74 centres less both +0x80 radii) is pushed away along the direction from
 * the owner: 0.75 scaled by how close it is, added to its +0xe4 push. Once the +0xc idle byte
 * clears, animation 0x19 plays, the +0x3a8 part plays motion 0x13 and the tick hands over to
 * func_ov235_020d0b5c. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { void *item; } ListNode;
struct Bits40 { int b0 : 1, b1 : 1; };
struct Flags60 { u16 lo : 8; u16 hi : 8; };

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern ListNode *func_01fffd70(void *list);
extern ListNode *func_01fffd8c(void *list);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020d0b5c(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov235_020d0970(int *node)
{
    int *state = (int *)node[1];
    int world = *(int *)(*state + 4);
    Vec3 d;
    Vec3 push;
    ListNode *link;
    char *obj;
    int gap;
    int t;

    state[0x15] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x65) == 0 && state[0x15] >= 0x1c44) {
        func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0xe, (void *)state[1]);
        *((unsigned char *)state + 0x65) = 1;
    }
    state[0x11] += *(int *)(node[0] + 0x2c);
    if (state[0x11] >= 0x1a00) {
        link = func_01fffd70((void *)(world + 0xa8));
        obj = link == 0 ? 0 : (char *)link->item;
        while (obj != 0) {
            if (((struct Bits40 *)(obj + 0x40))->b1 && (((struct Flags60 *)(obj + 0x60))->lo & 1) != 0) {
                int owner;

                VEC_Subtract(obj + 0x74, (void *)(*state + 0x74), &d);
                owner = *state;
                gap = func_01ff8d18(&d, &d) - (*(int *)(obj + 0x80) + *(int *)(owner + 0x80));
                if (gap <= 0x6000) {
                    t = FX_Inv(gap, 0x6000);
                    if (t < 0) {
                        t = 0;
                    }
                    if (t > 0x1000) {
                        t = 0x1000;
                    }
                    func_01ff8d18(&d, &d);
                    func_01ffa724(FX_Mul(0x1000 - t, 0xc00), &d, &push);
                    VEC_Add(obj + 0xe4, &push, obj + 0xe4);
                }
            }
            link = func_01fffd8c((void *)(world + 0xa8));
            obj = link == 0 ? 0 : (char *)link->item;
        }
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x19, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a8), 0x13, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d0b5c);
}
