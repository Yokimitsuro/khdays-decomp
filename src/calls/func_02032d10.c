extern void func_0201b8e4(void *node);
extern void func_0201f70c(unsigned int a, void *node, void *dst);
extern char *data_0204c234;

void func_02032d10(unsigned int param_1)
{
    char *base = data_0204c234;

    *(unsigned char *)(base + 0xb46fc) = 1;
    *(unsigned short *)(base + 0xb46f6) = param_1;
    func_0201b8e4(*(void **)(base + 0xb04b4));
    func_0201f70c((unsigned short)param_1, *(void **)(base + 0xb04b4), base + 0xb46fc);
}
