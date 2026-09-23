/* Sound-cue tick of the ov259 enemy: the +0x70 clock runs up at the frame rate (capped at 39.84) and,
 * in phases 11 (six cues), 16 (six) and 17 (eleven) of +0xae, each +0xa8 step plays its sound 0x172
 * variants (020cd3c4) once the clock passes the step's time, advancing +0xa8. */
typedef unsigned short u16;

extern void func_ov259_020cd3c4(int actor, int id, u16 mode, int at);

void func_ov259_020cd648(int *node)
{
    int *state = (int *)node[1];
    int phase;

    if (state[0x1c] < 0x27d80) {
        state[0x1c] += *(int *)(node[0] + 0x2c);
    }
    phase = *(signed char *)((char *)state + 0xae);
    if (phase == 0) {
        return;
    }
    switch (phase) {
    case 11:
        switch (state[0x2a]) {
        case 0:
            if (state[0x1c] > 0x3b8) {
                func_ov259_020cd3c4(*state, 0x172, 0x8, state[4]);
                state[0x2a]++;
            }
            break;
        case 1:
            if (state[0x1c] > 0x660) {
                func_ov259_020cd3c4(*state, 0x172, 0x18, state[4]);
                state[0x2a]++;
            }
            break;
        case 2:
            if (state[0x1c] > 0xff0) {
                func_ov259_020cd3c4(*state, 0x172, 0xa, state[4]);
                state[0x2a]++;
            }
            break;
        case 3:
            if (state[0x1c] > 0x1210) {
                func_ov259_020cd3c4(*state, 0x172, 0x1a, state[4]);
                state[0x2a]++;
            }
            break;
        case 4:
            if (state[0x1c] > 0x1650) {
                func_ov259_020cd3c4(*state, 0x172, 0x9, state[4]);
                state[0x2a]++;
            }
            break;
        case 5:
            if (state[0x1c] > 0x17e8) {
                func_ov259_020cd3c4(*state, 0x172, 0x19, state[4]);
                state[0x2a]++;
            }
            break;
        }
        break;
    case 16:
        switch (state[0x2a]) {
        case 0:
            if (state[0x1c] > 0x990) {
                func_ov259_020cd3c4(*state, 0x172, 0xa, state[4]);
                func_ov259_020cd3c4(*state, 0x172, 0x19, state[4]);
                state[0x2a]++;
            }
            break;
        case 1:
            if (state[0x1c] > 0xff0) {
                func_ov259_020cd3c4(*state, 0x172, 0x8, state[4]);
                state[0x2a]++;
            }
            break;
        case 2:
            if (state[0x1c] > 0x1650) {
                func_ov259_020cd3c4(*state, 0x172, 0xe, state[4]);
                func_ov259_020cd3c4(*state, 0x172, 0x18, state[4]);
                state[0x2a]++;
            }
            break;
        case 3:
            if (state[0x1c] > 0x1d38) {
                func_ov259_020cd3c4(*state, 0x172, 0xd, state[4]);
                state[0x2a]++;
            }
            break;
        case 4:
            if (state[0x1c] > 0x2310) {
                func_ov259_020cd3c4(*state, 0x172, 0x10, state[4]);
                state[0x2a]++;
            }
            break;
        case 5:
            if (state[0x1c] > 0x2b90) {
                func_ov259_020cd3c4(*state, 0x172, 0x1a, state[4]);
                state[0x2a]++;
            }
            break;
        }
        break;
    case 17:
        switch (state[0x2a]) {
        case 0:
            if (state[0x1c] > 0x908) {
                func_ov259_020cd3c4(*state, 0x172, 0xa, state[4]);
                state[0x2a]++;
            }
            break;
        case 1:
            if (state[0x1c] > 0x1650) {
                func_ov259_020cd3c4(*state, 0x172, 0xd, state[4]);
                state[0x2a]++;
            }
            break;
        case 2:
            if (state[0x1c] > 0x1d38) {
                func_ov259_020cd3c4(*state, 0x172, 0xb, state[4]);
                state[0x2a]++;
            }
            break;
        case 3:
            if (state[0x1c] > 0x1fe0) {
                func_ov259_020cd3c4(*state, 0x172, 0xa, state[4]);
                state[0x2a]++;
            }
            break;
        case 4:
            if (state[0x1c] > 0x29f8) {
                func_ov259_020cd3c4(*state, 0x172, 0xe, state[4]);
                state[0x2a]++;
            }
            break;
        case 5:
            if (state[0x1c] > 0x2f48) {
                func_ov259_020cd3c4(*state, 0x172, 0x8, state[4]);
                state[0x2a]++;
            }
            break;
        case 6:
            if (state[0x1c] > 0x3520) {
                func_ov259_020cd3c4(*state, 0x172, 0x9, state[4]);
                state[0x2a]++;
            }
            break;
        case 7:
            if (state[0x1c] > 0x3fc0) {
                func_ov259_020cd3c4(*state, 0x172, 0x9, state[4]);
                state[0x2a]++;
            }
            break;
        case 8:
            if (state[0x1c] > 0x5148) {
                func_ov259_020cd3c4(*state, 0x172, 0x10, state[4]);
                state[0x2a]++;
            }
            break;
        case 9:
            if (state[0x1c] > 0x5940) {
                func_ov259_020cd3c4(*state, 0x172, 0x9, state[4]);
                state[0x2a]++;
            }
            break;
        case 10:
            if (state[0x1c] > 0x97f0) {
                func_ov259_020cd3c4(*state, 0x172, 0x17, state[4]);
                state[0x2a]++;
            }
            break;
        }
        break;
    }
}
