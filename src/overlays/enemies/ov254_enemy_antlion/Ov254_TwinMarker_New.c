/* Allocate the 0x390-byte sub-actor, back-link the owner at +0x38c, install its update
 * handler at +0x18c, run the ov107 setup and return it. */
extern int CallocInstance(int size);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov254_TwinMarkerConstruct(void);
int Ov254_TwinMarker_New(int param_1) {
    int obj = CallocInstance(0x390);
    *(int *)(obj + 0x38c) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov254_TwinMarkerConstruct;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
