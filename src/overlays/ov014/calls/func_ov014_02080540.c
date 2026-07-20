/* Instantiate the ov014 object: allocate class 0x70 (0x138 bytes) on the given
 * owner, copy the descriptor's 0x10-byte name into +0x58, carry its two extra
 * words to +0x68/+0x6c, then fill the handler table at +0x8..+0x2c and +0x3c
 * with this overlay's entry points and set the type tag at +0x4c to 0x12. */
extern void *func_ov002_020769b0(int cls, int size, int owner);
extern char *strncpy(char *dst, const char *src, unsigned int n);

extern void func_ov014_02080230(void);
extern void func_ov014_02080264(void);
extern void func_ov014_02080340(void);
extern void func_ov014_02080244(void);
extern void func_ov014_02080268(void);
extern void func_ov014_020803c0(void);
extern void func_ov014_02080430(void);
extern void func_ov014_02080444(void);
extern void func_ov014_02080458(void);
extern void func_ov014_02080460(void);

void *func_ov014_02080540(int owner, int *desc) {
    char *self = (char *)func_ov002_020769b0(0x70, 0x70 + 0xc8, owner);

    strncpy(self + 0x58, (const char *)desc[0], 0x10);
    *(int *)(self + 0x68) = desc[1];
    *(int *)(self + 0x6c) = desc[2];

    *(int *)(self + 0x00) = 0;
    *(int *)(self + 0x04) = 0;
    *(void **)(self + 0x08) = (void *)&func_ov014_02080230;
    *(void **)(self + 0x0c) = (void *)&func_ov014_02080264;
    *(void **)(self + 0x10) = (void *)&func_ov014_02080340;
    *(void **)(self + 0x14) = (void *)&func_ov014_02080244;
    *(void **)(self + 0x18) = (void *)&func_ov014_02080268;
    *(int *)(self + 0x1c) = 0;
    *(void **)(self + 0x20) = (void *)&func_ov014_020803c0;
    *(void **)(self + 0x24) = (void *)&func_ov014_02080430;
    *(void **)(self + 0x28) = (void *)&func_ov014_02080444;
    *(void **)(self + 0x2c) = (void *)&func_ov014_02080458;
    *(int *)(self + 0x38) = 0;
    *(int *)(self + 0x44) = 0;
    *(void **)(self + 0x3c) = (void *)&func_ov014_02080460;
    *(unsigned short *)(self + 0x4c) = 0x12;

    return self;
}
