/* Allocate, link owner (+0x398), store arg (+0x390 byte), install callback (+0x18c), init, return. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov256_ShardInitTail(int);
int Ov256_Shard_New(int param_1, int param_2) {
    int obj = CallocInstance(0x39c);
    *(int *)(obj + 0x398) = param_1;
    *(signed char *)(obj + 0x390) = param_2;
    *(int *)(obj + 0x18c) = (int)&Ov256_ShardInitTail;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
