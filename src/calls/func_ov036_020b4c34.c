extern int func_ov022_02091228();
extern int func_020236ac();

struct S {
    char pad[0x2644];
    void *p;
};

void func_ov036_020b4c34(struct S *a) {
    func_ov022_02091228(a->p);
    func_020236ac(a->p);
}
