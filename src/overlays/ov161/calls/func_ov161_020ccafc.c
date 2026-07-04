extern void func_0203b9fc();
extern void func_0203c634();

void func_ov161_020ccafc(int this_) {
    int node = *(int *)(this_ + 4);
    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) return;
    func_0203b9fc(*(int *)(node + 4), 2, 1, 1);
    func_0203b9fc(*(int *)(node + 4), 0, 1, 1);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
