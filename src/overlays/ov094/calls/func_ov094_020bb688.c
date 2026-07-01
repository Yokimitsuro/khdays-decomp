extern int func_0202aa9c();

struct vec3 { int a, b, c; };

void func_ov094_020bb688(char *a0, char *a1)
{
    struct vec3 tmp;
    if (*(int *)a1 != 2)
        return;
    tmp = *(struct vec3 *)(a0 + 0x48c);
    *(unsigned short *)(a1 + 0x80) =
        (unsigned short)(*(unsigned short *)(*(char **)(a0 + 0x20) + 0x80) - 0x8000) + 0x8000;
    *(unsigned short *)(a1 + 4) |= 0x20;
    *(struct vec3 *)(a1 + 0xa8) = tmp;
    func_0202aa9c(a1 + 4);
}
