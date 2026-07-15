/* func_ov006_0204fab8 -- sample the RTC-availability flag and forward it, ov006. */
extern int OS_IsTickAvailable_0x01ff8138(void);
extern void func_ov006_0204feb0(short *p);
void func_ov006_0204fab8(void) {
    short avail = OS_IsTickAvailable_0x01ff8138();
    func_ov006_0204feb0(&avail);
}
