/* Place the widget: copy the caller's position into +0xa4 as one three-word
 * move, apply the anchor, drive sub-node 3 to the given value and refresh. */
typedef struct {
    int x, y, z;
} VecFx32;

extern void func_0202afdc(void *self, int anchor);
extern void func_01fff774(void *self, int slot, int value);
extern void func_0202aa9c(void *self);

void func_ov002_02060d0c(char *self, const VecFx32 *pos, int anchor, int value) {
    *(VecFx32 *)(self + 0xa4) = *pos;
    func_0202afdc(self, anchor);
    func_01fff774(self, 3, value);
    func_0202aa9c(self);
}
