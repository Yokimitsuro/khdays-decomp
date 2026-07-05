extern unsigned int func_02023eb4(int);
extern void func_ov107_020c9264(int node, int a, int b);
extern void func_0203c634();

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov287_020d0728(int this_) {
    int node = *(int *)(this_ + 4);
    if ((((struct hw60 *)(*(int *)node + 0x60))->lo & 1) == 0) return;
    *(int *)(*(int *)node + 0x38c) = func_02023eb4(0x64) < 0xa;
    func_ov107_020c9264(*(int *)node, 1, 0);
    *(signed char *)(*(int *)node + 0x1c7) = *(signed char *)(*(int *)node + 0x1c9);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
