extern void func_ov292_020d3e58();
extern void func_0203c634();

void func_ov292_020d4654(int this_) {
    int node = *(int *)(this_ + 4);
    func_ov292_020d3e58(node);
    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)node + 0x1c7) = 4;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
