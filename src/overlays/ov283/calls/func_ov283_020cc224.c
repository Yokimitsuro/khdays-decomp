extern void func_0203c7e8(int *param_1);
extern void func_ov107_020c68ec(int param_1);

struct Elem8 {
    int pad;
    int *ptr;
};

void func_ov283_020cc224(int param_1) {
    int i;
    for (i = 0; i < 6; i++) {
        func_0203c7e8(((struct Elem8 *)param_1)[i + 0x7d].ptr);
    }
    func_0203c7e8(*(int **)(param_1 + 0x384));
    func_ov107_020c68ec(param_1);
}
