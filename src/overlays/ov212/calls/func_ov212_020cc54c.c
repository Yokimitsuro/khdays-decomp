typedef struct { int x, y, z; } VecFx32;
typedef struct { char pad0[0x24]; VecFx32 pos; } Probe;

extern void func_0203bc78(int a, int b);
extern int func_02016320(int a, Probe *out, int b, int c);
extern int VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Mag(void *v);
extern int func_0203b9fc(void *a, int b, short c, int d);
extern VecFx32 data_02041dc8;

/* Re-probe the world and refresh the cached aim point (x3: ov212/266/267). Sibling
 * of func_ov212_020cc4e0, which probes the same way; this one also keeps the delta
 * from the previous hit and stores its length at owner+0x578. Once the actor is no
 * longer held (obj+0xad), stop: cancel the pending animation, and clear the cached
 * point, its distance and the two stance bytes. */
void func_ov212_020cc54c(int obj, int param_2) {
    Probe probe;
    VecFx32 hit;
    VecFx32 delta;
    int owner = *(int *)(obj + 0x84);
    short v;

    func_0203bc78(obj, param_2);
    if (func_02016320(*(int *)(obj + 0x88) + 0x20, &probe, 0, *(int *)(owner + 0x588)) != 0) {
        hit = probe.pos;
        VEC_Subtract(&hit, (void *)(owner + 0x4e4), &delta);
        *(VecFx32 *)(owner + 0x4e4) = hit;
        *(int *)(owner + 0x578) = VEC_Mag(&delta);
    }
    if (*(unsigned char *)(obj + 0xad) != 0) {
        return;
    }
    v = *(short *)(*(int *)(obj + 0x88) + 2);
    if (v >= 0) {
        func_0203b9fc((void *)obj, 0, v, 0);
    }
    *(int *)(owner + 0x578) = 0;
    *(VecFx32 *)(owner + 0x4e4) = data_02041dc8;
    *(int *)(owner + 0x5dc) = 0;
    *(char *)(owner + 0x5e0) = 0;
    *(char *)(owner + 0x5e1) = 0;
}
