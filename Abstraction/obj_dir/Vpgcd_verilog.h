// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VPGCD_VERILOG_H_
#define _VPGCD_VERILOG_H_  // guard

#include "systemc.h"
#include <verilated_sc.h>
#include <verilated.h>


//==========

class Vpgcd_verilog__Syms;

//----------

SC_MODULE(Vpgcd_verilog) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    sc_in<bool> clk;
    sc_in<bool> valid;
    sc_in<uint32_t> a;
    sc_in<uint32_t> b;
    sc_out<bool> ready;
    sc_out<uint32_t> pgcd;
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*7:0*/ PGCD__DOT__max;
    CData/*7:0*/ PGCD__DOT__min;
    CData/*7:0*/ PGCD__DOT__d;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vcellinp__PGCD__clk;
    CData/*7:0*/ __Vcellinp__PGCD__b;
    CData/*7:0*/ __Vcellinp__PGCD__a;
    CData/*0:0*/ __Vcellinp__PGCD__valid;
    CData/*0:0*/ __Vclklast__TOP____Vcellinp__PGCD__clk;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vpgcd_verilog__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vpgcd_verilog);  ///< Copying not allowed
  public:
    SC_CTOR(Vpgcd_verilog);
    virtual ~Vpgcd_verilog();
    
    // API METHODS
  private:
    void eval() { eval_step(); }
    void eval_step();
  public:
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vpgcd_verilog__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vpgcd_verilog__Syms* symsp, bool first);
  private:
    static QData _change_request(Vpgcd_verilog__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vpgcd_verilog__Syms* __restrict vlSymsp);
    static void _combo__TOP__4(Vpgcd_verilog__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vpgcd_verilog__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vpgcd_verilog__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vpgcd_verilog__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__3(Vpgcd_verilog__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vpgcd_verilog__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
