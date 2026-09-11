typedef struct { int w[11]; } Blk44;

extern int func_ov107_020c6980(void *self, int a);

int func_ov273_020d54a4(char *self, int a) {
    *(Blk44 *)(*(char **)(self + 0x38c) + 0x10) = *(Blk44 *)(self + 0xa0);
    return func_ov107_020c6980(self, a);
}
