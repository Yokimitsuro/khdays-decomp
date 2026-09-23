/* Recover tick of the ov252 actor: once its +0x60 guard flag is up, +0x578 clears, the +0x5c rest time
 * is rolled between +0x224 and +0x228 (eight times as long while the +0x4ec shape is hidden), the +0x8e
 * shield regenerates to a ninth of the maximum health, the hit state clears and the queued +0x1c9 move
 * becomes next. */
typedef unsigned char u8;
typedef struct { unsigned f : 8; } B8;
typedef struct { unsigned short lo : 8; unsigned short hi : 8; } flags16;

extern int func_02023eb4(int bound);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov252_020cf150(int *node)
{
    int *state = (int *)node[1];
    int lo;
    int mult;
    int span;

    if ((((flags16 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    *(u8 *)(*state + 0x578) = 0;
    mult = (((B8 *)(*(int *)(*state + 0x4ec) + 8))->f & 1) ? 1 : 8;
    lo = *(int *)(*state + 0x224);
    span = *(int *)(*state + 0x228) - lo;
    if (span < 0) {
        span = -span;
    }
    state[0x17] = lo + func_02023eb4(span + 1);
    state[0x17] *= mult;
    *(short *)((char *)state + 0x8e) = *(short *)(*state + 0x218) / 9;
    *((u8 *)state + 0x8a) = 0;
    *((u8 *)state + 0x8b) = 0;
    *((u8 *)state + 0x85) = 0;
    state[0x26] = 0;
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
