typedef struct { int w[11]; } Blk44;

void func_ov235_020d21c0(char *obj) {
    char *node = *(char **)(obj + 4);
    char *dst = *(char **)(node + 4);
    char *src = *(char **)(node + 8);
    *(Blk44 *)(dst + 0x30) = *(Blk44 *)src;
}
