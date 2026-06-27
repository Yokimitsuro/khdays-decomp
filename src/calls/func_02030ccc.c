extern void func_02030cf8(int a, void (*b)(void));
extern void func_02030b58(void);

struct Foo02030ccc {
    char _0[0x60];
    unsigned short arr[4];
};

extern struct Foo02030ccc *data_0204c22c;

void func_02030ccc(void)
{
    struct Foo02030ccc *p = data_0204c22c;
    int i;
    for (i = 0; i < 4; i++) {
        p->arr[i] = 0;
    }
    func_02030cf8(11, func_02030b58);
}
