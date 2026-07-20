/* Draw onto a tiled surface, bracketed by the surface's begin/end pair
 * (func_02030158 / func_020300f8). Takes FIVE arguments: the fifth arrives on
 * the stack and is forwarded as the sixth word of the draw call, with a literal
 * 4 wedged in as the fifth.
 */
extern void func_02030158(void *surface);
extern void func_020302ec(void *surface, int a, int b, int c, int d, int e);
extern void func_020300f8(void *surface);

void func_ov002_02067120(void *surface, int a, int b, int c, int e) {
    func_02030158(surface);
    func_020302ec(surface, a, b, c, 4, e);
    func_020300f8(surface);
}
