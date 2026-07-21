extern void func_0202ba18(int node);
extern void func_0202a7dc(int field);
/* Tear down the render node (obj+0x2c, if present) and its field chain (obj+0x30), then clear
 * status bit 2 (obj+0x12). */
void func_ov015_0207fa90(int obj) {
    if (*(int *)(obj + 0x2c) != 0) {
        func_0202ba18(*(int *)(obj + 0x2c));
    }
    func_0202a7dc(obj + 0x30);
    *(unsigned short *)(obj + 0x12) &= ~4;
}
