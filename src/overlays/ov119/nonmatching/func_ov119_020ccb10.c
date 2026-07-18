/*
 * func_ov119_020ccb10 -- x3. Decide the next attack once the retarget timer expires. Measure the
 * planar gap to the target: mag = normalise(target(state[2])+0x74 - state[0x13]); gap = mag -
 * *(state[2]+0x80) - *(state[0]+0x80). Tick state[0x14] -= owner_delta; while it stays >= 0 return 0.
 * Once it goes negative, reroll it to a random value in [*(state[0]+0x224), *(state[0]+0x228)]. If any
 * of the low bits of *(u8)(state[0]+0x1c4) is set, pick attack 7. Otherwise roll a d100: when the gap
 * is close (< 0x5000), pick 0xa if the target is airborne (state[2]+0x1e4 bit3) and the roll < 0x23,
 * else 7; when far, pick (airborne ? 0xa : 7) on a roll < 0x32, else 9. Return 1 when an attack was
 * chosen.
 *
 * NON-MATCHING: scheduling/register-allocation difference in the distance+timer block (size-exact,
 * 312B, semantics and the inverted return-branch all correct). The ROM hoists the state[2] and state[0]
 * loads into callee-saved r5/r6 BEFORE the normalise call and interleaves the gap subtraction with the
 * state[0x14] timer decrement afterwards (self stays in r7); mwcc keeps self in r5, reloads state[2]/
 * state[0] after the call, and orders the timer before the gap. Tried: preloading s2/s0 before the
 * VEC_Subtract (hoists too early), a scoped s2/s0 block between the calls (+4B). The load-placement the
 * ROM chose is not reachable from these C forms. Checklist clean (ARM; VEC_Subtract/01ff8d18 3/2-arg,
 * two genuine 02023eb4 rolls).
 */
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *a, void *b);
extern int  func_02023eb4(int scale);

int func_ov119_020ccb10(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int mag, gap, roll;

    VEC_Subtract((void *)(state[2] + 0x74), (void *)state[0x13], v);
    mag = func_01ff8d18(v, v);
    state[0x14] -= *(int *)(*self + 0x2c);
    gap = mag - *(int *)(state[2] + 0x80) - *(int *)(*state + 0x80);
    if (state[0x14] < 0) {
        int a = *(int *)(*state + 0x224);
        int d = *(int *)(*state + 0x228) - a;
        if (d < 0) {
            d = -d;
        }
        state[0x14] = a + func_02023eb4(d + 1);
        if (*(unsigned char *)(*state + 0x1c4) & 0xf) {
            *(char *)(*state + 0x1c7) = 7;
            return 1;
        }
        roll = func_02023eb4(0x65);
        if (gap < 0x5000) {
            if ((*(int *)(state[2] + 0x1e4) & 8) && roll < 0x23) {
                *(char *)(*state + 0x1c7) = 0xa;
            } else {
                *(char *)(*state + 0x1c7) = 7;
            }
        } else if (roll < 0x32) {
            *(char *)(*state + 0x1c7) = (*(int *)(state[2] + 0x1e4) & 8) ? 0xa : 7;
        } else {
            *(char *)(*state + 0x1c7) = 9;
        }
        return 1;
    }
    return 0;
}
