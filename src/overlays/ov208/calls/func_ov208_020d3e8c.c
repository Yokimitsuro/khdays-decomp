/* Copy the pose vector from (child)+0xc to (*child)+0xf0, then update the transform node
 * at (*child)+0xa0 from (child)+0x30. */
extern void func_0203c9d0(int a, int b);
struct Vec3_020d3e8c { int x, y, z; };
void func_ov208_020d3e8c(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(struct Vec3_020d3e8c *)(*(int *)child + 0xf0) = *(struct Vec3_020d3e8c *)(child + 0xc);
    func_0203c9d0(*(int *)child + 0xa0, child + 0x30);
}
