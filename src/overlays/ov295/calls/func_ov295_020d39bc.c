extern void func_ov107_020c6980(void *obj);
struct blk11 { int w[11]; };
void func_ov295_020d39bc(char *obj) {
    func_ov107_020c6980(obj);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x388)) + 0x10) =
        *(struct blk11 *)(*(char **)(obj + 0x384) + 0x30);
    *(struct blk11 *)(*(char **)(obj + 0x390) + 0x10) =
        *(struct blk11 *)(*(char **)(obj + 0x384) + 0x30);
}
