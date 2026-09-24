/* Dispatches a command through the eight-entry handler table data_02041e4c: the handler gets the
 * value looked up for the command's pair (func_020241b0 over data_02041e14), whether the command's
 * third halfword is set, and the two extra arguments. Sibling of func_0202489c. */
extern int func_020241b0(void *ptr, unsigned short arg1, unsigned short arg2);
extern void (*const data_02041e4c[])(int value, int flag, int arg1, int arg2);
extern char data_02041e14;

enum { FLAG_CLEAR = 0, FLAG_SET = 1 };

void func_02024844(int index, unsigned short *args, int arg1, int arg2)
{
    int flag = args[2] == 0 ? FLAG_CLEAR : FLAG_SET;
    int value = func_020241b0(&data_02041e14, args[0], args[1]);

    data_02041e4c[index](value, flag, arg1, arg2);
}
