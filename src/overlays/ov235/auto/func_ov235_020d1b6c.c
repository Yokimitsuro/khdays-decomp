typedef struct { int w[11]; } Blk44;

void func_ov235_020d1b6c(char *obj) {
    char *node = *(char **)(obj + 4);
    char *dst = *(char **)node;
    char *src = *(char **)(node + 4);
    *(Blk44 *)(dst + 0x30) = *(Blk44 *)src;
}
