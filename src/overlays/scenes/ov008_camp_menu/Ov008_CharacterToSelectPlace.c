/* Turns a data folders' character number into its place in the character select (0-18), the
 * other way from Ov008_SelectPlaceToCharacter. Character 19 (Roxas's dual wield,
 * his own folder r2) gives Roxas's place 12; anything else out of range gives 0. */

int Ov008_CharacterToSelectPlace(int nCharacter)
{
    int nPlace = 0;

    switch (nCharacter) {
    case 13: nPlace = 0;    break;
    case 2:  nPlace = 1;    break;
    case 4:  nPlace = 2;    break;
    case 12: nPlace = 3;    break;
    case 8:  nPlace = 4;    break;
    case 15: nPlace = 5;    break;
    case 3:  nPlace = 6;    break;
    case 1:  nPlace = 7;    break;
    case 6:  nPlace = 8;    break;
    case 9:  nPlace = 9;    break;
    case 10: nPlace = 0xa;  break;
    case 7:  nPlace = 0xb;  break;
    case 0:  nPlace = 0xc;  break;
    case 14: nPlace = 0xd;  break;
    case 16: nPlace = 0xe;  break;
    case 5:  nPlace = 0xf;  break;
    case 11: nPlace = 0x10; break;
    case 17: nPlace = 0x11; break;
    case 18: nPlace = 0x12; break;
    case 19: nPlace = 0xc;  break;
    }
    return nPlace;
}
