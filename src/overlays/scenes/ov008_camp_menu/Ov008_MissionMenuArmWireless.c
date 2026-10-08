/* State: arms the wireless callback, marks the context and enters the mission menu. */

extern char *data_ov008_02090fa0;
extern void Ov008_OpenMissionLobby(int arg0);
extern void Ov008_MissionMenuEnter(void);

void (*Ov008_MissionMenuArmWireless(void))(void)
{
    Ov008_OpenMissionLobby(0);
    *(int *)(data_ov008_02090fa0 + 0x2c) = 1;
    return Ov008_MissionMenuEnter;
}
