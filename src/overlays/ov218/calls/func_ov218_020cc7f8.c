/* Walk decision of the ov218 actor at target distance `dist`: the +0x18 wait runs down by the frame
 * rate; when it expires a roll is drawn, the wait is rerolled between +0x224 and +0x228 and, if one of
 * the two +0x394 partners is unguarded, far away (16.0+) the next move is 5, at mid range (above 7.0)
 * it is 5 on a 68 % roll (else 6). Returns 1 when a next move is set. */
typedef unsigned short u16;
typedef struct { u16 lo : 8; u16 hi : 8; } flags16;
struct Ov218Actor { char pad[0x394]; int partners[2]; };

extern int func_02023eb4(int bound);

int func_ov218_020cc7f8(int *node, int dist)
{
    int *state = (int *)node[1];
    int roll;
    int lo;
    int span;
    int i;
    int free;

    state[6] -= *(int *)(node[0] + 0x2c);
    if (state[6] <= 0) {
        roll = func_02023eb4(0x64);
        lo = *(int *)(*state + 0x224);
        span = *(int *)(*state + 0x228) - lo;
        if (span < 0) {
            span = -span;
        }
        state[6] = lo + func_02023eb4(span + 1);
        for (i = 0; i < 2; i++) {
            if ((((flags16 *)(((struct Ov218Actor *)*state)->partners[i] + 0x60))->lo & 1) == 0) {
                break;
            }
        }
        free = i < 2;
        if (dist >= 0x8000) {
            if (free) {
                *(unsigned char *)(*state + 0x1c7) = 5;
            }
        } else if (dist > 0x3800) {
            *(unsigned char *)(*state + 0x1c7) = roll < 0x44 && free ? 5 : 6;
        }
        if (*(signed char *)(*state + 0x1c7) != -1) {
            return 1;
        }
    }
    return 0;
}
