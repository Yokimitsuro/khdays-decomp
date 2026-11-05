/* Allocate, seed +0x390 from *(owner+0x3c8), install callback (+0x18c), init and return. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov245_HopperConstruct(int);
int Ov245_Hopper_New(int param_1) {
    int obj = CallocInstance(0x3ac);
    *(int *)(obj + 0x390) = *(int *)(param_1 + 0x3c8);
    *(int *)(obj + 0x18c) = (int)&Ov245_HopperConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
