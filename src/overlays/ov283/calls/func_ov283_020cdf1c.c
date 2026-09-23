/* Barrage tick of the ov283 actor: after the shared step (020ccb48) the +0x48 clock runs up at the
 * frame rate; with all 16 shots out (+0x68) it recovers (020cea48). Each shot fires once the clock
 * passes its step (x 0x88): a launch (020cc9e0) that finds no free helper ends in 020ce97c, otherwise
 * the shot counts. Each time the +4 rig goes idle the next pose of the +0x6c sequence plays (sounds
 * 8 / 7 / 9 of bank 0x173 with poses 10 / 9 / 11) and the sequence advances. */
typedef unsigned char u8;
typedef struct { int v[16]; } Steps16;

extern int func_ov283_020ccb48(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov283_020cc9e0(int *node);
extern void func_ov283_020cc92c(int owner, int id, int mode, int at);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov283_020cea48(void);
extern void func_ov283_020ce97c(void);
extern const Steps16 data_ov283_020cfb88;

void func_ov283_020cdf1c(int *node)
{
    int *state = (int *)node[1];
    Steps16 steps = data_ov283_020cfb88;

    func_ov283_020ccb48(node);
    state[0x12] += *(int *)(node[0] + 0x2c);
    if ((unsigned int)state[0x1a] >= 0x10) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020cea48);
        return;
    }
    if (state[0x12] > steps.v[state[0x1a]] * 0x88) {
        if (func_ov283_020cc9e0(node) == 0) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020ce97c);
            return;
        }
        state[0x1a]++;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    switch (state[0x1b]) {
    case 0:
    case 2:
    case 4:
        func_ov283_020cc92c(*state, 0x173, 8, state[2]);
        func_ov107_020c9264(*state, 10, 0);
        break;
    case 1:
    case 3:
    case 5:
        func_ov283_020cc92c(*state, 0x173, 7, state[2]);
        func_ov107_020c9264(*state, 9, 0);
        break;
    case 6:
        func_ov283_020cc92c(*state, 0x173, 9, state[2]);
        func_ov107_020c9264(*state, 0xb, 0);
        break;
    }
    state[0x1b]++;
}
