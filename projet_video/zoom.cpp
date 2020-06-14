#include "zoom.h"

void ZOOM::receive_image()
{

    if (!reset_n)
    {
        pixel_counter = 0;
        cout << "module: " << name() << "... reset!" << endl;
        return;
    }

    if (h_in)
    {
        int line = pixel_counter / WIDTH;
        int column = pixel_counter % WIDTH;

        // on récupère les pixels du rectangle central à dupliquer
        if (line >= start_line && line < end_line && column >= start_col && column < end_col)
            buffer[line - start_line][column - start_col] = p_in;

        pixel_counter++;
        pixel_counter %= (WIDTH * HEIGHT);
    }

    buffer_ready = (pixel_counter / WIDTH >= start_line);
}

void ZOOM::send_zoom()
{
    h_out = false;
    p_out = 0;
    v_out = false;

    while (1)
    {
        // buffer not ready
        while (!buffer_ready)
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
                p_out = buffer[y / 2][x / 2];
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
