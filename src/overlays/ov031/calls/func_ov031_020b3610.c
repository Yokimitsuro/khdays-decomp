extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(int a, int b);
extern void func_ov022_02091474(int a);
extern int func_ov022_020912d8(int a);
extern short func_02030788(void);
extern void func_ov022_020ad588(int a);

void func_ov031_020b3610(int this) {
    int v;
    v = func_ov022_02083f90();
    func_ov022_0209145c(*(int *)(this + 0x2644), v);
    v = func_ov022_02083f90();
    func_ov022_0209145c(*(int *)(this + 0x2644) + 0x30, v);
    v = func_ov022_02083f90();
    func_ov022_0209145c(*(int *)(this + 0x2644) + 0x60, v);
    func_ov022_02091474(*(int *)(this + 0x2644));
    func_ov022_02091474(*(int *)(this + 0x2644) + 0x30);
    func_ov022_02091474(*(int *)(this + 0x2644) + 0x60);
    if (func_ov022_020912d8(*(int *)(this + 0x2644)) == 0 ||
        func_ov022_020912d8(*(int *)(this + 0x2644) + 0x30) == 0 ||
        func_ov022_020912d8(*(int *)(this + 0x2644) + 0x60) == 0) {
        if (func_02030788() == 0) {
            *(unsigned long long *)(this + 0x464) |= 0x10000;
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(this + 0x46c) |= 0x10000;
        }
    }
    func_ov022_020ad588(this);
}
