struct vec3 { int x, y, z; };

extern void func_ov050_020b7308(struct vec3 *out, void *a, int b, int c);
extern void func_ov022_02091b48(void *a, int b, struct vec3 *c, struct vec3 *d);
extern void func_ov022_02091540(int a, int b);
extern int func_01ff8e94(int a, struct vec3 *b);
extern void VEC_Add(struct vec3 *a, struct vec3 *b, struct vec3 *c);
extern void func_ov022_020914a0(int a, int b);

/* Per-frame homing/approach step: copy the target's stored offset (+0xcc) into a
 * work vector, run the approach solver (020b4b08 + 02091b48), and advance the
 * sub-state. If still approaching (state 2) commit the new offset back; otherwise
 * latch state 4, reset the timer to 0x3000, clear the 8-slot history to -1, and
 * hand off to 020914a0. */
int func_ov050_020b7020(void *param_1, int param_2, int param_3, int param_4) {
    struct vec3 s;
    struct vec3 out;
    int *iVar3 = *(int **)(param_2 + 0x138);

    s = *(struct vec3 *)(param_2 + 0xcc);
    func_ov050_020b7308(&out, param_1, param_2, param_3);
    func_ov022_02091b48(param_1, param_2, &s, &out);
    func_ov022_02091540(param_2 + 0x28, param_3);
    if (*(char *)(param_2 + 2) != 3) {
        if (func_01ff8e94(param_2 + 0x10, &s) > iVar3[5] ||
            *(int *)(param_2 + 4) >= iVar3[6]) {
            *(char *)(param_2 + 2) = 4;
        }
    }
    if (*(char *)(param_2 + 2) != 2) {
        int i;
        *(char *)(param_2 + 2) = 4;
        *(int *)(param_2 + 4) = 0x3000;
        for (i = 0; i < 8; i++) {
            ((short *)param_2)[i + 0x9e] = -1;
        }
        func_ov022_020914a0(param_2, iVar3[0xf]);
    } else {
        VEC_Add(&s, &out, &s);
        *(struct vec3 *)(param_2 + 0xcc) = s;
    }
    return 0;
}
