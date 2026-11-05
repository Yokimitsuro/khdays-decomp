/* Allocates the 0x3a8-byte actor with its owner and constructor. */

extern void *CallocInstance(int size);
extern void Ov107_AiState_Init(void *obj, int flag);
extern void Ov152_ConstructPet(void);

void *Ov152_New(void *a) {
    void *obj = CallocInstance(0x3a8);
    *(void **)((char *)obj + 0x38c) = a;
    *(void **)((char *)obj + 0x18c) = Ov152_ConstructPet;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
