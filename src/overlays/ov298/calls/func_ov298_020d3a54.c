extern void func_ov107_020c6980(void *obj);
struct blk11 { int w[11]; };
void func_ov298_020d3a54(char *obj) {
    func_ov107_020c6980(obj);
    *(struct blk11 *)(*(char **)(obj + 0x390) + 0x10) = *(struct blk11 *)(obj + 0xa0);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x38c)) + 0x10) =
        *(struct blk11 *)(*(char **)(obj + 0x390) + 0x10);
}
