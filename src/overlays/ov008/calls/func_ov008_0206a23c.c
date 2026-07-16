/* func_ov008_0206a23c -- reset the ov008 mission-slot state and set its mode word (obj+2):
 * mode 2 only when the shared flag, func_02030670 and NOT func_02030694 all agree; otherwise 1. */
extern int  func_ov008_02050cd4(void);
extern void MI_CpuFill8(void *dst, int val, unsigned int size);
extern int  func_02030640(void);
extern int  func_02030670(void);
extern int  func_02030694(void);

void func_ov008_0206a23c(void) {
    int *obj = (int *)func_ov008_02050cd4();
    int alt;
    MI_CpuFill8(obj, 0, 0xbc);
    alt = 0;
    obj[0x2d] = alt;
    obj[0x2e] = alt;
    if (func_02030640() == 0) {
        alt = 1;
    }
    if (func_02030670() == 0) {
        alt = 1;
    }
    if (func_02030694() != 0) {
        alt = 1;
    }
    *(unsigned short *)((int)obj + 2) = (alt != 0) ? 1 : 2;
}
