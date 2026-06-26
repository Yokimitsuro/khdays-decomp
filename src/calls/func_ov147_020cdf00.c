extern int func_0203c7e8();
extern int func_ov107_020c68ec();

struct S {
    char pad[0x394];
    int arr[2][2];
};

int func_ov147_020cdf00(struct S *r5) {
    int i;
    func_0203c7e8(*(int *)((char *)r5 + 0x384));
    for (i = 0; i < 2; i++) {
        func_0203c7e8(r5->arr[i][0]);
    }
    return func_ov107_020c68ec(r5);
}
