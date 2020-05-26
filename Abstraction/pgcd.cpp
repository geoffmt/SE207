#include <systemc.h>
#include "obj_dir/Vpgcd_verilog.h"

#define print_terminal(x)             \
    do                                \
    {                                 \
        cout << #x ": " << x << endl; \
    } while (0)

unsigned int pgcd(unsigned int a, unsigned int b)
{
    unsigned int tmp = 0;

    if (b > a)
    {
        tmp = b;
        b = a;
        a = tmp;
    }

    while (b != 0)
    {
        a -= b;
        if (b > a)
        {
            tmp = a;
            a = b;
            b = tmp;
        }
    }

    return a;
}

SC_MODULE(PGCD_MOD)
{

    sc_in<bool> clk;
    sc_in<bool> valid;
    sc_in< sc_uint<8> > A;
    sc_in< sc_uint<8> > B;
    sc_out<bool> ready;
    sc_out<sc_uint<8>  > PGCD;

    sc_uint<8> pgcd(sc_uint<8> a, sc_uint<8> b)
    {
        sc_uint<8> tmp;

        if (b > a)
        {
            tmp = b;
            b = a;
            a = tmp;
        }
        while (b != 0)
        {
            a -= b;
            wait();
            if (b > a)
            {
                wait();
                tmp = a;
                wait();
                a = b;
                wait();
                b = tmp;
                wait();
            }
        }
    
        return a;
    }

    void mthread()
    {
        while(1){ // on garde le thread en vie
            ready = 0;
            // Attendre que les entrées soient prêtes
            while (!valid)
            {
                wait();
            }
            // Exécuter la fonction pgcd
            PGCD = pgcd(A, B);
            ready = 1;
            wait();
        }
    }

    SC_CTOR(PGCD_MOD):clk("CLK"), valid("valid"), A("A"), B("B"), ready("ready"), PGCD("PGCD")
    {
        SC_CTHREAD(mthread, clk.pos());
    }
};

SC_MODULE(PGCD_RTL)
{
    sc_in<bool> clk;
    sc_in<bool> valid;
    sc_in< sc_uint<8> > A;
    sc_in< sc_uint<8> > B;
    sc_out<bool> ready;
    sc_out<sc_uint<8>  > PGCD;

    sc_signal< sc_uint<8> > max;
    sc_signal< sc_uint<8> > min;
    sc_signal<bool> state_computed; // variable qui permet de savoir si le calcul est terminé 

    void mthread()
    {
        PGCD = max;

        if ((min == sc_uint<8>(0)) & state_computed) // calcul terminé le pgcd est trouvé
        {
            ready = 1;
            state_computed = 0;
        }
        else
        {
            ready = 0;
            if (valid){
                state_computed=1;
            }
        }

        sc_uint<8> tmp;
        if (valid) // les variables sont disponibles : on peut faire le calcul 
        {
            if (A > B)
            {
                max = A;
                min = B;
            }
            else
            {
                max = B;
                min = A;
            }
        }
        else // les variables ne sont pas dispos donc cela signifie que le résultat de max-min n'a pas été fait 
        {
            tmp = max.read() - min.read();
            if (tmp > min)
            {
                max = tmp;
            }
            else
            {
                max = min;
                min = tmp;
            }
        }
    }

    SC_CTOR(PGCD_RTL):clk("CLK"), valid("valid"), A("A"), B("B"), ready("ready"), PGCD("PGCD")
    {
        state_computed = 0;
        SC_METHOD(mthread);
        sensitive << clk.pos();
    }
};

int sc_main(int argc, char *argv[])
{

    sc_clock clk("clk", 10, SC_NS);

    sc_signal<bool> valid, ready;
    sc_signal< sc_uint<8> > A, B, PGCD;

    int PERIOD = 5;

    /**
    PGCD_MOD pgcd_mod("PGCD_MOD");
    pgcd_mod.clk(clk);
    pgcd_mod.valid(valid);
    pgcd_mod.ready(ready);
    pgcd_mod.A(A);
    pgcd_mod.B(B);
    pgcd_mod.PGCD(PGCD);
    **/

    PGCD_RTL pgcd_rtl("PGCD_RTL");
    pgcd_rtl.clk(clk);
    pgcd_rtl.valid(valid);
    pgcd_rtl.ready(ready);
    pgcd_rtl.A(A);
    pgcd_rtl.B(B);
    pgcd_rtl.PGCD(PGCD);

    
    sc_trace_file *trace_f;
    trace_f = sc_create_vcd_trace_file("my_simu_trace");
    trace_f->set_time_unit(100, SC_PS);

    /**
    sc_trace(trace_f, clk, pgcd_mod.clk.name());
    sc_trace(trace_f, valid, pgcd_mod.valid.name());
    sc_trace(trace_f, ready, pgcd_mod.ready.name());
    sc_trace(trace_f, A, pgcd_mod.A.name());
    sc_trace(trace_f, B, pgcd_mod.B.name());
    sc_trace(trace_f, PGCD, pgcd_mod.PGCD.name());
    **/
  
    sc_trace(trace_f, clk, pgcd_rtl.clk.name());
    sc_trace(trace_f, valid, pgcd_rtl.valid.name());
    sc_trace(trace_f, ready, pgcd_rtl.ready.name());
    sc_trace(trace_f, A, pgcd_rtl.A.name());
    sc_trace(trace_f, B, pgcd_rtl.B.name());
    sc_trace(trace_f, PGCD, pgcd_rtl.PGCD.name());


    valid = 0;

    sc_start(30, SC_NS);
    
    for (unsigned int a = 0; a <= 255; a++)
    {
        for (unsigned int b = 0; b <= 255; b++)
        {
            A = a;
            B = b;
            valid = 1; // Les données sont prêtes
            sc_start(PERIOD, SC_NS);
            valid = 0;

            // On avance dans la simulation tant que le thread n'a pas terminé le calcul
            while (!ready)
            {
                sc_start(PERIOD, SC_NS);
            }

            // On affiche le résultat
            print_terminal(a);
            print_terminal(b);
            print_terminal(PGCD);
            print_terminal(pgcd(a, b));

            sc_start(PERIOD, SC_NS);
        }
    }


    cout << "Fin des tests" << endl;

    sc_start(30, SC_NS);
    sc_close_vcd_trace_file(trace_f);

    return 0;
}
