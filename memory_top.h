#ifndef MEMORY_TOP_H
#define MEMORY_TOP_H
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

//#include "memory_tb.h"
#include "memory.h"
#include "memory_tb.cpp"
using namespace sc_core;
using namespace std;
using namespace sc_dt;

SC_MODULE(top_mem)
{
public:
    Initiator* bus;
    Target* memory[2];
    tb_mem<2>* tb;

    //SC_HAS_PROCESS(top_mem);
    SC_CTOR(top_mem);
};
#endif
























/*
sc_signal<bool> rst_sig;
sc_fifo<int> addr_sig;
sc_fifo<char> datain_sig;
sc_fifo<char> dataout_sig;
sc_signal<bool> rden_sig;
sc_signal<bool> wten_sig;
SC_CTOR(top_mem);
*/
