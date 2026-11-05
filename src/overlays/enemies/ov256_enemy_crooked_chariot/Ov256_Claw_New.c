/* Allocate, link owner (+0x3ac), store arg (+0x394 byte), install callback (+0x18c), init, return. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov256_ClawInit(int);
int Ov256_Claw_New(int param_1, int param_2) {
    int obj = CallocInstance(0x3b0);
    *(int *)(obj + 0x3ac) = param_1;
    *(signed char *)(obj + 0x394) = param_2;
    *(int *)(obj + 0x18c) = (int)&Ov256_ClawInit;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
