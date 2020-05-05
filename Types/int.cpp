#include <systemc.h>

#define print_terminal(x)             \
    do                                \
    {                                 \
        cout << #x ": " << x << endl; \
    } while (0)

int sc_main(int argc, char *argv[])
{

    sc_int<10> v6 = 15;
    print_terminal(v6);
    print_terminal(v6 + sc_int<10>(1000));
    print_terminal(sc_int<10>(v6 + 1000));

    print_terminal((~sc_int<4>("0b1010")));

    print_terminal(sc_int<4>(sc_lv<4>("0101")));

    print_terminal(sc_bv<4>(sc_int<4>(sc_lv<4>("xxxx"))));
    print_terminal(sc_bv<4>(sc_int<4>(sc_lv<4>("01xz"))));
    return 0;
}