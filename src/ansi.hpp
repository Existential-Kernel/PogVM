namespace ANSI {
    const char *BLACK_BG = "\x1B[48;2;0;0;0m";
    const char *RED_BG   = "\x1B[48;2;255;0;0m";

    const char *RED      = "\x1B[38;2;255;0;0m";
    const char *ORANGE   = "\x1B[38;2;255;180;5m";
    const char *GREEN    = "\x1B[38;2;0;255;0m";
    const char *GREY     = "\x1B[38;2;70;70;70m";
    const char *EXIT     = "\x1B[0m";
    std::ostream &BOLD(std::ostream& log) { return log << "\033[1m"; }
}