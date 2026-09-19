/* Volley tick: while the +0x6a latch is clear the +0x70 timer runs and past 0x1555 the latch is
 * set and effect 7 is spawned at the zero vector. The +0x1c countdown runs by the frame step;
 * each time it expires with fewer than four (+0x64) pairs launched it is reseeded to
 * rand(0x301) + 0x100, the pair's two projectiles (+0x3e0 table) are placed at the +0x3f0 / +0x3f4
 * anchors (+0x14) and told to launch through their +0x1cc hook. Unless the +8 flag byte is set,
 * pose request 5 is queued and the node dispatches null. */
struct vec3 { int x, y, z; };
struct Pair { int a, b; };
typedef void (*LaunchHook)(int part, int arg);
extern void func_ov107_020c0b90();  /* K&R + const vector: hoists the pool load over the latch store */
extern int  func_02023eb4(int bound);
extern void func_0203ca30(int srt, int translation);
extern void func_0203c634(int self, int idx, int cb);
extern const struct vec3 data_02041dc8;

void func_ov273_020d3a88(int *self) {
    int *state = (int *)self[1];

    if (*((unsigned char *)state + 0x6a) == 0) {
        state[0x1c] += *(int *)(self[0] + 0x2c);
        if (state[0x1c] >= 0x1555) {
            *((unsigned char *)state + 0x6a) = 1;
            func_ov107_020c0b90(*state, 7, data_02041dc8, 0);
        }
    }
    state[7] -= *(int *)(self[0] + 0x2c);
    if (state[7] < 0 && state[0x19] < 4) {
        int a;
        int b;
        state[7] = func_02023eb4(0x301) + 0x100;
        a = ((struct Pair *)*(int *)(*state + 0x3e0))[state[0x19]].a;
        b = ((struct Pair *)*(int *)(*state + 0x3e0))[state[0x19]].b;
        func_0203ca30(a + 0xa0, *(int *)(*state + 0x3f0) + 0x14);
        func_0203ca30(b + 0xa0, *(int *)(*state + 0x3f4) + 0x14);
        {
            LaunchHook hook = *(LaunchHook *)(a + 0x1cc);
            if (hook != 0) hook(a, 0);
        }
        {
            LaunchHook hook = *(LaunchHook *)(b + 0x1cc);
            if (hook != 0) hook(b, 0);
        }
        state[0x19]++;
    }
    if (*(unsigned char *)state[2] != 0) return;
    *(unsigned char *)(*state + 0x1c7) = 5;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
