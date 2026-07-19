extern int func_ov002_0205a3f0(int *out, int kind);
extern int func_ov002_0205a4a0(void);
extern int func_ov002_0205a4ec(void);
extern void func_ov002_0205d214(int a, int b);
extern void func_ov002_0205d430(int a);
extern long long func_02020400(int a, int b);
extern char *data_ov002_0207f620;

/* Refreshes the member panel for the current list kind: clears it when the list is empty, and
 * for kind 5 republishes the member id and its row. */
void func_ov002_0205e448(void) {
    int slot;
    char *self = data_ov002_0207f620;
    switch (func_ov002_0205a3f0(&slot, *(unsigned char *)(self + 1))) {
    case 2:
        if (func_ov002_0205a4a0() == 0) {
            func_ov002_0205d214(0, -1);
            func_ov002_0205d430(0);
        }
        return;
    case 3:
        if (func_ov002_0205a4ec() == 0) {
            func_ov002_0205d214(0, -1);
            func_ov002_0205d430(0);
        }
        return;
    case 5:
        if (func_ov002_0205a4ec() == 0) {
            func_ov002_0205d214(0, -1);
            func_ov002_0205d430(0);
            return;
        }
        self[0] = (char)(func_02020400(*(unsigned char *)(self + 4), 6) >> 32);
        func_ov002_0205d214((int)func_02020400(*(unsigned char *)(self + 4), 6) + 6, -1);
        return;
    }
}
