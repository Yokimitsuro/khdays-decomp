/* Follow the +0xc link of the stride-8 table entry indexed by the second ov009 counter. */
struct e8b { int a, b; };
extern int data_ov009_020563ec;
extern int data_ov009_020562d4;
int func_ov009_0204ee30(void) {
    int idx = (&data_ov009_020563ec)[1];
    return *(int *)(((struct e8b *)&data_ov009_020562d4)[idx].a + 0xc);
}
