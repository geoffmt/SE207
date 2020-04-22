#include <systemc.h>


void print_terminal(sc_logic x){
   cout << x << endl;
}

int sc_main(int argc, char *argv[])
{

   print_terminal(sc_logic(0));
   print_terminal(sc_logic(1));
   print_terminal(sc_logic(2));
   print_terminal(sc_logic(3));


   print_terminal(sc_logic('0'));
   print_terminal(sc_logic('1'));
   print_terminal(sc_logic('2'));
   print_terminal(sc_logic('3'));
   print_terminal(sc_logic('w'));
 
   print_terminal(sc_logic('x'));
   print_terminal(sc_logic('z'));
   print_terminal(sc_logic('X'));
   print_terminal(sc_logic('Z'));

   print_terminal(sc_logic(true));
   print_terminal(sc_logic(false));

   sc_logic l_0;
   l_0 = 0; 
   sc_logic l_1;
   l_1 = 1;
   sc_logic l_x;
   l_x = 2;
   sc_logic l_z;
   l_z = 3;

   print_terminal(l_0);
   print_terminal(l_1);
   print_terminal(l_x);
   print_terminal(l_z);

   print_terminal(~l_0);
   print_terminal(~l_1);
   print_terminal(~l_x);
   print_terminal(~l_z);

   print_terminal((l_0 | false));
   print_terminal((l_0 | true));
   print_terminal((l_0 | l_0));
   print_terminal((l_0 | l_1));
   print_terminal((l_0 | l_x));
   print_terminal((l_0 | l_z));

   print_terminal((l_1 | false));
   print_terminal((l_1 | true));
   print_terminal((l_1 | l_0));
   print_terminal((l_1 | l_1));
   print_terminal((l_1 | l_x));
   print_terminal((l_1 | l_z));

   print_terminal((l_x | false));
   print_terminal((l_x | true));
   print_terminal((l_x | l_0));
   print_terminal((l_x | l_1));
   print_terminal((l_x | l_x));
   print_terminal((l_x | l_z));

   print_terminal((l_z | false));
   print_terminal((l_z | true));
   print_terminal((l_z | l_0));
   print_terminal((l_z | l_1));
   print_terminal((l_z | l_x));
   print_terminal((l_z | l_z));

   print_terminal((l_0 & l_1));
   print_terminal((l_0 & l_x));
   print_terminal((l_0 & l_z));
   print_terminal((l_1 & l_1));
   print_terminal((l_1 & l_x));
   print_terminal((l_1 & l_z));
   print_terminal((l_x & l_x));
   print_terminal((l_x & l_z));
   print_terminal((l_z & l_z));

   print_terminal((l_0 ^ l_0));
   print_terminal((l_1 ^ l_0));
   print_terminal((l_1 ^ l_1));
   print_terminal((l_1 ^ l_z));
   print_terminal((l_x ^ l_x));
   print_terminal((l_x ^ l_z));
   print_terminal((l_z ^ l_z));

   return 0;
}