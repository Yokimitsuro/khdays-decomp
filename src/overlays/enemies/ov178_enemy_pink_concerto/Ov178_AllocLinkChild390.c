/* Allocates a sub-object linked to this object (+0x388), installs its initialiser as the state
 * callback and hands it to the shared enemy framework. */

extern int CallocInstance();
extern void Ov107_AiState_Init();
extern void Ov178_Construct_2();

int Ov178_AllocLinkChild390(int this_) {
    int obj = CallocInstance(0x390);
    *(int *)(obj + 0x388) = this_;
    *(int *)(obj + 0x18c) = (int)&Ov178_Construct_2;
    Ov107_AiState_Init(obj, 0, (int)&Ov178_Construct_2);
    return obj;
}
