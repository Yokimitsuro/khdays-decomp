/* Play the anim (ov107 mode 2). When +0x4c is live, build a transform in a local from
 * data_02042264 / +0x44 / (+0x4c)+0x190 (via 0203cd7c), apply it to +0x18 (via 0202ea48) and
 * copy the result into +8. Always dispatch. */
struct w4 { int a, b, c, d; };
struct mtx { int w[9]; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203cd7c(struct mtx *out, int a, int b, const void *c);
extern void func_0202ea48(int a, struct mtx *b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov187_020d4d8c(int);
extern const struct mtx data_02042264;
void func_ov187_020d4d10(int param_1) {
    int child = *(int *)(param_1 + 4);
    struct mtx buf;
    func_ov107_020c9264(*(int *)child, 2, 0);
    if (*(int *)(child + 0x4c) != 0) {
        func_0203cd7c(&buf, *(int *)(child + 0x4c) + 0x190, *(int *)(child + 0x44), &data_02042264);
        func_0202ea48(child + 0x18, &buf);
        *(struct w4 *)(child + 8) = *(struct w4 *)(child + 0x18);
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov187_020d4d8c);
}
