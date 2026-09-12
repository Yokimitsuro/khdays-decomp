/* Per-frame command dispatcher for the object anchored at data_0204c234, plus the tail
 * maintenance pass over its "active" SlotLink list (base+0xb46e8): each node is either
 * kept spatialised (func_02032af0) or unlinked (func_02032a7c) depending on
 * func_0201a090's verdict on the node's index field, then func_02019bf0() runs.
 *
 * The dispatcher itself is a phase byte at +0xb46fc (0..4) selecting one of four blocks,
 * each of which in turn switches on a queued command id at +0xb479e (0..5) with its
 * parameter byte at +0xb479f. Field names beyond that are honestly unknown: field_6f6/
 * field_6f8/field_6fa are short state slots read/written across the four phases, field_7a0
 * is a value forwarded into func_02032d6c/func_02019e9c and into the +0xb4700 countdown,
 * and +0xb44c4 is an opaque sub-object passed to several helpers.
 *
 * data_02042124 is a 48-byte slot-kind table living in .rodata (confirmed in
 * build/data_index.json), so the `const` on it is the honest declaration -- and it is also
 * load-bearing for codegen. Without it mwcc cannot prove the table cannot alias the stores
 * made through `base` (a plain char *), and the four temporaries in the cmdId==5 /
 * target>=0 block (table address, loaded kind, the 0xb46f6 offset, the -1 constant) colour
 * differently: the -1 takes r1 and the kind is pushed out to ip. With const, the kind lands
 * in r1 and the -1 in lr, as in the ROM. Nothing else in this function is sensitive to it. */
extern char *data_0204c234;
extern void func_02032870(void);
extern void func_02032c40(void);
extern void func_02032d10(unsigned int param_1);
extern void func_02032d6c(int arg);
extern void func_02019e9c(void *ptr, int arg);
extern int func_0201a238(int *param_1, int param_2, short *param_3);
extern int *func_02032cbc(int i);
extern int func_0201c5c0(void *ptr, int arg);
extern int func_0201a284(void *obj, int a, int b);
extern void func_0201a124(void *obj, int param_1, int param_2);
extern int func_0201a090(int index);
extern void func_02032a7c(void *ptr);
extern void func_02032af0(int param_1);
extern void func_02019bf0(void);
extern const unsigned char data_02042124[48];

typedef struct SlotLink {
    struct SlotLink *next;
    struct SlotLink *prev;
} SlotLink;

void func_02032f5c(void)
{
    char *base = data_0204c234;

    func_02032870();

    switch (*(unsigned char *)(base + 0xb46fc)) {
    case 0:
        if (*(unsigned char *)(base + 0xb47b3) != 0) {
            func_02032c40();
            switch (*(unsigned char *)(base + 0xb479e)) {
            case 1:
            case 2:
            case 4:
            case 5:
                *(short *)(base + 0xb46f8) = -1;
                if (*(unsigned char *)(base + 0xb479e) != 1) {
                    *(unsigned char *)(base + 0xb479e) = 2;
                }
                func_02032d10(*(unsigned char *)(base + 0xb479f));
                break;
            case 0:
            case 3:
            default:
                *(unsigned char *)(base + 0xb479e) = 0;
                break;
            }
        }
        break;

    case 3:
        if (*(unsigned char *)(base + 0xb47b3) != 0) {
            short target = *(short *)(base + 0xb46f6);
            unsigned char cmdId;
            unsigned char param;
            int targetKind;

            func_02032c40();
            cmdId = *(unsigned char *)(base + 0xb479e);
            param = *(unsigned char *)(base + 0xb479f);

            switch (cmdId) {
            case 0:
                break;
            case 1:
            case 2:
                *(short *)(base + 0xb46f8) = -1;
                func_02032d10(param);
                break;
            case 3:
                *(short *)(base + 0xb46f8) = -1;
                func_02032d6c(*(unsigned short *)(base + 0xb47a0));
                break;
            case 4:
                *(short *)(base + 0xb46f8) = -1;
                if (target == param) {
                    break;
                }
                if (target >= 0) {
                    *(short *)(base + 0xb46f6) = -1;
                    func_02019e9c(base + 0xb44c4, *(unsigned short *)(base + 0xb47a0));
                    *(int *)(base + 0xb4700) = *(unsigned short *)(base + 0xb47a0);
                    *(unsigned char *)(base + 0xb46fc) = 4;
                } else {
                    func_02032d10(param);
                }
                break;
            case 5:
                if (target == param) {
                    break;
                }
                if (target >= 0) {
                    targetKind = data_02042124[target];
                    *(short *)(base + 0xb46f6) = -1;
                    if (targetKind == 1 && data_02042124[param] == 2) {
                        *(short *)(base + 0xb46f8) = target;
                        *(unsigned char *)(base + 0xb479e) = 4;
                        func_0201a238((int *)(base + 0xb44c4), 0, (short *)(base + 0xb46fa));
                    } else if (!(*(short *)(base + 0xb46f8) >= 0 &&
                                 *(short *)(base + 0xb46f8) == param &&
                                 data_02042124[param] == 1)) {
                        *(short *)(base + 0xb46f8) = -1;
                        *(unsigned char *)(base + 0xb479e) = 4;
                    }
                    func_02019e9c(base + 0xb44c4, *(unsigned short *)(base + 0xb47a0));
                    *(int *)(base + 0xb4700) = *(unsigned short *)(base + 0xb47a0);
                    *(unsigned char *)(base + 0xb46fc) = 4;
                } else {
                    *(short *)(base + 0xb46f8) = -1;
                    *(unsigned char *)(base + 0xb479e) = 4;
                    func_02032d10(param);
                }
                break;
            }
        }
        break;

    case 2:
        switch (*(unsigned char *)(base + 0xb479e)) {
        case 0:
            func_02032c40();
            break;
        case 1: {
            if (func_02032cbc(0) == 0) {
                break;
            }
            func_02032c40();
            {
                unsigned char cmdId = *(unsigned char *)(base + 0xb479e);
                if (cmdId == 2 || cmdId == 4) {
                    unsigned char param = *(unsigned char *)(base + 0xb479f);
                    if (*(short *)(base + 0xb46f6) != param) {
                        func_02032d10(param);
                        break;
                    }
                }
                if (cmdId == 3) {
                    *(short *)(base + 0xb46f8) = -1;
                    func_02032d6c(*(unsigned short *)(base + 0xb47a0));
                }
            }
            break;
        }
        case 2:
        case 4:
            func_0201c5c0(base + 0xb44c4, *(short *)(base + 0xb46f6));
            func_0201a284(base + 0xb44c4, 0, 0);
            func_0201a124(base + 0xb44c4, *(unsigned char *)(base + 0xb46fd), 0);
            *(unsigned char *)(base + 0xb479e) = 0;
            *(unsigned char *)(base + 0xb46fc) = 3;
            break;
        case 3:
            break;
        case 5:
            func_0201c5c0(base + 0xb44c4, *(short *)(base + 0xb46f6));
            func_0201a284(base + 0xb44c4, 0, *(short *)(base + 0xb46fa));
            func_0201a124(base + 0xb44c4, *(unsigned char *)(base + 0xb46fd), 0x14);
            *(unsigned char *)(base + 0xb479e) = 0;
            *(unsigned char *)(base + 0xb46fc) = 3;
            break;
        }
        break;

    case 4: {
        int timer = *(int *)(base + 0xb4700);
        if (timer > 0) {
            *(int *)(base + 0xb4700) = timer - 1;
        }
        if (*(int *)(base + 0xb4700) != 0) {
            break;
        }
        {
            switch (*(unsigned char *)(base + 0xb479e)) {
            case 4:
            case 5:
                func_02032d10(*(unsigned char *)(base + 0xb479f));
                break;
            default:
                *(unsigned char *)(base + 0xb479e) = 0;
                *(unsigned char *)(base + 0xb46fc) = 0;
                break;
            }
        }
        break;
    }
    }

    {
        SlotLink *node = *(SlotLink **)(base + 0xb46e8);
        while (node != 0) {
            short idx = *(short *)((char *)node + 0x16);
            SlotLink *next = node->next;
            if (func_0201a090(idx) == 0) {
                func_02032a7c(node);
            } else {
                func_02032af0((int)node);
            }
            node = next;
        }
    }
    func_02019bf0();
}
