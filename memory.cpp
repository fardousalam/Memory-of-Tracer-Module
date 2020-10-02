#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "memory.h"

using namespace sc_core;
using namespace std;
using namespace sc_dt;

void Initiator::thread_process()
{
  // TLM-2 generic payload transaction, reused across calls to b_transport
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);

  // Generate a random sequence of reads and writes
  for (int i = 32; i < 196; i += 4)
  {
    tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
    if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;
    // Initialize 8 out of the 10 attributes, byte_enable_length and extensions being unused
    trans->set_command(cmd);
    trans->set_address(i);
    trans->set_data_ptr(reinterpret_cast<unsigned char*>(&data));
    trans->set_data_length(4);
    trans->set_streaming_width(4); // = data_length to indicate no streaming
    trans->set_byte_enable_ptr(0); // 0 indicates unused
    trans->set_dmi_allowed(false); // Mandatory initial value
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE); // Mandatory initial value

    socket->b_transport(*trans, delay);  // Blocking transport call

    if (trans->is_response_error())
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
    else
    cout << "trans = { " << (cmd ? 'W' : 'R') << ", " << hex << i
         << " } , data = " << hex << data << " at time " << sc_time_stamp()
         << " delay = " << delay << endl;
    // Realize the delay annotated onto the transport call
    wait(delay);
  }
}

void Target::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address()/4;
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  // Obliged to check address range and check for unsupported features,
  //   i.e. byte enables, streaming, and bursts
  // Can ignore DMI hint and extensions
  // Using the SystemC report handler is an acceptable way of signalling an error

  if (adr >= sc_dt::uint64(SIZE) || byt != 0 || len > 4 || wid < len)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

  // Obliged to implement read and write commands
  if (cmd == tlm::TLM_READ_COMMAND)
    memcpy(ptr, &mem[adr], len);
  else if (cmd == tlm::TLM_WRITE_COMMAND)
    memcpy(&mem[adr], ptr, len);

  // Obliged to set response status to indicate successful completion
  trans.set_response_status(tlm::TLM_OK_RESPONSE);
}















































/*
void mem::initread()
{
  bool rd=rden.read();
  while(rd)
  {
    unsigned char initrddata=mem_size[0];
    dataout->write(initrddata);
    cout<<"\n@initreadThread : "<<sc_time_stamp()
    <<"Memory read from intial address"<<endl;
    cout<<"Data : "<<(char)initrddata<<endl;
  }
}

void mem::initwrite()
{
  bool wt=wten.read();
  while(wt)
  {
    unsigned char initwtdata=datain->read();
    mem_size[0]=(int)initwtdata;
    cout<<"\n@initwriteThread : "<<sc_time_stamp()
    <<"\nMemory Written to initial address"<<endl;
  }
}

void mem::memwrite()
{
  bool reset=rst.read();
  bool rd=rden.read();
  bool wt=wten.read();
  int address=addr->read();
  char indata=datain->read();

  while(rd=!1)
  {
  if(reset==1&&wt==1)
  {
    cout<<"\nReset in progress... Memory cannot be written to, access denied!";
  }
  else if(reset==0&&wt==1)
  {
    if(address<=SIZE)
    {
      mem_size[address]=(int)indata;
    }
    else cout<<"Memory location out of bound. Please enter valid address within 0 to 255";
  }
  else if (wt==0)
  {
    cout<<"\nMemory Write prohibited!";
  }
  }
}


void mem::memread()
{
  bool reset=rst.read();
  bool rd=rden.read();
  bool wt=wten.read();
  int address=addr->read();
  unsigned char outdata;

  while(wt=!1)
  {
  if(reset=1&&rd==1)
  {
    outdata=(char)(mem_size[address]);
  }
  else if(reset==0&&rd==1)
  {
    cout<<"\nReset in progress... Memory reset to base address";
    outdata=(char)mem_size[0];
  }
  else if(rd==0)
  {
    cout<<"\nMemory Read prohibited!";
  }
  dataout->write(outdata);
  }
}
*/
