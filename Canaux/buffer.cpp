#include <systemc.h>

#define print_terminal(x)             \
    do                                \
    {                                 \
        cout << #x ": " << x << endl; \
    } while (0)

SC_MODULE(SIGNAL)
{
    sc_port< sc_signal_in_if<bool> > signal;

    SC_CTOR(SIGNAL) : signal("Signal")
    {
        SC_METHOD(print);
        sensitive << signal;
    }

    void print()
    {
        cout << "Signal has been notified" << endl;
    }
};

SC_MODULE(BUFFER)
{
    sc_port< sc_signal_in_if<bool> > buffer;

    SC_CTOR(BUFFER) : buffer("Buffer")
    {
        SC_METHOD(print);
        sensitive << buffer;
    }

    void print()
    {
        cout << "Buffer has been notified" << endl;
    }
};

int sc_main(int argc, char *argv[])
{
    sc_signal<bool> signal;
    SIGNAL sig("SIG");
    sig.signal(signal);

    sc_buffer<bool> buffer;
    BUFFER buf("BUF");
    buf.buffer(buffer);

    sc_start(100, SC_NS);
    cout << sc_time_stamp() << endl;
    print_terminal(signal);
    print_terminal(buffer);
    cout << endl;
    signal = 1;
    buffer = 1;

    sc_start(100, SC_NS);
    cout << sc_time_stamp() << endl;
    print_terminal(signal);
    print_terminal(buffer);
    cout << endl;
    signal = 1;
    buffer = 1;

    sc_start(100, SC_NS);
    cout << sc_time_stamp() << endl;
    print_terminal(signal);
    print_terminal(buffer);
    cout << endl;
    signal = 0;
    buffer = 0;

    sc_start(100, SC_NS);
    cout << sc_time_stamp() << endl;
    print_terminal(signal);
    print_terminal(buffer);

    return 0;
}
