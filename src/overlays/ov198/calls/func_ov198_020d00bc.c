extern void func_0203c7ac(void *p);
extern void func_0203c86c(void *p, int x);
extern void func_ov107_020c6980(void *obj, int arg2);
struct blk11 { int w[11]; };
void func_ov198_020d00bc(char *obj, int arg2) {
    func_0203c7ac(*(void **)(obj + 0x388));
    func_0203c86c(*(void **)(obj + 0x388), 1);
    func_ov107_020c6980(obj, arg2);
    *(struct blk11 *)(*(char **)(obj + 0x390) + 0x10) = *(struct blk11 *)(obj + 0xa0);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x38c)) + 0x10) =
        *(struct blk11 *)(*(char **)(obj + 0x390) + 0x10);
}
