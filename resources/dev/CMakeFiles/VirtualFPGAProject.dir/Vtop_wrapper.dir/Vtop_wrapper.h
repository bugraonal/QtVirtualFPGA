// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VTOP_WRAPPER_H_
#define _VTOP_WRAPPER_H_  // guard

#include "verilated.h"

//==========

class Vtop_wrapper__Syms;

//----------

VL_MODULE(Vtop_wrapper) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(sw,7,0);
    VL_IN8(btn,3,0);
    VL_OUT8(led,7,0);
    VL_OUT8(seg,7,0);
    VL_OUT8(an,3,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*3:0*/ top_wrapper__DOT__top__DOT__cnt;
    CData/*3:0*/ top_wrapper__DOT__top__DOT__cntNext;
    CData/*5:0*/ top_wrapper__DOT__top__DOT__timer;
    CData/*5:0*/ top_wrapper__DOT__top__DOT__timerNext;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*4:0*/ __Vtableidx1;
    CData/*0:0*/ __Vclklast__TOP__clk;
    static CData/*3:0*/ __Vtable1_an[32];
    static CData/*7:0*/ __Vtable1_seg[32];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop_wrapper__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop_wrapper);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vtop_wrapper(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop_wrapper();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vtop_wrapper__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vtop_wrapper__Syms* symsp, bool first);
  private:
    static QData _change_request(Vtop_wrapper__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vtop_wrapper__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__3(Vtop_wrapper__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vtop_wrapper__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vtop_wrapper__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vtop_wrapper__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__1(Vtop_wrapper__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vtop_wrapper__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
