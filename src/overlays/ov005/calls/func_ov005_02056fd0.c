/* Transfer each dirty result row buffer, then clear the dirty mask. */
typedef struct Ov005ResultContext { char unknown00[0x4b64]; void *rowBuffers[4]; char unknown4b74[12]; unsigned char dirtyTextBuffers; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern const int data_ov005_0205b38c[4];
extern void GFXi_EnqueueCommand(int, int, void *, int);
void func_ov005_02056fd0(void) {
    int index;
    for (index = 0; index < 4; index++) {
        if (data_ov005_0205b810->dirtyTextBuffers & (1 << index)) {
            GFXi_EnqueueCommand(data_ov005_0205b38c[index], 0,
                data_ov005_0205b810->rowBuffers[index], 0x600);
        }
    }
    data_ov005_0205b810->dirtyTextBuffers = 0;
}
