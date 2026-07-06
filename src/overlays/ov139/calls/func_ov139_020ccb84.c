typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef struct ActorFlags60 {
    unsigned short lo : 8;
    unsigned short hi : 8;
} ActorFlags60;

extern int func_ov107_020cab14(int actor, int arg);
extern void VEC_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int actor, int a, int b);
extern void func_0203c634(void *node, int idx, void *next);
extern void func_ov139_020ccc4c(void);

void func_ov139_020ccb84(int *node) {
    Vec3 delta;
    int *frame = (int *)node[0];
    int *state = (int *)node[1];
    int timer = state[0xf] + frame[0xb];
    int target;
    int angle;

    state[0xf] = timer;
    if (timer < 0x6ee) return;

    target = func_ov107_020cab14(*state, 0);
    state[0x1] = target;
    if (target != 0) {
        VEC_Subtract((Vec3 *)(target + 0x74), (Vec3 *)state[0x13], &delta);
        angle = func_020050b4(delta.x, delta.z);
        state[0x2] = state[0x3] = angle;
    }

    ((ActorFlags60 *)(*state + 0x60))->hi &= ~0x80;
    func_ov107_020c9264(*state, 0, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov139_020ccc4c);
}
