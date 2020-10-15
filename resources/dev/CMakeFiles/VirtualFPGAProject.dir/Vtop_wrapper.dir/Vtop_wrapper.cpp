// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_wrapper.h for the primary calling header

#include "Vtop_wrapper.h"
#include "Vtop_wrapper__Syms.h"

//==========

void Vtop_wrapper::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtop_wrapper::eval\n"); );
    Vtop_wrapper__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("top_wrapper.v", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vtop_wrapper::_eval_initial_loop(Vtop_wrapper__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("top_wrapper.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vtop_wrapper::_sequent__TOP__1(Vtop_wrapper__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_sequent__TOP__1\n"); );
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top_wrapper__DOT__top__DOT__cnt = vlTOPp->top_wrapper__DOT__top__DOT__cntNext;
    vlTOPp->top_wrapper__DOT__top__DOT__timer = vlTOPp->top_wrapper__DOT__top__DOT__timerNext;
    vlTOPp->led = vlTOPp->top_wrapper__DOT__top__DOT__cnt;
}

VL_INLINE_OPT void Vtop_wrapper::_combo__TOP__3(Vtop_wrapper__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_combo__TOP__3\n"); );
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top_wrapper__DOT__top__DOT__cntNext = vlTOPp->top_wrapper__DOT__top__DOT__cnt;
    vlTOPp->top_wrapper__DOT__top__DOT__timerNext = 
        (0x3fU & ((IData)(1U) + (IData)(vlTOPp->top_wrapper__DOT__top__DOT__timer)));
    if ((1U & (IData)(vlTOPp->btn))) {
        vlTOPp->top_wrapper__DOT__top__DOT__cntNext = 0U;
        vlTOPp->top_wrapper__DOT__top__DOT__timerNext = 0U;
    } else {
        if ((0U == (IData)(vlTOPp->top_wrapper__DOT__top__DOT__timer))) {
            vlTOPp->top_wrapper__DOT__top__DOT__cntNext 
                = (0xfU & ((1U & (IData)(vlTOPp->sw))
                            ? ((9U == (IData)(vlTOPp->top_wrapper__DOT__top__DOT__cnt))
                                ? 0U : ((IData)(1U) 
                                        + (IData)(vlTOPp->top_wrapper__DOT__top__DOT__cnt)))
                            : ((0U == (IData)(vlTOPp->top_wrapper__DOT__top__DOT__cnt))
                                ? 9U : ((IData)(vlTOPp->top_wrapper__DOT__top__DOT__cnt) 
                                        - (IData)(1U)))));
        }
    }
    vlTOPp->__Vtableidx1 = (((IData)(vlTOPp->top_wrapper__DOT__top__DOT__cnt) 
                             << 1U) | (1U & (IData)(vlTOPp->btn)));
    vlTOPp->an = vlTOPp->__Vtable1_an[vlTOPp->__Vtableidx1];
    vlTOPp->seg = vlTOPp->__Vtable1_seg[vlTOPp->__Vtableidx1];
}

void Vtop_wrapper::_eval(Vtop_wrapper__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_eval\n"); );
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    vlTOPp->_combo__TOP__3(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

VL_INLINE_OPT QData Vtop_wrapper::_change_request(Vtop_wrapper__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_change_request\n"); );
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vtop_wrapper::_change_request_1(Vtop_wrapper__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_change_request_1\n"); );
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vtop_wrapper::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((btn & 0xf0U))) {
        Verilated::overWidthError("btn");}
}
#endif  // VL_DEBUG
