typedef unsigned int u32;

struct Foo {
    u32 _00;
    u32 _04;
    u32 _08;
    u32 arr[23];
    u32 _68;
    u32 _6c;
};

extern struct Foo *NNSi_FndGetCurrentRootHeap(void);
extern u32 CARD_GetResultCode_0x0203065c(void);
extern void func_020308a0(void);
extern void func_02030ccc(void);
extern void func_ov105_020bd59c(u32 a, void *b, u32 c);
extern void func_01fff9b8(void);
extern void func_01fffa04(void);
extern void func_02030a2c(void);

extern struct Foo *data_0204c22c;

void (*func_02030988(void))(void)
{
    struct Foo *p;
    u32 r;
    int i;

    p = NNSi_FndGetCurrentRootHeap();
    data_0204c22c = p;
    CARD_GetResultCode_0x0203065c();
    func_020308a0();
    p->_6c = 0;
    p->_68 = 0;
    for (i = 0; i < 20; i++) {
        p->arr[i] = 0;
    }
    func_02030ccc();
    r = CARD_GetResultCode_0x0203065c();
    switch (r) {
    case 2:
        func_ov105_020bd59c(12, func_01fff9b8, 0);
        break;
    case 3:
        func_ov105_020bd59c(12, func_01fffa04, 0);
        break;
    }
    p->_00 = 0;
    return func_02030a2c;
}
