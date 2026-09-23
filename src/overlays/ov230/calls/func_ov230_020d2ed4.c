/* Move picker of the ov230 actor (sibling of the ov249 one, without the projectile slots): once the
 * +0x54 cooldown is spent it rerolls within the owner's +0x224..+0x228 range and a queued move (+0x60)
 * is taken first. Otherwise, one time in five nothing is picked; within 3.0 of the target half the
 * time the actor steps (move 4, flag +0x5c) queueing move 6/9/10 by a d100 roll, else it picks move 6
 * or 8; within 8.0 move 10 or 8; farther move 10. Returns whether a next move was set. */
extern int func_02023eb4(int bound);

int func_ov230_020d2ed4(int self, int range)
{
    int *ctx;
    int roll;
    int lo;
    int spread;
    int queued;

    ctx = *(int **)(self + 4);
    if (ctx[0x15] <= 0) {
        roll = func_02023eb4(100);
        lo = *(int *)(ctx[0] + 0x224);
        spread = *(int *)(ctx[0] + 0x228) - lo;
        if (spread < 0) {
            spread = -spread;
        }
        ctx[0x15] = lo + func_02023eb4(spread + 1);

        queued = *(signed char *)((char *)ctx + 0x60);
        if (queued != -1) {
            *(signed char *)(ctx[0] + 0x1c7) = queued;
            *(signed char *)((char *)ctx + 0x60) = -1;
            goto done;
        }

        if ((unsigned int)func_02023eb4(100) < 0x14) {
            goto done;
        }

        if (range < 0x3000) {
            if ((unsigned int)func_02023eb4(100) < 0x32) {
                ctx[0x17] = 1;
                ctx[0x15] = 0;
                *(signed char *)(ctx[0] + 0x1c7) = 4;

                if (roll < 0x28) {
                    *(signed char *)((char *)ctx + 0x60) = 6;
                    goto done;
                }
                if (roll < 0x3c) {
                    *(signed char *)((char *)ctx + 0x60) = 9;
                    goto done;
                }
                if (roll < 0x50) {
                    *(signed char *)((char *)ctx + 0x60) = 0xa;
                } else {
                    *(signed char *)((char *)ctx + 0x60) = -1;
                }
                goto done;
            }

            if (roll < 0x3c) {
                *(signed char *)(ctx[0] + 0x1c7) = 6;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            }
            goto done;
        }

        if (range < 0x8000) {
            if (roll < 0x42) {
                *(signed char *)(ctx[0] + 0x1c7) = 0xa;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            }
            goto done;
        }

        *(signed char *)(ctx[0] + 0x1c7) = 0xa;

    done:
        if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
            return 1;
        }
    }

    return 0;
}
