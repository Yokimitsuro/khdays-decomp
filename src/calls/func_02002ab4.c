#pragma opt_level 1
extern unsigned int OS_GetConsoleType(void);
extern unsigned int *data_02044588;

unsigned int func_02002ab4(unsigned int idx) {
    switch (idx) {
    case 0:
        return 0x020d73e0;
    case 2:
        if (((unsigned int *)&data_02044588)[1] == 0 || (OS_GetConsoleType() & 3) == 1) {
            return 0;
        }
        return 0x023e0000;
    case 3:
        return 0x01fffee0;
    case 4:
        return 0x027e0e60;
    case 5:
        return 0x027ff000;
    case 6:
        return 0x037f8000;
    default:
        return 0;
    }
}
