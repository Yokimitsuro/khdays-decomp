extern void func_ov107_020c7a90(int self, int node, int arg3);

void func_ov146_020cf134(int self, int node, int arg3) {
    if (*(unsigned char *)(node + 2) == 0) {
        *(signed char *)(node + 0x24) =
            (signed char)((*(int *)(*(int *)(self + 0x384) + 0x5c) << 30) >> 31);
        *(signed char *)(node + 0x25) = *(int *)(self + 0x38c);
    }
    func_ov107_020c7a90(self, node, arg3);
}
