#include <systemc.h>

#define PP(x) do{\
                  cout << #x": " << x << endl;\
                } while(0)


void print_terminal(x){
   cout << 
}

int sc_main(int argc, char *argv[])
{
   //PP(sc_logic(-1)); Not valid
   PP(sc_logic(0));
   PP(sc_logic(1));
   PP(sc_logic(2));
   PP(sc_logic(3));
   //PP(sc_logic(4)); Not valid

   PP(sc_logic('0'));
   PP(sc_logic('1'));
   PP(sc_logic('2'));
   PP(sc_logic('3'));
   PP(sc_logic('w'));
   //PP(sc_logic("w")); Not valid with char *
   PP(sc_logic('x'));
   PP(sc_logic('z'));
   PP(sc_logic('X'));
   PP(sc_logic('Z'));

   PP(sc_logic(true));
   PP(sc_logic(false));

   sc_logic l_0;
   l_0 = 0; //sc_logic l_0 = 0; does not work
   sc_logic l_1;
   l_1 = 1;
   sc_logic l_x;
   l_x = 2;
   sc_logic l_z;
   l_z = 3;

   PP(l_0);
   PP(l_1);
   PP(l_x);
   PP(l_z);

   PP(~l_0);
   PP(~l_1);
   PP(~l_x);
   PP(~l_z);

   //Tests exhaustifs pour le OU
   PP((l_0 | false));
   PP((l_0 | true));
   PP((l_0 | l_0));
   PP((l_0 | l_1));
   PP((l_0 | l_x));
   PP((l_0 | l_z));

   PP((l_1 | false));
   PP((l_1 | true));
   PP((l_1 | l_0));
   PP((l_1 | l_1));
   PP((l_1 | l_x));
   PP((l_1 | l_z));

   PP((l_x | false));
   PP((l_x | true));
   PP((l_x | l_0));
   PP((l_x | l_1));
   PP((l_x | l_x));
   PP((l_x | l_z));

   PP((l_z | false));
   PP((l_z | true));
   PP((l_z | l_0));
   PP((l_z | l_1));
   PP((l_z | l_x));
   PP((l_z | l_z));

   PP((l_0 & l_1));
   PP((l_0 & l_x));
   PP((l_0 & l_z));
   PP((l_1 & l_1));
   PP((l_1 & l_x));
   PP((l_1 & l_z));
   PP((l_x & l_x));
   PP((l_x & l_z));
   PP((l_z & l_z));

   PP((l_0 ^ l_0));
   PP((l_1 ^ l_0));
   PP((l_1 ^ l_1));
   PP((l_1 ^ l_z));
   PP((l_x ^ l_x));
   PP((l_x ^ l_z));
   PP((l_z ^ l_z));

   return 0;
}