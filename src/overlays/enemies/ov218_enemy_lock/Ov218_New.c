/* Allocate, link owner (+0x390), set +0x19c=0x30, install callback (+0x18c), init and return. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov218_Build(int);
int Ov218_New(int param_1) {
    int obj = CallocInstance(0x3b8);
    *(int *)(obj + 0x390) = param_1;
    *(signed char *)(obj + 0x19c) = 0x30;
    *(int *)(obj + 0x18c) = (int)&Ov218_Build;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
