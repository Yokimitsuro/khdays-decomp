/* Guarded drift tick of the ov252 actor: the guard sweep runs (020ce370) and it faces the target
 * (020cdfe8 0, 1); while the +0xac guard is up and the partner's +0xaf flag is clear poses 0x31 and
 * 0x35 play. The +0xc velocity follows the +0x574 part's +0x2c vector turned by the +0x54 heading;
 * once the partner holds no queued move the next move is 5 with the guard up, else 2. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020ce370(int *node);
extern int func_ov252_020cdfe8(int *node, Vec3 *delta, int face);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov252_020d26dc(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov252_020ce370(node);
    func_ov252_020cdfe8(node, 0, 1);
    if (state[0x2b] != 0 && *(unsigned char *)(state[1] + 0xaf) == 0) {
        func_ov107_020c9264(*state, 0x31, 0);
        func_ov107_020c9264(*state, 0x35, 0);
    }
    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x2b] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
    } else {
        *(unsigned char *)(*state + 0x1c7) = 5;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
