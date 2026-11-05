/* Allocate a 0x38c-byte object, link it back to this owner (+0x384),
 * install the 020d1b24 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov212_ConstructTailActor(int);
int Ov212_Tail_New(int param_1) {
    int obj = CallocInstance(0x38c);
    *(int *)(obj + 0x384) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov212_ConstructTailActor;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
