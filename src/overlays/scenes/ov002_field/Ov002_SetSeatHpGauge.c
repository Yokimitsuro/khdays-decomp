/* Sets seat nSeat's HP gauge on the field's panel to nHp, in the default style (7): the panel's
 * +0x220 holds each seat's gauge, an index into data_ov002_0207f618 (Ov002_SetGaugeValue's gauges).
 * The panel (data_ov002_0207f614) is 0 until the field's panel is set up, while the battle's
 * actors already exist. */

extern int data_ov002_0207f614;
extern int Ov002_SetGaugeValueDefault();

int Ov002_SetSeatHpGauge(int nSeat, int nHp) {
    return Ov002_SetGaugeValueDefault(*(int *)(*(int *)&data_ov002_0207f614 + nSeat * 4 + 0x220), nHp, 7);
}
