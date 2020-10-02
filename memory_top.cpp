#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "memory_top.h"


using namespace sc_core;
using namespace std;
using namespace sc_dt;

top_mem::top_mem(sc_module_name tm):sc_module(tm)
{
  // Instantiate components
  bus = new Initiator("Bus_Initiator");
  memory[0] = new Target("Target_ROM");
  memory[1] = new Target("Target_RAM");
  tb = new tb_mem<2>("TESTBENCH");
  bus -> socket.bind(tb->target_socket);
  tb -> initiator_socket[0] -> bind(memory[0]->socket);
  tb -> initiator_socket[1] -> bind(memory[1]->socket);

  // One initiator is bound directly to one target
  // Bind initiator socket to target socket
}


































/*{

    tb=new tb_mem("TESTBENCH");

    tb -> clk(clk_sig);
    tb -> rst(rst_sig);
    tb -> addr(addr_sig);
    tb -> datain(datain_sig);
    tb -> dataout(dataout_sig);
    tb -> rden(rden_sig);
    tb -> wten(wten_sig);

    xram=new mem("RAM");
    xram-> clk(clk_sig);
    xram-> rst(rst_sig);
    xram-> addr(addr_sig);
    xram-> datain(datain_sig);
    xram-> dataout(dataout_sig);
    xram-> rden(rden_sig);
    xram-> wten(wten_sig);

    xrom=new mem("ROM");
    xrom-> clk(clk_sig);
    xrom-> rst(rst_sig);
    xrom-> addr(addr_sig);
    xrom-> datain(datain_sig);
    xrom-> dataout(dataout_sig);
    xrom-> rden(rden_sig);
    xrom-> wten(wten_sig);

}
*/
