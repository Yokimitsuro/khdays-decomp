extern void NNS_FndInitList(void *list, unsigned int offset);
extern void NNS_FndAppendListObject(void *list, void *object);

extern char data_0204a314[];
extern char data_0204a308[];
extern char data_0204a320[];
extern char data_0204a760[];

void func_0201a2ac(void)
{
    int i;
    char *p;
    char *q;

    NNS_FndInitList(data_0204a314, 0x14);
    NNS_FndInitList(data_0204a308, 0x14);

    p = data_0204a320;
    for (i = 0; i < 16; i++) {
        *(unsigned char *)(p + 0x2c) = 0;
        *(unsigned char *)(p + 0x3c) = (unsigned char)i;
        NNS_FndAppendListObject(data_0204a308, p);
        p += 0x44;
    }

    q = data_0204a760;
    for (i = 0; i < 32; i++) {
        NNS_FndInitList(q, 0xc);
        NNS_FndInitList(q + 0xc, 0);
        *(unsigned char *)(q + 0x20) = 0x7f;
        *(int *)(q + 0x18) = 1;
        *(int *)(q + 0x1c) = 0;
        q += 0x24;
    }
}
