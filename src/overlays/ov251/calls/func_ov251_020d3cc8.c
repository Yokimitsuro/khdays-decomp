extern void func_ov107_020c7ca4(void *obj);
struct blk11 { int w[11]; };
void func_ov251_020d3cc8(char *obj) {
    *(struct blk11 *)(*(char **)(obj + 0x38c) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x39c) + 4);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x388)) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x38c) + 0x10);
    func_ov107_020c7ca4(obj);
}
