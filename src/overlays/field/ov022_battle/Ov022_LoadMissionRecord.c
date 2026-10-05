/* Loads the per-mission record file named by the index (formatted path) and copies the object's
 * record out of it. */

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int Archive_LoadFile(void *arg0, int arg1);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int gOv022BaChCpPath;
extern int data_02042a70;

typedef struct { int w[13]; } Ov022Rec;

typedef struct {
    char pad0000[0xc];
    int index0c;
    char pad0010[0x2678];
    Ov022Rec record2688;
} Ov022Context;

void Ov022_LoadMissionRecord(Ov022Context *arg0) {
    char buf[128];
    int x;
    OS_SPrintf(buf, (char *)&gOv022BaChCpPath,
               ((int *)&data_02042a70)[arg0->index0c],
               arg0->index0c * 4);
    x = Archive_LoadFile(buf, 6);
    arg0->record2688 = ((Ov022Rec *)x)[arg0->index0c];
    NNSi_FndFreeFromDefaultHeap(x);
}
