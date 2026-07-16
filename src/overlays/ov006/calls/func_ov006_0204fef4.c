/* func_ov006_0204fef4 -- blank both screens' BG mode bits and tear down the title text layers. */
#define REG_DISPCNT     (*(volatile unsigned int *)0x04000000)
#define REG_DISPCNT_SUB (*(volatile unsigned int *)0x04001000)
extern void func_ov006_02056030(void);   /* reset text layers */
extern void func_ov006_02056098(void);   /* flush text layers */
extern void func_ov006_02055a54(int a, int b, int c);

void func_ov006_0204fef4(void) {
    REG_DISPCNT &= 0xffffe0ff;
    REG_DISPCNT_SUB &= 0xffffe0ff;
    func_ov006_02056030();
    func_ov006_02056098();
    func_ov006_02055a54(10, 0, 0);
}
