/* Sub-state dispatcher of the ov241 enemy (x2: ov241/242). In sub-states 2/3/4 the +0x30 target
 * is refreshed by the target finder (020d3ee0). A target whose +0x1b4 kind has flag bit 16 set
 * is handed to the actor's +0x3b8 target hook; otherwise its +0x18c item is activated (ad838)
 * and sub-state 6 is requested. A pending +0x1c7 request then becomes the +0x1c6 sub-state:
 * bits 1/2/3/6/7 of the +0x60 high byte, bit 0 of +0x1ae and bit 1 of the three +0x38c parts'
 * +0x5c clear, slot 1 takes the sub-state's entry (020d439c, 020d4458, 020d447c, 020d4670;
 * 4/5 keep it; 6: 020d4848) and the request is cleared. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Ov242Actor { char pad[0x38c]; int *parts[3]; };

extern int func_ov242_020d3ee0(int *node);
extern long long *func_01fffde0(int kind);
extern void func_ov242_020d439c(void);
extern void func_ov242_020d4458(void);
extern void func_ov242_020d447c(void);
extern void func_ov242_020d4670(void);
extern void func_ov242_020d4848(void);
extern void func_ov022_020ad838(int item, int on);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov242_020d4154(int *node)
{
    int *state = (int *)node[1];
    int i;

    if (!(*(signed char *)(*state + 0x1c6) != 3 && *(signed char *)(*state + 0x1c6) != 2 &&
          *(signed char *)(*state + 0x1c6) != 4)) {
        state[0xc] = func_ov242_020d3ee0(node);
        if (state[0xc] != 0) {
            if ((*func_01fffde0(*(unsigned char *)(state[0xc] + 0x1b4)) & 0x10000) != 0) {
                /* the hook takes the target kind and the actor (r1 keeps the actor live) */
                if (*(void (**)(int, int))(*state + 0x3b8) != 0) {
                    (*(void (**)(int, int))(*state + 0x3b8))(*(unsigned char *)(state[0xc] + 0x1b4), *state);
                }
            } else {
                func_ov022_020ad838(*(int *)(state[0xc] + 0x18c), 1);
                *(unsigned char *)(*state + 0x1c7) = 6;
            }
        }
    }
    if (*(signed char *)(*state + 0x1c7) != -1) {
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        ((struct hw60 *)(*state + 0x60))->hi &= ~0xce;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        for (i = 0; i < 3; i++) {
            ((struct Ov242Actor *)*state)->parts[i][0x17] &= ~2;
        }
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov242_020d439c);
            break;
        case 1:
            func_0203c634(node, 1, func_ov242_020d4458);
            break;
        case 2:
            func_0203c634(node, 1, func_ov242_020d447c);
            break;
        case 3:
            func_0203c634(node, 1, func_ov242_020d4670);
            break;
        case 6:
            func_0203c634(node, 1, func_ov242_020d4848);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}
