#include "filtre.h"
#include <string>

void FILTER::receive_image()
{

    if (!reset_n)
    {
        current_pixel = 0;
        old_vref = false;

        cout << "module: " << name() << "... reset!" << endl;
        return;
    }

    if (h_in)
    {
        if (v_in && !old_vref)
            current_pixel = 0;

        buffer[current_pixel] = p_in;
        current_pixel++;
        current_pixel %= BUF_SIZE;
    }

    old_vref = v_in;
}


void FILTER::send_moy()
{

    h_out = false;
    p_out = 0;
    v_out = false;

    while (1)
    {
        // buffer not ready
        while (current_pixel < WIDTH + 2)
            wait();

        for (int y = 0; y < HEIGHT; y++)
        {
            // maj de v_out
            if (y < 3)
            {
                v_out = 1;
            }

            for (int x = 0; x < WIDTH; x++)
            {
                // on se positionne au bon endroit dans le buffer
                int initial_index = (y * WIDTH + x) % BUF_SIZE;
                unsigned char tab[9];

                // parcours des 3 lignes autour du pixel pour récupérer les bons pixels à moyenner
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        // on récupere les pixels tout autour du initial_index central
                        int index_to_add = (initial_index - ((1-i) * WIDTH) + (- 1 + j) + BUF_SIZE)%BUF_SIZE;
                        tab[3*i+j] = buffer[index_to_add];
                    }
                }


                h_out = true;
                p_out = f(tab);
                wait();
            }

            h_out = false;
            p_out = 0;
            for (int x = 0; x < fWIDTH - WIDTH; x++)
                wait();
        }

        for (int y = 0; y < fHEIGHT - HEIGHT; y++)
            for (int x = 0; x < fWIDTH; x++)
                wait();
    }
}
