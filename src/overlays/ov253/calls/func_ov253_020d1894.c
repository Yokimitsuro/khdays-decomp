/* func_ov253_020d1894 -- ring lay-out along the chain: the owner's ring entries (stride 0x38,
 * count at +0x8c) are spread over the four segments between the actor's +0x390..+0x39c joints
 * and the +0x3ac one, a quarter of them per segment, each placed at its fraction along the
 * segment (raised by 0.5) with scale 1.0 (the last segment's entries grow with the fraction);
 * the owner's +0x88 model rebinds channels 0, 2, 1 and 4 to its +0xe0 and clears them; the
 * node moves to 020d1af4. */
typedef struct { int x, y, z; } Vec3;
struct Ov253JointsNext { char *cur[1]; char *next[4]; };
struct Ov253Links { char pad[0x390]; char *link[4]; };

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202accc(int object, int channel, void *target, int flag);
extern void func_01fff774(int object, int channel, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020d1af4(void);

void func_ov253_020d1894(int *node) {
    int *state = (int *)node[1];
    Vec3 a;
    Vec3 b;
    char *joints[5];
    Vec3 pos;
    int i;
    int actor = *state;
    int quarter = *(int *)(state[1] + 0x8c) / 4;
    int seg;
    int t;
    char *entry;

    for (i = 0; i < 4; i++) {
        joints[i] = ((struct Ov253Links *)actor)->link[i];
    }
    joints[i] = *(char **)(actor + 0x3ac);
    for (i = 0; i < *(int *)(state[1] + 0x8c); i++) {
        entry = *(char **)(state[1] + 0x90) + i * 0x38;
        seg = i / quarter;
        t = ((i % quarter) << 12) / quarter;
        a = *(Vec3 *)(joints[seg] + 0x14);
        b = *(Vec3 *)(joints[seg + 1] + 0x14);
        VEC_Subtract(&b, &a, &pos);
        func_01ffa724(t, &pos, &pos);
        VEC_Add(&a, &pos, &pos);
        pos.y += 0x800;
        *(Vec3 *)(entry + 0x2c) = pos;
        if (seg + 1 == 4) {
            *(int *)entry = (t << 1) + 0x1000;
        } else {
            *(int *)entry = 0x1000;
        }
    }
    func_0202accc(*(int *)(state[1] + 0x88), 0, (void *)(*(int *)(state[1] + 0x88) + 0xe0), 0);
    func_01fff774(*(int *)(state[1] + 0x88), 0, 0);
    func_0202accc(*(int *)(state[1] + 0x88), 2, (void *)(*(int *)(state[1] + 0x88) + 0xe0), 0);
    func_01fff774(*(int *)(state[1] + 0x88), 2, 0);
    func_0202accc(*(int *)(state[1] + 0x88), 1, (void *)(*(int *)(state[1] + 0x88) + 0xe0), 0);
    func_01fff774(*(int *)(state[1] + 0x88), 1, 0);
    func_0202accc(*(int *)(state[1] + 0x88), 4, (void *)(*(int *)(state[1] + 0x88) + 0xe0), 0);
    func_01fff774(*(int *)(state[1] + 0x88), 4, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d1af4);
}
