/* NONMATCHING: 84/84 bytes, pure instruction scheduling. The ROM materialises BOTH constants
 * first (mvn r3,#0 ; mov r2,#0) and then does both stores; mwcc interleaves them
 * (mvn r2,#0 ; str ; mov r1,#0 ; str). Hoisting them into explicit locals does not change it.
 *
 * func_ov024_02082c44 -- MobiClip player: tear the player down.
 * Releases the two blocks the player owns on the root heap (the stream state at +0x8b4c and
 * the reader at +0x8b40), drops sound channel 3, then invalidates the current-clip id and
 * clears the player block's second word. */
extern int  NNSi_FndGetCurrentRootHeap(void);
extern void WM_EndKeySharing_0x020835cc(int p);
extern void func_0202f818(int p);
extern void func_02020aa8(int ch, int a);
extern int  data_ov024_02093900;
extern int  data_ov024_02093a20;

void func_ov024_02082c44(void) {
    int heap = NNSi_FndGetCurrentRootHeap();
    WM_EndKeySharing_0x020835cc(heap + 0x8b4c);
    func_0202f818(heap + 0x8b40);
    func_02020aa8(3, 0);
    {
        int invalid = -1;
        int zero = 0;
        data_ov024_02093900 = invalid;
        *(int *)((char *)&data_ov024_02093a20 + 4) = zero;
    }
}
