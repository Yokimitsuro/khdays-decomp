extern void func_02015b70(void);
extern int data_02047394[];
extern int data_0204749c[];

/* Lazy one-time init (guarded by bit 0x80 at +0xd4), then return the resource. */
int func_02015bc8(void) {
    if ((data_02047394[0x35] & 0x80) == 0) {
        func_02015b70();
        data_02047394[0x35] |= 0x80;
    }
    return (int)data_0204749c;
}
