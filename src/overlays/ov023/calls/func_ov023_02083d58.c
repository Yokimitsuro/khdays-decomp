/* func_ov023_02083d58 -- post a message box on the ov023 scene's dialogue object.
 * The object sits at +0x87564 of the scene root (data_ov023_0208a784[1]). func_02035fb0 takes the
 * two caller-supplied parameters plus a fixed style 0x32 as its fifth (stack) argument; the object
 * is then committed with func_02035ffc. */
extern void func_02035fb0(int obj, int a, int b, int c, int d);
extern void func_02035ffc(int obj);
extern int data_ov023_0208a784;

void func_ov023_02083d58(int a, int b) {
    func_02035fb0(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x87564, 0, a, b, 0x32);
    func_02035ffc(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x87564);
}
