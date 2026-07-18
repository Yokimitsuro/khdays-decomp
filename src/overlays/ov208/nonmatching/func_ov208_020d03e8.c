/*
 * NON-MATCHING (VERY CLOSE -- 1 register). Size-exact (436B) and byte-exact EXCEPT the scratch register
 * that holds the 3rd pack's first byte across the other two loads: mwcc 3.0/139 uses r7 (callee-saved),
 * the ROM uses ip -- because the ROM reserves r7 for the switch's `idx & 0xff` and gives the pack byte
 * ip. A global allocation interaction between the last byte-pack and the case-1/4/5 idx; not steerable
 * by pack-store ordering. ★ This function VALIDATES the 24-bit byte-pack crack (struct triple with a
 * garbage pad byte, read as signed int >>8; see codegen-cracks.md) -- the packs, the jump-table switch,
 * the byte-typed facing/idx args, and every spawn all match. A future session can nail the last register
 * (try forcing idx into ip, or reducing callee-saved pressure).
 */
/*
 * func_ov208_020d03e8 -- x3 (ov208/...). Message 5: decode a 3x3 orientation from the packet and spawn
 * the requested reaction node. Only acts on message kind 5. Build the identity basis (0203c960), decode
 * three 24-bit big-endian vectors from bytes 5..7, 8..10, 11..13 (sign-extended via the pad-byte pack),
 * apply them to the basis (0203ca30). Then dispatch on sub-kind msg[3]: 0 spawns the primary reaction
 * (020c09a0 into *(self+0x40c)[1] from self+0x3e0); 2/3 spawn the secondary (into [0x14] from self+0xa0,
 * facing bit from ==3); 1/4/5 spawn from slot 1/3/4 with the decoded basis (020c0794), and 5 also
 * kicks 020c0b14(self,1). Always forward the message (020c7500).
 */
struct triple { signed char pad; signed char x0, x1, x2; };

extern void func_0203c960(int *basis);
extern void func_0203ca30(int *basis, int *vec);
extern int func_ov107_020c09a0(int scene, int slot, int kind, int owner, unsigned char facing, int flag);
extern int func_ov107_020c0794(int scene, int slot, int kind, int flag, int *basis);
extern void func_ov107_020c0b14(int self, int a);
extern void func_ov107_020c7500(int self, unsigned char *msg, int arg);

void func_ov208_020d03e8(int self, unsigned char *msg, int arg) {
    if (msg[2] == 5) {
        int basis[11];
        int vec[3];
        struct triple t2, t1, t0;

        func_0203c960(basis);
        t0.x2 = msg[5]; t0.x1 = msg[6]; t0.x0 = msg[7]; vec[0] = *(int *)&t0 >> 8;
        t1.x2 = msg[8]; t1.x1 = msg[9]; t1.x0 = msg[10]; vec[1] = *(int *)&t1 >> 8;
        t2.x2 = msg[11]; t2.x1 = msg[12]; t2.x0 = msg[13]; vec[2] = *(int *)&t2 >> 8;
        func_0203ca30(basis, vec);
        switch (msg[3]) {
        case 0: {
            int r = func_ov107_020c09a0(*(int *)(self + 0x3c), **(int **)(self + 0x40c), 0x17,
                                        self + 0x3e0, 3, 0);
            *(int *)(*(int *)(self + 0x40c) + 4) = r;
            break;
        }
        case 2:
        case 3: {
            int r = func_ov107_020c09a0(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x40c) + 0x10),
                                        0x17, self + 0xa0, msg[3] == 3, 0);
            *(int *)(*(int *)(self + 0x40c) + 0x14) = r;
            break;
        }
        case 1:
        case 4:
        case 5: {
            unsigned char idx = (msg[3] == 1) ? 1 : (msg[3] == 4) ? 3 : 4;
            int r = func_ov107_020c0794(*(int *)(self + 0x3c),
                                        *(int *)(*(int *)(self + 0x40c) + idx * 8), 0x17, 0, basis);
            *(int *)(*(int *)(self + 0x40c) + idx * 8 + 4) = r;
            if (msg[3] == 5) {
                func_ov107_020c0b14(self, 1);
            }
            break;
        }
        default:
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
