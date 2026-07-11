/* ov003 display/MMIO setup (1568B). Faithful readable reconstruction from Ghidra +
 * pool map. main-engine regs 0x04000xxx, sub-engine 0x04001xxx held as pooled ptrs;
 * data_0204f9a0 is the heap-base global. Likely nonmatching (MMIO pointer-hold tie
 * class, same as ov010_0204cb3c) — kept as the readable C for the PC port. */
extern int data_0204f9a0;
extern char func_0202e9b8(unsigned int *p);
extern int func_ov003_0204cadc(int mode);
extern int func_020066a4(void);
extern void func_ov003_0204cb44(int a);
extern void func_02006bac(unsigned short *p, int a, int b);
extern void func_02006b90(unsigned int *p, int a, int b, unsigned int c, unsigned int d);
extern int func_02006810(void);
extern void func_02006128(int a);
extern void func_0202e4f4(int a, int b, void *c, void *d);
extern void func_02023cc0(void *p);

void func_ov003_0204cba0(void) {
    short sVar1;
    char cVar4;
    int iVar5;
    int iVar6;
    unsigned int uVar10;
    unsigned int *puVar9;
    unsigned int *puVar11;
    unsigned short *puVar8;
    volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;

    cVar4 = func_0202e9b8((unsigned int *)(data_0204f9a0 + 0x44));
    *(int *)(data_0204f9a0 + 0x54) = (int)cVar4;
    iVar5 = func_ov003_0204cadc(*(int *)(data_0204f9a0 + 0x3c));
    sVar1 = (short)(iVar5 << 3);
    if (*(int *)(data_0204f9a0 + 0x54) == 0) {
        iVar6 = func_02006810();
        func_ov003_0204cb44(iVar6);
        puVar11 = (unsigned int *)0x04000014;
        iVar6 = data_0204f9a0;
        if (*(int *)(iVar6 + 0x17ac) == 0) {
            *reg_dispcnt = *reg_dispcnt & 0xffffe0ff | 0x900;
            *(volatile unsigned int *)0x04000050 = 0;
        } else {
            if (*(int *)(iVar6 + 0x1e0c) < 1) {
                uVar10 = (unsigned int)(*(int *)(iVar6 + 0x17b4) / 2);
                *(unsigned int *)0x04000014 = 0x01ff0000 & *(int *)(iVar6 + 0x17b0) << 0x10;
                iVar5 = data_0204f9a0;
                if ((int)uVar10 < 0xf) {
                    *(unsigned short *)((int)puVar11 + 0x2e) = 0xff;
                    *(unsigned short *)((int)puVar11 + 0x32) = (short)*(int *)(iVar5 + 0x17b0) * -0x100 | 0xbf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & 0xc0ff | 0x3b00;
                    *(unsigned short *)(puVar11 + 0xb) = 0x10ff;
                    *(short *)(puVar11 + 0xc) = (short)0x0000afbf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & 0xffc0 | 0x33;
                    *(unsigned short *)((int)puVar11 + 0x36) = *(unsigned short *)((int)puVar11 + 0x36) & 0xffc0 | 0x19;
                    *reg_dispcnt = *reg_dispcnt & 0xffff1fff | 0x6000;
                    func_02006b90((unsigned int *)0x04000050, 2, 1, uVar10, 0xf - uVar10);
                } else {
                    uVar10 = *(unsigned int *)(iVar5 + 0x1e08);
                    *(unsigned short *)(puVar11 + 0xb) = 0xff;
                    *(unsigned short *)(puVar11 + 0xc) = 0xaf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & 0xffc0 | 0x3b;
                    *(unsigned short *)((int)puVar11 + 0x2e) = 0x10ff;
                    *(short *)((int)puVar11 + 0x32) = (short)0x0000afbf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & 0xc0ff | 0x3900;
                    *(unsigned short *)((int)puVar11 + 0x36) = *(unsigned short *)((int)puVar11 + 0x36) & 0xffc0 | 0x19;
                    *reg_dispcnt = *reg_dispcnt & 0xffff1fff | 0x6000;
                    if (uVar10 == 0xf) {
                        *(volatile unsigned int *)0x04000050 = 0;
                    } else {
                        func_02006b90((unsigned int *)0x04000050, 8, 3, uVar10, 0xf - uVar10);
                    }
                }
            } else {
                puVar11 = (unsigned int *)0x04000050;
                *(unsigned int *)0x04000014 = 0;
                func_02006bac((unsigned short *)puVar11, 2, *(int *)(data_0204f9a0 + 0x1e0c));
                puVar8 = (unsigned short *)0x04000040;
                *(unsigned short *)0x04000040 = (unsigned short)(iVar5 << 0xb) | sVar1 + 0x3fU & 0xff;
                puVar8[2] = 0x17;
                puVar8[4] = puVar8[4] & 0xffc0 | 0x23;
                puVar8[5] = puVar8[5] & 0xffc0 | 0xb;
                *reg_dispcnt = *reg_dispcnt & 0xffff1fff | 0x2000;
            }
            *reg_dispcnt = *reg_dispcnt & 0xffffe0ff | 0xb00;
        }
        puVar8 = (unsigned short *)0x04000008;
        *(unsigned short *)0x04000008 = *(unsigned short *)0x04000008 & 0xfffc | 3;
        puVar8[1] = puVar8[1] & 0xfffc | 1;
        puVar8[3] = puVar8[3] & 0xfffc;
        func_02006128(0x180);
        puVar11 = (unsigned int *)(0x04001050 - 0x28);
        *(unsigned int *)0x04001050 = 0;
        puVar9 = (unsigned int *)((unsigned short *)0x04001050 - 0x21);
        *puVar11 = *puVar11 & 0xffffe0ff | 0x1400;
        *(unsigned short *)puVar9 = *(unsigned short *)puVar9 & 0xfffc | 3;
        puVar8 = (unsigned short *)0x04001050 - 0x22;
        *puVar8 = *puVar8 & 0xfffc;
        *puVar11 = *puVar11 & 0xffff1fff;
    } else {
        *(volatile unsigned short *)0x04000008 = *(volatile unsigned short *)0x04000008 & 0xfffc | 3;
        *(volatile unsigned short *)0x0400000c = *(volatile unsigned short *)0x0400000c & 0xfffc;
        *reg_dispcnt = *reg_dispcnt & 0xffff00ff | 0x500;
        *(volatile unsigned int *)0x04000050 = 0;
        iVar6 = func_020066a4();
        func_ov003_0204cb44(iVar6);
        puVar9 = (unsigned int *)0x04001000;
        puVar11 = (unsigned int *)0x04001014;
        iVar6 = data_0204f9a0;
        if (*(int *)(iVar6 + 0x17ac) == 0) {
            *(unsigned int *)0x04001000 = *(unsigned int *)0x04001000 & 0xffffe0ff | 0x900;
            *puVar9 = *puVar9 & 0xffff1fff;
            *(unsigned short *)(puVar9 + 0x14) = 0;
        } else {
            if (*(int *)(iVar6 + 0x1e0c) < 1) {
                uVar10 = (unsigned int)(*(int *)(iVar6 + 0x17b4) / 2);
                *(unsigned int *)0x04001014 = 0x01ff0000 & *(int *)(iVar6 + 0x17b0) << 0x10;
                iVar5 = data_0204f9a0;
                if ((int)uVar10 < 0xf) {
                    *(unsigned short *)((int)puVar11 + 0x2e) = 0xff;
                    *(unsigned short *)((int)puVar11 + 0x32) = (short)*(int *)(iVar5 + 0x17b0) * -0x100 | 0xbf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & 0xc0ff | 0x3b00;
                    *(unsigned short *)(puVar11 + 0xb) = 0x10ff;
                    *(short *)(puVar11 + 0xc) = (short)0x0000afbf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & 0xffc0 | 0x3a;
                    *(unsigned short *)((int)puVar11 + 0x36) = *(unsigned short *)((int)puVar11 + 0x36) & 0xffc0 | 0x19;
                    puVar11[-5] = puVar11[-5] & 0xffff1fff | 0x6000;
                    func_02006b90(puVar11 + 0xf, 2, 8, uVar10, 0xf - uVar10);
                } else {
                    uVar10 = *(unsigned int *)(iVar5 + 0x1e08);
                    *(unsigned short *)(puVar11 + 0xb) = 0xff;
                    *(unsigned short *)(puVar11 + 0xc) = 0xaf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & 0xffc0 | 0x3b;
                    *(unsigned short *)((int)puVar11 + 0x2e) = 0x10ff;
                    *(short *)((int)puVar11 + 0x32) = (short)0x0000afbf;
                    *(unsigned short *)(puVar11 + 0xd) = *(unsigned short *)(puVar11 + 0xd) & 0xc0ff | 0x3900;
                    *(unsigned short *)((int)puVar11 + 0x36) = *(unsigned short *)((int)puVar11 + 0x36) & 0xffc0 | 0x19;
                    puVar11[-5] = puVar11[-5] & 0xffff1fff | 0x6000;
                    if (uVar10 == 0xf) {
                        *(unsigned short *)(puVar11 + 0xf) = 0;
                    } else {
                        func_02006b90(puVar11 + 0xf, 1, 10, uVar10, 0xf - uVar10);
                    }
                }
            } else {
                puVar11 = (unsigned int *)0x04001050;
                *(unsigned int *)0x04001014 = 0;
                func_02006bac((unsigned short *)puVar11, 2, *(int *)(data_0204f9a0 + 0x1e0c));
                puVar8 = (unsigned short *)0x04001040;
                *(unsigned short *)0x04001040 = (unsigned short)(iVar5 << 0xb) | sVar1 + 0x3fU & 0xff;
                puVar8[2] = 0x17;
                puVar8[4] = puVar8[4] & 0xffc0 | 0x2a;
                puVar8[5] = puVar8[5] & 0xffc0 | 0xb;
                *(unsigned int *)(puVar8 - 0x20) = *(unsigned int *)(puVar8 - 0x20) & 0xffff1fff | 0x2000;
            }
            *(unsigned int *)0x04001000 = *(unsigned int *)0x04001000 & 0xffffe0ff | 0xb00;
        }
        puVar11 = (unsigned int *)0x0400100e;
        puVar9 = (unsigned int *)0x0400100e - 1;
        puVar8 = (unsigned short *)(0x0400100e - 6);
        *(unsigned short *)0x0400100e = *(unsigned short *)0x0400100e & 0xfffc | 3;
        *(unsigned short *)puVar9 = *(unsigned short *)puVar9 & 0xfffc | 1;
        *puVar8 = *puVar8 & 0xfffc;
    }
    func_0202e4f4(data_0204f9a0 + 0x58, 0x800, puVar9, puVar11);
    func_0202e4f4(data_0204f9a0 + 0xb0, 0x800, puVar9, puVar11);
    func_02023cc0((void *)(*(int *)(data_0204f9a0 + 0x54) * 0x58 + data_0204f9a0 + 0x68));
}
