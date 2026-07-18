extern int func_ov107_020c08cc(int a, int b, int c, int d, int e, void *f);
extern void func_ov107_020c7500(int a, void *b, int c);

void func_ov130_020cc2b4(int self, unsigned char *node, int arg) {
    switch (node[2]) {
    case 5:
        if (node[3] == 0) {
        *(int *)(*(int *)(self + 0x394) + node[3] * 8 + 4) =
            func_ov107_020c08cc(*(int *)(self + 0x3c),
                                *(int *)(*(int *)(self + 0x394) + node[3] * 8),
                                0x17, 2, 0x2000, node + 5);
        }
        break;
    }
    func_ov107_020c7500(self, node, arg);
}
