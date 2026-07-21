extern void func_ov002_0205eca0(void);
extern char *data_ov002_0207f624;
extern int data_ov002_0207eb24;
/* Latch the pending count's payload (ctx+0x7dc) into the shared slot when the count is positive,
 * then run the refresh either way. */
void func_ov002_0205f50c(void) {
    int ctx = (int)data_ov002_0207f624;
    if (*(int *)(ctx + 0x7e0) > 0) {
        data_ov002_0207eb24 = *(int *)(ctx + 0x7dc);
    }
    func_ov002_0205eca0();
}
