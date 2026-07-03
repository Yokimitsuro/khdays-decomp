extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov132_020ced4c(void);
extern void func_ov132_020cedf0(void);
extern void func_ov132_020cefe0(void);
extern void func_ov132_020cf0b0(void);
extern void func_ov132_020cf330(void);
extern void func_ov132_020cf5a0(void);
extern void func_ov132_020cf68c(void);
extern void func_ov132_020cfd0c(void);
extern void func_ov132_020cff08(void);
extern void func_ov132_020d0814(void);
extern void func_ov132_020d08dc(void);

struct node60 { unsigned short lo : 8, hi : 8; };
struct flagbyte { unsigned int b : 8; };

void func_ov132_020ceab0(int *node)
{
    int *state = (int *)node[1];
    int *obj = (int *)*state;

    if ((signed char)*((char *)obj + 0x100 + 0xc7) != -1) {
        ((struct node60 *)((char *)obj + 0x60))->hi &= ~0xce;

        *(unsigned short *)((char *)*(int *)state + 0x100 + 0xae) &= ~1;

        ((struct flagbyte *)((char *)*(int *)((char *)*(int *)state + 0x388) + 8))->b |= 1;

        {
            int *o = (int *)*state;
            *((signed char *)o + 0x1c6) = (signed char)*((char *)o + 0x100 + 0xc7);
        }

        switch ((signed char)*((char *)*(int *)state + 0x100 + 0xc6)) {
        case 0:
            func_0203c634(node, 1, func_ov132_020ced4c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov132_020cedf0);
            break;
        case 2:
            func_0203c634(node, 1, func_ov132_020cefe0);
            break;
        case 4:
            func_0203c634(node, 1, func_ov132_020cf0b0);
            break;
        case 9:
            func_0203c634(node, 1, func_ov132_020cf330);
            break;
        case 5:
            func_0203c634(node, 1, func_ov132_020cf5a0);
            break;
        case 6:
            func_0203c634(node, 1, func_ov132_020cf68c);
            break;
        case 7:
            func_0203c634(node, 1, func_ov132_020cfd0c);
            break;
        case 8:
            func_0203c634(node, 1, func_ov132_020cff08);
            break;
        case 3:
            func_0203c634(node, 1, func_ov132_020d0814);
            break;
        case 10:
            func_0203c634(node, 1, func_ov132_020d08dc);
            break;
        }
    }

    *((signed char *)*(int *)state + 0x1c7) = -1;
}
