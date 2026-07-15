/* func_ov006_02055104 -- commit a queued title sub-state transition, ov006.
 * When a transition is pending (obj+0x956c != 0) and not blocked (bit2 of obj+0x955c set),
 * optionally fires the transition SFX (func_ov006_020551a4(nextState, 1000, sfxA, sfxB)) if
 * obj+0x9560 is set, then advances the state machine: prev=cur (0x94fc<-0x94f4),
 * cur=next (0x94f4<-0x94f8), and clears the pending flag (0x956c=0). */
struct StateBits { unsigned pad : 2; unsigned block : 1; };
extern int *data_ov006_02056664;
extern void func_ov006_020551a4(unsigned int state, int a, int sfxA, int sfxB, int e);

#define O ((char *)data_ov006_02056664 + 0x9000)

void func_ov006_02055104(void) {
    if (*(int *)(O + 0x56c) == 0) {
        return;
    }
    if (((struct StateBits *)(O + 0x55c))->block == 0) {
        return;
    }
    if (*(int *)(O + 0x560) != 0) {
        func_ov006_020551a4(*(unsigned int *)(O + 0x4f8), 1000,
                            (signed char)*(int *)(O + 0x504), (signed char)*(int *)(O + 0x500), 0);
    }
    *(int *)(O + 0x4fc) = *(int *)(O + 0x4f4);
    *(int *)(O + 0x4f4) = *(int *)(O + 0x4f8);
    *(int *)(O + 0x56c) = 0;
}
