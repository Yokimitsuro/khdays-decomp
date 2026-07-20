/* Poll one request bit of the global flag word (data_0204c190 bit 3).
 * When game flag 0x2483 is set, give ov023 first refusal on the request
 * (func_ov023_02083e08); if it declines, play sound 4 and drop the request.
 * Otherwise latch the request in the halfword at data_0204be08+2 -- playing
 * sound 1 only on the transition from 0 -- and post event 0x12. */
extern unsigned short data_0204c190;
extern unsigned short data_0204be08;
extern unsigned short data_0204be0a;

extern int func_02023588(int flag);
extern int func_ov023_02083e08(void);
extern void func_02033b24(int a, int b);
extern void func_02033b78(int a, int b);
extern short func_02031384(int a, void *b, int c);

void func_0202348c(void) {
    if ((data_0204c190 & 8) == 0) return;

    if (func_02023588(0x2483) != 0) {
        if (func_ov023_02083e08() == 0) {
            func_02033b24(0, 4);
        }
        return;
    }

    if ((&data_0204be08)[1] == 0) {
        func_02033b78(0, 1);
    }
    (&data_0204be08)[1] = 1;
    func_02031384(0x12, &data_0204be0a, 2);
}
