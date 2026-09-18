/* Recoil tick of the ov161 enemy (x2: ov161/162). Walks the scene's +0xa8 object list and, for
 * every visible object (+0x40 bit 1, +0x60 bit 0) closer than 0xc000 (surface to surface), adds
 * a sideways drift to its +0xe4 velocity: the direction from the object to the actor, bent by its
 * cross product with the world up axis, normalised and scaled by (1 - dist / 0xc000) * 0x300.
 * While the +0x58 latch is set the actor's +0x60 bit 6 is dropped, the +0x18 velocity takes the
 * +0x24 vector and the +0x30 counter runs: past 3 with the +0x17a bit-0 flag set the latch clears,
 * otherwise +0x28 sinks by 30 frames * 0x80 per frame; with the latch clear bit 6 is set and the
 * counter reset. A set +0x3cc bit 0 on the actor ends the state with sub-state 8. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { int x, y, z; } Vec3;

struct ListNode {
    void *item;
};

struct Flags60 {
    u16 lo : 8;
    u16 hi : 8;
};

struct Bit0 { int b0 : 1; };
struct Bits40 { int b0 : 1, b1 : 1; };
struct Flags17a { unsigned char b0 : 1; };

extern struct ListNode *func_01fffd70(void *list);
extern struct ListNode *func_01fffd8c(void *list);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int FX_Inv(int a, int b);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042240;

void func_ov162_020d038c(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 drift;
    Vec3 side;
    char *world;
    char *obj;
    struct ListNode *ln;
    int actor;
    int dist;
    int t;

    world = *(char **)(*state + 4);
    ln = func_01fffd70(world + 0xa8);
    obj = ln == 0 ? 0 : (char *)ln->item;
    while (obj != 0) {
        if (((struct Bits40 *)(obj + 0x40))->b1 && (((struct Flags60 *)(obj + 0x60))->lo & 1) != 0) {
            VEC_Subtract((Vec3 *)(*state + 0x74), (Vec3 *)(obj + 0x74), &dir);
            actor = *state;
            dist = func_01ff8d18(&dir, &dir) - (*(int *)(obj + 0x80) + *(int *)(actor + 0x80));
            if (dist <= 0xc000) {
                t = FX_Inv(dist, 0xc000);
                if (t < 0) {
                    t = 0;
                }
                if (t > 0x1000) {
                    t = 0x1000;
                }
                VEC_CrossProduct(&data_02042240, &dir, &side);
                VEC_Add(&dir, &side, &dir);
                func_01ff8d18(&dir, &dir);
                func_01ffa724((int)(((long long)(0x1000 - t) * 0x300 + 0x800) >> 12), &dir, &drift);
                VEC_Add((Vec3 *)(obj + 0xe4), &drift, (Vec3 *)(obj + 0xe4));
            }
        }
        ln = func_01fffd8c(world + 0xa8);
        obj = ln == 0 ? 0 : (char *)ln->item;
    }
    if (state[0x16] != 0) {
        ((struct Flags60 *)(*state + 0x60))->hi &= ~0x40;
        *(Vec3 *)(state + 6) = *(Vec3 *)(state + 9);
        state[0xc]++;
        if (state[0xc] > 3 && ((struct Flags17a *)(*state + 0x17a))->b0) {
            state[0x16] = 0;
        } else {
            state[10] -= (int)(((long long)(*(int *)(*node + 0x2c) * 0x1e) * 0x80 + 0x800) >> 12);
        }
    } else {
        u16 *hw = (u16 *)(*state + 0x60);
        unsigned int h = *hw;
        *hw = h & ~0xff00 | (((((u32)h << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
        state[0xc] = 0;
    }
    if (((struct Bit0 *)(*state + 0x3cc))->b0) {
        *(unsigned char *)(*state + 0x1c7) = 8;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
