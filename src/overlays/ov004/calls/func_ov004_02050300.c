typedef void (*Ov004StateHandler)(void);

typedef struct Ov004StateHandlerTable {
    Ov004StateHandler handlers[5];
} Ov004StateHandlerTable;

extern const Ov004StateHandlerTable data_ov004_020510b8;
extern char *data_ov004_02051384;

extern void func_ov004_020504c4(void);
extern void func_ov004_02050a04(void);
extern void func_ov004_02050400(void);
extern void func_ov004_02050488(void);
extern void func_ov004_02050398(void);
extern void func_ov004_02050934(void);

int func_ov004_02050300(void) {
    Ov004StateHandlerTable table;
    int state;

    table = data_ov004_020510b8;
    table.handlers[*(int *)(data_ov004_02051384 + 0xaf8)]();
    func_ov004_020504c4();

    state = *(int *)(data_ov004_02051384 + 0xaf8);
    switch (state) {
    case 1:
        if (*(int *)(data_ov004_02051384 + 0x5584) == 0) {
            break;
        }
    case 2:
    case 3:
        func_ov004_02050a04();
        func_ov004_02050400();
        func_ov004_02050488();
        break;
    }

    func_ov004_02050398();
    func_ov004_02050934();
    return 0;
}

