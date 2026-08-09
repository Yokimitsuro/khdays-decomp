typedef unsigned short u16;

extern void func_02010e38(int, int, int, int, int);
extern void func_02010f08(void);
extern void func_02010f7c(void);
extern void func_020110ec(void);

extern u16 data_02047360;
extern void (*data_020423ec)(void);
extern void (*data_020423f0)(void);

void func_02010e80(unsigned int selection, int installCallbacks)
{
    if (selection <= 2) {
        func_02010e38(4, 3, 2, 0, 1);
    } else {
        func_02010e38(4, 3, 0, 2, 1);
    }

    data_02047360 = selection;
    func_02010f08();

    if (installCallbacks) {
        data_020423ec = func_02010f7c;
        data_020423f0 = func_020110ec;
    }
}
