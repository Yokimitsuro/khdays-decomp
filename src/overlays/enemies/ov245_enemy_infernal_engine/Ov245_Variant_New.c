/* Allocate a 0x3cc-byte object, link it back to this owner (+0x3c8),
 * install the 020d1e50 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov245_ConstructVariant(int);
int Ov245_Variant_New(int param_1) {
    int obj = CallocInstance(0x3cc);
    *(int *)(obj + 0x3c8) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov245_ConstructVariant;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
