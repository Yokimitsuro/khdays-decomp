/* func_ov006_0204fe2c -- read the current-screen flag byte, ov006. Indexes the ov006
 * context (*data_ov006_020565e4) by the RTC-available bit and reads byte @+0x48e. */
extern int OS_IsTickAvailable(void);
extern char *data_ov006_020565e4;
int func_ov006_0204fe2c(void) {
    return *(unsigned char *)(data_ov006_020565e4 + OS_IsTickAvailable() + 0x48e);
}
