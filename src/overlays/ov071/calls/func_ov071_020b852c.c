extern void func_0202accc();
extern void func_ov071_020b9568();
extern void func_ov022_020a384c();

void func_ov071_020b852c(void *this, int code)
{
    char *base = (char *)this + 0x2c2c;
    int flag = -1;
    switch (code) {
    case 0x2e:
        func_0202accc((char *)this + 0xf10, 1, (char *)this + 0xff0, 1);
        if (*(int *)((char *)this + 0x6bc) != code) {
            func_ov071_020b9568(this, base);
        }
        break;
    case 0x2f:
    case 0x33:
        if (code == 0x33) {
            *(int *)(base + 4) = 1;
            flag = 0x33;
        } else {
            *(int *)(base + 4) = 0;
        }
        code = 0x2f;
        break;
    case 0x31:
        *(int *)(base + 4) = 1;
        break;
    case 0x30:
        *(int *)(base + 4) = 0;
        break;
    }
    func_ov022_020a384c(this, code);
    if (flag >= 0) {
        *(int *)((char *)this + 0x6bc) = 0x33;
    }
}
