typedef struct Ov005Context {
    char opaque00[0x4be4];
    void *rowBuffers[3];
    char opaque4bf0[0x4c];
    unsigned char dirtyTextBuffers;
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern const int data_ov005_0205b340[3];
extern int GFXi_EnqueueCommand(int, int, const void *, unsigned int);
void func_ov005_02053e44(void) {
    int index;
    for (index=0; index<3; index++) {
        if (data_ov005_0205b80c->dirtyTextBuffers & (1 << index)) {
            GFXi_EnqueueCommand(data_ov005_0205b340[index], 0,
                data_ov005_0205b80c->rowBuffers[index], 0x600);
        }
    }
    data_ov005_0205b80c->dirtyTextBuffers=0;
}
