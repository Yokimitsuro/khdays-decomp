extern void func_0202bc30(int node);
/* Release the node resources at obj+0x2c and mark the object released (obj+0x2bc = 1). */
void func_ov016_020822cc(int obj) {
    func_0202bc30(obj + 0x2c);
    *(unsigned char *)(obj + 0x2bc) = 1;
}
