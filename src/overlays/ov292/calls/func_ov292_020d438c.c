extern void func_0203c634();

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov292_020d438c(int this_) {
    int node = *(int *)(this_ + 4);
    if ((((struct hw60 *)(*(int *)node + 0x60))->lo & 1) == 0) return;
    *(int *)(node + 0x2c) = 0;
    *(int *)(node + 0x34) = 0;
    *(int *)(node + 0x30) = 0x1000;
    *(signed char *)(*(int *)node + 0x1c7) = *(signed char *)(*(int *)node + 0x1c9);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
