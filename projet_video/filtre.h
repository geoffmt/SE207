#ifndef FILTRE_H
#define FILTRE_H

#include <systemc.h>

typedef unsigned char (*filter) (unsigned char *);

/***************************************
 *  définition du module
 **************************************/
SC_MODULE(FILTER)
{

    // IO PORTS
    sc_in<bool> clk;
    sc_in<bool> reset_n;

    sc_in<unsigned char> p_in;
    sc_in<bool> h_in;
    sc_in<bool> v_in;

    sc_out<unsigned char> p_out;
    sc_out<bool> h_out;
    sc_out<bool> v_out;

    /***************************************************
    *  constructeur
    **************************************************/
    

    FILTER(sc_module_name n, filter f) : sc_module(n), f(f)
    {
        cout << "Instanciation de " << name() << " ...";

        SC_METHOD(receive_image);
        sensitive << clk.pos();
        async_reset_signal_is(reset_n, false);
        dont_initialize();

        SC_THREAD(send_moy);
        sensitive << clk.pos();
        async_reset_signal_is(reset_n, false);

        cout << "... réussie" << endl;
    }

    SC_HAS_PROCESS(FILTER);
    /***************************************************
    *  méthodes et champs internes
    **************************************************/
private:
    void receive_image();
    void send_moy();
    int mean_compute(int x, int y);

    int current_pixel;
    bool old_vref;

    // Pour ce projet les dimensions de l'image sont imposées
    static const int HEIGHT = 576;
    static const int WIDTH = 720;
    static const int fHEIGHT = HEIGHT + 49;
    static const int fWIDTH = WIDTH + 154;
    static const int BUF_SIZE = 3 * WIDTH;

    unsigned char buffer[BUF_SIZE];

    filter f;
};

#endif
