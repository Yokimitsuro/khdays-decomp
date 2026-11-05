/* Allocates the 0x3a0-byte actor, records its spawner (+0x38c) and state callback (+0x18c), runs
 * the AiState constructor. */

extern void *CallocInstance(int size);
extern void Ov107_AiState_Init(void *obj, int flag);
extern void Ov155_Construct(void);

void *Ov155_Actor_New(void *a) {
    void *obj = CallocInstance(0x3a0);
    *(void **)((char *)obj + 0x38c) = a;
    *(void **)((char *)obj + 0x18c) = Ov155_Construct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
