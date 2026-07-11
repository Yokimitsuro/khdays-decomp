extern void func_ov107_020c7ca4(void *obj);
struct blk11 { int w[11]; };
void func_ov292_020d3afc(char *obj) {
    *(struct blk11 *)(*(char **)(obj + 0x390) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x38c) + 4);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x388)) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x390) + 0x10);
    func_ov107_020c7ca4(obj);
}
