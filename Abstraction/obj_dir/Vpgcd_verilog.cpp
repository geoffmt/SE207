// Verilated -*- SystemC -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpgcd_verilog.h for the primary calling header

#include "Vpgcd_verilog.h"
#include "Vpgcd_verilog__Syms.h"

//==========

VL_SC_CTOR_IMP(Vpgcd_verilog) {
    Vpgcd_verilog__Syms* __restrict vlSymsp = __VlSymsp = new Vpgcd_verilog__Syms(this, name());
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Sensitivities on all clocks and combo inputs
    SC_METHOD(eval);
    sensitive << clk;
    sensitive << valid;
    sensitive << a;
    sensitive << b;
    
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vpgcd_verilog::__Vconfigure(Vpgcd_verilog__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vpgcd_verilog::~Vpgcd_verilog() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vpgcd_verilog::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vpgcd_verilog::eval\n"); );
    Vpgcd_verilog__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("pgcd_verilog.sv", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vpgcd_verilog::_eval_initial_loop(Vpgcd_verilog__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("pgcd_verilog.sv", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vpgcd_verilog::_combo__TOP__1(Vpgcd_verilog__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_combo__TOP__1\n"); );
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__PGCD__clk, vlTOPp->clk);
}

void Vpgcd_verilog::_settle__TOP__2(Vpgcd_verilog__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_settle__TOP__2\n"); );
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__PGCD__clk, vlTOPp->clk);
    VL_ASSIGN_ISI(8,vlTOPp->__Vcellinp__PGCD__b, vlTOPp->b);
    VL_ASSIGN_ISI(8,vlTOPp->__Vcellinp__PGCD__a, vlTOPp->a);
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__PGCD__valid, vlTOPp->valid);
    VL_ASSIGN_SII(8,vlTOPp->pgcd, vlTOPp->PGCD__DOT__max);
    VL_ASSIGN_SII(1,vlTOPp->ready, ((IData)(vlTOPp->PGCD__DOT__min) 
                                    == (IData)(vlTOPp->PGCD__DOT__max)));
    vlTOPp->PGCD__DOT__d = (0xffU & ((IData)(vlTOPp->PGCD__DOT__max) 
                                     - (IData)(vlTOPp->PGCD__DOT__min)));
}

VL_INLINE_OPT void Vpgcd_verilog::_sequent__TOP__3(Vpgcd_verilog__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_sequent__TOP__3\n"); );
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*7:0*/ __Vdly__PGCD__DOT__min;
    // Body
    __Vdly__PGCD__DOT__min = vlTOPp->PGCD__DOT__min;
    if (vlTOPp->__Vcellinp__PGCD__valid) {
        vlTOPp->PGCD__DOT__max = (((IData)(vlTOPp->__Vcellinp__PGCD__a) 
                                   > (IData)(vlTOPp->__Vcellinp__PGCD__b))
                                   ? (IData)(vlTOPp->__Vcellinp__PGCD__a)
                                   : (IData)(vlTOPp->__Vcellinp__PGCD__b));
        __Vdly__PGCD__DOT__min = (((IData)(vlTOPp->__Vcellinp__PGCD__a) 
                                   > (IData)(vlTOPp->__Vcellinp__PGCD__b))
                                   ? (IData)(vlTOPp->__Vcellinp__PGCD__b)
                                   : (IData)(vlTOPp->__Vcellinp__PGCD__a));
    } else {
        vlTOPp->PGCD__DOT__max = (((IData)(vlTOPp->PGCD__DOT__d) 
                                   > (IData)(vlTOPp->PGCD__DOT__min))
                                   ? (IData)(vlTOPp->PGCD__DOT__d)
                                   : (IData)(vlTOPp->PGCD__DOT__min));
        __Vdly__PGCD__DOT__min = (((IData)(vlTOPp->PGCD__DOT__d) 
                                   > (IData)(vlTOPp->PGCD__DOT__min))
                                   ? (IData)(vlTOPp->PGCD__DOT__min)
                                   : (IData)(vlTOPp->PGCD__DOT__d));
    }
    vlTOPp->PGCD__DOT__min = __Vdly__PGCD__DOT__min;
    VL_ASSIGN_SII(8,vlTOPp->pgcd, vlTOPp->PGCD__DOT__max);
    VL_ASSIGN_SII(1,vlTOPp->ready, ((IData)(vlTOPp->PGCD__DOT__min) 
                                    == (IData)(vlTOPp->PGCD__DOT__max)));
    vlTOPp->PGCD__DOT__d = (0xffU & ((IData)(vlTOPp->PGCD__DOT__max) 
                                     - (IData)(vlTOPp->PGCD__DOT__min)));
}

VL_INLINE_OPT void Vpgcd_verilog::_combo__TOP__4(Vpgcd_verilog__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_combo__TOP__4\n"); );
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    VL_ASSIGN_ISI(1,vlTOPp->__Vcellinp__PGCD__valid, vlTOPp->valid);
    VL_ASSIGN_ISI(8,vlTOPp->__Vcellinp__PGCD__a, vlTOPp->a);
    VL_ASSIGN_ISI(8,vlTOPp->__Vcellinp__PGCD__b, vlTOPp->b);
}

void Vpgcd_verilog::_eval(Vpgcd_verilog__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_eval\n"); );
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if (((IData)(vlTOPp->__Vcellinp__PGCD__clk) & (~ (IData)(vlTOPp->__Vclklast__TOP____Vcellinp__PGCD__clk)))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    vlTOPp->_combo__TOP__4(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP____Vcellinp__PGCD__clk 
        = vlTOPp->__Vcellinp__PGCD__clk;
}

void Vpgcd_verilog::_eval_initial(Vpgcd_verilog__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_eval_initial\n"); );
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP____Vcellinp__PGCD__clk 
        = vlTOPp->__Vcellinp__PGCD__clk;
}

void Vpgcd_verilog::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::final\n"); );
    // Variables
    Vpgcd_verilog__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vpgcd_verilog::_eval_settle(Vpgcd_verilog__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_eval_settle\n"); );
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

VL_INLINE_OPT QData Vpgcd_verilog::_change_request(Vpgcd_verilog__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_change_request\n"); );
    Vpgcd_verilog* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vpgcd_verilog::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG

void Vpgcd_verilog::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpgcd_verilog::_ctor_var_reset\n"); );
    // Body
    __Vcellinp__PGCD__b = VL_RAND_RESET_I(8);
    __Vcellinp__PGCD__a = VL_RAND_RESET_I(8);
    __Vcellinp__PGCD__valid = VL_RAND_RESET_I(1);
    __Vcellinp__PGCD__clk = VL_RAND_RESET_I(1);
    PGCD__DOT__max = VL_RAND_RESET_I(8);
    PGCD__DOT__min = VL_RAND_RESET_I(8);
    PGCD__DOT__d = VL_RAND_RESET_I(8);
}
