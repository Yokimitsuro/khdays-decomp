/* Message handler (second rider): a "spawned" message (kind 5) with slot byte 0 starts the
 * +0x38c node's first subitem with weight msg[4] << 8; slot 1 starts its second and third
 * subitems at weight 1.0 (all kind 0x17 with the packet's payload bytes). The base handler
 * always runs. */
extern void *func_ov107_020c08cc(void *taskList, void *subitem, int mode, int blend, int weight, void *payload);
extern void func_ov107_020c7500(int actor, unsigned char *msg, int param);

void func_ov277_020d0e20(int actor, unsigned char *msg, int param)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            (*(void ***)(actor + 0x38c))[1] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x38c))[0], 0x17, 0, msg[4] << 8, msg + 5);
            break;
        case 1:
            (*(void ***)(actor + 0x38c))[3] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x38c))[2], 0x17, 0, 0x1000, msg + 5);
            (*(void ***)(actor + 0x38c))[5] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x38c))[4], 0x17, 0, 0x1000, msg + 5);
            break;
        }
    }
    func_ov107_020c7500(actor, msg, param);
}
