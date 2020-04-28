#define SC_INCLUDE_FX
#include <systemc.h>

// 1 bit pour la partie entière et 2 bits après la virgule
#define WL  3
#define IWL 1

double compare (double d1, double d2)
{
   double ds = d1 + d2;
   sc_fix f1(d1);
   sc_fix f2(d2);
   sc_fix fs = f1 + f2;

   return ds - fs;
}

int sc_main (int argc, char * argv[])
{



   double d1 = 0.1;
   double d2 = 0.9;
   double ds = d1 + d2;

   sc_fixed<WL,IWL> f1(d1);
   sc_fixed<WL,IWL> f2 = d2;
   sc_fixed<WL,IWL> fs = f1 + f2;

   double e = ds - double(fs);

   cout 
      << "Double " << ds  << endl 
      << "Fixed  " << fs  << endl 
      << "Error  " << e   << endl;
   
   double d1_bis = 0.1;
   double d2_bis = 0.9;

   // 1 bit pour la partie entière et 2 bits après la virgule
   sc_fxtype_params param1(3,1);
   // 1 bit pour la partie entière et 4 bits après la virgule
   sc_fxtype_params param2(5,1);
   // 1 bit pour la partie entière et 6 bits après la virgule
   sc_fxtype_params param3(7,1);

   sc_fxtype_context ctxt1(param1);
   cout
      << "Error  in context " << ctxt1.default_value()
      << " is " <<  compare(d1_bis,d2_bis)  << endl;

   sc_fxtype_context ctxt2(param2);
   cout
      << "Error  in context " << ctxt1.default_value()
      << " is " <<  compare(d1_bis,d2_bis)  << endl;

   sc_fxtype_context ctxt3(param3);
   cout
      << "Error  in context " << ctxt1.default_value()
      << " is " <<  compare(d1_bis,d2_bis)  << endl;

   return 0;
}