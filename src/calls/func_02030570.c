extern void *func_02023c00(void);
extern int func_02030670(void);
extern int func_02030694(void);
extern int func_020306b4(void);
extern int OS_IsTickAvailable_0x01ff8138(void);
extern void func_020303d8(void);

typedef struct {
    char _00[0x20];
    unsigned short h20;
    char _22[0x2c - 0x22];
    unsigned short bit0 : 1;
    unsigned short rest : 15;
} Obj02030570;

int func_02030570(void)
{
    Obj02030570 *obj = (Obj02030570 *)func_02023c00();
    int flag = 0;

    if (func_02030670() != 0 && func_02030694() != 0) {
        if (obj->h20 != OS_IsTickAvailable_0x01ff8138())
            flag = 1;
    }
    if (func_020306b4() != 0)
        flag = 1;

    if (flag != 0 && obj->bit0 == 0)
        func_020303d8();

    return 0;
}
