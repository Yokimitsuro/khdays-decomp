/* Allocate, link owner (+0x3b4), set +0x19c=0x10, install callback (+0x18c), init and return. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov146_ActorConstruct(int);
int Ov146_Rider_New(int param_1) {
    int obj = CallocInstance(0x3bc);
    *(int *)(obj + 0x3b4) = param_1;
    *(signed char *)(obj + 0x19c) = 0x10;
    *(int *)(obj + 0x18c) = (int)&Ov146_ActorConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
