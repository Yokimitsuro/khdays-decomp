extern int func_020100c8();
extern int func_02010128();
extern int func_020236ac();
extern int func_020343cc();

void func_ov069_020ba71c(int unused, int **a, int *b) {
    int i, j;
    int *cur;
    int *next;

    if (a != 0) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 0x28; j++) {
                if (a[j] != 0) {
                    func_020343cc(&a[j]);
                }
            }
            a += 0x28;
        }
    }

    if (b == 0) {
        return;
    }

    cur = (int *)func_02010128(b, 0);
    if (cur == 0) {
        return;
    }

    for (;;) {
        next = (int *)func_02010128(b, cur);
        func_020100c8(b, cur);
        func_020343cc(cur + 9);
        if (cur != 0) {
            func_020236ac(cur);
        }
        cur = next;
        if (next == 0) {
            return;
        }
    }
}
