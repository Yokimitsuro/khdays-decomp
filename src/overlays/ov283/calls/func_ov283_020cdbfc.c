/* Volley-and-close tick of the ov283 actor: after the shared step (020ccb48, target distance) the
 * +0x48 clock runs up at the frame rate; with all 6 shots out (+0x68) it recovers (020cea48). Each
 * shot fires once the clock passes its step (x 0x88): a launch (020cc9e0) that finds no free helper
 * ends in 020ce97c, otherwise the shot counts. Once the +4 rig is idle: within 6.0 a d100 roll over 50
 * rerolls +0x34 (1.57 to 3.14; +0x7c = past 2.36, +0x3c cleared) for move 4, else move 2; farther
 * the +0x6c sequence plays (step 0: move 2 on a roll up to 20, else sound 8 with pose 10; step 1:
 * sound 9 with pose 11) and advances. */
typedef unsigned char u8;
typedef struct { int v[6]; } Steps6;

extern int func_ov283_020ccb48(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov283_020cc9e0(int *node);
extern int func_02023eb4(int bound);
extern int func_02023e80(int bound);
extern void func_ov283_020cc92c(int owner, int id, int mode, int at);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov283_020cea48(void);
extern void func_ov283_020ce97c(void);
extern const Steps6 data_ov283_020cfb70;

void func_ov283_020cdbfc(int *node)
{
    int *state = (int *)node[1];
    Steps6 steps = data_ov283_020cfb70;
    int dist;
    int lo = 0;

    dist = func_ov283_020ccb48(node);
    state[0x12] += *(int *)(node[0] + 0x2c);
    if ((unsigned int)state[0x1a] >= 6) {
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
    if (dist < 0x6000) {
        if (func_02023eb4(0x65) + lo > 0x32) {
            state[0xd] = func_02023e80(0x1922) + 0x1922;
            state[0x1f] = state[0xd] > 0x25b3;
            state[0xf] = 0;
            *(signed char *)(*state + 0x1c7) = 4;
            return;
        }
        *(signed char *)(*state + 0x1c7) = 2;
        return;
    }
    switch (state[0x1b]) {
    case 0:
        if (func_02023eb4(0x65) + lo <= 0x14) {
            *(signed char *)(*state + 0x1c7) = 2;
        } else {
            func_ov283_020cc92c(*state, 0x173, 8, state[2]);
            func_ov107_020c9264(*state, 10, 0);
        }
        break;
    case 1:
        func_ov283_020cc92c(*state, 0x173, 9, state[2]);
        func_ov107_020c9264(*state, 0xb, 0);
        break;
    }
    state[0x1b]++;
}
