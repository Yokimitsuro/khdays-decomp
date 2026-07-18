/* func_ov199_020d43a4 takes the vec BY VALUE (r1/r2/r3 via ldm) plus a stack flag. */
struct vec { int x, y, z; };
extern void VEC_Subtract();
extern void func_ov199_020d43a4(int *obj, struct vec v, int flag);
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_ov199_020d4234(int owner, int a);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov199_020d548c(void);

void func_ov199_020d5404(int self) {
    int *obj = *(int **)(self + 4);
    struct vec v;

    VEC_Subtract(*obj + 400, obj[3], &v);
    func_ov199_020d43a4(obj, v, 0);
    if (*(unsigned char *)(obj[1] + 0xad) == 0) {
        func_ov107_020c9264(*obj, 3, 1);
        func_ov199_020d4234(*obj, 1);
        func_0203c634(self, *(signed char *)(self + 0x20), &func_ov199_020d548c);
    }
}
