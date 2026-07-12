/* Forward to the sub-object handler at (*global)+0xdc, passing param_1. */
extern int func_ov002_02054c70(int obj, int arg);
extern int data_ov002_0207f60c;

int func_ov002_020538a0(int param_1) {
    return func_ov002_02054c70(*(int *)&data_ov002_0207f60c + 0xdc, param_1);
}
