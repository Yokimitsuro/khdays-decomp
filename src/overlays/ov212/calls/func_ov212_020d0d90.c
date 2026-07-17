/* Lock on and start a lunge (x3: ov212/266/267). Pick the current target; with none,
 * do nothing. Otherwise take the direction from the owner (owner+0xb0) to the target
 * (target+0x190), normalise it -- func_01ff8d18 writes the unit vector back and
 * returns the distance -- and cache that distance at +0x28, capped at 0x9000. Mark the
 * target slot live (owner+0x1c7 = 1), store the caller's aim vector at +0x14 and its
 * tag at +0x30, and clear the accumulated offset at +8. */
struct vec3 { int x, y, z; };

extern int *func_ov107_020cab14(int a, int b);
extern int VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(const struct vec3 *v, struct vec3 *out);
extern struct vec3 data_02041dc8;

void func_ov212_020d0d90(int *self, struct vec3 *param_2, int param_3) {
    struct vec3 d;
    int *tgt = func_ov107_020cab14(self[0], 0);

    if (tgt == 0) {
        return;
    }
    VEC_Subtract((char *)tgt + 0x190, (char *)self[0] + 0xb0, &d);
    self[0xa] = func_01ff8d18(&d, &d);
    self[9] = 0;
    if (self[0xa] > 0x9000) {
        self[0xa] = 0x9000;
    }
    *(char *)(self[0] + 0x1c7) = 1;
    *(struct vec3 *)((char *)self + 0x14) = *param_2;
    self[0xc] = param_3;
    *(struct vec3 *)((char *)self + 8) = data_02041dc8;
}
