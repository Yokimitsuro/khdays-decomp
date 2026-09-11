typedef struct { int w[11]; } Blk44;

extern void func_ov107_020c6980(char *self, int a);

void func_ov213_020d1864(char *self, int a) {
    *(Blk44 *)(*(char **)(self + 0x38c) + 0x10) = *(Blk44 *)(self + 0xa0);
    func_ov107_020c6980(self, a);
}
