extern unsigned char data_0204be04;

extern int func_01fffe14(void);
extern int func_ov002_020698f8(int nIndex);
extern int func_02020a9c(void);
extern int func_01fffde0(int nIndex);

/* Refresh one entry, or every active entry when the caller passes a negative
 * index. The broadcast form is suppressed while the lock byte is set, and it
 * stops after the local entry when the current mode is 0x2a. */
int func_ov002_0206b5a0(int nIndex)
{
    int nSelf;
    int i;

    if (nIndex < 0) {
        nSelf = func_01fffe14();

        if (data_0204be04 != 0) {
            return 0;
        }

        if (func_ov002_020698f8(nSelf) != 0) {
            if (func_02020a9c() == 0x2a) {
                return 1;
            }
            for (i = 0; i < 4; i++) {
                if (i != nSelf && func_01fffde0(i) != 0) {
                    func_ov002_020698f8(i);
                }
            }
            return 1;
        }
    } else {
        if (func_ov002_020698f8(nIndex) != 0) {
            return 1;
        }
    }

    return 0;
}
