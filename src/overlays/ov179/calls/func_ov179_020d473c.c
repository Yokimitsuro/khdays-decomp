/* Settle-pose hold of the ov178 enemy (x3: ov178/179/180): plays pose 1 while the actor's +0xad
 * flag is clear; every 0x800 of the node's +0x2c speed it sweeps a 0x2000 sphere around the
 * actor's +0x74 position through the pool's collision query and applies hit 1 (push from the
 * zero vector, flags 0x10) to everything it finds. The +0xc timer runs to 0xa000 -- or ends
 * early when the pool's +0x60 low byte has bit 7 set -- and then the target position (+8) is
 * pushed to the render hook (cmd 1), pose 2 plays and the release handler (020cee40) follows. */
typedef unsigned short u16;
struct vec3 { int x, y, z; };
typedef struct { int w[4]; } Vec4;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov107_020c9264(int obj, int anim, int flag);
extern int func_ov107_020c8eb8(int owner, Vec4 *src, int *out);
extern int func_ov107_020ca918(int victim, int a, int b, int mode, void *push, int flags);
extern void func_ov107_020c0b90(int obj, int cmd, struct vec3 v, int flag);
extern void func_0203c634(int obj, int slot, void *cb);
extern struct vec3 data_02041dc8;
extern void func_ov179_020d48a0(void);

void func_ov179_020d473c(int node) {
    int *state = *(int **)(node + 4);
    Vec4 sphere;
    int hits[4];
    int i;
    int n;

    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 1, 1);
    }
    state[4] += *(int *)(*(int *)node + 0x2c);
    if (state[4] >= 0x800) {
        state[4] = 0;
        sphere = *(Vec4 *)(*state + 0x74);
        sphere.w[3] = 0x2000;
        n = func_ov107_020c8eb8(*(int *)(*state + 0x388), &sphere, hits);
        for (i = 0; i < n; i++) {
            func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x388), 1, &data_02041dc8, 0x10);
        }
    }
    state[3] += *(int *)(*(int *)node + 0x2c);
    if (state[3] < 0xa000 && (((struct hw60 *)(*(int *)(*state + 0x388) + 0x60))->lo & 0x80) == 0) {
        return;
    }
    {
        struct vec3 v = *(struct vec3 *)state[2];
        func_ov107_020c0b90(*(int *)(*state + 0x388), 1, v, 0);
    }
    func_ov107_020c9264(*state, 2, 0);
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov179_020d48a0);
}
