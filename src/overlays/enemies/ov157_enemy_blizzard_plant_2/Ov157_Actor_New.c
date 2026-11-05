/* Allocates the 0x3a0-byte actor, records its spawner (+0x38c) and state callback (+0x18c), runs
 * the AiState constructor. */

extern void *CallocInstance(int size);
extern void Ov107_AiState_Init(void *obj, int flag);
extern void Ov157_ConstructHeldItem(void);

void *Ov157_Actor_New(void *a) {
    void *obj = CallocInstance(0x3a0);
    *(void **)((char *)obj + 0x38c) = a;
    *(void **)((char *)obj + 0x18c) = Ov157_ConstructHeldItem;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
