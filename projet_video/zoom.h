#ifndef ZOOM_H
#define ZOOM_H

#include <systemc.h>

/***************************************
 *  définition du module
 **************************************/
SC_MODULE(ZOOM)
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

    ZOOM(sc_module_name n, int start_line, int start_col) : sc_module(n), 
                                                           start_line(start_line),
                                                           start_col(start_col)
    {
        cout << "Instanciation de " << name() << " ...";

        SC_METHOD(receive_image);
        sensitive << clk.pos();
        async_reset_signal_is(reset_n, false);
        dont_initialize();

        SC_THREAD(send_zoom);
        sensitive << clk.pos();
        async_reset_signal_is(reset_n, false);

        cout << "... réussie" << endl;
    }

    SC_HAS_PROCESS(ZOOM);
    /***************************************************
    *  méthodes et champs internes
    **************************************************/
private:
    void receive_image();
    void send_zoom();

    int pixel_counter;

    // Pour ce projet les dimensions de l'image sont imposées
    static const int HEIGHT = 576;
    static const int WIDTH = 720;
    static const int fHEIGHT = HEIGHT + 49;
    static const int fWIDTH = WIDTH + 154;

    unsigned char buffer[HEIGHT / 2][WIDTH / 2];

    int  start_line;
    int  start_col;
    int  end_line = start_line + HEIGHT/2;
    int  end_col = start_col + WIDTH/2;
};

#endif
