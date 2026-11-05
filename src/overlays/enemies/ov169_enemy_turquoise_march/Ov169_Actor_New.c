/* Allocates a part actor, records its spawner (+0x38c) and its state callback (+0x18c), and hands
 * it to the shared enemy framework. */

extern void *CallocInstance(int size);
extern void Ov107_AiState_Init(void *obj, int flag);
extern void Ov169_SubObject_ConstructB(void);

void *Ov169_Actor_New(void *a) {
    void *obj = CallocInstance(0x39c);
    *(void **)((char *)obj + 0x38c) = a;
    *(void **)((char *)obj + 0x18c) = Ov169_SubObject_ConstructB;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
