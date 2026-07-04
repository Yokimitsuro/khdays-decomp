extern void func_0203d194();
extern void func_01fffd0c();

void func_0203c424(int this_, int node) {
    void (*cb)(int) = *(void (**)(int))(node + 0x18);
    if (cb != 0 && *(int *)(node + 0x14) == 0) {
        cb(node);
    }
    func_0203d194(*(int *)(node + 4));
    func_01fffd0c(this_, node);
}
