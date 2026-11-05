/* Allocate a 0x3f0-byte object, link it back to this owner (+0x388),
 * install the 020d2140 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov253_QueueActorConstruct(int);
int Ov253_QueueActor_New(int param_1) {
    int obj = CallocInstance(0x3f0);
    *(int *)(obj + 0x388) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov253_QueueActorConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
