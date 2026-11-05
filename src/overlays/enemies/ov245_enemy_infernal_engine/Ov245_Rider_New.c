/* Allocate, link owner (+0x3cc), set +0x19c=4, install callback (+0x18c), init with arg, set
 * +0x220=0x1000 and return. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov245_ConstructRider(int);
int Ov245_Rider_New(int param_1, int param_2) {
    int obj = CallocInstance(0x3d0);
    *(int *)(obj + 0x3cc) = param_1;
    *(signed char *)(obj + 0x19c) = 4;
    *(int *)(obj + 0x18c) = (int)&Ov245_ConstructRider;
    Ov107_AiState_Init(obj, param_2);
    *(int *)(obj + 0x220) = 0x1000;
    return obj;
}
