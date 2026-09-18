/* Dash tick of the ov175 enemy (and its byte-identical twins). Sweeps the +0x38c item's own sphere (the
 * actor's +0x74 position and +0x80 radius); the first victim that accepts a flat 0x800 push away
 * from the actor gets the +4 position published to the item (mode 2) and reaction 0x142 mode 6,
 * and the state ends with sub-state 0. Otherwise a set +0x17a bit 0 or bit 1 publishes the
 * position with mode 1, fires reaction 0x142 mode 7 and ends the same way; else the +0x20 travel
 * accumulates the +8 velocity's length and ends the dash once it passes 0x15000. */
typedef unsigned char u8;

struct Vecx32 { int x, y, z; };
struct Sphere { struct Vecx32 vCentre; int nRadius; };
struct Flags17a { u8 b0 : 1, b1 : 1; };

extern int func_ov107_020c8eb8(void *item, struct Sphere *sphere, void *out);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern int func_ov107_020ca918(void *hit, int actor, void *item, int mode, void *push, int z);
extern void func_ov107_020c0b90(void *item, int a, struct Vecx32 v, int b);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern int VEC_Mag(const struct Vecx32 *v);

void func_ov176_020d2484(int *node)
{
    int *state = (int *)node[1];
    struct Sphere sphere;
    void *hits[4];
    struct Vecx32 push;
    int i;
    int n;
    int actor;

    sphere = *(struct Sphere *)(*state + 0x74);
    n = func_ov107_020c8eb8(*(void **)(*state + 0x38c), &sphere, hits);
    i = 0;
    if (n > 0) {
        do {
            VEC_Subtract((char *)hits[i] + 0x74, (void *)(*state + 0x74), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(void **)(*state + 0x38c), 0, &push, 0) != 0) {
                func_ov107_020c0b90(*(void **)(*state + 0x38c), 2, *(struct Vecx32 *)state[1], 0);
                func_ov107_020c5af8(*state, 0x142, 6, (void *)state[1]);
                *(u8 *)(*state + 0x1c7) = 0;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            i++;
        } while (i < n);
    }
    actor = *state;
    if (((struct Flags17a *)(actor + 0x17a))->b0) {
        func_ov107_020c0b90(*(void **)(actor + 0x38c), 1, *(struct Vecx32 *)state[1], 0);
        func_ov107_020c5af8(*state, 0x142, 7, (void *)state[1]);
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (((struct Flags17a *)(actor + 0x17a))->b1) {
        func_ov107_020c0b90(*(void **)(actor + 0x38c), 1, *(struct Vecx32 *)state[1], 0);
        func_ov107_020c5af8(*state, 0x142, 7, (void *)state[1]);
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[8] += VEC_Mag((struct Vecx32 *)(state + 2));
    if (state[8] < 0x15000) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
