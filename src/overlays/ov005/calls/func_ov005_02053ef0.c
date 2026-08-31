typedef struct Ov005Context {char pad0[0x4be4];void *rowBuffers[3];} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern int func_ov005_02053ebc(int);
void *func_ov005_02053ef0(int entryId,int *outIndex) {
    int index=func_ov005_02053ebc(entryId);
    void *buffer=0;
    if(index!=-1)buffer=data_ov005_0205b80c->rowBuffers[index];
    if(outIndex)*outIndex=index;
    return buffer;
}
