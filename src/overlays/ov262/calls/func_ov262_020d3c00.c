extern void func_ov107_020c4924(void *obj);
struct blk11 { int w[11]; };
void func_ov262_020d3c00(char *obj) {
    func_ov107_020c4924(obj);
    *(struct blk11 *)(*(char **)(obj + 0x388) + 0x30) = *(struct blk11 *)(*(char **)(obj + 0x390) + 4);
    *(struct blk11 *)(*(char **)(obj + 0x38c) + 0x30) = *(struct blk11 *)(*(char **)(obj + 0x394) + 4);
}
