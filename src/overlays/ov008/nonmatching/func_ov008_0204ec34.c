/* NONMATCHING: structurally byte-exact (164 B, correct control flow + mla-once slot) except a
 * register-allocation tie in the two short-copy blocks -- the ROM holds the heap pointer in r5
 * / params in r2,r1 where our mwcc picks r3 / r1,r3, and reads param[0] before param[1] where we
 * read them reversed. No local-extraction / inline variant flips the allocation. */
/* func_ov008_0204ec34 -- prime the menu sub-scene slot from a 3-short init, ov008.
 * When the menu heap and the shared "sub-scene active" global are both live, copies the
 * caller's {a,b,c} init triple into heap+0x46/0x48/0x4a, then (if a sub-scene is running)
 * mirrors it into the current player slot (heap + player*6 + 0x2e..0x32) and refreshes the
 * slot's label (func_ov008_0204cadc(3)); otherwise refreshes the shared label (2). */
extern int   func_02030788(void);
extern int   func_02030640(void);
extern int   func_ov008_0204ed3c(void);
extern void  func_ov008_0204cadc(int n);
extern char *data_ov008_02090f00;

void func_ov008_0204ec34(unsigned short *param) {
    int u = func_02030788();
    char *heap;
    if (data_ov008_02090f00 == 0) {
        return;
    }
    if (func_02030640() == 0) {
        return;
    }
    if (param != 0) {
        unsigned short a = param[0];
        unsigned short b = param[1];
        heap = data_ov008_02090f00;
        *(unsigned short *)(heap + 0x46) = a;
        *(unsigned short *)(heap + 0x48) = b;
        *(unsigned short *)(heap + 0x4a) = param[2];
    }
    if (func_ov008_0204ed3c() != 0) {
        char *slot;
        heap = data_ov008_02090f00;
        slot = heap + u * 6;
        *(unsigned short *)(slot + 0x2e) = *(unsigned short *)(heap + 0x46);
        *(unsigned short *)(slot + 0x30) = *(unsigned short *)(heap + 0x48);
        *(unsigned short *)(slot + 0x32) = *(unsigned short *)(heap + 0x4a);
        func_ov008_0204cadc(3);
        return;
    }
    func_ov008_0204cadc(2);
}
