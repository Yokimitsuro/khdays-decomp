extern int OS_SPrintf(char *buf, char *fmt, int a, int b);
extern int func_0201ef9c(void *arg0, int arg1);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2cd8;
extern int data_02042a70;

typedef struct { int w[13]; } Ov022Rec;

typedef struct {
    char pad0000[0xc];
    int index0c;
    char pad0010[0x2678];
    Ov022Rec record2688;
} Ov022Context;

void func_ov022_02096e44(Ov022Context *arg0) {
    char buf[128];
    int x;
    OS_SPrintf(buf, (char *)&data_ov022_020b2cd8,
               ((int *)&data_02042a70)[arg0->index0c],
               arg0->index0c * 4);
    x = func_0201ef9c(buf, 6);
    arg0->record2688 = ((Ov022Rec *)x)[arg0->index0c];
    NNSi_FndFreeFromDefaultHeap(x);
}
