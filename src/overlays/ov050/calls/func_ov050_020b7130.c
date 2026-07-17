struct vec3 { int x, y, z; };

extern struct vec3 data_02041dc8;
extern int func_0202aef8(unsigned short *p, unsigned int idx);
extern void func_ov022_02091b48(void *a, int b, struct vec3 *c, struct vec3 *d);
extern unsigned int func_ov022_02091540(unsigned short *a, int b);
extern void func_ov022_02091d80(void *a, int b);

/* Per-frame step for a projectile/sub-object (x4: ov031/050/070/088). Advance the
 * lifetime by dt and, while it still has more than a 0x9000 lead-out left of the
 * animation's length, keep steering: the solver takes the target's stored offset
 * (+0xcc, biased up by 0x5000) plus a staging vector seeded from data_02041dc8
 * (biased down by 0xa000) and writes its result back through them. Then run the
 * death check, which sets the state byte at +2 itself; state 3 means expired, so
 * zero the lifetime and hand off to 02091d80. */
int func_ov050_020b7130(void *param_1, int param_2, int param_3) {
    struct vec3 target;
    struct vec3 staging;
    int animLen = func_0202aef8((unsigned short *)(param_2 + 0x28), 0);
    int steerUntil = animLen - 0x9000;

    target = *(struct vec3 *)(param_2 + 0xcc);
    staging = data_02041dc8;
    *(int *)(param_2 + 4) += param_3;
    target.y -= 0x5000;
    staging.y += 0xa000;
    if (*(int *)(param_2 + 4) <= steerUntil) {
        func_ov022_02091b48(param_1, param_2, &target, &staging);
    }
    *(char *)(param_2 + 2) = 4;
    if (func_ov022_02091540((unsigned short *)(param_2 + 0x28), param_3) != 0) {
        *(char *)(param_2 + 2) = 3;
    }
    if (*(signed char *)(param_2 + 2) == 3) {
        *(int *)(param_2 + 4) = 0;
        func_ov022_02091d80(param_1, param_2);
    }
    return 0;
}
