extern void func_ov107_020c7ca4(void *obj);
struct blk11 { int w[11]; };
void func_ov146_020ce608(char *obj) {
    *(struct blk11 *)(*(char **)(obj + 0x3b0) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3b8) + 4);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x3ac)) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3b0) + 0x10);
    func_ov107_020c7ca4(obj);
}
