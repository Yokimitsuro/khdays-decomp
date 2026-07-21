extern int func_ov002_0207285c(int frame);
extern void func_0202ba9c(int node, unsigned int id, int c, int d);
/* Unless the widget is hidden (flag bit 1 at +0x12), submit its render node at +0x1c with the
 * palette id resolved from the frame byte (+0x10). */
void func_ov016_020800fc(int obj) {
    if ((*(unsigned short *)(obj + 0x12) & 2) != 0) {
        return;
    }
    func_0202ba9c(obj + 0x1c, func_ov002_0207285c(*(unsigned char *)(obj + 0x10)) & 0xffff, 0, 0);
}
