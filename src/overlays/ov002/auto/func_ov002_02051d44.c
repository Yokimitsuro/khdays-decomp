typedef struct { int w[12]; } Blk48;

void func_ov002_02051d44(char *obj, void *src) {
    *(Blk48 *)(obj + 0x10c) = *(Blk48 *)src;
}
