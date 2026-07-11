extern void func_ov107_020c7ca4(void *obj);
struct blk11 { int w[11]; };
void func_ov293_020d1e3c(char *obj) {
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x388)) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x390) + 4);
    *(struct blk11 *)(*(char **)(obj + 0x38c) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x390) + 4);
    func_ov107_020c7ca4(obj);
}
