/* Allocate a 0x3bc-byte object, link it back to this owner (+0x390),
 * install the 020d0a58 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov260_SubPartAConstruct(int);
int Ov260_New_2(int param_1) {
    int obj = CallocInstance(0x3bc);
    *(int *)(obj + 0x390) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov260_SubPartAConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
