struct vec3 { int x, y, z; };
struct bits1 { unsigned char b0 : 1; };

extern void func_ov022_0209198c(struct vec3 *out, void *a, int b, int c);
extern void func_ov022_02091b48(void *a, int b, struct vec3 *c, struct vec3 *d);
extern void VEC_Add(struct vec3 *a, struct vec3 *b, struct vec3 *c);
extern void func_ov022_02091540(int a, int b);
extern int func_01ff8e94(int a, struct vec3 *b);
extern void func_ov022_02091e08(void *a, int b);
extern void func_02033d0c(int a, int b, struct vec3 *c, int d);
extern void func_ov070_020b98e8(struct vec3 *a, struct vec3 *b);
extern int func_02030788(void);
extern void func_ov022_020914a0(int a, int b);

int func_ov070_020b9574(void *param_1, int param_2, int param_3) {
    struct vec3 s;
    struct vec3 out;
    int *puVar4 = *(int **)((char *)param_1 + 8);
    int *iVar5 = *(int **)(param_2 + 0x138);

    s = *(struct vec3 *)(param_2 + 0xcc);
    func_ov022_0209198c(&out, param_1, param_2, param_3);
    func_ov022_02091b48(param_1, param_2, &s, &out);
    VEC_Add(&s, &out, &s);
    *(struct vec3 *)(param_2 + 0xcc) = s;
    func_ov022_02091540(param_2 + 0x28, param_3);
    if (*(char *)(param_2 + 2) != 3) {
        if (func_01ff8e94(param_2 + 0x10, &s) > iVar5[5]) {
            *(char *)(param_2 + 2) = 4;
        }
    }
    func_ov022_02091e08(param_1, param_2);
    if (*(unsigned char *)param_2 & 1) {
        if (*(int *)(param_2 + 4) >= iVar5[6]) {
            *(char *)(param_2 + 2) = 4;
        }
    }
    if (*(char *)(param_2 + 2) != 2) {
        int i;
        if (*(int *)param_1 == 1) {
            if (((struct bits1 *)((char *)puVar4 + 0x694))->b0) {
                func_02033d0c(0xcb, 1, &s, 0);
            }
            func_ov070_020b98e8(&s, &out);
            if (func_02030788() == 0 && (*puVar4 & 0x10000) == 0) {
                *(unsigned char *)((char *)puVar4 + 0x47a) = 3;
                *(unsigned char *)((char *)puVar4 + 0x47b) = 1;
            }
        }
        *(char *)(param_2 + 2) = 4;
        *(int *)(param_2 + 4) = 0x3000;
        for (i = 0; i < 8; i++) {
            ((short *)param_2)[i + 0x9e] = -1;
        }
        func_ov022_020914a0(param_2, iVar5[0xf]);
    }
    return 0;
}
