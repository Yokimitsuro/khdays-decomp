extern int func_0201eea8(int h);
extern void func_ov000_020532f0(void);
extern void func_ov000_02053524(void);
extern void func_ov000_020535b4(void);
extern long long func_020031d4(void);
extern void func_ov000_02054108(void);
extern char *data_ov000_0205ac28;

/* Waits for the pending load; once it lands, builds the three menu layers, records the 64-bit
 * timestamp and hands over to the menu tick. */
void *func_ov000_02053f08(void) {
    void *next = 0;
    if (func_0201eea8(*(int *)(data_ov000_0205ac28 + 0x4000 + 0xb00)) != 0) {
        long long stamp;
        func_ov000_020532f0();
        func_ov000_02053524();
        func_ov000_020535b4();
        stamp = func_020031d4();
        next = (void *)&func_ov000_02054108;
        *(long long *)(data_ov000_0205ac28 + 0x14) = stamp;
    }
    return next;
}
