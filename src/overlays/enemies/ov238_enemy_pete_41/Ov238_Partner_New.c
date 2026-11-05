/* Allocate a 0x3ac-byte object, link it back to this owner (+0x398),
 * install the 020d2674 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov238_Partner_Build(int);
int Ov238_Partner_New(int param_1) {
    int obj = CallocInstance(0x3ac);
    *(int *)(obj + 0x398) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov238_Partner_Build;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
