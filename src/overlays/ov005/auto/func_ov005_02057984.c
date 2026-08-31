/* Split milliseconds into byte-sized result timer fields. */
void func_ov005_02057984(unsigned int milliseconds, unsigned char *minutes,
                       unsigned char *seconds, unsigned char *centiseconds) {
    *centiseconds = (milliseconds / 10) % 100;
    *seconds = (milliseconds / 1000) % 60;
    *minutes = (milliseconds / 1000) / 60;
    if (*minutes > 59) {
        *minutes = 59;
        *seconds = 59;
        *centiseconds = 99;
    }
}
