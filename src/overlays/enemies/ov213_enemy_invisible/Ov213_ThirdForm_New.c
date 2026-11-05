/* Allocate a 0x398-byte object, link it back to this owner (+0x384),
 * install the 020d165c callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov213_ConstructThirdForm(int);
int Ov213_ThirdForm_New(int param_1) {
    int obj = CallocInstance(0x398);
    *(int *)(obj + 0x384) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov213_ConstructThirdForm;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
