/* MobiClip player teardown: release the two blocks the player owns on the root heap (the stream
 * state at +0x8b4c and the reader at +0x8b40), drop sound channel 3, then invalidate the
 * current-clip id and clear the player block's second word.
 *
 * Parked as pure instruction scheduling -- the original materialises both constants first and
 * then does both stores, while mwcc interleaved them. It was the global read: written as
 * `*(int *)((char *)&data + 4)` the whole store is one expression mwcc schedules as it likes;
 * written as `data[1]` it comes out as the original has it. Same lever as
 * func_ov008_02050970. */
extern int  NNSi_FndGetCurrentRootHeap(void);
extern void WM_EndKeySharing_0x020835cc(int p);
extern void func_0202f818(int p);
extern void func_02020aa8(int channel, int a);
extern int  data_ov024_02093900;
extern int  data_ov024_02093a20[];

void func_ov024_02082c44(void) {
    int heap = NNSi_FndGetCurrentRootHeap();
    WM_EndKeySharing_0x020835cc(heap + 0x8b4c);
    func_0202f818(heap + 0x8b40);
    func_02020aa8(3, 0);
    data_ov024_02093900 = -1;
    data_ov024_02093a20[1] = 0;
}
