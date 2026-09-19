/* Model pose init: after the base 020c4924 step, push the +0x3a0 clip's pose (+4) into the
 * +0x3b0 and +0x398 targets' +0x10 slots and the +0x3a4 clip's into the +0x3b4 / +0x39c ones. */
extern void func_ov107_020c4924(void *obj);
struct blk11 { int w[11]; };
void func_ov236_020cd450(char *obj) {
    func_ov107_020c4924(obj);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x3b0)) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3a0) + 4);
    *(struct blk11 *)(*(char **)(obj + 0x398) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3a0) + 4);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x3b4)) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3a4) + 4);
    *(struct blk11 *)(*(char **)(obj + 0x39c) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3a4) + 4);
}
