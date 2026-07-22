/* Reads the completion tag the ARM7 writes into the shared work area. */
extern void DC_InvalidateRange(void *p, unsigned int len);
extern int *data_02046280;

int SNDi_GetFinishedCommandTag(void) {
    DC_InvalidateRange(data_02046280, 4);
    return *data_02046280;
}
