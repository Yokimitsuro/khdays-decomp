/* func_ov279_020d0750 -- x3. Decide the next attack once the retarget timer expires. Measure the
 * planar gap to the target: mag = normalise(target(state[2])+0x74 - state[0x13]); gap = mag -
 * *(state[2]+0x80) - *(state[0]+0x80). Tick state[0x14] -= owner_delta; while it stays >= 0 return 0.
 * Once it goes negative, reroll it to a random value in [*(state[0]+0x224), *(state[0]+0x228)]. If any
 * of the low bits of *(u8)(state[0]+0x1c4) is set, pick attack 7. Otherwise roll a d100: when the gap
 * is close (< 0x5000), pick 0xa if the target is airborne (state[2]+0x1e4 bit3) and the roll < 0x23,
 * else 7; when far, pick (airborne ? 0xa : 7) on a roll < 0x32, else 9. Return 1 when an attack was
 * chosen. Both rolls are the inline RandRange (lo + rand(|hi - lo| + 1)); the d100's zero
 * low bound survives as the `add r1,r0,#0` copy of the roll. The target and owner pointers are
 * read between the two vector calls and kept callee-saved for the gap. */
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *a, void *b);
extern int  func_02023eb4(int scale);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

int func_ov279_020d0750(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int mag, gap, roll;
    int target, owner;

    VEC_Subtract((void *)(state[2] + 0x74), (void *)state[0x13], v);
    target = state[2];
    owner = state[0];
    mag = func_01ff8d18(v, v);
    gap = mag - *(int *)(target + 0x80) - *(int *)(owner + 0x80);
    state[0x14] -= *(int *)(*self + 0x2c);
    if (state[0x14] < 0) {
        state[0x14] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
        if (*(unsigned char *)(*state + 0x1c4) & 0xf) {
            *(char *)(*state + 0x1c7) = 7;
        } else {
            roll = RandRange(0, 100);
            if (gap < 0x5000) {
                if ((*(int *)(state[2] + 0x1e4) & 8) && roll < 0x23) {
                    *(char *)(*state + 0x1c7) = 0xa;
                } else {
                    *(char *)(*state + 0x1c7) = 7;
                }
            } else if (roll < 0x32) {
                if (*(int *)(state[2] + 0x1e4) & 8) {
                    *(char *)(*state + 0x1c7) = 0xa;
                } else {
                    *(char *)(*state + 0x1c7) = 7;
                }
            } else {
                *(char *)(*state + 0x1c7) = 9;
            }
        }
        return 1;
    }
    return 0;
}
