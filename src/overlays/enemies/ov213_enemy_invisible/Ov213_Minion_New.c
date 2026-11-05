/* Allocate a 0x39c-byte object, link it back to this owner (+0x384),
 * install the 020d23c0 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov213_Construct_2(int);
int Ov213_Minion_New(int param_1) {
    int obj = CallocInstance(0x39c);
    *(int *)(obj + 0x384) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov213_Construct_2;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
