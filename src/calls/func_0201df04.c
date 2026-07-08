extern int func_0201b7e0();
extern void func_0201df84();
extern void func_0201dff8();
extern void func_0201e008();
extern void func_0201e040();
extern void func_0201e050();
extern void func_0201e078();
extern void func_0201e07c();
extern void func_0201e098();
void func_0201df04(int param_1, unsigned int param_2)
{
    if (func_0201b7e0(param_2) == 0) {
        *(void **)(param_1 + 0x164) = (void *)func_0201df84;
        *(void **)(param_1 + 0x168) = (void *)func_0201dff8;
        *(void **)(param_1 + 0x16c) = (void *)func_0201e008;
        *(void **)(param_1 + 0x170) = (void *)func_0201e040;
        return;
    }
    *(void **)(param_1 + 0x164) = (void *)func_0201e050;
    *(void **)(param_1 + 0x168) = (void *)func_0201e078;
    *(void **)(param_1 + 0x16c) = (void *)func_0201e07c;
    *(void **)(param_1 + 0x170) = (void *)func_0201e098;
}
