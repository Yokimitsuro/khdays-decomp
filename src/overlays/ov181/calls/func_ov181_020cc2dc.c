/* Message handler of the ov181 enemy (x4: ov181/182/183/184). A kind-0 message stores its +0x24
 * word into +0x394 (the item's Y scale), scales the +0x384 item's +4 placement to (1.0, that, 1.0) and clears the
 * subscriber's state; a "spawned" message (kind 5) starts the sub-item of the +0x398 set picked
 * by the sub-kind (0 -> entry 0, 1 -> entry 2, 2 -> entry 4) through ov107::020c08cc (mode 0x17,
 * weight 0x1000, the packet's payload) and keeps the handle in the following entry. The base
 * handler always runs. (020c08cc takes six arguments -- see func_ov120_020cc2a4.) */
extern void func_0203ca50(void *placement, int x, int y, int z);
extern void func_0203c7ac(int subscriber, int a);
extern void *func_ov107_020c08cc(void *taskList, void *subitem, int mode, int blend, int weight, void *payload);
extern void func_ov107_020c7500(int actor, unsigned char *msg, int param);

void func_ov181_020cc2dc(int actor, unsigned char *msg, int param)
{
    if (msg[2] == 0) {
        *(int *)(actor + 0x394) = *(int *)(msg + 0x24);
        func_0203ca50((void *)(*(int *)(actor + 0x384) + 4), 0x1000, *(int *)(actor + 0x394), 0x1000);
        func_0203c7ac(*(int *)(actor + 0x9c), 0);
    } else if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            (*(void ***)(actor + 0x398))[1] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x398))[0], 0x17, 0, 0x1000, msg + 5);
            break;
        case 2:
            (*(void ***)(actor + 0x398))[5] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x398))[4], 0x17, 0, 0x1000, msg + 5);
            break;
        case 1:
            (*(void ***)(actor + 0x398))[3] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x398))[2], 0x17, 0, 0x1000, msg + 5);
            break;
        }
    }
    func_ov107_020c7500(actor, msg, param);
}
