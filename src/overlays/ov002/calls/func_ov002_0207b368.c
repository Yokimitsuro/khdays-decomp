/* Begin the request at +0x1b6, once. Refuses while the busy byte is already set,
 * while func_ov002_0206b828 reports the subsystem occupied, and -- when the mode
 * byte at +0x1bb is non-zero -- unless func_ov002_0206b88c(1) grants it. On
 * success it latches the busy byte, dispatches the request kind, and if the
 * follow-up state is 1 hands the ov022 handle on to func_ov002_0204cee0.
 * Every path reports 0. */
extern int func_ov002_0206b828(void);
extern int func_ov002_0206b88c(int a);
extern void func_ov002_0207b078(void *self, int kind, int a);
extern void func_02020878(char arg0);
extern int func_ov002_0206b78c(void);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern void func_ov022_02086818(int a, int b);
extern void func_ov002_0204cee0(int a, int b);

int func_ov002_0207b368(unsigned char *self, unsigned char *req) {
    if (func_ov002_0206b828() != 0) {
        return 0;
    }
    if (self[0x1b6] == 0) {
        if (*(signed char *)(self + 0x1bb) != 0) {
            if (func_ov002_0206b88c(1) == 0) {
                return 0;
            }
        }

        self[0x1b6] = 1;
        func_ov002_0207b078(self, req[0], 1);
        func_02020878(0);

        if (func_ov002_0206b78c() == 1) {
            int handle = func_ov022_02083f0c();

            func_ov022_02086818(func_ov022_02083f5c(), 0);
            func_ov002_0204cee0(handle, 1);
        }
    }

    return 0;
}
