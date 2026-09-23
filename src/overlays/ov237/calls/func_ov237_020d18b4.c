/* Start of the ov237 spark emitter: the owner's +0x78 draw hook becomes 020d1610 (context = this
 * state), tracks 0, 2, 4 and 1 of its +0x88 animation bind to the +0xe0 table, the +8 point is the
 * node's +0x2c and every record of the +0x90 ring (+0x8c of them) is reset to kind 0, scale 1.0, the
 * identity rotation and the +0xc owner's +0xb0 pose; the cursor (+4) rewinds. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { int kind; int scale; Quat rot; int a; int value; int c; char pad24[8]; Vec3 pos; } Particle;

extern void func_0202accc(int a, int b, int c, int d);
extern void func_ov237_020d1610(void);
extern const Quat data_020420f8;

void func_ov237_020d18b4(int *node)
{
    int *state = (int *)node[1];
    int i;

    *(void **)(*state + 0x78) = func_ov237_020d1610;
    *(int **)(*state + 0x84) = state;
    func_0202accc(*(int *)(*state + 0x88), 0, *(int *)(*state + 0x88) + 0xe0, 0);
    func_0202accc(*(int *)(*state + 0x88), 2, *(int *)(*state + 0x88) + 0xe0, 0);
    func_0202accc(*(int *)(*state + 0x88), 4, *(int *)(*state + 0x88) + 0xe0, 0);
    func_0202accc(*(int *)(*state + 0x88), 1, *(int *)(*state + 0x88) + 0xe0, 0);
    state[2] = node[0] + 0x2c;
    for (i = 0; i < *(int *)(*state + 0x8c); i++) {
        Quat rot = data_020420f8;
        Particle *p = (Particle *)(*(int *)(*state + 0x90) + i * 0x38);

        p->kind = 0;
        p->scale = 0x1000;
        p->rot = rot;
        p->pos = *(Vec3 *)(state[3] + 0xb0);
    }
    state[1] = 0;
}
