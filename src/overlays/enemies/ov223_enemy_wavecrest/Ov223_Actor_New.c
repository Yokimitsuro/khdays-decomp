/* Allocate a 0x3a0-byte object, wire its owner (+0x38c) and vtable/handler
 * (+0x18c = Ov223_ConstructItem), start it via Ov107_AiState_Init, and return it. */
extern int CallocInstance(int size);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov223_ConstructItem(void);
int Ov223_Actor_New(int param_1) {
    int obj = CallocInstance(0x3a0);
    *(int *)(obj + 0x38c) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov223_ConstructItem;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
