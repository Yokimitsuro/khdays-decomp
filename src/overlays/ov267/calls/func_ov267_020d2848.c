struct vec3 { int x, y, z; };

extern void func_0202f384(struct vec3 *out, const void *mtx, struct vec3 *in);
extern void VEC_Add(struct vec3 *a, struct vec3 *b, struct vec3 *c);
extern void func_ov107_020c0b90(int obj, int cmd, struct vec3 v, int flag);
extern void func_ov107_020c5af8(int a, int b, int c, void *d);
extern void func_0203c634(void *self, int idx, void *cb);
extern void func_ov267_020d2920(void);

/* Wind-up wait, then fire the effect (x3: ov212/266/267). Accumulate dt into the
 * phase timer (ctx1+0x40) and bail until it reaches 3400. Then take the fixed
 * local offset {0, 10650, 6327}, rotate it by the owner's orientation matrix
 * (owner+0xa0) and add the anchor point (ctx1[2]) to get a world position; spawn
 * the effect there, kick the 0x48 animation, reset the timer and advance state. */
void func_ov267_020d2848(void *self) {
    int *c0 = ((int **)self)[0];
    int *c1 = ((int **)self)[1];
    struct vec3 v;
    int t = c1[0x10] + c0[0xb];

    c1[0x10] = t;
    if (t < 3400) {
        return;
    }
    v.x = 0;
    v.y = 10650;
    v.z = 6327;
    func_0202f384(&v, (const void *)(c1[0] + 0xa0), &v);
    VEC_Add(&v, (struct vec3 *)c1[2], &v);
    func_ov107_020c0b90(c1[0], 0, v, 0);
    func_ov107_020c5af8(c1[0], 0, 0x48, (void *)(c1[0] + 0x74));
    c1[0x10] = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), func_ov267_020d2920);
}
