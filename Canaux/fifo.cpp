#include <systemc.h>

#define print_terminal(x)             \
    do                                \
    {                                 \
        cout << #x ": " << x << endl; \
    } while (0)

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

SC_MODULE(WRITER_THREAD)
{
    sc_in<bool> clk;
    sc_fifo_out<Pixel> out;

    void write()
    {
        Pixel pixel;
        int cycles;

        while (1)
        {
            for (int i = 0; i < 100; i++)
            {
                out.write(pixel);
                cout << "Time: " << sc_time_stamp() << endl;
                cout << "Write: " << pixel << endl;
                pixel = pixel.increment();
                wait();
            }
            cycles = rand() % 32;
            wait(cycles);
        }
    }

    SC_CTOR(WRITER_THREAD) : clk("clk"), out("out")
    {
        SC_CTHREAD(write, clk.pos());
    }
};

SC_MODULE(WRITER_METHOD)
{
    sc_in<bool> clk;
    sc_fifo_out<Pixel> out;

    bool boolean = 0;
    int i = 0;
    int cycles = 0;
    Pixel pixel;

    void write()
    {   
        if (cycles == 0)
        {   
            out_ack = out.nb_write(pixel);
            if (out_ack){
                i++;
                cout << "Time: " << sc_time_stamp() << endl;
                cout << "Write: " << pixel << endl;
                pixel = pixel.increment();
            }
            if (i == 100)
            {
                cycles = rand() % 32;
            }
        }
        else // reset
        {
            cycles--;
            i = 0;
        }
    }

    SC_CTOR(WRITER_METHOD) : clk("Clk"), out("out")
    {
        SC_METHOD(write);
        sensitive << clk.pos();
        dont_initialize();
    }
};

SC_MODULE(READER)
{
    sc_in<bool> clk;
    sc_fifo_in<Pixel> in;

    void read()
    {
        Pixel pixel;
        int cycles;

        while (1)
        {
            pixel = in.read();
            cout << "Time: " << sc_time_stamp() << endl;
            cout << "Read: " << pixel << endl;
            int sum = pixel.r + pixel.g + pixel.b;
            if (sum % 2)
            {
                cycles = 3;
            }
            else
            {
                cycles = 2;
            }
            wait(cycles);
        }
    }

    SC_CTOR(READER) : clk("Clk"), in("in")
    {
        SC_CTHREAD(read, clk.pos());
    }
};

int sc_main(int argc, char *argv[])
{
    sc_fifo<Pixel> fifo(1);
    sc_clock clk("clk", 10, SC_NS);

    READER reader("Reader");
    WRITER_METHOD writer("Writer");

    reader.clk(clk);
    writer.clk(clk);
    reader.in(fifo);
    writer.out(fifo);

    sc_start(200, SC_NS);
    cout << "Time: " << sc_time_stamp() << endl
         << fifo << endl;

    return 0;
}
