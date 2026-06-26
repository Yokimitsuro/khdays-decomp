extern int NNS_FndRemoveListObject();
extern int NNS_FndGetNextListObject();
extern int func_020236ac();
extern int func_020343cc();

void func_ov005_02050bfc(int unused, int **a, int *b) {
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

    cur = (int *)NNS_FndGetNextListObject(b, 0);
    if (cur == 0) {
        return;
    }

    for (;;) {
        next = (int *)NNS_FndGetNextListObject(b, cur);
        NNS_FndRemoveListObject(b, cur);
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
