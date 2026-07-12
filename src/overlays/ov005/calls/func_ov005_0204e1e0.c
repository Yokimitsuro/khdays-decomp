/* Offset param_3's two-int vector by func_ov005_0204e1d8(param_1)'s vector and
 * forward the sum (on the stack) to func_ov005_0204e194 with param_2. */
struct vec2_020548bc { int x, y; };
extern struct vec2_020548bc *func_ov005_0204e1d8(int obj);
extern void func_ov005_0204e194(int obj, int arg, struct vec2_020548bc *sum);

void func_ov005_0204e1e0(int param_1, int param_2, struct vec2_020548bc *param_3) {
    struct vec2_020548bc sum;
    struct vec2_020548bc *v = func_ov005_0204e1d8(param_1);
    sum.x = param_3->x + v->x;
    sum.y = param_3->y + v->y;
    func_ov005_0204e194(param_1, param_2, &sum);
}
