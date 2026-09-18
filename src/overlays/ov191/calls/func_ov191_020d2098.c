/* Message handler of the ov191 enemy (x3: ov191/192/193): a "spawned" message (kind 5) starts
 * the first node slot's subitem (sub 0, weight 0x1000) or the second's (sub 1, weight 0x800)
 * through ov107::020c08cc with the packet's payload bytes and keeps the handle; the base handler
 * always runs. (Two-case switch; 020c08cc takes six arguments -- see func_ov120_020cc2a4.) */
extern void *func_ov107_020c08cc(void *taskList, void *subitem, int mode, int blend, int weight, void *payload);
extern void func_ov107_020c7500(int actor, unsigned char *msg, int param);

void func_ov191_020d2098(int actor, unsigned char *msg, int param)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            (*(void ***)(actor + 0x390))[1] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x390))[0], 0x17, 0, 0x1000, msg + 5);
            break;
        case 1:
            (*(void ***)(actor + 0x390))[3] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x390))[2], 0x17, 0, 0x800, msg + 5);
            break;
        }
    }
    func_ov107_020c7500(actor, msg, param);
}
