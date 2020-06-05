#ifndef VIDEO_OUT_H
#define VIDEO_OUT_H

#include <systemc.h>
#include "image.h"

/***************************************
 *  définition du module
 **************************************/
SC_MODULE(VIDEO_OUT) {

   // IO PORTS
   sc_in<bool>         clk;
   sc_in<bool>         reset_n;

   sc_in<bool>        href;
   sc_in<bool>        vref;

   sc_in<unsigned char> pixel_in;

   /***************************************************
    *  constructeur
    **************************************************/
   VIDEO_OUT(sc_module_name n, const std::string & b_n = "wallace"): sc_module(n), base_name(b_n + "_out")
   {
      cout << "Instanciation de " << name() <<" ..." ;

      SC_THREAD (accept_image);
      sensitive << clk.pos();
      async_reset_signal_is(reset_n,false);
      dont_initialize();

      current_image_number = 0;
      image.height = HEIGHT;
      image.width = WIDTH;
      image.pixel = new unsigned char[HEIGHT * WIDTH];

      cout << "... réussie" << endl;
   }

   SC_HAS_PROCESS(VIDEO_OUT);

   /***************************************************
    *  méthodes et champs internes
    **************************************************/
   private:

   void accept_image();
   void output_image();

   const std::string   base_name;              // nom de base des images d'entrée
   int                 current_image_number;   // numéro de l'image courante
   int                 current_index;
   bool                old_vref;

   Image               image;

   // Pour ce projet les dimensions de l'image sont imposées
   static const int HEIGHT  = 576;
   static const int WIDTH   = 720;
   static const int fHEIGHT = HEIGHT+49;
   static const int fWIDTH  = WIDTH +154;
};

#endif
