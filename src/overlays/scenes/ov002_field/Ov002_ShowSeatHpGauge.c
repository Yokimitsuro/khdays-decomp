/* Shows (bOn 1) or hides seat nSeat's HP gauge on the field's panel: the panel's +0x220 holds each
 * seat's gauge, an index into Ov002_SetGaugeSlotShown's gauges (data_ov002_0207f618). */
extern int Ov002_SetGaugeSlotShown(int nGauge, int bOn);
extern int data_ov002_0207f614;

int Ov002_ShowSeatHpGauge(int nSeat, int bOn) {
    return Ov002_SetGaugeSlotShown(*(int *)(*(int *)&data_ov002_0207f614 + nSeat * 4 + 0x220), bOn);
}
