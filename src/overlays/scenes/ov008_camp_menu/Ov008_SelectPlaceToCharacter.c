/* Turns a place in the character select (its own order, 0-18) into the data folders' character
 * number (place 12 is Roxas, character 0). Anything out of range gives 0 too. */
int Ov008_SelectPlaceToCharacter(int nPlace) {
    int nCharacter = 0;
    switch (nPlace) {
    case 0:  nCharacter = 0xd;  break;
    case 1:  nCharacter = 2;    break;
    case 2:  nCharacter = 4;    break;
    case 3:  nCharacter = 0xc;  break;
    case 4:  nCharacter = 8;    break;
    case 5:  nCharacter = 0xf;  break;
    case 6:  nCharacter = 3;    break;
    case 7:  nCharacter = 1;    break;
    case 8:  nCharacter = 6;    break;
    case 9:  nCharacter = 9;    break;
    case 10: nCharacter = 0xa;  break;
    case 11: nCharacter = 7;    break;
    case 12: nCharacter = 0;    break;
    case 13: nCharacter = 0xe;  break;
    case 14: nCharacter = 0x10; break;
    case 15: nCharacter = 5;    break;
    case 16: nCharacter = 0xb;  break;
    case 17: nCharacter = 0x11; break;
    case 18: nCharacter = 0x12; break;
    }
    return nCharacter;
}
