/* Allocate a 0x3a0-byte object, link it back to this owner (+0x394),
 * install the 020d12e0 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov245_ThrownConstruct(int);
int Ov245_Thrown_New(int param_1) {
    int obj = CallocInstance(0x3a0);
    *(int *)(obj + 0x394) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov245_ThrownConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
