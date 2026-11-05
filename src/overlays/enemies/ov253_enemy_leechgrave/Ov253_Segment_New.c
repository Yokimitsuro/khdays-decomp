/* Allocate, link owner (+0x384), install callback (+0x18c), init with arg and return. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov253_Setup(int);
int Ov253_Segment_New(int param_1, int param_2) {
    int obj = CallocInstance(0x3c4);
    *(int *)(obj + 0x384) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov253_Setup;
    Ov107_AiState_Init(obj, param_2);
    return obj;
}
