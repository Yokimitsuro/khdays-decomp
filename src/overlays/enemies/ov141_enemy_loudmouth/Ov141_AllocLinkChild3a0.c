/* Allocates a sub-object linked to this object (+0x398), installs its initialiser as the state
 * callback and hands it to the shared enemy framework. */

extern int CallocInstance();
extern void Ov107_AiState_Init();
extern void Ov141_InitializeSubObject();

int Ov141_AllocLinkChild3a0(int this_) {
    int obj = CallocInstance(0x3a0);
    *(int *)(obj + 0x398) = this_;
    *(int *)(obj + 0x18c) = (int)&Ov141_InitializeSubObject;
    Ov107_AiState_Init(obj, 0, (int)&Ov141_InitializeSubObject);
    return obj;
}
