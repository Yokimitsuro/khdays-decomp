/* Ov000_ArmAutoAdvanceTimer -- arm the logo auto-advance timer, ov000. Sets the pending mode
 * (@+0x6a44 = 2 if Ov000_WriteSlotHeaders reports active, else 0) and latches the deadline
 * ((tick*64)/0x82ea + 0x5dc) into the scene block @+0x6a58. */
extern int Ov000_WriteSlotHeaders(int);
extern unsigned long long OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern char *data_ov000_0205ac24;
void Ov000_ArmAutoAdvanceTimer(int slot) {
    *(int *)(data_ov000_0205ac24 + 0x6a44) = (Ov000_WriteSlotHeaders(slot) != 0) ? 2 : 0;
    *(int *)(data_ov000_0205ac24 + 0x6a58) =
        (unsigned int)(func_02020368(OS_GetTick() << 6, 0x82ea) + 0x5dc);
}
