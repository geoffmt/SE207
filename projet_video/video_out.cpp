#include "video_out.h"
#include <string>

void VIDEO_OUT::accept_image()
{

    if (!reset_n)
    {
        current_image_number = 0;
        current_pixel = 0;

        cout << "module: " << name() << "... reset!" << endl;
        return;
    }

    if (href)
    {
        // reset index if vref changes to 1
        if (vref && !old_vref)
            current_pixel = 0;

        // incrementing pixel array
        image.pixel[current_pixel] = pixel_in;
        current_pixel++;

        // we stop at the end and show the resulting image
        if (current_pixel == HEIGHT * WIDTH)
        {
            output_image();
            current_pixel = 0;
            current_image_number++;
        }
    }
    old_vref = vref;
}

void VIDEO_OUT::output_image()
{
    std::string b_name = base_name + std::to_string(current_image_number) + ".png";
    std::cout << name() << "Affichage de l'image " << b_name << endl;
    image_write(&image, b_name.c_str());
}