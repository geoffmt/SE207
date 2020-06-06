#include "zoom.h"

void ZOOM::receive_image()
{

    if (!reset_n)
    {
        current_pixel = 0;
        cout << "module: " << name() << "... reset!" << endl;
        return;
    }

    if (h_in)
    {
        int line = current_pixel / WIDTH;
        int column = current_pixel % WIDTH;

        // on récupère les pixels du rectangle central à dupliquer
        if (line > 144 && line < 433 && column > 180 && column < 541)
            buffer[line-145][column-181] = p_in;

        current_pixel++;
        current_pixel %= (WIDTH * HEIGHT);
    }
}

void ZOOM::send_zoom()
{
    h_out = false;
    p_out = 0;
    v_out = false;

    while (1)
    {
        // buffer not ready
        while (current_pixel/WIDTH < 145)
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
                h_out = true;
                p_out = buffer[y/2][x/2];
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
