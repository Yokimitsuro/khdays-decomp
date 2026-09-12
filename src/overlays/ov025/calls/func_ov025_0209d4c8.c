/* func_ov025_0209d4c8 -- Ov008_DispatchMenuInput: route one frame of pressed
 * buttons to the menu's handlers, one per frame in priority order: up (0x40),
 * down (0x80), confirm (0x20), cancel (0x10), then A/B (1, 2), the two shoulder
 * buttons (0x200, 0x100) and Start (8).  The menu context getter is called for
 * its side effect only.
 */
typedef unsigned int u32;

#define KEY_A      0x0001
#define KEY_B      0x0002
#define KEY_START  0x0008
#define KEY_RIGHT  0x0010
#define KEY_LEFT   0x0020
#define KEY_UP     0x0040
#define KEY_DOWN   0x0080
#define KEY_R      0x0100
#define KEY_L      0x0200

extern void *func_ov025_02084afc(void);      /* Ov008_GetMenuContext */
extern void func_ov025_0209c8f4(void);       /* move up */
extern void func_ov025_0209c9b0(void);       /* move down */
extern void func_ov025_0209ca78(void);       /* Ov008_ConfirmMenuSelection */
extern void func_ov025_0209cb3c(void);       /* Ov008_CancelMenuSelection */
extern void func_ov025_0209cc00(void);       /* A / B / Start */
extern void func_ov025_0209cc28(void);       /* L */
extern void func_ov025_0209cc58(void);       /* R */

void func_ov025_0209d4c8(int nUnused, u32 nKeys)
{
    func_ov025_02084afc();
    if ((nKeys & KEY_UP) != 0) {
        func_ov025_0209c8f4();
        return;
    }
    if ((nKeys & KEY_DOWN) != 0) {
        func_ov025_0209c9b0();
        return;
    }
    if ((nKeys & KEY_LEFT) != 0) {
        func_ov025_0209ca78();
        return;
    }
    if ((nKeys & KEY_RIGHT) != 0) {
        func_ov025_0209cb3c();
        return;
    }
    if ((nKeys & KEY_A) != 0) {
        func_ov025_0209cc00();
        return;
    }
    if ((nKeys & KEY_B) != 0) {
        func_ov025_0209cc00();
        return;
    }
    if ((nKeys & KEY_L) != 0) {
        func_ov025_0209cc28();
        return;
    }
    if ((nKeys & KEY_R) != 0) {
        func_ov025_0209cc58();
        return;
    }
    if ((nKeys & KEY_START) != 0) {
        func_ov025_0209cc00();
    }
}
