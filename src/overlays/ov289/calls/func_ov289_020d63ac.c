extern int data_02041dc8;
extern void func_ov107_020c9264(int node, int a, int b);
extern void func_0203c634();
extern void func_ov289_020d641c(void);

struct w3 { int a, b, c; };

void func_ov289_020d63ac(int this_) {
    int holder = *(int *)(this_ + 4);
    func_ov107_020c9264(*(int *)holder, 1, 0);
    *(int *)(*(int *)holder + 0x394) = 1;
    *(struct w3 *)(holder + 0x10) = *(struct w3 *)(*(int *)(holder + 0xc));
    *(struct w3 *)(holder + 0x1c) = *(struct w3 *)&data_02041dc8;
    *(int *)(holder + 8) = 0;
    *(int *)(holder + 0x58) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov289_020d641c);
}
