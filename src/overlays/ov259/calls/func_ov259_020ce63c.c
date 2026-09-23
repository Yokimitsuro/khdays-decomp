/* Hit-window step of the ov259 actor: the +0x418 pose clock accumulates the frame rate and the
 * current pose (+0x41c) decides whether its attack is live: 9 in 0x3b8-0x770, 10 from 0x7f8, 11 up
 * to 0x550, 14 in 0xe58-0x1430 or 0x1fe0-0x2750, 16 in 0-0xd48 or 0xff0-0x1540, 17 in 0-0x2e38,
 * 18 and 19 always, 20 in 0-0x1100, 0x1540-0x1d38 or from 0x2288, 21 in 0-0xdd0, 26 from 0xd48.
 * When the window opens (+0x42c clear) or closes (+0x42c set) the actor is told at the +0x10 point
 * (020c0b90 mode 0x11 / 0x10). */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);

void func_ov259_020ce63c(int *node)
{
    int *state = (int *)node[1];
    int live = 0;
    int t;

    *(int *)(*state + 0x418) += *(int *)(node[0] + 0x2c);
    t = *(int *)(*state + 0x418);
    switch (*(int *)(*state + 0x41c)) {
    case 0:
        break;
    case 9:
        if (t >= 0x3b8 && t <= 0x770) {
            live = 1;
        }
        break;
    case 10:
        if (t >= 0x7f8) {
            live = 1;
        }
        break;
    case 11:
        if (t <= 0x550) {
            live = 1;
        }
        break;
    case 14:
        if ((t >= 0xe58 && t <= 0x1430) || (t >= 0x1fe0 && t <= 0x1fe0 + 0x770)) {
            live = 1;
        }
        break;
    case 16:
        if ((t >= 0 && t <= 0xd48) || (t >= 0xff0 && t <= 0x1540)) {
            live = 1;
        }
        break;
    case 17:
        if (t >= 0 && t <= 0x2e38) {
            live = 1;
        }
        break;
    case 18:
    case 19:
        live = 1;
        break;
    case 20:
        if ((t >= 0 && t <= 0x1100) || (t >= 0x1540 && t <= 0x1d38) || t >= 0x2288) {
            live = 1;
        }
        break;
    case 21:
        if (t >= 0 && t <= 0xdd0) {
            live = 1;
        }
        break;
    case 26:
        if (t >= 0xd48) {
            live = 1;
        }
        break;
    }
    if (live) {
        if (*(int *)(*state + 0x42c) != 0) {
            return;
        }
        func_ov107_020c0b90(*state, 0x11, *(Vec3 *)state[4], 0);
    } else {
        if (*(int *)(*state + 0x42c) == 0) {
            return;
        }
        func_ov107_020c0b90(*state, 0x10, *(Vec3 *)state[4], 0);
    }
}
