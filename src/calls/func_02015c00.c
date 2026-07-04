extern void func_02015b70(void);
extern int data_02047394[];
extern int data_020474cc[];

/* Lazy one-time init (guarded by bit 0x80 at +0xd4), then return the resource. */
int func_02015c00(void) {
    if ((data_02047394[0x35] & 0x80) == 0) {
        func_02015b70();
        data_02047394[0x35] |= 0x80;
    }
    return (int)data_020474cc;
}
