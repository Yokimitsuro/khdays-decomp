/* Creates a child actor (enemy 0x73) owned by the object. */

extern int CallocInstance();
extern void Ov107_AiState_Init();
extern void Ov299_Construct();

int Ov299_AllocInitObject3ac(int this_) {
    int obj = CallocInstance(0x3ac);
    *(int *)(obj + 0x390) = this_;
    *(unsigned char *)(obj + 0x19c) = 0x73;
    *(int *)(obj + 0x18c) = (int)&Ov299_Construct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
