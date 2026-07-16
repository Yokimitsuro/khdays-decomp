/* func_ov210_020d3108 -- enter the state: play mode 0x15, seed the offset vector at ctx+0x54 by
 * scaling the constant axis data_02042264 by 0x1200, clear the counter at +0x2c and hand off to
 * func_ov210_020d3158. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_01ffa724(int scale, const VecFx32 *v, VecFx32 *out);
extern void func_0203c634(int self, int action, void *cb);
extern void func_ov210_020d3158(void);
extern VecFx32 data_02042264;

void func_ov210_020d3108(int self) {
    int *ctx;

    ctx = *(int **)(self + 4);
    func_ov107_020c9264(ctx[0], 0x15, 0);
    func_01ffa724(0x1200, &data_02042264, (VecFx32 *)((char *)ctx + 0x54));
    ctx[0xb] = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov210_020d3158);
}
