/* Return tick of the ov252 actor: it faces the target (020cdfe8 0, 1) and then turns its +0x58 heading
 * toward the origin from its +8 point; once the partner holds no queued move, with a +0xa0 reward
 * pending the next move is 8, else pose 1 and part motion 0 start and the node moves on to 020cf324. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov252_020cdfe8(int *node, Vec3 *delta, int face);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020cf324(void);
extern const Vec3 data_02041dc8;

void func_ov252_020cf254(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    func_ov252_020cdfe8(node, 0, 1);
    VEC_Subtract(&data_02041dc8, (Vec3 *)state[2], &d);
    d.y = 0;
    func_01ff8d18(&d, &d);
    state[0x16] = func_020050b4(d.x, d.z);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x28] != 0) {
        *(unsigned char *)(*state + 0x1c7) = 8;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    } else {
        func_ov107_020c9264(*state, 1, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 0, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cf324);
    }
}
