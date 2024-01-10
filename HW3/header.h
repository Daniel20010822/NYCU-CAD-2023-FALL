#ifndef HEADER_H
#define HEADER_H

#include <bits/stdc++.h>
using namespace std;

// Define class first for later use!!!
class Cell;
class Wire;
class Netlist;
class Liberty;

//  #####    #####   ##   ##   #####    ######       ##  ##   ##   ######   #####
// #######  #######  ##   ##  #######   ######      ###  ##   ##   ######  #######
// ##       ##   ##  ##   ##  ##          ##          #  ###  ##     ##    ##
// ##       ##   ##  ## # ##  ######      ##       ####  ## # ##     ##    ######
// ##       ##   ##  ##  ###       ##     ##      #####  ##  ###     ##         ##
// #######  #######  ##   ##  #######     ##     ##  ##  ##   ##     ##    #######
//  #####    #####   ##   ##   #####      ##    ##   ##  ##   ##     ##     #####

const int TABLE_SIZE = 7;


vector<double> total_output_net_capacitance;
vector<double> input_transition_time;

double NOR2X1_A1_capacitance;
double NOR2X1_A2_capacitance;
vector<vector<double>> NOR2X1_rise_power;
vector<vector<double>> NOR2X1_fall_power;
vector<vector<double>> NOR2X1_cell_rise;
vector<vector<double>> NOR2X1_cell_fall;
vector<vector<double>> NOR2X1_rise_transition;
vector<vector<double>> NOR2X1_fall_transition;

double INVX1_I_capacitance;
vector<vector<double>> INVX1_rise_power;
vector<vector<double>> INVX1_fall_power;
vector<vector<double>> INVX1_cell_rise;
vector<vector<double>> INVX1_cell_fall;
vector<vector<double>> INVX1_rise_transition;
vector<vector<double>> INVX1_fall_transition;

double NANDX1_A1_capacitance;
double NANDX1_A2_capacitance;
vector<vector<double>> NANDX1_rise_power;
vector<vector<double>> NANDX1_fall_power;
vector<vector<double>> NANDX1_cell_rise;
vector<vector<double>> NANDX1_cell_fall;
vector<vector<double>> NANDX1_rise_transition;
vector<vector<double>> NANDX1_fall_transition;




const int CELL_ND     = 0;
const int CELL_NOR2X1 = 1;
const int CELL_INVX1  = 2;
const int CELL_NANDX1 = 3;
const int WIRE_ND  = 0;
const int WIRE_IN  = 1;
const int WIRE_OUT = 2;
const int WIRE_W   = 3;
const int DELAY_ND   = -1;
const int DELAY_FALL = 0;
const int DELAY_RISE = 1;
const double OUTPUT_CAPACITANCE = 0.03;
const double WIRE_DELAY = 0;
const double VOLTAGE = 0.9;





// #######  ##   ##  ##   ##   #####
// #######  ##   ##  ##   ##  #######
// ##       ##   ##  ###  ##  ##
// #####    ##   ##  ## # ##  ##
// ##       ##   ##  ##  ###  ##
// ##       #######  ##   ##  #######
// ##        #####   ##   ##   #####

/* Print queue */
void print_queue(queue<Cell*> q);

/* String Operations */
bool found_str(string, string);
vector<string> split_str_by_comma(string);

/* Print Table Functions */
void print_table(vector<vector<double>>);
void print_NOR2X1_rise_power();
void print_NOR2X1_fall_power();
void print_NOR2X1_cell_rise();
void print_NOR2X1_cell_fall();
void print_NOR2X1_rise_transition();
void print_NOR2X1_fall_transition();
void print_INVX1_rise_power();
void print_INVX1_fall_power();
void print_INVX1_cell_rise();
void print_INVX1_cell_fall();
void print_INVX1_rise_transition();
void print_INVX1_fall_transition();
void print_NANDX1_rise_power();
void print_NANDX1_fall_power();
void print_NANDX1_cell_rise();
void print_NANDX1_cell_fall();
void print_NANDX1_rise_transition();
void print_NANDX1_fall_transition();

/* Compare Functions */
bool sort_by_instance_name(Cell* cell_a, Cell* cell_b);
bool sort_by_capacitance(Cell* cell_a, Cell* cell_b);
bool sort_by_delay(Cell* cell_a, Cell* cell_b);







//  #####   ##            ##   #####    #####
// #######  ##           ###  #######  #######
// ##       ##           # #  ##       ##
// ##       ##          ####  ######   ######
// ##       ##         #####       ##       ##
// #######  #######   ##  ##  #######  #######
//  #####   #######  ##   ##   #####    #####

class Wire{
public:
    /* Attributes */
    string wire_name;
    Cell *prev_cell = nullptr;
    vector<Cell*> next_cells;
    int wire_type = WIRE_ND; // 0: ND, 1:Input, 2:Output, 3:Wire
    bool isInput = false;
    bool isOutput = false;
    bool logic_value = false;

    /* Methods */
    Wire(string name, int type);
    void print_wire_info();
};


class Cell{
public:
    /* Attributes */
    string instance_name;
    Wire *ZN = nullptr;
    Wire *A1 = nullptr;
    Wire *A2 = nullptr; // INVX1 will be NULL
    int cell_type = CELL_ND;
    // OUTPUT LOAD
    double output_capacitance = 0;
    // OUTPUT DELAY
    double output_transition = 0;
    double delay = 0;
    double total_delay = 0;
    int rise_or_fall = DELAY_ND; // 1:rise, 0:fall
    // OUTPUT POWER
    double internel_power = 0;
    double switching_power = 0;
    // TOGGLE COUNT
    int toggle_0to1 = 0;
    int toggle_1to0 = 0;

    bool updated = false; // Used in cell_queue



    Cell(string name, int type, Wire *PIN_ZN, Wire *PIN_A1, Wire *PIN_A2);

    /* Methods */
    void reset_cell();
    void update_cell_delay_transition(); // HW2
    void update_cell_by_logic_value(unordered_map<string, bool>& pattern, double& total_power);
    double interpolation(const vector<vector<double>>&, double&, double&);
    void print_cell_info();
};


class Netlist{
private:
    vector<Cell*> cell_list;
    vector<Wire*> wire_list;
    vector<string> PI_name;
    vector<string> PO_name;
    unordered_map<string, Wire*> wire_lut; // Cheatsheet
    unordered_map<string, vector<bool>> input_patterns;
    vector<Wire*> longest_path;
    vector<Wire*> shortest_path;
    double total_power = 0;

    string load_txt;
    string gate_info_txt;
    string gate_power_txt;
    string converage_txt;
public:
    int PAT_NUM = 0;
    Netlist(ifstream&);
    void parse_cell(string);
    void parse_wire(string);
    void calculate_output_capacitance();
    void calculate_delay(int pat);
    void find_longest_path(Wire*&);
    void find_shortest_path(Wire*&);
    void read_input_pattern(ifstream&);

    // Print Functions
    void print_wire_lut();
    void print_PI_name();
    void print_PO_name();
    void print_all_cell();
    void print_all_wire();
    void print_all_patterns();

    // Write Results
    void write_result_load();
    void write_gate_info();
    void write_gate_power();
    void write_coverage(int);
    void write_output(ofstream&, ofstream&, ofstream&, ofstream&);

    void write_result_delay(ofstream&); // Previous HW
    void write_result_path(ofstream&); // Previous HW
};

class Liberty{
public:
    Liberty(ifstream&);
};

#endif