typedef unsigned char u8;

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

struct Ov140RushState {
    void *pOwner;
    char pad004[0x1c];
    Vec3 vInitialDirection;
    Vec3 vDirection;
    int nSpeed;
    int nTimer;
    char pad040[4];
    void *pTarget;
    Vec3 *pPosition;
    Vec3 *pEffectPosition;
    u8 pad050[4];
    u8 nPhase;
};

extern void func_ov107_020c9264(void *actor, int animation, int loop);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *source, void *dest);
extern void func_ov107_020c5af8(void *actor, int reaction, int mode,
                                Vec3 *position);
extern void func_0203c634(int *node, int slot, void *callback);
extern const Vec3 data_02042258;
extern void func_ov140_020d1f18(void);

void func_ov140_020d1e58(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264((void *)*state, 9, 0);
    if (state[0x11] != 0) {
        VEC_Subtract((void *)state[0x12],
                     (void *)(state[0x11] + 0x190),
                     state + 0xb);
        state[0xc] = 0;
    } else {
        *(Vec3 *)(state + 0xb) = *(Vec3 *)(state + 8);
        state[0xc] = 0;
    }
    if (func_01ff8d18(state + 0xb, state + 0xb) == 0) {
        *(Vec3 *)(state + 0xb) = data_02042258;
    }
    state[0xe] = 0x800;
    *(u8 *)((char *)state + 0x54) = 0;
    state[0xf] = 0;
    func_ov107_020c5af8((void *)*state, 0x11f, 8, (Vec3 *)state[0x13]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20),
                  func_ov140_020d1f18);
}
