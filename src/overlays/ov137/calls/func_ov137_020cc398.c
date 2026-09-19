/* Message handler of the ov137 enemy. A "spawned" message (kind 5) dispatches on its slot byte
 * over the +0x390 pair table: 0 / 1 start pairs 0 (kind 0x15) and 7 (kind 5) at the +0x398
 * bone's transform and then effect 0x11d, mode 5 into +0x3a8 (slot 0) or mode 4 into +0x3a4
 * (slot 1), there; 2 starts pair 2 (kind 0x15) at the +0x394 bone's transform and 3 pair 3
 * (kind 0x15, c0794) there; 4 builds pair 4 through func_ov137_020cdec4 from pairs 6 and 5.
 * The base handler always runs. */
typedef unsigned char u8;
struct Ov137Pair { int pItem; int pChild; };

extern int func_ov107_020c09a0(int list, int parent, int kind, void *at, int a, int b);
extern int func_ov107_020c0794(int list, int parent, int kind, int a, void *at);
extern int func_ov107_020cb040(char *self, int id, int a3, int a4, void *xform);
extern int func_ov137_020cdec4(char *self, int item, int a, int b);
extern void func_ov107_020c7500(char *self, u8 *cmd, void *arg3);

void func_ov137_020cc398(char *self, u8 *cmd, void *arg3)
{
    if (cmd[2] == 5) {
        switch (cmd[3]) {
        case 0:
        case 1:
            (*(struct Ov137Pair **)(self + 0x390))[0].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov137Pair **)(self + 0x390))[0].pItem,
                                    0x15, *(char **)(self + 0x398) + 4, 0, 0);
            (*(struct Ov137Pair **)(self + 0x390))[7].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov137Pair **)(self + 0x390))[7].pItem,
                                    5, *(char **)(self + 0x398) + 4, 0, 0);
            if (cmd[3] == 0) {
                *(int *)(self + 0x3a8) = func_ov107_020cb040(self, 0x11d, 5, 0, *(char **)(self + 0x398) + 4);
            } else if (cmd[3] == 1) {
                *(int *)(self + 0x3a4) = func_ov107_020cb040(self, 0x11d, 4, 0, *(char **)(self + 0x398) + 4);
            }
            break;
        case 2:
            (*(struct Ov137Pair **)(self + 0x390))[2].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov137Pair **)(self + 0x390))[2].pItem,
                                    0x15, *(char **)(self + 0x394) + 4, 0, 0);
            break;
        case 3:
            (*(struct Ov137Pair **)(self + 0x390))[3].pChild =
                func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Ov137Pair **)(self + 0x390))[3].pItem,
                                    0x15, 0, *(char **)(self + 0x394) + 4);
            break;
        case 4:
            (*(struct Ov137Pair **)(self + 0x390))[4].pChild =
                func_ov137_020cdec4(self, (*(struct Ov137Pair **)(self + 0x390))[4].pItem,
                                    (*(struct Ov137Pair **)(self + 0x390))[6].pItem,
                                    (*(struct Ov137Pair **)(self + 0x390))[5].pItem);
            break;
        }
    }
    func_ov107_020c7500(self, cmd, arg3);
}
