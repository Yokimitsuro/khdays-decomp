/*
 * func_ov282_020d1670 -- x3. AI-state tick: track the leader, aim below it, then range-check the
 * acquired target. Copy the leader position (**(state[0]+0x3d4))+0xb0 into state[0xd..0xf]; if the
 * leader's sub-node (+0x190) exists, cache state[0xe] = *(that+0x44). Aim point w = state[0xd..0xf]
 * with Y lowered by 0x6000, fed to 020c5c54. Acquire a target -> state[4]; if found, dist =
 * VEC_Mag(flatten_y(target(+0x74) - state[0]+0x74)) and pick next-state 7 (in range, dist>0x4000) or
 * 0x10 (too far); if no target, next-state 0x10. Hand off via 0203c634 (cb=0).
 */
struct vec3 { int x, y, z; };
extern void func_ov107_020c5c54(int obj, struct vec3 *v);
extern int  func_ov107_020cab14(int obj, int *out);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  VEC_Mag(int *v);
extern void func_0203c634(int self, int idx, int cb);

void func_ov282_020d1670(int *self) {
    int *state = (int *)self[1];
    struct vec3 w;
    int v[3];
    int dist;
    int target;
    int c;

    *(struct vec3 *)(state + 0xd) = *(struct vec3 *)(*(int *)(*(int *)(*state + 0x3d4)) + 0xb0);
    c = *(int *)(*(int *)(*(int *)(*state + 0x3d4)) + 0x190);
    if (c != 0) {
        state[0xe] = *(int *)(c + 0x44);
    }
    w = *(struct vec3 *)(state + 0xd);
    w.y -= 0x6000;
    func_ov107_020c5c54(*state, &w);
    target = func_ov107_020cab14(*state, &dist);
    state[4] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x74), (void *)(*state + 0x74), v);
        v[1] = 0;
        dist = VEC_Mag(v);
        if (dist > 0x4000) {
            *(char *)(*state + 0x1c7) = 7;
        } else {
            *(char *)(*state + 0x1c7) = 0x10;
        }
    } else {
        *(char *)(*state + 0x1c7) = 0x10;
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
