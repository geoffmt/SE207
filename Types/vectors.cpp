#include <systemc.h>

#define print_terminal(x)           \
   do                               \
   {                                \
      cout << #x ": " << x << endl; \
   } while (0)

int sc_main(int argc, char *argv[])
{

   sc_lv<4> vec_1 = 5;
   sc_lv<4> vec_2 = 8;
   print_terminal(sc_bv<4>('0'));
   print_terminal(sc_bv<4>('1'));
   print_terminal(sc_bv<4>('x'));

   print_terminal(vec_1);
   print_terminal(vec_2);

   sc_lv<4> vec_3 = "01xz";
   print_terminal(vec_3);

   print_terminal((vec_1 | vec_2));
   print_terminal((vec_1 & vec_2));
   print_terminal((vec_1 ^ vec_2));

   print_terminal(vec_1.or_reduce());
   print_terminal((vec_1 | vec_2).nand_reduce());

   print_terminal(vec_3.to_int());

   print_terminal(sc_lv<4>(sc_bv<4>("0101")));
   print_terminal(sc_bv<4>(sc_lv<4>("01xz")));
   print_terminal(sc_lv<2>(sc_bv<4>("0101")));
   print_terminal(sc_bv<2>(sc_lv<4>("01xz")));

   return 0;
}