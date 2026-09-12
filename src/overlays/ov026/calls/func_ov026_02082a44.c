/* func_ov026_02082a44 -- restore the capture/blend engines (func_0201e374/3cc with -0x10),
 * clear the BG-mode/screen-base bits of both DISPCNT registers, and switch the main engine
 * to the top physical LCD via func_ov002_02076028. */
typedef volatile unsigned int vu32;

extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern void func_ov002_02076028(int top);

void func_ov026_02082a44(void) {
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    *(vu32 *)0x04000000 &= ~0x1f00;
    *(vu32 *)0x04001000 &= ~0x1f00;
    func_ov002_02076028(1);
}
