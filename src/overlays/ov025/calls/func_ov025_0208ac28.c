typedef unsigned short u16;
typedef signed short s16;

extern void *func_ov025_02084a50(void);
extern void *func_ov025_020894b0(void *context, u16 tag);
extern void func_ov025_02089560(void *context, void *entry,
                                int value, int subId);

void
func_ov025_0208ac28(int group, int value, int maximum,
                    int width, int subId)
{
    void *context = (void *)*(volatile int *)&subId;
    int subIdValue = (int)context;
    void *entry;
    int digit;

    context = func_ov025_02084a50();
    if (value <= maximum) {
        if (value < 0) {
            value = 0;
        }
        maximum = value;
    }

    do {
        digit = maximum % 10;
        maximum = maximum / 10;
        entry = func_ov025_020894b0(context, (u16)(group + digit));
        func_ov025_02089560(context, entry, (s16)width--,
                            (s16)subIdValue);
        if (width < 0) {
            return;
        }
    } while (maximum > 0);
}
