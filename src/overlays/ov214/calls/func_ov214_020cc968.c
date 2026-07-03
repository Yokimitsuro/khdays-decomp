extern void func_0202a440(void *p);
extern void func_02014b5c(void *a, int b);
extern void func_0202a388(void *a, void *b, int c, int d);
extern void func_0203b9ac(void *a, void *b);
extern void func_0203b9fc(void *a, int b, int c, int d);
extern void func_0203c7ac(void *a, int b);

void func_ov214_020cc968(char *this, int param2, int param3, char *param4) {
    char *obj = *(char **)(this + 0x88);
    func_0202a440(param4);
    *(int *)(param4 + 0xc) = 0;
    func_02014b5c(obj + 0x20, *(int *)(obj + 0x78));
    func_0202a388(param4, obj, param2, 0xc);
    func_0203b9ac(this, param4);
    func_0203b9fc(this, 0, 0, param3);
    func_0203c7ac(this, 0);
}
