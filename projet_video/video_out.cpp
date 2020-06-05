#include "video_out.h"
#include <string>

void VIDEO_OUT::accept_image(){

    if (!reset_n){
        current_image_number = 0;
        current_index = 0;
        return;
    }

    if (href){
        // reset index if vref changes to 1
        if (vref && !old_vref) current_index = 0;

        // incrementing pixel array
        image.pixel[current_index] = pixel_in;
        current_index++;

        // we stop at the end and show the resulting image
        if (current_index == HEIGHT * WIDTH){
            output_image();
            current_index = 0;
            current_image_number++;
        }
    }
    old_vref = vref;
}

void VIDEO_OUT::output_image(){
    std::string b_name = base_name + std::to_string(current_image_number);
    std::cout << name() << "Affichage de l'image " << b_name << endl;
    image_write(&image, b_name.c_str());
}