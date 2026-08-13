extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_02023c40(void);

static inline int get_limit(void)
{
    return func_02023c40() == 1 ? 0x600 : 0x400;
}

static inline int scale_difference(int difference)
{
    return (int)(((long long)difference * 0x2ac + 0x800) >> 12);
}

unsigned int func_ov002_0204e474(int angle, int targetAngle)
{
    int difference;
    int scaled;
    int limit;

    NNSi_FndGetCurrentRootHeap();
    difference = (unsigned short)(targetAngle - angle);
    if (difference >= 0x8000) {
        difference -= 0x10000;
    }
    if (difference > 0) {
        limit = get_limit();
        scaled = scale_difference(difference);
        if (scaled + limit <= difference) {
            limit = get_limit();
            if (scaled + limit < 0) {
                difference = 0;
            } else {
                limit = get_limit();
                difference = scaled + limit;
            }
        }
    } else {
        limit = get_limit();
        scaled = scale_difference(difference);
        if (scaled - limit > 0) {
            difference = 0;
            goto done;
        }
        limit = get_limit();
        if (scaled - limit < difference) {
            goto done;
        }
        limit = get_limit();
        difference = scaled - limit;
    }
done:
    return (angle + difference) & 0xffff;
}
