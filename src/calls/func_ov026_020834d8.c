extern int func_020236ac();

struct S {
    int unk0;
    int unk4;
    int unk8;
    int unkc;
};

void func_ov026_020834d8(int a0, struct S *a1) {
    a1->unkc = 0;
    if (a1->unk4 != 0) {
        func_020236ac(a1->unk4);
        a1->unk4 = 0;
    }
}
