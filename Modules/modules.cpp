#include <systemc.h>

SC_MODULE(foo)
{
    sc_in<bool> i{"i"};
    sc_out<bool> o{"o"};
    SC_CTOR(foo) {}
};

SC_MODULE(bar)
{
    sc_in<bool> i{"i"};
    sc_out<bool> o{"o"};
    SC_CTOR(bar) {}
};

SC_MODULE(foobar)
{
    // entrée/sortie
    sc_in<bool> i{"i"};
    sc_out<bool> o{"o"};
    // interne
    sc_signal<bool> s;
    // sous modules
    foo foo_i{"foo_i"};
    bar bar_i{"bar_i"};

    SC_CTOR(foobar)
    {
        // connexions aux I/O
        foo_i.i(i);
        bar_i.o(o);
        // connexion interne
        foo_i.o(s);
        bar_i.i(s);
    }
};

int sc_main(int argc, char *argv[])
{
    sc_signal<bool> o("o");
    sc_clock clk1("clk1", 10, SC_NS);

    foobar foob("foobar");

    foob.i(clk1);
    foob.o(o);


    
    sc_trace_file *trace_f;
    trace_f = sc_create_vcd_trace_file("my_simu_trace");
    trace_f->set_time_unit(100, SC_PS);

    sc_trace(trace_f, clk1, clk1.name());
    sc_trace(trace_f, foob.i, foob.i.name());
    sc_trace(trace_f, foob.o, foob.o.name());
    sc_trace(trace_f, foob.s, foob.s.name());
    sc_trace(trace_f, foob.foo_i.i, foob.foo_i.i.name());
    sc_trace(trace_f, foob.foo_i.o, foob.foo_i.o.name());
    sc_trace(trace_f, foob.bar_i.i, foob.bar_i.i.name());
    sc_trace(trace_f, foob.bar_i.o, foob.bar_i.o.name());
    sc_trace(trace_f, o, o.name());



    sc_start(100, SC_NS);
    sc_close_vcd_trace_file(trace_f);

    return 0;
}