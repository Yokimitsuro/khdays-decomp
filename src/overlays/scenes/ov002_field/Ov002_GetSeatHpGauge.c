/* Returns seat nSeat's HP gauge on the field's panel (the panel's +0x220 + 4 x seat), an index into
 * Ov002_SetGaugeSlotShown's gauges (data_ov002_0207f618). */

extern int data_ov002_0207f614;

int Ov002_GetSeatHpGauge(int nSeat) {
    return *(int *)(*(int *)&data_ov002_0207f614 + nSeat * 4 + 0x220);
}
