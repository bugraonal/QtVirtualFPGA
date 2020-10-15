// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_wrapper.h for the primary calling header

#include "Vtop_wrapper.h"
#include "Vtop_wrapper__Syms.h"

//==========
CData/*3:0*/ Vtop_wrapper::__Vtable1_an[32];
CData/*7:0*/ Vtop_wrapper::__Vtable1_seg[32];

VL_CTOR_IMP(Vtop_wrapper) {
    Vtop_wrapper__Syms* __restrict vlSymsp = __VlSymsp = new Vtop_wrapper__Syms(this, name());
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vtop_wrapper::__Vconfigure(Vtop_wrapper__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vtop_wrapper::~Vtop_wrapper() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = nullptr);
}

void Vtop_wrapper::_settle__TOP__2(Vtop_wrapper__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_settle__TOP__2\n"); );
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->led = vlTOPp->top_wrapper__DOT__top__DOT__cnt;
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

void Vtop_wrapper::_eval_initial(Vtop_wrapper__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_eval_initial\n"); );
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vtop_wrapper::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::final\n"); );
    // Variables
    Vtop_wrapper__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vtop_wrapper::_eval_settle(Vtop_wrapper__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_eval_settle\n"); );
    Vtop_wrapper* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void Vtop_wrapper::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_wrapper::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    sw = VL_RAND_RESET_I(8);
    btn = VL_RAND_RESET_I(4);
    led = VL_RAND_RESET_I(8);
    seg = VL_RAND_RESET_I(8);
    an = VL_RAND_RESET_I(4);
    top_wrapper__DOT__top__DOT__cnt = VL_RAND_RESET_I(4);
    top_wrapper__DOT__top__DOT__cntNext = VL_RAND_RESET_I(4);
    top_wrapper__DOT__top__DOT__timer = VL_RAND_RESET_I(6);
    top_wrapper__DOT__top__DOT__timerNext = VL_RAND_RESET_I(6);
    __Vtableidx1 = 0;
    __Vtable1_an[0] = 7U;
    __Vtable1_an[1] = 7U;
    __Vtable1_an[2] = 7U;
    __Vtable1_an[3] = 7U;
    __Vtable1_an[4] = 7U;
    __Vtable1_an[5] = 7U;
    __Vtable1_an[6] = 7U;
    __Vtable1_an[7] = 7U;
    __Vtable1_an[8] = 7U;
    __Vtable1_an[9] = 7U;
    __Vtable1_an[10] = 7U;
    __Vtable1_an[11] = 7U;
    __Vtable1_an[12] = 7U;
    __Vtable1_an[13] = 7U;
    __Vtable1_an[14] = 7U;
    __Vtable1_an[15] = 7U;
    __Vtable1_an[16] = 7U;
    __Vtable1_an[17] = 7U;
    __Vtable1_an[18] = 7U;
    __Vtable1_an[19] = 7U;
    __Vtable1_an[20] = 7U;
    __Vtable1_an[21] = 7U;
    __Vtable1_an[22] = 7U;
    __Vtable1_an[23] = 7U;
    __Vtable1_an[24] = 7U;
    __Vtable1_an[25] = 7U;
    __Vtable1_an[26] = 7U;
    __Vtable1_an[27] = 7U;
    __Vtable1_an[28] = 7U;
    __Vtable1_an[29] = 7U;
    __Vtable1_an[30] = 7U;
    __Vtable1_an[31] = 7U;
    __Vtable1_seg[0] = 0xc0U;
    __Vtable1_seg[1] = 0xffU;
    __Vtable1_seg[2] = 0xf9U;
    __Vtable1_seg[3] = 0xffU;
    __Vtable1_seg[4] = 0xa4U;
    __Vtable1_seg[5] = 0xffU;
    __Vtable1_seg[6] = 0xb0U;
    __Vtable1_seg[7] = 0xffU;
    __Vtable1_seg[8] = 0x99U;
    __Vtable1_seg[9] = 0xffU;
    __Vtable1_seg[10] = 0x92U;
    __Vtable1_seg[11] = 0xffU;
    __Vtable1_seg[12] = 0x82U;
    __Vtable1_seg[13] = 0xffU;
    __Vtable1_seg[14] = 0xf8U;
    __Vtable1_seg[15] = 0xffU;
    __Vtable1_seg[16] = 0x80U;
    __Vtable1_seg[17] = 0xffU;
    __Vtable1_seg[18] = 0x90U;
    __Vtable1_seg[19] = 0xffU;
    __Vtable1_seg[20] = 0xc0U;
    __Vtable1_seg[21] = 0xffU;
    __Vtable1_seg[22] = 0xc0U;
    __Vtable1_seg[23] = 0xffU;
    __Vtable1_seg[24] = 0xc0U;
    __Vtable1_seg[25] = 0xffU;
    __Vtable1_seg[26] = 0xc0U;
    __Vtable1_seg[27] = 0xffU;
    __Vtable1_seg[28] = 0xc0U;
    __Vtable1_seg[29] = 0xffU;
    __Vtable1_seg[30] = 0xc0U;
    __Vtable1_seg[31] = 0xffU;
}
