typedef struct { int w[11]; } Blk44;

void func_ov161_020ccac8(char *obj) {
    char *node = *(char **)(obj + 4);
    char *src = *(char **)(*(char **)node + 0x3c0);
    char *dst = *(char **)(node + 4);
    *(Blk44 *)(dst + 4) = *(Blk44 *)(src + 4);
}
