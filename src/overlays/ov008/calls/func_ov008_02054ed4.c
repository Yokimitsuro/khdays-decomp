/* For each variable-stride record, build a sprite via func_ov008_0205556c (kind-mapped priority) and place it via func_ov008_02055874. */
extern int func_ov008_0205556c(int self, int a, int b, int c, int d, int e, int f, int prio);
extern void func_ov008_02055874(int self, int handle, int x, int y);
extern unsigned char data_ov008_0208e8f8;
extern unsigned char data_ov008_0208e8f4;
void func_ov008_02054ed4(int param_1, int param_2) {
    unsigned int n = *(unsigned int *)param_2;
    int p = param_2 + 4;
    unsigned int i;
    for (i = 0; i < n; i++) {
        unsigned int kind = *(unsigned short *)(p + 0x14);
        unsigned char prio = kind >= 0xa ? (&data_ov008_0208e8f8)[kind - 0xa] : (&data_ov008_0208e8f4)[kind];
        int handle = func_ov008_0205556c(param_1, *(unsigned short *)(p + 6),
            *(unsigned short *)(p + 4), *(unsigned short *)(p + 0xc),
            *(unsigned short *)(p + 0xe), *(short *)(p + 0x10),
            *(short *)(p + 0x12), prio);
        func_ov008_02055874(param_1, handle, *(short *)(p + 8), *(short *)(p + 0xa));
        p += *(int *)p;
    }
}
