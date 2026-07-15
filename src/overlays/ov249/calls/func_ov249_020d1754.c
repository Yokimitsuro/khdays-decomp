/* c634 handler: add the owner's local offset (owner+0x494) to its parent's position
 * (*(owner+0x490)+0x2c) into a vec, push it to the owner via func_ov107_020c0b90, arm
 * func_ov107_020c5af8(owner, 0, 0x48, &vec), and dispatch via func_0203c634. */
struct vec { int x, y, z; };
extern void VEC_Add(int *a, int *b, struct vec *out);
extern void func_ov107_020c0b90(int owner, int a, struct vec v, int flag);
extern void func_ov107_020c5af8(int owner, int a, int b, struct vec *v);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov249_020d17d8(void);
void func_ov249_020d1754(int self) {
    int *obj = *(int **)(self + 4);
    struct vec buf;
    VEC_Add((int *)(*obj + 0x494), (int *)(*(int *)(*obj + 0x490) + 0x2c), &buf);
    func_ov107_020c0b90(*obj, 0, buf, 1);
    func_ov107_020c5af8(*obj, 0, 0x48, &buf);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov249_020d17d8);
}
