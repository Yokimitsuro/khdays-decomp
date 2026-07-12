/* Forward to func_ov002_0205bff4 with the byte at *global as the first arg. */
extern int func_ov002_0205bff4(int val, int arg);
extern int data_ov002_0207f620;

int func_ov002_0205d430(int param_1) {
    return func_ov002_0205bff4(*(unsigned char *)*(int *)&data_ov002_0207f620, param_1);
}
