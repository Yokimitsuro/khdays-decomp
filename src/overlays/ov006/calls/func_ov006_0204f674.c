/* func_ov006_0204f674 -- if the tick source is early (<2), mark the input object busy
 * (ctx+0x4e8 = 1); then kick its update (func_02023a44 with callback func_ov006_0204f6bc),
 * and return the busy flag. */
extern unsigned short OS_IsTickAvailable_0x01ff8138(void);
extern void func_02023a44(int obj, void *cb);
extern void func_ov006_0204f6bc(void);
extern int  data_ov006_020565e4;   /* title-screen state struct: [1] = input object */

int func_ov006_0204f674(void) {
    if (OS_IsTickAvailable_0x01ff8138() <= 1) {
        *(int *)(data_ov006_020565e4 + 0x4e8) = 1;
    }
    func_02023a44(*(int *)((int)&data_ov006_020565e4 + 4), func_ov006_0204f6bc);
    return *(int *)(data_ov006_020565e4 + 0x4e8);
}
