/* How many frames to blend when an actor changes animation mode.
 *
 * A pure table: no memory is touched and there are no relocations. The answer is zero by default,
 * zero whenever the mode does not actually change, and otherwise decided in two stages.
 *
 * First by the new mode. Then, but only when either mode reaches 0x2e, a second table keyed on the
 * actor kind can override it.
 *
 * Callers pass the new mode, the actor's current mode from self+0x6bc and its kind from self+0xc,
 * and hand the result to the animation apply as its blend argument. Thirty-four matched sources
 * call it, across ov002 and the enemy overlays from ov030 to ov046.
 *
 * Codegen notes, all four measured against the alternatives. Both dispatches are switches, not if
 * chains; an if chain inverts the first branch and costs 24 bytes. The kind switch must contain
 * exactly FOUR cases in the 0 to 4 range: with five of them mwcc widens the jump table all the way
 * to 13 and costs 32 bytes, with three it drops to a compare chain and costs 8. The mode switch
 * bodies are laid out 3, 1, 14, the 0x17 group, then 0. And mode 1's answer is written with the
 * inequality first, not-3 gives 5 else 10, which orders the two predicated moves the ROM's way
 * round.
 *
 * Ghidra carries this as Ov002_GetModeBlendFrames.
 */

int func_ov002_020519b0(int from, int to, int ctx) {
    int result = 0;

    if (from == to) {
        return 0;
    }

    switch (from) {
    case 3:
        if (to != 2 && to != 6 && to != 5) {
            result = 5;
        }
        break;
    case 1:
        result = (to != 3) ? 5 : 10;
        break;
    case 14:
        result = 3;
        break;
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
        result = 5;
        break;
    case 0:
        if ((to < 0x1b || to >= 0x2e) && to >= 0) {
            result = 5;
        }
        if (to == 0x11 || to == 0x12 || to == 0x1a || to == 0xc) {
            result = 0;
        }
        break;
    case 15:
        result = 10;
        break;
    }

    if (from >= 0x2e || to >= 0x2e) {
        switch (ctx) {
        case 0:
            if (from == 4) {
                result = 5;
            }
            break;
        case 1:
            break;
        case 2:
            if (to == 3) {
                result = 5;
            }
            break;
        case 4:
            if (from == 0x2f && to == 0x30) {
                result = 8;
            }
            break;
        case 13:
            if (from == 0x2f && to == 0x32) {
                result = 5;
            }
            if (from == 0x32 && to == 0x32) {
                result = 5;
            }
            break;
        case 0x13:
            if (from == 0x30 && to == 0x2f) {
                result = 5;
            }
            break;
        }
    }
    return result;
}
