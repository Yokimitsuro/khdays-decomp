extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov164_020d0bb0(void);
extern void func_ov164_020d0c54(void);
extern void func_ov164_020d0e44(void);
extern void func_ov164_020d0f14(void);
extern void func_ov164_020d1194(void);
extern void func_ov164_020d1404(void);
extern void func_ov164_020d14f0(void);
extern void func_ov164_020d1b70(void);
extern void func_ov164_020d1e08(void);
extern void func_ov164_020d273c(void);
extern void func_ov164_020d27d8(void);

struct node60 { unsigned short lo : 8, hi : 8; };
struct flagbyte { unsigned int b : 8; };

void func_ov164_020d0914(int *node)
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
            func_0203c634(node, 1, func_ov164_020d0bb0);
            break;
        case 1:
            func_0203c634(node, 1, func_ov164_020d0c54);
            break;
        case 2:
            func_0203c634(node, 1, func_ov164_020d0e44);
            break;
        case 4:
            func_0203c634(node, 1, func_ov164_020d0f14);
            break;
        case 9:
            func_0203c634(node, 1, func_ov164_020d1194);
            break;
        case 5:
            func_0203c634(node, 1, func_ov164_020d1404);
            break;
        case 6:
            func_0203c634(node, 1, func_ov164_020d14f0);
            break;
        case 7:
            func_0203c634(node, 1, func_ov164_020d1b70);
            break;
        case 8:
            func_0203c634(node, 1, func_ov164_020d1e08);
            break;
        case 3:
            func_0203c634(node, 1, func_ov164_020d273c);
            break;
        case 10:
            func_0203c634(node, 1, func_ov164_020d27d8);
            break;
        }
    }

    *((signed char *)*(int *)state + 0x1c7) = -1;
}
