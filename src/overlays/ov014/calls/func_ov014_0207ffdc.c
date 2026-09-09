typedef struct {
    int nField00;
    int nField04;
    signed char bField08;
    char pad09;
    short nField0a;
    short nField0c;
    short nField0e;
    int nField10;
    int nField14;
    int nField18;
    unsigned char bField1c;
} Ov014Params;

extern void *func_ov002_020769b0(int headerSize, int entrySize, int count);
extern char *strncpy(char *dst, const char *src, unsigned int n);

extern void func_ov014_0207fa78(void);
extern void func_ov014_0207fa7c(void);
extern void func_ov014_0207faf4(void);
extern void func_ov014_0207fb88(void);
extern void func_ov014_0207fae4(void);
extern void func_ov014_0207fb04(void);
extern void func_ov014_0207fbf0(void);
extern void func_ov014_0207fcb0(void);
extern void func_ov014_0207fce8(void);
extern void func_ov014_0207fd24(void);
extern void func_ov014_0207fd2c(void);

void *func_ov014_0207ffdc(unsigned short id, Ov014Params *params) {
    char *self = (char *)func_ov002_020769b0(0x84, 0x1d4, id);

    strncpy(self + 0x58, (const char *)params->nField00, 0x10);
    *(int *)(self + 0x68) = params->nField04;
    *(signed char *)(self + 0x6c) = params->bField08;
    *(short *)(self + 0x6e) = params->nField0a;
    *(short *)(self + 0x70) = params->nField0c;
    *(short *)(self + 0x72) = params->nField0e;
    *(int *)(self + 0x74) = params->nField10;
    *(int *)(self + 0x78) = params->nField14;
    *(int *)(self + 0x7c) = params->nField18;
    *(unsigned char *)(self + 0x80) = params->bField1c;

    *(int *)(self + 0x00) = 0;
    *(void **)(self + 0x04) = (void *)&func_ov014_0207fa78;
    *(void **)(self + 0x08) = (void *)&func_ov014_0207fa7c;
    *(void **)(self + 0x0c) = (void *)&func_ov014_0207faf4;
    *(void **)(self + 0x10) = (void *)&func_ov014_0207fb88;
    *(void **)(self + 0x14) = (void *)&func_ov014_0207fae4;
    *(void **)(self + 0x18) = (void *)&func_ov014_0207fb04;
    *(void **)(self + 0x1c) = (void *)&func_ov014_0207fbf0;
    *(int *)(self + 0x20) = 0;
    *(void **)(self + 0x24) = (void *)&func_ov014_0207fcb0;
    *(void **)(self + 0x28) = (void *)&func_ov014_0207fce8;
    *(void **)(self + 0x2c) = (void *)&func_ov014_0207fd24;
    *(int *)(self + 0x38) = 0;
    *(int *)(self + 0x44) = 0;
    *(void **)(self + 0x3c) = (void *)&func_ov014_0207fd2c;
    *(unsigned short *)(self + 0x4c) = 7;

    return self;
}
