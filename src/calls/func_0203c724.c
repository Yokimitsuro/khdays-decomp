extern void func_0203c960(void *o);
extern void func_0203c900(void);
extern void func_0203c8fc(void);
extern void func_0203c904(int *ptr);
extern int data_0204caa8;

typedef struct {
    int x0;
    char _4[0x58];
    unsigned int flags;
    unsigned char x60;
    char _61[3];
    void (*x64)(void);
    void (*x68)(int *);
    void (*x6c)(void);
    short x70;
    char _72[2];
    int x74;
    int x78;
    int x7c;
    int x80;
    int x84;
} S;

void func_0203c724(S *p)
{
    p->flags &= ~1u;
    p->flags &= ~2u;
    p->x0 = 0;
    p->x60 = 0;
    p->x70 = 0;
    p->x64 = func_0203c900;
    p->x6c = func_0203c8fc;
    p->x74 = 0;
    p->x78 = 0;
    p->x84 = 0;
    p->x68 = func_0203c904;
    p->x7c = 0;
    p->x80 = 0;
    func_0203c960((char *)p + 4);
    func_0203c960((char *)p + 0x30);
    data_0204caa8++;
}
