/* Broadcast the working 44-byte pose at (+0x3e8)+4 into the three pose consumers: the +0x3d8
 * clip's slot at +0x10, the +0x3d4 handle's target at +0x10 and the +0x430 owner's +0x18 pose. */
struct blk11 { int w[11]; };

void func_ov213_020cbfc8(int unused, char *obj) {
    *(struct blk11 *)(*(char **)(obj + 0x3d8) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3e8) + 4);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x3d4)) + 0x10) = *(struct blk11 *)(*(char **)(obj + 0x3e8) + 4);
    *(struct blk11 *)(*(char **)(*(char **)(obj + 0x430) + 0x18) + 4) = *(struct blk11 *)(*(char **)(obj + 0x3e8) + 4);
}
