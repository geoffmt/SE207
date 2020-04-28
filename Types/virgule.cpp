#define SC_INCLUDE_FX
#include <systemc.h>
#include <cmath>

#define print_terminal(x)             \
    do                                \
    {                                 \
        cout << #x ": " << x << endl; \
    } while (0)

int print_bit_size(int n, double ecart)
{
    double d = M_PI * sin((M_PI * n) / 256);
    int b = 0;

    sc_fxtype_params param(3 + b, 3); //3 bits pour la partie entière et b bits après la virgule
    sc_fxtype_context ctxt(param);
    sc_fix f(d);

    while (true)
    {
        b += 1;
        sc_fxtype_params param(3 + b, 3);
        sc_fxtype_context ctxt(param);
        sc_fix f(d);
        if (abs(double(f) - d) < ecart) //tant que l'on est pas inférieur à la précision demandée,
            break;                      //on augmente la capacité de la zone après la virgule
    }
    return b;
}

int sc_main(int argc, char *argv[])
{
    print_terminal(print_bit_size(10, 0.01));
    print_terminal(print_bit_size(10, 0.001));
    print_terminal(print_bit_size(10, 0.0001));

    return 0;
}