typedef int (*fn)();

int func_02010dec(fn **p, int a) {
    return (*p)[1]((int)p, a);
}
