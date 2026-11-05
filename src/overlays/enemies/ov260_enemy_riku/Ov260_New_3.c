/* Allocate a 0x3ac-byte object, link it back to this owner (+0x38c),
 * install the 020d1858 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov260_SubPartBConstruct(int);
int Ov260_New_3(int param_1) {
    int obj = CallocInstance(0x3ac);
    *(int *)(obj + 0x38c) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov260_SubPartBConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
