#include <verilated.h>
#include "Vtop_wrapper.h"
#include <iostream>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <sstream>
#include <ostream>
#include <chrono>
#include <thread>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "UDPClient.hpp"

using boost::asio::ip::udp;

vluint64_t main_time = 0;
UDPClient *client;

void printLeds(vluint8_t dataOut) {
    for (int i = 0; i < 8; i++) {
        if (dataOut & 0x80)
            std::cout << "[*]";
        else 
            std::cout << "[-]";
        dataOut = dataOut << 1;
    }
    std::cout << std::endl;
}

void printData(vluint8_t ledOut, vluint8_t digitOut, vluint8_t anode) {
    printf("%d %d %d", ledOut, digitOut, anode);
}

int main(int argc, char ** argv) {
    // Initial verilator commands
    Verilated::debug(0);
    Verilated::randReset(2);
    Verilated::traceEverOn(true);
    Verilated::commandArgs(argc, argv);
    
    // Boost network 
    boost::asio::io_service io_service;
    client = new UDPClient(io_service, "localhost", "7755");

    // Pointer to verilog top module
    auto *top = new Vtop_wrapper();
    // Initialize inputs
    top->clk = 0;
    top->rst = 0;
    std::cout << "IT: " << IT_PER_CYCLE << " DLY: " << SIM_DELAY << std::endl;  
    // Wait for UI to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
 // Simulation steps
    while (!Verilated::gotFinish()) {
        // Increment time
        main_time++;
    
        // Toggle clk
        if ((main_time % IT_PER_CYCLE/2) == 1) {
            top->clk = !top->clk;
        }

        // Reset
        if (main_time > 1 && main_time < 40) {
            top->rst = 1;
        }
        else {
            top->rst = 0;
        }
        std::stringstream ss;
        char msg[10];        
        sprintf(msg, "%d %d %d", top->led, top->seg, top->an);
        std::string msg_str(msg);
        std::cout << "Model: Message " << msg_str << " sent" << std::endl;
        client->send(msg_str);
        if (main_time > 50) {
            auto recv_data = client->recv();
            std::cout << "Model: Message " << recv_data << " received" << std::endl;
            ss.str(recv_data);
            std::string btn_string, sw_string;
            ss >> btn_string >> sw_string;
            top->btn = stoi(btn_string);
            top->sw = stoi(sw_string);
        }

        top->eval();
        std::this_thread::sleep_for(std::chrono::milliseconds(SIM_DELAY));
    }

    top->final();
    return 0;

}
