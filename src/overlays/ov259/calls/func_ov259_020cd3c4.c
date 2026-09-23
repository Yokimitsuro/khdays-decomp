/* Play an ov259 actor sound: bank 0x172 normally; with the +0x428 alternate voice set, variants
 * 0-0x17 play from bank 0x17d instead and any other variant is dropped. `id` is ignored (callers
 * always pass 0x172). */
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);

void func_ov259_020cd3c4(int actor, int id, int variant, void *at)
{
    if (*(int *)(actor + 0x428) != 0) {
        switch (variant) {
        case 0x0:
            variant = 0x0;
            break;
        case 0x1:
            variant = 0x1;
            break;
        case 0x2:
            variant = 0x2;
            break;
        case 0x3:
            variant = 0x3;
            break;
        case 0x4:
            variant = 0x4;
            break;
        case 0x5:
            variant = 0x5;
            break;
        case 0x6:
            variant = 0x6;
            break;
        case 0x7:
            variant = 0x7;
            break;
        case 0x11:
            variant = 0x11;
            break;
        case 0x12:
            variant = 0x12;
            break;
        case 0x13:
            variant = 0x13;
            break;
        case 0x14:
            variant = 0x14;
            break;
        case 0x15:
            variant = 0x15;
            break;
        case 0x16:
            variant = 0x16;
            break;
        case 0x17:
            variant = 0x17;
            break;
        case 0x8:
            variant = 0x8;
            break;
        case 0x9:
            variant = 0x9;
            break;
        case 0xa:
            variant = 0xa;
            break;
        case 0xb:
            variant = 0xb;
            break;
        case 0xc:
            variant = 0xc;
            break;
        case 0xd:
            variant = 0xd;
            break;
        case 0xe:
            variant = 0xe;
            break;
        case 0xf:
            variant = 0xf;
            break;
        case 0x10:
            variant = 0x10;
            break;
        default:
            return;
        }
        func_ov107_020c5af8(actor, 0x17d, variant, at);
        return;
    }
    func_ov107_020c5af8(actor, 0x172, variant, at);
}
