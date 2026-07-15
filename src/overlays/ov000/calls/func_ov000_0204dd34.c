/* func_ov000_0204dd34 -- Scene 1 (boot/logo) second fade state, ov000.
 * Same shape as func_ov000_0204dc38 (the logo fade) but for the next logo/screen
 * pair: uses animation players at heap[0x63]/[0x57] and, when the fade completes,
 * advances to func_ov000_0204de30. heap[0] is the frame counter; the master
 * brightness of both screens fades in (0..0x1f), holds (0x20..0x3a), fades out
 * (0x3b..0x5a), then resets and advances. */

typedef void *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_ov000_0204d354(void);
extern void  func_02024b04(int id, void *player, int, int);
extern void  func_0201e374(int brightness);
extern void  func_0201e3cc(int brightness);
extern void  func_ov000_0204de30(void);

StateFn func_ov000_0204dd34(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    func_ov000_0204d354();
    if (h[0] == 0) {
        func_02024b04(1, (void *)h[0x63], 0, *(int *)(h[0x63] + 8));
        func_02024b04(5, (void *)h[0x57], 0, *(int *)(h[0x57] + 8));
    }
    if (h[0] < 0x20) {
        func_0201e374(0x10 - h[0] / 2);
        func_0201e3cc(0x10 - h[0] / 2);
    } else if (h[0] <= 0x3a) {
        func_0201e374(0);
        func_0201e3cc(0);
    } else if (h[0] <= 0x5a) {
        func_0201e374((h[0] - 0x3a) / 2);
        func_0201e3cc((h[0] - 0x3a) / 2);
    } else {
        func_0201e374(0x10);
        func_0201e3cc(0x10);
        h[0] = 0;
        return (StateFn)func_ov000_0204de30;
    }
    h[0]++;
    return 0;
}
