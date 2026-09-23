/* Lift entry of the ov252 actor: pending turn/retreat and +0x6c clear, +0x89 = 1, sound 0x148/0x12
 * plays at the +8 point, the lift height (+0x78) is 30.0 / 22.0 / 15.0 by the last armour piece still
 * shown (30.0 with the +0xac guard up), +0x88 = 1, +0x64 clears, poses 0x23, 0x32 and 0x36 play and the
 * node moves on to 020d15b8. */
typedef struct { unsigned f : 8; } B8;
struct Ov252Pieces { char pad[0x4f4]; int shapes[4]; };

extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d15b8(void);

void func_ov252_020d14cc(int *node)
{
    int *state = (int *)node[1];
    signed char i;

    state[0x2a] = 0;
    state[0x29] = 0;
    state[0x1b] = 0;
    *((unsigned char *)state + 0x89) = 1;
    func_ov107_020c5af8(*state, 0x148, 0x12, (void *)state[2]);
    for (i = 3; i >= 0; i--) {
        if (((B8 *)(((struct Ov252Pieces *)*state)->shapes[i] + 8))->f & 1) {
            break;
        }
    }
    state[0x1e] = i == 0 ? 0x1e000 : i == 1 ? 0x16000 : 0xf000;
    if (state[0x2b] != 0) {
        state[0x1e] = 0x1e000;
    }
    *((unsigned char *)state + 0x88) = 1;
    state[0x19] = 0;
    func_ov107_020c9264(*state, 0x23, 0);
    func_ov107_020c9264(*state, 0x32, 0);
    func_ov107_020c9264(*state, 0x36, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d15b8);
}
