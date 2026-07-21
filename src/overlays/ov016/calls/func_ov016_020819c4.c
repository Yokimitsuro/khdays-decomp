extern void func_0202bc30(int node);
/* Release the node resources at obj+0x498 and invalidate the handle at obj+0x6a (= -1). */
void func_ov016_020819c4(int obj) {
    func_0202bc30(obj + 0x498);
    *(short *)(obj + 0x6a) = -1;
}
