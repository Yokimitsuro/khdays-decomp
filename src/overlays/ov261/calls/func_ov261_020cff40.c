extern void func_ov107_020c6980(void *obj);
extern void func_ov002_02076ce8(int a, void *b);
struct blk11 { int w[11]; };
void func_ov261_020cff40(char *obj) {
    func_ov107_020c6980(obj);
    *(struct blk11 *)(*(char **)(obj + 0x398) + 0x10) = *(struct blk11 *)(obj + 0xa0);
    if (*(int *)(*(char **)(obj + 0x3a0)) != 0) {
        func_ov002_02076ce8(*(int *)(*(char **)(obj + 0x3a0)), *(char **)(obj + 0x398) + 0x20);
    }
}
