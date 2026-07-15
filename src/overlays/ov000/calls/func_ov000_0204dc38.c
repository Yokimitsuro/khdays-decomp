/* func_ov000_0204dc38 -- Scene 1 (boot/logo) fade state, ov000.
 * The logo's per-frame running state (returned by the fresh-boot setup). heap[0]
 * is a frame counter. Each frame it ticks the scene (func_ov000_0204d354), and on
 * frame 0 kicks the two animation players (func_02024b04, ids 1 and 5). It then
 * drives the master brightness of both screens (func_0201e374 main / func_0201e3cc
 * sub) as a timed fade:
 *   frames  0..0x1f : fade in   -> 0x10 - f/2   (0x10 dark .. 0 bright)
 *   frames 0x20..0x3a: hold      -> 0           (full brightness)
 *   frames 0x3b..0x5a: fade out  -> (f-0x3a)/2  (0 .. 0x10 dark)
 *   frames  >0x5a    : done      -> 0x10 dark, reset counter, advance to
 *                                   func_ov000_0204dd34.
 * Otherwise it increments the counter and stays (returns 0). */

typedef void *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_ov000_0204d354(void);
extern void  func_02024b04(int id, void *player, int, int);
extern void  func_0201e374(int brightness);
extern void  func_0201e3cc(int brightness);
extern void  func_ov000_0204dd34(void);

StateFn func_ov000_0204dc38(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    func_ov000_0204d354();
    if (h[0] == 0) {
        func_02024b04(1, (void *)h[0x60], 0, *(int *)(h[0x60] + 8));
        func_02024b04(5, (void *)h[0x54], 0, *(int *)(h[0x54] + 8));
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
        return (StateFn)func_ov000_0204dd34;
    }
    h[0]++;
    return 0;
}
