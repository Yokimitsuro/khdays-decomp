extern int func_02023eb4();
extern void func_0203c634();
extern void func_ov299_020d3b94();

void func_ov299_020d3b54(int this_) {
    int node = *(int *)(this_ + 4);
    int x = *(int *)(*(int *)node + 0x390);
    int v;
    if (x <= 0) v = 0;
    else v = func_02023eb4(x);
    *(int *)(node + 8) = v;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov299_020d3b94);
}
