extern int func_ov008_02063018(void *context, int index);

void func_ov008_0206311c(void *context, int index)
{
    do {
        index = (index + 1) % 8;
    } while (func_ov008_02063018(context, index) == 0);
}
