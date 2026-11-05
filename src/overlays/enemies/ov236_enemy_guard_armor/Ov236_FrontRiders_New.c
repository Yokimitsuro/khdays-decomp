/* Allocate a 0x3c8-byte object, link it back to this owner (+0x394),
 * install the 020cce54 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov236_FrontRidersConstruct(int);
int Ov236_FrontRiders_New(int param_1) {
    int obj = CallocInstance(0x3c8);
    *(int *)(obj + 0x394) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov236_FrontRidersConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
