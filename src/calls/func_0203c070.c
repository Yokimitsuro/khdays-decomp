/* Per-frame update of a model node and its children (+0x88 list): after the base update
 * (func_0203c904) a node whose bit 2 (+0x5c) is set drops its +0x70 animation id; otherwise a
 * changed id (+0x70 vs the +0xb0 copy) is pushed to every child. Each child is then updated in
 * turn (func_0203c7ac). */
typedef unsigned short u16;
typedef struct { int b0 : 1; int b1 : 1; int b2 : 1; } NodeFlags;

extern void func_0203c904(char *node, int arg);
extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void func_0203c7ac(int child, int arg);

void func_0203c070(char *node, int arg)
{
    int *it;

    func_0203c904(node, arg);
    if (!((NodeFlags *)(node + 0x5c))->b2) {
        if (*(u16 *)(node + 0xb0) != *(u16 *)(node + 0x70)) {
            *(u16 *)(node + 0xb0) = *(u16 *)(node + 0x70);
            for (it = func_01fffd70(node + 0x88); it != 0; it = func_01fffd8c(node + 0x88)) {
                *(u16 *)(*it + 0x70) = *(u16 *)(node + 0x70);
            }
        }
    } else {
        *(u16 *)(node + 0x70) = 0;
    }
    for (it = func_01fffd70(node + 0x88); it != 0; it = func_01fffd8c(node + 0x88)) {
        func_0203c7ac(*it, arg);
    }
}
