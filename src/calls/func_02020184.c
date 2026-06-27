extern void OS_FreeToHeap(int heap, int handle, void *ptr);

void func_02020184(void *ptr)
{
    OS_FreeToHeap(0, -1, ptr);
}
