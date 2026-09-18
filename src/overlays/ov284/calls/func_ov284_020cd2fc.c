/* Chain layout of the ov284 enemy: gathers the actor's four +0x388 parts and the +0x3a4 tail
 * into a five-entry list, then places every segment of the +4 item's +0x90 array (count at
 * +0x8c, 0x38 bytes each) on the polyline through the parts' +0x14 positions -- segment i sits
 * at a quarter-count fraction between parts i / step and i / step + 1 (0x800 above it) and its
 * +0 scale is 1.0, or 1.0 + 2 x the fraction on the last span. Finally binds the item's +0x88
 * model on channels 0, 2, 1 and 4 (0202accc against its +0xe0 block, 01fff774) and hands the
 * node to 020cd55c. Codegen: the segment counter is initialised at its declaration, before the
 * actor local (the gather loop then counts in r3 and keeps the actor in r4). */
typedef struct { int x, y, z; } Vec3;

extern long long func_02020400(int num, int den);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202accc(int model, int channel, void *block, int a);
extern void func_01fff774(int model, int channel, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov284_020cd55c(void);

void func_ov284_020cd2fc(int *node)
{
    int *state = (int *)node[1];
    int i = 0;
    int *actor = (int *)state[0];
    int item = state[1];
    int count = *(int *)(item + 0x8c);
    int step = count / 4;
    Vec3 a;
    Vec3 b;
    int parts[5];
    Vec3 d;
    int idx;
    int frac;
    char *seg;

    for (; i < 4; i++) {
        parts[i] = actor[0xe2 + i];
    }
    parts[i] = actor[0xe9];
    for (i = 0; i < count; i++) {
        seg = *(char **)(item + 0x90) + i * 0x38;
        idx = (int)func_02020400(i, step);
        frac = (int)func_02020400((int)(func_02020400(i, step) >> 32) << 12, step);
        a = *(Vec3 *)(parts[idx] + 0x14);
        b = *(Vec3 *)(parts[idx + 1] + 0x14);
        VEC_Subtract(&b, &a, &d);
        func_01ffa724(frac, &d, &d);
        VEC_Add(&a, &d, &d);
        d.y += 0x800;
        *(Vec3 *)(seg + 0x2c) = d;
        if (idx + 1 == 4) {
            *(int *)seg = (frac << 1) + 0x1000;
        } else {
            *(int *)seg = 0x1000;
        }
        item = state[1];
        count = *(int *)(item + 0x8c);
    }
    func_0202accc(*(int *)(item + 0x88), 0, (void *)(*(int *)(item + 0x88) + 0xe0), 0);
    func_01fff774(*(int *)(state[1] + 0x88), 0, 0);
    func_0202accc(*(int *)(state[1] + 0x88), 2, (void *)(*(int *)(state[1] + 0x88) + 0xe0), 0);
    func_01fff774(*(int *)(state[1] + 0x88), 2, 0);
    func_0202accc(*(int *)(state[1] + 0x88), 1, (void *)(*(int *)(state[1] + 0x88) + 0xe0), 0);
    func_01fff774(*(int *)(state[1] + 0x88), 1, 0);
    func_0202accc(*(int *)(state[1] + 0x88), 4, (void *)(*(int *)(state[1] + 0x88) + 0xe0), 0);
    func_01fff774(*(int *)(state[1] + 0x88), 4, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov284_020cd55c);
}
