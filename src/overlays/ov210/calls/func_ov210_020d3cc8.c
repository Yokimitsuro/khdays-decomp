/* Allocate the 0x198-byte sub-actor, back-link the owner at +0x18c, run the setup and return it. */
extern int func_0203d15c(int size);
extern void func_ov210_020d3cf0(int a, int b);
int func_ov210_020d3cc8(int param_1) {
    int obj = func_0203d15c(0x198);
    *(int *)(obj + 0x18c) = param_1;
    func_ov210_020d3cf0(obj, param_1);
    return obj;
}
