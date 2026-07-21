extern int func_ov002_0207285c(int frame);
extern void func_0202ba9c(int *node, int id, int c, void *d);
/* Submit the render node at obj+0x2c with the palette id resolved from frame (obj+0x10). */
void func_ov016_020809f4(int obj) {
    unsigned int id = func_ov002_0207285c(*(unsigned char *)(obj + 0x10));
    func_0202ba9c((int *)(obj + 0x2c), id & 0xffff, 0, 0);
}
