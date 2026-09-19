/* func_ov253_020d1f7c -- ring setup: installs the draw callback (020d1ea0) and this state at the
 * owner's +0x78 / +0x84, binds channels 0 and 2 of the +0x88 object to its +0xe0 (0202accc),
 * keeps the frame-step pointer at +8, resets every ring entry (stride 0x38: marker 0, scale 1.0
 * and the data_020420f8 rotation) and clears +4. */
struct vec4 { int a, b, c, d; };

extern void func_0202accc(int object, int channel, void *target, int flag);
extern const struct vec4 data_020420f8;
extern void func_ov253_020d1ea0(void);

void func_ov253_020d1f7c(int *node) {
    int *state = (int *)node[1];
    int i;

    *(void **)(*state + 0x78) = func_ov253_020d1ea0;
    *(int **)(*state + 0x84) = state;
    func_0202accc(*(int *)(*state + 0x88), 0, (void *)(*(int *)(*state + 0x88) + 0xe0), 0);
    func_0202accc(*(int *)(*state + 0x88), 2, (void *)(*(int *)(*state + 0x88) + 0xe0), 0);
    state[2] = node[0] + 0x2c;
    for (i = 0; i < *(int *)(*state + 0x8c); i++) {
        char *entry = *(char **)(*state + 0x90) + i * 0x38;
        *(int *)entry = 0;
        *(int *)(entry + 4) = 0x1000;
        *(struct vec4 *)(entry + 8) = data_020420f8;
    }
    state[1] = 0;
}
