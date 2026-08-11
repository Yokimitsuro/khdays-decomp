typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_ov107_020cab14(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int actor, int a, int b);
extern void func_ov107_020c5af8(int actor, int resource, int mode, int position);
extern void func_0203c634(void *node, int index, void *next);
extern void func_ov281_020cd2e0(void);

struct Ov281ActorFlags60 {
    unsigned short lo : 8;
    unsigned short hi : 8;
};

void func_ov281_020cd1fc(int *node)
{
    int *owner = (int *)node[0];
    int *state = (int *)node[1];
    VecFx32 delta;
    int timer;
    int heading;

    timer = state[6] + owner[11];
    state[6] = timer;
    if (timer < 0x6ee) {
        return;
    }

    state[2] = func_ov107_020cab14(state[0], 0);
    if (state[2] != 0) {
        VEC_Subtract((void *)(state[2] + 0x74), (void *)(state[0] + 0x74), &delta);
        heading = func_020050b4(delta.x, delta.z);
        state[5] = heading;
        state[4] = heading;
    }

    ((struct Ov281ActorFlags60 *)(state[0] + 0x60))->hi &= ~0x82;
    func_ov107_020c9264(state[0], 0, 0);
    func_ov107_020c5af8(state[0], 0x169, 6, state[3]);
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov281_020cd2e0);
}
