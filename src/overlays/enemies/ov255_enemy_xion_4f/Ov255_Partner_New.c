/* Allocate a 0x3d0-byte object, link it back to this owner (+0x384),
 * install the 020d187c callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov255_PartnerCtor(int);
int Ov255_Partner_New(int param_1) {
    int obj = CallocInstance(0x3d0);
    *(int *)(obj + 0x384) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov255_PartnerCtor;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
