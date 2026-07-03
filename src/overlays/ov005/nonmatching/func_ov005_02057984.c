/*
 * func_ov005_02057984 — split a millisecond timer into MM:SS:CC (minutes,
 * seconds, centiseconds), clamped at 59:59:99.
 *
 * centis   = (ms/10)  % 100   -> *param_4
 * seconds  = (ms/1000)% 60    -> *param_3
 * minutes  = (ms/1000)/60     -> *param_2 (byte)
 * if minutes>59: minutes=59, seconds=';'(59), centis='c'(99).
 * Divisors verified from the pool magics: 0xcccccccd>>35=/10,
 * 0x10624dd3>>38=/1000, 0x51eb851f>>37=/100, 0x88888889>>37=/60.
 *
 * NON-MATCHING: semantics are exact and every instruction lines up, but the
 * four umull magic-divide chains (/10, /1000, /100, /60) leave 21 pure
 * register-coloring differences (same ops, different register numbers) that no
 * statement/decl reordering resolves. Same class as the documented
 * multi-umull scheduler/coloring ties. Affects the 3 byte-identical siblings.
 */
void func_ov005_02057984(unsigned int ms, unsigned char *minutes, char *seconds, char *centis)
{
    unsigned int cs = ms / 10;
    unsigned int s = ms / 1000;
    unsigned int m = s / 60;
    *centis = (char)(cs % 100);
    *seconds = (char)(s % 60);
    *minutes = (unsigned char)m;
    if ((m & 0xff) <= 59)
        return;
    *minutes = 59;
    *seconds = ';';
    *centis = 'c';
}
