extern void func_02010b48(int heap);
extern void func_02010b5c(int heap);

void func_02010c00(int heap, int flags)
{
    if (flags & 1) func_02010b48(heap);
    if (flags & 2) func_02010b5c(heap);
}
