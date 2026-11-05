/* Allocate, link owner (+0x390), store arg (+0x38c byte), install callback (+0x18c), init, return. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov258_ItemConstruct(int);
int Ov258_New(int param_1, int param_2) {
    int obj = CallocInstance(0x394);
    *(int *)(obj + 0x390) = param_1;
    *(signed char *)(obj + 0x38c) = param_2;
    *(int *)(obj + 0x18c) = (int)&Ov258_ItemConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
