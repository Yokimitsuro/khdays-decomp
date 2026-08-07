/* State-change request for the ov066 panel. Three states are handled specially: 0x2e
 * and 0x31 only tear down when the state actually changes, and 0/1/4 resolve a
 * transition argument -- but only if the object is currently displayable. When it is
 * not, that same case falls through into a validation step which demotes the panel to
 * state 0x2f if the requested state is not the one its table says it should be in.
 * Any other state is simply not handled here and drops straight to the tail, where the
 * panel either commits the resolved transition or takes the plain path.
 *
 * Two shapes here are load-bearing and neither is obvious.
 *
 * `case 0x30:` is empty and does nothing at runtime, but it is a real value in the
 * decision tree mwcc builds: with it, the upper arm is bounded from below
 * (cmp #0x30 / ble) before 0x31 is tested; without it, 0x31 is compared directly and
 * the function is eight bytes short. There must be no `default:` either -- giving the
 * unmatched states a block of their own moves the same comparison.
 *
 * nExpected is declared at function scope and assigned INSIDE the comparison. That is
 * what puts the model pointer in r2 and leaves r1 and r0 free for the table and the
 * expected value; declared inside the block, or assigned before the comparison, the
 * model lands in r1, the table is pushed to r0 and the expected value has to reuse the
 * dying model register. Assigning it above the whole condition also reaches r2 but
 * then the load cannot sink past the short-circuit and is emitted too early. */
extern void func_ov066_020b6340(char *self);
extern void func_ov066_020b60f0(char *blk);
extern int func_ov022_02095524(char *obj);
extern int func_ov002_020519b0(int nState, int nPrev, int nKind);
extern void func_ov022_020a46f8(char *self, int nState);
extern int func_ov022_02095600(char *obj);
extern void func_ov022_020a3c78(char *self, int a, int b, int c);
extern void func_ov022_020a384c(char *self, int nState);

void func_ov066_020b34cc(char *self, int nState)
{
    char *blk = self + 0xc50 + 0x2000;
    int nFlag = -1;
    int nArg = 0;
    int nExpected;

    switch (nState) {
    case 0x2e:
        if (*(int *)(self + 0x6bc) != nState) {
            *(int *)(blk + 0xc) = nArg;
            func_ov066_020b6340(self);
        }
        break;

    case 0x31:
        if (*(int *)(self + 0x6bc) != nState) {
            func_ov066_020b60f0(blk);
        }
        break;

    case 0x30:
        break;

    case 0:
    case 1:
    case 4:
        if (func_ov022_02095524(self + 0x2f8 + 0x2000) != 0) {
            if (nState == *(int *)(self + 0x6bc) && *(int *)(blk + 0xc) != 0) {
                break;
            }
            nFlag = 1;
            nArg = func_ov002_020519b0(nState, *(int *)(self + 0x6bc),
                                       *(int *)(self + 0xc));
            if (nState == 4) {
                nArg = 5;
            }
            break;
        }
        {
            char *model = *(char **)(self + 0x20);
            if (nState == *(int *)(self + 0x6bc) &&
                (*(unsigned short *)(model + 4) & 4) == 0 &&
                (*(int **)(model + 0xf4))[nState] !=
                    (nExpected = *(int *)(model + 0x10))) {
                *(int *)(self + 0x6bc) = 0x2f;
            }
        }
        break;
    }

    if (nFlag >= 0) {
        *(int *)(blk + 0xc) = 1;
        func_ov022_020a46f8(self, nState);
        func_ov022_020a3c78(self, func_ov022_02095600(self + 0x2f8 + 0x2000), nFlag, nArg);
        *(int *)(self + 0x6bc) = nState;
        return;
    }
    func_ov022_020a384c(self, nState);
}
