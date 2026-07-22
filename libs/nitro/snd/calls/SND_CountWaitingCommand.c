/* Free slots in the command ring: 0x100 minus the reserved ones minus the queued ones. */
extern int SND_CountReservedCommand(void);
extern int func_02008aa0(void);

int SND_CountWaitingCommand(void) {
    int reserved = SND_CountReservedCommand();
    return 0x100 - reserved - func_02008aa0();
}
