/* Drop entry of the ov256 actor's shell: a 10.0 drop ray from the +0xc point finds the ground (the
 * rig's world collision) and the point's +0x10 height moves down by the hit fraction of it. The shell
 * rig (+0) is reset and placed at the point, shown again (flag 1 of its +0x5c clears), actions
 * 0/2/4/3/1 are disabled and its animation stopped; the +0x18 clock and +0x1c flag reset and brain
 * slot +0x20 runs 020d0e5c. */
typedef struct { int x, y, z; } Vec3;

extern int func_01fff920(int collision, Vec3 *start, Vec3 *ray);
extern void func_0203c960(void *transform);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void func_0203c7ac(int item, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020d0e5c(void);

void func_ov256_020d0d18(int *node)
{
    int *state = (int *)node[1];
    Vec3 ray = {0};
    int hit;
    int world;

    world = *(int *)(state[1] + 4);
    ray.y = -0xa000;
    hit = func_01fff920(*(int *)(world + 0x7c), (Vec3 *)(state + 3), &ray);
    if (hit != 0) {
        state[4] += (int)(((long long)*(int *)(hit + 0xc) * ray.y) >> 27);
    }
    func_0203c960((void *)(*state + 4));
    func_0203ca30((void *)(*state + 4), (Vec3 *)(state + 3));
    *(int *)(*state + 0x5c) &= ~2;
    func_0203b9fc(*state, 0, 0, 0);
    func_0203b9fc(*state, 2, 0, 0);
    func_0203b9fc(*state, 4, 0, 0);
    func_0203b9fc(*state, 3, 0, 0);
    func_0203b9fc(*state, 1, 0, 0);
    func_0203c7ac(*state, 0);
    state[6] = 0;
    *(unsigned char *)(state + 7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020d0e5c);
}
