#ifndef MEMORY_TB_H
#define MEMORY_TB_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace std;
using namespace sc_dt;

template<unsigned int NO_OF_TARGETS>

SC_MODULE (tb_mem)
 {
public:
    tlm_utils::simple_target_socket<tb_mem> target_socket;
    tlm_utils::simple_initiator_socket_tagged<tb_mem>* initiator_socket[NO_OF_TARGETS];

    SC_HAS_PROCESS(tb_mem);
    tb_mem(sc_module_name nm);
    virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);
  };

#endif
/*
sc_out<bool> rst;
sc_out<bool> clk;

sc_port<sc_fifo_out_if<int> >addr;
sc_port<sc_fifo_out_if<char> >datain;
sc_port<sc_fifo_in_if<char> >dataout;

sc_out<bool> rden;
sc_out<bool> wten;




  sensitive<<rst<<clk<<rden<<wten;
  */
