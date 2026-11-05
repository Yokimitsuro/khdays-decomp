/* Allocate a 0x3a4-byte object, link it back to this owner (+0x390),
 * install the 020d55a8 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov199_InitSubActor(int);
int Ov199_AllocLinkChild3a4(int param_1) {
    int obj = CallocInstance(0x3a4);
    *(int *)(obj + 0x390) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov199_InitSubActor;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
