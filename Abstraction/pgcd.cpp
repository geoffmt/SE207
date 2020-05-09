#include <systemc.h>

#define print_terminal(x)             \
    do                                \
    {                                 \
        cout << #x ": " << x << endl; \
    } while (0)

uint pgcd(uint a, uint b)
{
    uint tmp = 0;

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
        sc_out< sc_uint<8> > PGCD;

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
            // Attendre que les entrées soient prêtes
            while (!valid)
            {
                wait();
                ready = 0;
            }
            // Exécuter la fonction pgcd
            PGCD = pgcd(A, B);
            // Ajout de la latence
            wait();
            // prévenir que la sortie est prête
            ready = 1;
        }

        SC_CTOR(PGCD_MOD)
        {
            SC_CTHREAD(mthread, clk.pos());
        }
    };

    int sc_main(int argc, char *argv[])
    {
        sc_clock clk("clk", 10, SC_NS);

        sc_signal<bool> valid, ready;
        sc_signal< sc_uint<8> > A, B, PGCD;

        PGCD_MOD pgcd_mod("PGCD_compute");
        pgcd_mod.clk(clk);
        pgcd_mod.valid(valid);
        pgcd_mod.ready(ready);
        pgcd_mod.A(A);
        pgcd_mod.B(B);
        pgcd_mod.PGCD(PGCD);

        sc_trace_file *trace_f;
        trace_f = sc_create_vcd_trace_file("my_simu_trace");
        trace_f->set_time_unit(100, SC_PS);

        sc_trace(trace_f, clk, pgcd_mod.clk.name());
        sc_trace(trace_f, valid, pgcd_mod.valid.name());
        sc_trace(trace_f, ready, pgcd_mod.ready.name());
        sc_trace(trace_f, A, pgcd_mod.A.name());
        sc_trace(trace_f, B, pgcd_mod.B.name());
        sc_trace(trace_f, PGCD, pgcd_mod.PGCD.name());

        valid = 0;

    sc_start(10, SC_NS);
    
    for (uint a = 5; a<=255; a++){
        for(uint b = 10; b <= 255; b++){
            A = a;
            B = b;
            valid = 1; // Les données sont prêtes
            
            // On avance dans la simulation tant que le thread n'a pas terminé le calcul
            while(!ready){
                sc_start(10, SC_NS);
            }

            // On affiche le résultat 
            print_terminal(a);
            print_terminal(b);
            print_terminal(PGCD);
            print_terminal(pgcd(a,b));

        }
    }

        cout << "Fin des tests" << endl;

        sc_start(100, SC_NS);
        sc_close_vcd_trace_file(trace_f);

        return 0;
    }
