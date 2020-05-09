#include <systemc.h>

// un type utilisateur
struct Pixel
{
    sc_uint<5> r;
    sc_uint<6> g;
    sc_uint<5> b;
    // un constructeur particulier avec des valeurs par défaut
    Pixel(sc_uint<5> _r = 0, sc_uint<6> _g = 0, sc_uint<5> _b = 0) : r(_r), g(_g), b(_b) {}

    bool operator==(const Pixel &other) const
    {
        return (r == other.r) && (g == other.g) && (b == other.b);
    }

    Pixel operator+(const Pixel &other) const
    {
        return Pixel(r + other.r, g + other.g, b + other.b);
    }
    // On doit pouvoir imprimer la valeur d'un objet de ce type
    // l'opérateur << est un opérateur de la classe std::ostream
    friend ostream &operator<<(ostream &o, const Pixel &P)
    {
        o << "{" << P.r << "," << P.g << "," << P.b << "}";
        return o;
    }

    Pixel increment() const
    {
        Pixel p = Pixel(r, g, b);
        p.b++;
        if (p.b == 0)
        {
            p.g++;
            if (p.g == 0)
            {
                p.r++;
            }
        }
        return p;
    }
};

// surcharge de la fonction sc_trace pour le type utilisateur
void sc_trace(sc_trace_file *_f, const Pixel &_foo, const std::string &_s)
{
    sc_trace(_f, _foo.r, _s + "_r");
    sc_trace(_f, _foo.g, _s + "_g");
    sc_trace(_f, _foo.b, _s + "_b");
}

SC_MODULE(SUM_METH)
{
    sc_in<Pixel> p1;
    sc_in<Pixel> p2;
    sc_out<Pixel> p_out;

    void sum()
    {
        p_out = p1.read() + p2.read();
    }

    SC_CTOR(SUM_METH)
    {
        SC_METHOD(sum);
        sensitive << p1 << p2;
    }
};

SC_MODULE(SUM_TH)
{
    sc_in<Pixel> p1;
    sc_in<Pixel> p2;
    sc_out<Pixel> p_out;

    void sum()
    {
        while (1)
        {
            p_out = p1.read() + p2.read();
            wait();
        }
    }

    SC_CTOR(SUM_TH)
    {
        SC_METHOD(sum);
        sensitive << p1 << p2;
    }
};

SC_MODULE(PIXEL_SEQ_METH)
{

    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_out<Pixel> p_out;

    SC_CTOR(PIXEL_SEQ_METH)
    {
        SC_METHOD(increment);
        sensitive << clk.pos();
        async_reset_signal_is(rst, true);
    }

    void increment()
    {
        if (rst)
        {
            p_out = Pixel();
        }
        else
        {
            p_out = p_out.read().increment();
        }
    }
};

SC_MODULE(PIXEL_SEQ_TH)
{

    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_out<Pixel> p_out;

    SC_CTOR(PIXEL_SEQ_TH)
    {
        SC_THREAD(increment);
        sensitive << clk.pos();
        async_reset_signal_is(rst, true);
    }

    void increment()
    {
        p_out = Pixel();
        for (;;)
        {
            wait();
            p_out = p_out.read().increment();
        }
    }
};

SC_MODULE(PIXEL_SEQ_CTH)
{

    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_out<Pixel> p_out;

    SC_CTOR(PIXEL_SEQ_CTH)
    {
        SC_CTHREAD(increment, clk.pos());
        async_reset_signal_is(rst, true);
    }

    void increment()
    {
        p_out = Pixel();
        for (;;)
        {
            wait();
            p_out = p_out.read().increment();
        }
    }
};
// Le test
int sc_main(int argc, char *argv[])
{
    sc_trace_file *trace_f;
    trace_f = sc_create_vcd_trace_file("my_simu_trace");
    trace_f->set_time_unit(100, SC_PS);

    sc_signal<Pixel> P1, P2, P3, P4;

    sc_clock ck1("ck1", 10, SC_NS);
    sc_signal<bool> rst;

    SUM_METH s("Sum");
    s.p1(P1);
    s.p2(P2);
    s.p_out(P3);

    sc_trace(trace_f, P1, s.p1.name());
    sc_trace(trace_f, P2, s.p2.name());
    sc_trace(trace_f, P3, s.p_out.name());

    PIXEL_SEQ_METH incr_seq("Increment_sequence");
    incr_seq.clk(ck1);
    incr_seq.rst(rst);
    incr_seq.p_out(P4);

    sc_trace(trace_f, ck1, "clk");
    sc_trace(trace_f, rst, "rst");
    sc_trace(trace_f, P4, incr_seq.p_out.name());

    sc_start(10, SC_NS);

    rst = true;
    sc_start(20, SC_NS);

    cout << P1 << endl;
    cout << P2 << endl;
    cout << P3 << endl;
    cout << P4 << endl;

    rst = false;
    P2 = Pixel(1, 2, 1);

    sc_start(20, SC_NS);

    cout << P1 << endl;
    cout << P2 << endl;
    cout << P3 << endl;
    cout << P4 << endl;

    sc_start(500, SC_NS);
    sc_close_vcd_trace_file(trace_f);

    return 0;
}