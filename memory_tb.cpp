#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>
#include "memory_tb.h"

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

template<unsigned int NO_OF_TARGETS>
tb_mem<NO_OF_TARGETS>::tb_mem(sc_module_name tb):target_socket("Target Socket")
{
  target_socket.register_b_transport(this, &tb_mem::b_transport);

  char label[20];


  for(unsigned int i=0; i<NO_OF_TARGETS; i++)
  {
       sprintf(label, "Socket_%d", i);
    initiator_socket[i] = new tlm_utils::simple_initiator_socket_tagged<tb_mem>(label);
  }


}
template<unsigned int NO_OF_TARGETS>
void tb_mem<NO_OF_TARGETS>::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
  sc_dt::uint64 address = trans.get_address();

  unsigned int target_number;

  if (address >= 0 && address <= 127)
    target_number = 0;
  else if (address >= 128 && address <= 255)
    target_number = 1;

  cout<< "At Interconnect " << address << " ### " << endl;
  cout<< "Target Number " << target_number << " ### " << endl;
  cout << "Data Frame " << trans.get_data_ptr() << endl;
  (*initiator_socket[target_number]) -> b_transport(trans,delay);
}


















































/*void tb_mem::test_memory()

{
  int i;
	cout << "\n\n    @" << sc_time_stamp() <<" Starting Simulation\n" << endl;
  // Clock Check
  for (i=0; i<1; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }

  cout << "\n\n     Asserting Reset\n" << endl;
  for (i=0; i<1; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    rst = 1;      // Assert the reset
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }


  cout << "\n\n     De-Asserting Reset\n" << endl;
  for (i=0; i<1; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    rst = 0;    // De-assert the reset
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }

  cout << "\n\n     Asserting Read Enable\n" << endl;
  for (i=0; i<1; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    rden= 1;     // Assert Read enable
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }


  cout << "\n\n     De-Asserting read Enable\n" << endl;
  for (i=0; i<2; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    rden = 0;      // De-Assert read enable
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }

  cout << "\n\n    Assert Write Enable\n" << endl;
  for (i=0; i<1; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    wten= 1;	// Assert write enable
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }

  cout << "\n\n     De-Asserting write Enable\n" << endl;
  for (i=0; i<2; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    wten = 0;      // De-Assert enable
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }

  cout << "\n\n     Writing in address 0 \n" << endl;
  for (i=0; i<1; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_PS));
    wten = 1;            // Assert write
    rden=0;              // De Assert read
    addr->write(0);      // Address 0
    datain->write('S');  // Input Data s
    clk=1;
    sc_start(sc_time(1,SC_PS));
  }

  cout << "\n\n     Reading in address 0 \n" << endl;
  for (i=0; i<2; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_PS));
    clk=1;
    wten = 0;	// De-Assert write
    rden=1;      //Assert Read
    addr->write(0);    // Reading Address 0
    char data0=dataout->read();
    cout<<data0<<endl;
    sc_start(sc_time(1,SC_PS));
  }

  cout << "\n\n     Writing in address 2 \n" << endl;
  for (i=0; i<1; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    wten = 1;            // Assert write
    rden=0;              // De Assert read
    addr->write(2);      // Address 2
    datain->write('A');  // Input Data A
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }

  cout << "\n\n     Reading:1\n" << endl;
  for (i=0; i<2; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    wten = 0;	// De-Assert write
    rden=1;      //Assert Read
    addr->write(2);	// Reading Address 2
    char data2=dataout->read();
    cout<<data2<<endl;
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }

  cout << "\n\n     Writing in address 4\n" << endl;
  for (i=0; i<1; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    wten = 1;            // Assert write
    rden=0;              // De Assert read
    addr->write(4);      // Address 4
    datain->write('F');  // Input Data F
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }

  cout << "\n\n     Reading in address 4\n" << endl;
  for (i=0; i<2; i++)
  {
    clk=0;
    sc_start(sc_time(1,SC_NS));
    wten = 0;	// De-Assert write
    rden=1;      //Assert Read
    addr->write(4);      // Reading Address 4
    char data4=dataout->read();
    cout<<data4<<endl;
    clk=1;
    sc_start(sc_time(1,SC_NS));
  }

  cout << "\n\n    @" << sc_time_stamp() <<" Terminating Simulation\n" << endl;
  }
*/
