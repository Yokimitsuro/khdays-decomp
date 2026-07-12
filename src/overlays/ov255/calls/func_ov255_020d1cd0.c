/* Save the current pose vector from (child)+8 to (*child)+0xf0, then reset (child)+8 from
 * the const offset vector. */
struct Vec3_020d1d5c { int x, y, z; };
extern struct Vec3_020d1d5c data_02041dc8;
void func_ov255_020d1cd0(int param_1) {
    int child = *(int *)(param_1 + 4);
    struct Vec3_020d1d5c *p = (struct Vec3_020d1d5c *)(child + 8);
    *(struct Vec3_020d1d5c *)(*(int *)child + 0xf0) = *p;
    *p = data_02041dc8;
}
