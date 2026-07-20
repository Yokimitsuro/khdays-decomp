/* Point the actor at the fixed reference direction: take the difference between
 * the two constant vectors into self+0x7c, normalise it in place, copy the
 * second constant straight into self+0x88, then hand off to
 * func_ov107_020c2cec. */
typedef struct {
    int x, y, z;
} VecFx32;

extern VecFx32 data_020475c4;
extern VecFx32 data_020475ac;

extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *dst);
extern void func_01ff8d18(VecFx32 *src, VecFx32 *dst);
extern void func_ov107_020c2cec(void *self, int arg);

void func_ov107_020c980c(char *self, int arg) {
    VEC_Subtract(&data_020475c4, &data_020475ac, (VecFx32 *)(self + 0x7c));
    func_01ff8d18((VecFx32 *)(self + 0x7c), (VecFx32 *)(self + 0x7c));
    *(VecFx32 *)(self + 0x88) = data_020475ac;
    func_ov107_020c2cec(self, arg);
}
