/* Allocate a 0x398-byte object, link it back to this owner (+0x394),
 * install the 020d2b40 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov254_HelperEConstruct(int);
int Ov254_HelperE_New(int param_1) {
    int obj = CallocInstance(0x398);
    *(int *)(obj + 0x394) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov254_HelperEConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
