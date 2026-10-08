/* Interworking tail-call veneer (`ldr ip,[pc] ; bx ip`): forwards to Ov105_WH_StateInSetMPData: WH_SendData (wh.c). */
extern void *Ov105_WH_StateInSetMPData();

void *Ov105_WH_SendData(void *data, int dataSize, int callback) {
    return Ov105_WH_StateInSetMPData(data, dataSize, callback);
}
