/* NONMATCHING: correct logic; several interlocking codegen diffs remain (uVar3 wants a
 * callee-saved r5 + early r4=0; the 14-short copy loop uses subs-preserved-flags not sub+cmp;
 * the slot bit-test uses ldrh/cmp#1 vs ldrsh/cmp#0). Menu top state - kept readable for port. */
/* func_ov008_0204de40 -- main-menu top state after the intro slide-in, ov008.
 * Each frame refreshes cursor state (0204cac0/da6c) and marks the menu ready (heap+0x18=1).
 * If a page transition is in flight (0207baf8) it commits the staged option set (copies the
 * 14-short working layout heap+0x110 -> heap+0xa0) and hands off to func_ov008_0204e04c.
 * Otherwise, with no sub-scene active it gates on the current page's option count (high nibble
 * of heap+0x1e): 0 -> redraw title (cadc 9) and stay; 1 -> redraw one row (cadc 1) and stay;
 * else advance (func_ov008_0204dfb4). With a sub-scene active it waits for the pending flag
 * (heap+8), then (cadc 5) verifies every enabled slot has a loaded save (heap+slot*4+0x92)
 * before committing the layout and advancing. */
extern int   func_02030788(void);
extern int   func_ov008_0204cac0(void);
extern void  func_ov008_0204da6c(void);
extern int   func_ov008_0207baf8(void);
extern int   func_ov008_0204ed3c(void);
extern void  func_ov008_0204cadc(int n);
extern void  func_ov008_0204e04c(void);
extern void  func_ov008_0204dfb4(void);
extern char *data_ov008_02090f00;

void *func_ov008_0204de40(void) {
    unsigned int uVar3;
    void *result;
    int n;
    unsigned char *src, *dst;
    func_02030788();
    uVar3 = func_ov008_0204cac0();
    func_ov008_0204da6c();
    *(int *)(data_ov008_02090f00 + 0x18) = 1;
    if (func_ov008_0207baf8() != 0) {
        n = 0xe;
        src = (unsigned char *)(data_ov008_02090f00 + 0x110);
        dst = (unsigned char *)(data_ov008_02090f00 + 0xa0);
        do {
            unsigned char a = src[0];
            unsigned char b = src[1];
            src += 2;
            n--;
            dst[0] = a;
            dst[1] = b;
            dst += 2;
        } while (n != 0);
        return (void *)func_ov008_0204e04c;
    }
    if (func_ov008_0204ed3c() == 0) {
        uVar3 = (unsigned int)*(unsigned char *)(data_ov008_02090f00 + 0x1e) << 0x18 >> 0x1c;
        if (uVar3 == 0) {
            func_ov008_0204cadc(9);
            return 0;
        }
        result = (void *)func_ov008_0204dfb4;
        if (uVar3 < 2) {
            func_ov008_0204cadc(1);
            result = 0;
        }
    } else if (*(int *)(data_ov008_02090f00 + 8) == 0) {
        func_ov008_0204cadc(9);
        result = 0;
    } else {
        unsigned int i;
        *(int *)(data_ov008_02090f00 + 8) = 0;
        func_ov008_0204cadc(5);
        i = 1;
        do {
            if ((uVar3 & 1 << i) != 0 &&
                *(short *)(data_ov008_02090f00 + i * 4 + 0x92) == 0) {
                return 0;
            }
            i++;
        } while ((int)i < 4);
        n = 0xe;
        src = (unsigned char *)(data_ov008_02090f00 + 0x110);
        dst = (unsigned char *)(data_ov008_02090f00 + 0xa0);
        do {
            unsigned char a = src[0];
            unsigned char b = src[1];
            src += 2;
            n--;
            dst[0] = a;
            dst[1] = b;
            dst += 2;
        } while (n != 0);
        result = (void *)func_ov008_0204dfb4;
    }
    return result;
}
