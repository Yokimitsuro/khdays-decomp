/* func_ov008_02081650 -- if a heap is active, reset the two title tween channels (-0x10) and
 * blank both screens' BG mode bits. */
#define REG_DISPCNT     (*(volatile unsigned int *)0x04000000)
#define REG_DISPCNT_SUB (*(volatile unsigned int *)0x04001000)
extern int  NNSi_FndGetCurrentRootHeap(void);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);

void func_ov008_02081650(void) {
    if (NNSi_FndGetCurrentRootHeap() == 0) {
        return;
    }
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    REG_DISPCNT &= 0xffffe0ff;
    REG_DISPCNT_SUB &= 0xffffe0ff;
}
