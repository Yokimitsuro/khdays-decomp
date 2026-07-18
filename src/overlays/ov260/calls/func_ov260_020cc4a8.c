extern void func_ov107_020c9ec8(void *p);
extern void func_ov107_020c6980(void *obj, int arg2);
struct blk11 { int w[11]; };
void func_ov260_020cc4a8(char *obj, int arg2) {
    func_ov107_020c9ec8(*(void **)(obj + 0x428));
    func_ov107_020c6980(obj, arg2);
    *(struct blk11 *)(*(char **)(obj + 0x41c) + 0x10) = *(struct blk11 *)(obj + 0xa0);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x418)) + 0x10) =
        *(struct blk11 *)(*(char **)(obj + 0x41c) + 0x10);
}
