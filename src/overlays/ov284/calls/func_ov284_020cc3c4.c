extern void func_ov107_020c6980(void *obj);
struct blk11 { int w[11]; };

void func_ov284_020cc3c4(char *obj) {
    func_ov107_020c6980(obj);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x3a8)) + 0x10) =
        *(struct blk11 *)(*(char **)(obj + 0x3a4) + 4);
}
