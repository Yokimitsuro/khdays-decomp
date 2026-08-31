/* Resolve a result resource's row buffer and optionally report its slot index. */
typedef struct Ov005ResultContext { char unknown00[0x4b64]; void *rowBuffers[4]; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern int func_ov005_02057048(int);
void *func_ov005_0205708c(int resourceId, int *outIndex) {
    int bufferIndex = func_ov005_02057048(resourceId);
    void *buffer = 0;
    if (bufferIndex != -1) buffer = data_ov005_0205b810->rowBuffers[bufferIndex];
    if (outIndex) *outIndex = bufferIndex;
    return buffer;
}
