typedef unsigned char u8;

extern u8 data_0204be04;
extern const char data_ov002_0207f480[];

extern int func_01fffe14(void);
extern void func_ov002_0207b078(char *pElement, int nIndex, int bOn);
extern int func_ov002_020573cc(void);
extern int func_ov002_0206b828(void);
extern void func_02020878(int nMode);
extern void func_ov002_0206b88c(int bOn);
extern int func_ov002_0206b78c(void);
extern int func_ov002_0206b9cc(void);
extern void func_ov002_0206b9b4(u8 nBits);
extern void func_ov002_0206b97c(void);
extern void func_ov002_0206aae4(int nKind, u8 nBits);
extern int func_02023588(int nField);
extern void func_ov002_0207b054(int a, int b, int c, int d);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern int func_ov022_02083f40(void);
extern void func_ov022_02086818(int nHandle, int nMode);
extern void func_ov002_0204cee0(int nHandle, int nMode);
extern void func_ov002_0204cb70(int nHandle, int nMode, void *pExtra);
extern int OS_IsThreadAvailable_0x0205f534(void);
extern void func_ov002_0206b910(const char *pName, void *pText);
extern int func_02030788(void);
extern void func_ov002_0206d928(int nMode);
extern void func_ov002_0206f514(int nMode);
extern void func_ov002_02057390(int nMode);
extern int func_ov002_020573a4(void);
extern void func_ov002_0205f594(void);

/* Follow-up handler an element hands over to when its line finishes.
 *
 * Nothing runs at all while the global hold is set. The element takes the other
 * entries over again if it had released them, and then the step depends on how
 * far the hand-over has got: step 1 opens the choice, using the owner's own
 * parameters when the game state asks for it and the plain ones otherwise;
 * step 2 reads the answer back and either says the closing line or drops
 * straight out; step 3 waits for the transition and restores the step it had
 * saved; step 4 puts everything back. Always returns zero.
 */
int func_ov002_0207b698(char *pElement)
{
    char *pOwner;
    int nRes;
    int nA;
    int nB;

    pOwner = *(char **)(pElement + 8);

    if (data_0204be04 != 0) {
        return 0;
    }

    if ((*(u8 *)(pElement + 0x1b5) & 2) != 0) {
        func_ov002_0207b078(pElement, func_01fffe14(), 1);
    }

    switch (*(u8 *)(pElement + 0x1b6)) {
    case 1:
        if (func_ov002_020573cc() != 0 || func_ov002_0206b828() != 0) {
            func_ov002_0207b078(pElement, func_01fffe14(), 0);
            *(u8 *)(pElement + 0x1b6) = 0;
            func_02020878(1);
            if (*(signed char *)(pElement + 0x1bb) != 0) {
                func_ov002_0206b88c(0);
            }
            return 0;
        }

        if (func_ov002_0206b78c() == 5) {
            func_ov002_0206aae4(1, (u8)(func_ov002_0206b9cc() & ~0xb));
        } else {
            func_ov002_0206aae4(1, (u8)(func_ov002_0206b9cc() & ~0xa));
        }

        if (func_02023588(0x2085) != 0) {
            func_ov002_0207b054(*(int *)(pOwner + 0x70),
                                *(int *)(pOwner + 0x78),
                                *(int *)(pOwner + 0x7c), 1);
            *(u8 *)(pElement + 0x1b6) = 2;
        } else {
            func_ov002_0207b054(*(int *)(pOwner + 0x6c), 0, 0, 0);
            *(u8 *)(pElement + 0x1b7) = 4;
            *(u8 *)(pElement + 0x1b6) = 3;
            if (*(signed char *)(pElement + 0x1bb) != 0) {
                func_ov002_0206b88c(0);
            }
        }

        if (func_ov002_0206b78c() == 1 || func_ov002_0206b78c() == 5) {
            nA = func_ov022_02083f0c();
            func_ov022_02086818(func_ov022_02083f5c(), 0);
            func_ov002_0204cee0(nA, 1);
            func_ov002_0204cb70(nA, 1, 0);
            if (func_ov002_0206b78c() == 5) {
                func_ov002_0204cee0(func_ov022_02083f40(), 1);
            }
        }
        break;

    case 2:
        nRes = OS_IsThreadAvailable_0x0205f534();
        if (nRes < 0) {
            break;
        }
        if (nRes == 0) {
            if (*(signed char *)(pElement + 0x1bb) != 0) {
                func_ov002_0206b910(data_ov002_0207f480, pElement + 0x1bb);
                if (func_ov002_0206b78c() == 5) {
                    func_ov002_0206b9b4((u8)(func_ov002_0206b9cc() & ~0xb));
                } else {
                    func_ov002_0206b9b4((u8)(func_ov002_0206b9cc() & ~0xa));
                }
                func_ov002_0206b97c();
            } else if (func_02030788() == 0) {
                func_ov002_0206d928(0);
            }
            *(u8 *)(pElement + 0x1b6) = 0;
            func_ov002_0206f514(1);
        } else {
            func_ov002_02057390(0);
            *(u8 *)(pElement + 0x1b7) = 4;
            *(u8 *)(pElement + 0x1b6) = 3;
            if (*(signed char *)(pElement + 0x1bb) != 0) {
                func_ov002_0206b88c(0);
            }
        }
        break;

    case 3:
        if (func_ov002_020573a4() != 0) {
            func_ov002_0205f594();
            *(u8 *)(pElement + 0x1b6) = *(u8 *)(pElement + 0x1b7);
            *(u8 *)(pElement + 0x1b7) = 0;
        }
        break;

    case 4:
        func_02020878(1);
        func_ov002_0207b078(pElement, func_01fffe14(), 0);
        func_ov002_0206aae4(0, 0);
        *(u8 *)(pElement + 0x1b6) = 0;

        if (func_ov002_0206b78c() == 1 || func_ov002_0206b78c() == 5) {
            nA = func_ov022_02083f0c();
            nB = func_ov022_02083f5c();
            func_ov002_0204cb70(nA, 0, 0);
            func_ov002_0204cee0(nA, 0);
            func_ov022_02086818(nB, 1);
            if (func_ov002_0206b78c() == 5) {
                func_ov002_0204cee0(func_ov022_02083f40(), 0);
            }
        }
        break;
    }

    return 0;
}
