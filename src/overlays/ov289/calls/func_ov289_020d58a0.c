extern void func_ov107_020c6980(void *obj);
extern void func_ov002_02076ce8(int a, void *b);
struct blk11 { int w[11]; };
void func_ov289_020d58a0(char *obj) {
    func_ov107_020c6980(obj);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x388)) + 0x10) = *(struct blk11 *)(obj + 0xa0);
    if (*(int *)(obj + 0x390) != 0) {
        func_ov002_02076ce8(*(int *)(obj + 0x390), obj + 0xb0);
    }
}
