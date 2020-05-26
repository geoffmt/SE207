// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VPGCD_VERILOG__SYMS_H_
#define _VPGCD_VERILOG__SYMS_H_  // guard

#include "systemc.h"
#include <verilated_sc.h>
#include <verilated.h>

// INCLUDE MODULE CLASSES
#include "Vpgcd_verilog.h"

// SYMS CLASS
class Vpgcd_verilog__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vpgcd_verilog*                 TOPp;
    
    // CREATORS
    Vpgcd_verilog__Syms(Vpgcd_verilog* topp, const char* namep);
    ~Vpgcd_verilog__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
