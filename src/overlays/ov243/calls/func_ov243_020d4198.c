/* Facing update of the ov241 enemy (x3: ov241/242/243): eases the +4 heading towards the +8
 * target at the +0x28 rate, turns it into a quaternion about the world Y axis for the actor's
 * +0xa0 orientation, shifts the +0x10 offset into the actor's +0xf0 and reloads the zero vector
 * into it (the func_ov120_020cca40 shape). */
struct vec3 { int x, y, z; };

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(int *out, int *tbl, int r);
extern void func_0203c9d0(int dst, int *src);
extern int data_02042264;
extern int data_02041dc8;

void func_ov243_020d4198(int *this)
{
    int *node = (int *)this[1];
    int scratch[4];
    node[1] = func_0203d040(node[1], node[2], node[10], 0);
    func_0202f188(scratch, &data_02042264, node[1]);
    func_0203c9d0(node[0] + 0xa0, scratch);
    {
        struct vec3 *triple = (struct vec3 *)(node + 4);
        *(struct vec3 *)(node[0] + 0xf0) = *triple;
        *triple = *(struct vec3 *)&data_02041dc8;
    }
}
