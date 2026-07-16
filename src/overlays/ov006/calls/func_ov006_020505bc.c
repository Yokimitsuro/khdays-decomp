/* func_ov006_020505bc -- test whether the Mission Mode menu confirm should fire, ov006.
 * When the Mission Mode is idle (base+0x20 == 0), checks the currently highlighted option
 * (func_ov006_0204f554 on the 0-based cursor from base+0x38); when active, checks the generic
 * confirm (func_ov006_0204f470). Either success selects the confirm state fn
 * (func_ov006_02050630). Always refreshes the cursor sprite (func_ov006_02055b0c(0xff)) and, on
 * confirm, plays the decide SFX (func_ov006_02055a54(2,0)). Returns the selected state (or 0). */
extern int  func_ov006_0204f470(void);
extern int  func_ov006_0204f554(int option);
extern void func_ov006_02055b0c(int a);
extern void func_ov006_02055a54(int a, int b, int c);
extern int  data_ov006_02056660;
extern void func_ov006_02050630(void);

int func_ov006_020505bc(void) {
    int result = 0;
    if (*(int *)(data_ov006_02056660 + 0x20) != 0) {
        if (func_ov006_0204f470() != 0) {
            result = (int)func_ov006_02050630;
        }
    } else {
        if (func_ov006_0204f554((*(int *)(data_ov006_02056660 + 0x38) - 1U) & 0xff) != 0) {
            result = (int)func_ov006_02050630;
        }
    }
    func_ov006_02055b0c(-1);
    if (result != 0) {
        func_ov006_02055a54(2, 0, 0);
    }
    return result;
}
