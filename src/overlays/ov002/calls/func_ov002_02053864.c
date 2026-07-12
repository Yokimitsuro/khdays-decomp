/* Forward to the sub-object handler at (*global)+0xdc, passing param_1. */
extern int func_ov002_02054c44(int obj, int arg);
extern int data_ov002_0207f60c;

int func_ov002_02053864(int param_1) {
    return func_ov002_02054c44(*(int *)&data_ov002_0207f60c + 0xdc, param_1);
}
