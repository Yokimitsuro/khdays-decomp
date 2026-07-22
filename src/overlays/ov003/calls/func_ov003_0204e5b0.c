/* func_ov003_0204e5b0 -- ov003 per-frame step. Lazily create the +0xf0a object, run the shared
 * cleanup on the +0x84 block, then push every live entry through func_ov003_0204e4b8 and release
 * its two 0x108-stride buffers. If the retry counter at +0xbba is still under 0x10, bump it, kick
 * the two retry hooks with (counter - 0x10) and bail out with 0; otherwise reset the per-entry
 * triple (offset, 0, 0) and hand the next step function back to the caller.
 *
 * Parked as a "4-byte strength-reduction tie" and it was three separate things, none of them a tie:
 *  1. `func_0201e374(iVar4 - 0xf)` folds the +1 and the -0x10 into one constant. The ROM stores
 *     `iVar4 + 1` and then subtracts 0x10 FROM THE STORED VALUE (`add r2,r0,#1 ; sub r0,r2,#0x10`),
 *     so the source reads the slot back: `*(int *)(root + 0xbba) - 0x10`. mwcc forwards the value,
 *     so the read-back costs nothing -- and the SECOND hook really does reload it from memory.
 *  2. the early `return 0` belongs OUT OF LINE. The ROM branches to a `mov r0,#0 ; pop` block
 *     placed after the normal return; written as a plain `return 0;` inside the `if`, mwcc emits it
 *     inline and saves the branch -- exactly the 4 bytes. `goto ret0;` plus a label after the
 *     normal return reproduces the ROM's layout.
 *  3. `iVar4 * -8` is what invites the strength reduction (mwcc turns it into a running
 *     `sub r2,r2,#8`). Written as `(-iVar4) << 3` -- negate, then shift, which is what the ROM
 *     emits (`rsb r2,r3,#0 ; lsl r2,r2,#3`) -- the multiply never appears and there is nothing to
 *     reduce. The shape of the expression, not the compiler, decides this.
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_ov105_020bd7c4(void);
extern void func_0202aa9c(void *p);
extern void func_ov003_0204e4b8(int i, int v);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern int func_ov003_0204e6b8(void);

int func_ov003_0204e5b0(void) {
    unsigned short *root;
    unsigned int uVar3;
    int iVar4;
    unsigned short *puVar5;
    unsigned short *puVar6;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_ov105_020bd7c4();
    }
    func_0202aa9c(root + 0x84);
    uVar3 = *root;
    iVar4 = 0;
    if (0 < (int)uVar3) {
        puVar5 = root + 0x108;
        puVar6 = root + 0x318;
        do {
            func_ov003_0204e4b8(iVar4, ((int *)root)[iVar4 + 0x5d4]);
            func_0202aa9c(puVar5);
            func_0202aa9c(puVar6);
            uVar3 = *root;
            iVar4 = iVar4 + 1;
            puVar5 = puVar5 + 0x84;
            puVar6 = puVar6 + 0x84;
        } while (iVar4 < (int)uVar3);
    }
    iVar4 = *(int *)(root + 0xbba);
    if (iVar4 < 0x10) {
        *(int *)(root + 0xbba) = iVar4 + 1;
        func_0201e374(*(int *)(root + 0xbba) - 0x10);
        func_0201e3cc(*(int *)(root + 0xbba) - 0x10);
        goto ret0;
    }
    iVar4 = 0;
    if (0 < (int)uVar3) {
        do {
            ((int *)root)[iVar4 + 0x5df] = (-iVar4) << 3;
            ((int *)root)[iVar4 + 0x5e3] = 0;
            ((int *)root)[iVar4 + 0x5e7] = 0;
            iVar4 = iVar4 + 1;
        } while (iVar4 < (int)(unsigned int)*root);
    }
    return (int)func_ov003_0204e6b8;
ret0:
    return 0;
}
