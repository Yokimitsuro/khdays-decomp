typedef unsigned short u16;
typedef signed short s16;

extern void *func_ov008_02050c28(void);
extern void *func_ov008_02055808(void *context, u16 tag);
extern void func_ov008_020558b8(void *context, void *entry,
                                int value, int subId);

void
func_ov008_02056fb8(int group, int value, int maximum,
                    int width, int subId)
{
    void *context = (void *)*(volatile int *)&subId;
    int subIdValue = (int)context;
    void *entry;
    int digit;

    context = func_ov008_02050c28();
    if (value <= maximum) {
        if (value < 0) {
            value = 0;
        }
        maximum = value;
    }

    do {
        digit = maximum % 10;
        maximum = maximum / 10;
        entry = func_ov008_02055808(context, (u16)(group + digit));
        func_ov008_020558b8(context, entry, (s16)width--,
                            (s16)subIdValue);
        if (width < 0) {
            return;
        }
    } while (maximum > 0);
}
