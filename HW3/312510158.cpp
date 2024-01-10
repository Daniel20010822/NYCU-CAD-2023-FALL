#include "header.h"
#include <bits/stdc++.h>
using namespace std;


// #######  ##   ##  ##   ##   #####
// #######  ##   ##  ##   ##  #######
// ##       ##   ##  ###  ##  ##
// #####    ##   ##  ## # ##  ##
// ##       ##   ##  ##  ###  ##
// ##       #######  ##   ##  #######
// ##        #####   ##   ##   #####

void print_queue(queue<Cell*> q) {
    while (!q.empty()) {
        Cell* qf = q.front();
        cout << qf->instance_name << " ";
        q.pop();
    }
    cout << endl;
}

/* String Operations */
bool found_str(string line, string target) {
    return line.find(target) != string::npos;
}

vector<string> split_str_by_comma(string line){
    vector<string> result;
    stringstream ss(line);

    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        result.push_back(substr);
    }

    return result;
}

/* Compare functions */
bool sort_by_instance_name(Cell* cell_a, Cell* cell_b){
    string inst_num_a, inst_num_b;
    for (const char character: cell_a->instance_name) if ('0' <= character && character <= '9') inst_num_a.push_back(character);
    for (const char character: cell_b->instance_name) if ('0' <= character && character <= '9') inst_num_b.push_back(character);
    return stoi(inst_num_a) < stoi(inst_num_b);
}

bool sort_by_capacitance(Cell* cell_a, Cell* cell_b){
    if (cell_a->output_capacitance > cell_b->output_capacitance)  return true;
    else if (cell_a->output_capacitance == cell_b->output_capacitance){
        string inst_num_a, inst_num_b;
        for (const char character: cell_a->instance_name) if ('0' <= character && character <= '9') inst_num_a.push_back(character);
        for (const char character: cell_b->instance_name) if ('0' <= character && character <= '9') inst_num_b.push_back(character);
        return stoi(inst_num_a) < stoi(inst_num_b);
    }
    return false;
}

bool sort_by_delay(Cell* cell_a, Cell* cell_b){
    if (cell_a->delay > cell_b->delay)  return true;
    else if (cell_a->delay == cell_b->delay){
        string inst_num_a, inst_num_b;
        for (const char character: cell_a->instance_name) if ('0' <= character && character <= '9') inst_num_a.push_back(character);
        for (const char character: cell_b->instance_name) if ('0' <= character && character <= '9') inst_num_b.push_back(character);
        return stoi(inst_num_a) < stoi(inst_num_b);
    }
    return false;
}

void print_NOR2X1_rise_power()      { cout << endl << "NOR2X1_rise_power:"      << endl; print_table(NOR2X1_rise_power); }
void print_NOR2X1_fall_power()      { cout << endl << "NOR2X1_fall_power:"      << endl; print_table(NOR2X1_fall_power); }
void print_NOR2X1_cell_fall()       { cout << endl << "NOR2X1_cell_fall:"       << endl; print_table(NOR2X1_cell_fall); }
void print_NOR2X1_cell_rise()       { cout << endl << "NOR2X1_cell_rise:"       << endl; print_table(NOR2X1_cell_rise); }
void print_NOR2X1_rise_transition() { cout << endl << "NOR2X1_rise_transition:" << endl; print_table(NOR2X1_rise_transition); }
void print_NOR2X1_fall_transition() { cout << endl << "NOR2X1_fall_transition:" << endl; print_table(NOR2X1_fall_transition); }
void print_INVX1_rise_power()       { cout << endl << "INVX1_rise_power:"       << endl; print_table(INVX1_rise_power); }
void print_INVX1_fall_power()       { cout << endl << "INVX1_fall_power:"       << endl; print_table(INVX1_fall_power); }
void print_INVX1_cell_rise()        { cout << endl << "INVX1_cell_rise:"        << endl; print_table(INVX1_cell_rise); }
void print_INVX1_cell_fall()        { cout << endl << "INVX1_cell_fall:"        << endl; print_table(INVX1_cell_fall); }
void print_INVX1_rise_transition()  { cout << endl << "INVX1_rise_transition:"  << endl; print_table(INVX1_rise_transition); }
void print_INVX1_fall_transition()  { cout << endl << "INVX1_fall_transition:"  << endl; print_table(INVX1_fall_transition); }
void print_NANDX1_rise_power()      { cout << endl << "NANDX1_rise_power:"      << endl; print_table(NANDX1_rise_power); }
void print_NANDX1_fall_power()      { cout << endl << "NANDX1_fall_power:"      << endl; print_table(NANDX1_fall_power); }
void print_NANDX1_cell_rise()       { cout << endl << "NANDX1_cell_rise:"       << endl; print_table(NANDX1_cell_rise); }
void print_NANDX1_cell_fall()       { cout << endl << "NANDX1_cell_fall:"       << endl; print_table(NANDX1_cell_fall); }
void print_NANDX1_rise_transition() { cout << endl << "NANDX1_rise_transition:" << endl; print_table(NANDX1_rise_transition); }
void print_NANDX1_fall_transition() { cout << endl << "NANDX1_fall_transition:" << endl; print_table(NANDX1_fall_transition); }

/* Print Table Functions*/
void print_table(vector<vector<double>> table){
    // First row
    cout << endl;
    for (int i = 0; i < TABLE_SIZE + 1; i++){
        if (i == 0) cout << setw(10) << " " << left;
        else        cout << setw(10) << total_output_net_capacitance[i-1] << left;
    }
    cout << endl;
    for (int i = 0; i < TABLE_SIZE + 1; i++){
        cout << "----------";
    }
    cout << endl;

    // The rest
    for (int i = 0; i < TABLE_SIZE; i++){
        cout << setw(7) << input_transition_time[i] << left << setw(3) << "|" << left;
        for (int j = 0; j < TABLE_SIZE; j++)
            cout << setw(10) << table[i][j] << left;
        cout << endl;
    }
    cout << endl;
}

//  #####   #######  ##       ##
// #######  #######  ##       ##
// ##       ##       ##       ##
// ##       ####     ##       ##
// ##       ##       ##       ##
// #######  #######  #######  #######
//  #####   #######  #######  #######

Cell::Cell(string name, int type, Wire *PIN_ZN, Wire *PIN_A1, Wire *PIN_A2){
    instance_name = name;
    cell_type = type;
    ZN = PIN_ZN;
    A1 = PIN_A1;
    A2 = PIN_A2;
}

void Cell::reset_cell(){
    // Delay type
    output_transition = 0;
    delay = 0;
    total_delay = 0;
    rise_or_fall = DELAY_ND;
    // Power type
    internel_power = 0;
    switching_power = 0;
    // Update type
    updated = false;
}

void Cell::update_cell_delay_transition(){
    double total_delay_from_A1 = 0;
    double input_transition_A1 = 0;
    if (A1->prev_cell){
        total_delay_from_A1 = A1->prev_cell->total_delay;
        input_transition_A1 = A1->prev_cell->output_transition;
    }
    double total_delay_from_A2 = 0;
    double input_transition_A2 = 0;
    if (cell_type != CELL_INVX1) {
        if (A2->prev_cell){
            total_delay_from_A2 = A2->prev_cell->total_delay;
            input_transition_A2 = A2->prev_cell->output_transition;
        }
    }


    if (cell_type == CELL_NOR2X1){
        double delay_rise_A1      = interpolation(NOR2X1_cell_rise, input_transition_A1, output_capacitance);
        double delay_fall_A1      = interpolation(NOR2X1_cell_fall, input_transition_A1, output_capacitance);
        double transition_rise_A1 = interpolation(NOR2X1_rise_transition, input_transition_A1, output_capacitance);
        double transition_fall_A1 = interpolation(NOR2X1_fall_transition, input_transition_A1, output_capacitance);
        double delay_rise_A2      = interpolation(NOR2X1_cell_rise, input_transition_A2, output_capacitance);
        double delay_fall_A2      = interpolation(NOR2X1_cell_fall, input_transition_A2, output_capacitance);
        double transition_rise_A2 = interpolation(NOR2X1_rise_transition, input_transition_A2, output_capacitance);
        double transition_fall_A2 = interpolation(NOR2X1_fall_transition, input_transition_A2, output_capacitance);

        if (total_delay_from_A1 > total_delay_from_A2) {
            if (delay_rise_A1 > delay_fall_A1){
                rise_or_fall = DELAY_RISE;
                output_transition = transition_rise_A1;
                delay = delay_rise_A1;
                total_delay = total_delay_from_A1 + delay + WIRE_DELAY;
            }
            else {
                rise_or_fall = DELAY_FALL;
                output_transition = transition_fall_A1;
                delay = delay_fall_A1;
                total_delay = total_delay_from_A1 + delay + WIRE_DELAY;
            }
        }
        else {
            if (delay_rise_A2 > delay_fall_A2){
                rise_or_fall = DELAY_RISE;
                output_transition = transition_rise_A2;
                delay = delay_rise_A2;
                total_delay = total_delay_from_A2 + delay + WIRE_DELAY;
            }
            else {
                rise_or_fall = DELAY_FALL;
                output_transition = transition_fall_A2;
                delay = delay_fall_A2;
                total_delay = total_delay_from_A2 + delay + WIRE_DELAY;
            }
        }
    }
    else if (cell_type == CELL_INVX1){
        double delay_rise      = interpolation(INVX1_cell_rise, input_transition_A1, output_capacitance);
        double delay_fall      = interpolation(INVX1_cell_fall, input_transition_A1, output_capacitance);
        double transition_rise = interpolation(INVX1_rise_transition, input_transition_A1, output_capacitance);
        double transition_fall = interpolation(INVX1_fall_transition, input_transition_A1, output_capacitance);

        if (delay_rise > delay_fall){
            rise_or_fall = DELAY_RISE;
            output_transition = transition_rise;
            delay = delay_rise;
            total_delay = total_delay_from_A1 + delay + WIRE_DELAY;
        }
        else {
            rise_or_fall = DELAY_FALL;
            output_transition = transition_fall;
            delay = delay_fall;
            total_delay = total_delay_from_A1 + delay + WIRE_DELAY;
        }
    }
    else if (cell_type == CELL_NANDX1){
        double delay_rise_A1      = interpolation(NANDX1_cell_rise, input_transition_A1, output_capacitance);
        double delay_fall_A1      = interpolation(NANDX1_cell_fall, input_transition_A1, output_capacitance);
        double transition_rise_A1 = interpolation(NANDX1_rise_transition, input_transition_A1, output_capacitance);
        double transition_fall_A1 = interpolation(NANDX1_fall_transition, input_transition_A1, output_capacitance);
        double delay_rise_A2      = interpolation(NANDX1_cell_rise, input_transition_A2, output_capacitance);
        double delay_fall_A2      = interpolation(NANDX1_cell_fall, input_transition_A2, output_capacitance);
        double transition_rise_A2 = interpolation(NANDX1_rise_transition, input_transition_A2, output_capacitance);
        double transition_fall_A2 = interpolation(NANDX1_fall_transition, input_transition_A2, output_capacitance);

        if (total_delay_from_A1 > total_delay_from_A2) {
            if (delay_rise_A1 > delay_fall_A1){
                rise_or_fall = DELAY_RISE;
                output_transition = transition_rise_A1;
                delay = delay_rise_A1;
                total_delay = total_delay_from_A1 + delay + WIRE_DELAY;
            }
            else {
                rise_or_fall = DELAY_FALL;
                output_transition = transition_fall_A1;
                delay = delay_fall_A1;
                total_delay = total_delay_from_A1 + delay + WIRE_DELAY;
            }
        }
        else {
            if (delay_rise_A2 > delay_fall_A2){
                rise_or_fall = DELAY_RISE;
                output_transition = transition_rise_A2;
                delay = delay_rise_A2;
                total_delay = total_delay_from_A2 + delay + WIRE_DELAY;
            }
            else {
                rise_or_fall = DELAY_FALL;
                output_transition = transition_fall_A2;
                delay = delay_fall_A2;
                total_delay = total_delay_from_A2 + delay + WIRE_DELAY;
            }
        }
    }
}

void Cell::update_cell_by_logic_value(unordered_map<string, bool>& pattern, double& total_power){
    //===================================//
    // 1. Delay Initialize               //
    //===================================//
    double total_delay_from_A1 = 0;
    double input_transition_A1 = 0;
    if (A1->prev_cell){
        total_delay_from_A1 = A1->prev_cell->total_delay;
        input_transition_A1 = A1->prev_cell->output_transition;
    }
    double total_delay_from_A2 = 0;
    double input_transition_A2 = 0;
    if (cell_type != CELL_INVX1) {
        if (A2->prev_cell){
            total_delay_from_A2 = A2->prev_cell->total_delay;
            input_transition_A2 = A2->prev_cell->output_transition;
        }
    }


    //===================================//
    // 2. Logic Value Initialize         //
    //===================================//
    bool value_A1 = false;
    bool value_A2 = false;
    bool value_ZN = false;

    if (A1->isInput) value_A1 = pattern[A1->wire_name];
    else             value_A1 = A1->prev_cell->ZN->logic_value;

    if (cell_type != CELL_INVX1){
        if (A2->isInput) value_A2 = pattern[A2->wire_name];
        else             value_A2 = A2->prev_cell->ZN->logic_value;
    }

    //========================================//
    // 3. Update Datas and Evaluate Output    //
    //========================================//
    if (cell_type == CELL_NOR2X1){
        // NOR controlling value -> 1
        if (!value_A1 && !value_A2){
            value_ZN = true; // Use rise table

            // Latest non-controlling value (All non-c)
            if (total_delay_from_A1 > total_delay_from_A2){
                output_transition = interpolation(NOR2X1_rise_transition, input_transition_A1, output_capacitance);
                delay             = interpolation(NOR2X1_cell_rise      , input_transition_A1, output_capacitance);
                internel_power    = interpolation(NOR2X1_rise_power     , input_transition_A1, output_capacitance);
                total_delay       = total_delay_from_A1 + delay + WIRE_DELAY;
            }
            else {
                output_transition = interpolation(NOR2X1_rise_transition, input_transition_A2, output_capacitance);
                delay             = interpolation(NOR2X1_cell_rise      , input_transition_A2, output_capacitance);
                internel_power    = interpolation(NOR2X1_rise_power     , input_transition_A2, output_capacitance);
                total_delay       = total_delay_from_A2 + delay + WIRE_DELAY;
            }
        }
        else if (!value_A1 && value_A2){
            value_ZN = false; // Use fall table

            // Earliest controlling value (A2 c)
            output_transition = interpolation(NOR2X1_fall_transition, input_transition_A2, output_capacitance);
            delay             = interpolation(NOR2X1_cell_fall      , input_transition_A2, output_capacitance);
            internel_power    = interpolation(NOR2X1_fall_power     , input_transition_A2, output_capacitance);
            total_delay       = total_delay_from_A2 + delay + WIRE_DELAY;
        }
        else if (value_A1 && !value_A2){
            value_ZN = false; // Use fall table

            // Earliest controlling value (A1 c)
            output_transition = interpolation(NOR2X1_fall_transition, input_transition_A1, output_capacitance);
            delay             = interpolation(NOR2X1_cell_fall      , input_transition_A1, output_capacitance);
            internel_power    = interpolation(NOR2X1_fall_power     , input_transition_A1, output_capacitance);
            total_delay       = total_delay_from_A1 + delay + WIRE_DELAY;
        }
        else {
            value_ZN = false; // Use fall table

            // Earliest controlling value (All c)
            if (total_delay_from_A1 < total_delay_from_A2){
                output_transition = interpolation(NOR2X1_fall_transition, input_transition_A1, output_capacitance);
                delay             = interpolation(NOR2X1_cell_fall      , input_transition_A1, output_capacitance);
                internel_power    = interpolation(NOR2X1_fall_power     , input_transition_A1, output_capacitance);
                total_delay       = total_delay_from_A1 + delay + WIRE_DELAY;
            }
            else {
                output_transition = interpolation(NOR2X1_fall_transition, input_transition_A2, output_capacitance);
                delay             = interpolation(NOR2X1_cell_fall      , input_transition_A2, output_capacitance);
                internel_power    = interpolation(NOR2X1_fall_power     , input_transition_A2, output_capacitance);
                total_delay       = total_delay_from_A2 + delay + WIRE_DELAY;
            }
        }
    }
    else if (cell_type == CELL_INVX1){
        if (value_A1 == false){
            value_ZN = true; // Use rise table

            output_transition = interpolation(INVX1_rise_transition, input_transition_A1, output_capacitance);
            delay             = interpolation(INVX1_cell_rise      , input_transition_A1, output_capacitance);
            internel_power    = interpolation(INVX1_rise_power     , input_transition_A1, output_capacitance);
            total_delay       = total_delay_from_A1 + delay + WIRE_DELAY;
        }
        else {
            value_ZN = false; // Use fall table

            output_transition = interpolation(INVX1_fall_transition, input_transition_A1, output_capacitance);
            delay             = interpolation(INVX1_cell_fall      , input_transition_A1, output_capacitance);
            internel_power    = interpolation(INVX1_fall_power     , input_transition_A1, output_capacitance);
            total_delay       = total_delay_from_A1 + delay + WIRE_DELAY;
        }
    }
    else if (cell_type == CELL_NANDX1){
        // NAND controlling value -> 0
        if (!value_A1 && !value_A2){
            value_ZN = true; // Use rise table

            // Earliest controlling value (All c)
            if (total_delay_from_A1 < total_delay_from_A2){
                output_transition = interpolation(NANDX1_rise_transition, input_transition_A1, output_capacitance);
                delay             = interpolation(NANDX1_cell_rise      , input_transition_A1, output_capacitance);
                internel_power    = interpolation(NANDX1_rise_power     , input_transition_A1, output_capacitance);
                total_delay       = total_delay_from_A1 + delay + WIRE_DELAY;
            }
            else {
                output_transition = interpolation(NANDX1_rise_transition, input_transition_A2, output_capacitance);
                delay             = interpolation(NANDX1_cell_rise      , input_transition_A2, output_capacitance);
                internel_power    = interpolation(NANDX1_rise_power     , input_transition_A2, output_capacitance);
                total_delay       = total_delay_from_A2 + delay + WIRE_DELAY;
            }
        }
        else if (!value_A1 && value_A2){
            value_ZN = true; // Use rise table

            // Earliest controlling value (A1 c)
            output_transition = interpolation(NANDX1_rise_transition, input_transition_A1, output_capacitance);
            delay             = interpolation(NANDX1_cell_rise      , input_transition_A1, output_capacitance);
            internel_power    = interpolation(NANDX1_rise_power     , input_transition_A1, output_capacitance);
            total_delay       = total_delay_from_A1 + delay + WIRE_DELAY;
        }
        else if (value_A1 && !value_A2){
            value_ZN = true; // Use rise table

            // Earliest controlling value (A2 c)
            output_transition = interpolation(NANDX1_rise_transition, input_transition_A2, output_capacitance);
            delay             = interpolation(NANDX1_cell_rise      , input_transition_A2, output_capacitance);
            internel_power    = interpolation(NANDX1_rise_power     , input_transition_A2, output_capacitance);
            total_delay       = total_delay_from_A2 + delay + WIRE_DELAY;
        }
        else {
            value_ZN = false; // Use fall table

            // Latest non-controlling value (All non-c)
            if (total_delay_from_A1 > total_delay_from_A2){
                output_transition = interpolation(NANDX1_fall_transition, input_transition_A1, output_capacitance);
                delay             = interpolation(NANDX1_cell_fall      , input_transition_A1, output_capacitance);
                internel_power    = interpolation(NANDX1_fall_power     , input_transition_A1, output_capacitance);
                total_delay       = total_delay_from_A1 + delay + WIRE_DELAY;
            }
            else {
                output_transition = interpolation(NANDX1_fall_transition, input_transition_A2, output_capacitance);
                delay             = interpolation(NANDX1_cell_fall      , input_transition_A2, output_capacitance);
                internel_power    = interpolation(NANDX1_fall_power     , input_transition_A2, output_capacitance);
                total_delay       = total_delay_from_A2 + delay + WIRE_DELAY;
            }
        }
    }

    switching_power = 0.5 * output_capacitance * VOLTAGE * VOLTAGE;
    // if (ZN->logic_value != value_ZN) switching_power = 0.5 * output_capacitance * VOLTAGE * VOLTAGE;
    // else                             switching_power = 0;

    //===================================//
    // 4. Update Total Power             //
    //===================================//
    total_power += internel_power;
    if (ZN->logic_value == !value_ZN) total_power += switching_power;
    //===================================//
    // 5. Update Toggle                  //
    //===================================//
    toggle_0to1 += (!ZN->logic_value &&  value_ZN);
    toggle_1to0 += ( ZN->logic_value && !value_ZN);
    //===================================//
    // 6. Update Output Value            //
    //===================================//
    ZN->logic_value = value_ZN;
}





double Cell::interpolation(const vector<vector<double>>& table, double& input_transition, double& output_capacitance){

    // TODO: Add Boundary Conditions
    // Vertical  (x):   input_transition
    // Horizontal(y):   output_capacitance
    int x1 = -1, x2 = -1;
    int y1 = -1, y2 = -1;

    //===================================//
    // Step.1 Setup x1, x2, y1, y2       //
    //===================================//
    // Get y1, y2 position
    if (output_capacitance < total_output_net_capacitance[0]) {
        y1 = 0;
        y2 = 1;
    }
    else if (output_capacitance > total_output_net_capacitance[TABLE_SIZE-1]) {
        y1 = TABLE_SIZE - 2;
        y2 = TABLE_SIZE - 1;
    }
    else {
        for (int i = 1; i < TABLE_SIZE; i++){
            if (output_capacitance == total_output_net_capacitance[i-1]){
                y1 = i - 1;
                y2 = i - 1;
                break;
            }
            else if (output_capacitance == total_output_net_capacitance[i]){
                y1 = i;
                y2 = i;
                break;
            }
            else if (output_capacitance > total_output_net_capacitance[i-1] && output_capacitance < total_output_net_capacitance[i]){
                y1 = i - 1;
                y2 = i;
                break;
            }
        }
    }

    // Get x1, x2 position
    if (input_transition < input_transition_time[0]) {
        x1 = 0;
        x2 = 1;
    }
    else if (input_transition > input_transition_time[TABLE_SIZE-1]) {
        x1 = TABLE_SIZE - 2;
        x2 = TABLE_SIZE - 1;
    }
    else {
        for (int i = 1; i < TABLE_SIZE; i++) {
            if (input_transition == input_transition_time[i-1]) {
                x1 = i - 1;
                x2 = i - 1;
                break;
            }
            else if (input_transition == input_transition_time[i]) {
                x1 = i;
                x2 = i;
                break;
            }
            else if (input_transition > input_transition_time[i-1] && input_transition < input_transition_time[i]) {
                x1 = i - 1;
                x2 = i;
                break;
            }
        }
    }


    //===================================//
    // Step2. UR, UL, DR, DL             //
    //===================================//
    // UL    UR
    //
    // DL    DR
    double UL, UR;
    double DL, DR;

    UL = table[x1][y1];
    UR = table[x1][y2];
    DL = table[x2][y1];
    DR = table[x2][y2];
    // cout << "UL = " << UL << endl;
    // cout << "UR = " << UR << endl;
    // cout << "DL = " << DL << endl;
    // cout << "DR = " << DR << endl;

    //===================================//
    // Step3. UM, DM                     //
    //===================================//
    // UL UM UR
    //
    // DL DM DR
    double UM;
    double DM;
    double DEL_H;

    if (output_capacitance < total_output_net_capacitance[0]) {
        DEL_H = (total_output_net_capacitance[y1] - output_capacitance) / (total_output_net_capacitance[y2] - total_output_net_capacitance[y1]);
        UM = UL - ((UR - UL) * DEL_H);
        DM = DL - ((DR - DL) * DEL_H);
    }
    else if (output_capacitance > total_output_net_capacitance[TABLE_SIZE-1]) {
        DEL_H = (output_capacitance - total_output_net_capacitance[y2]) / (total_output_net_capacitance[y2] - total_output_net_capacitance[y1]);
        UM = UR + ((UR - UL) * DEL_H);
        DM = DR + ((DR - DL) * DEL_H);
    }
    else {
        DEL_H = (output_capacitance - total_output_net_capacitance[y1]) / (total_output_net_capacitance[y2] - total_output_net_capacitance[y1]);
        UM = UL + ((UR - UL) * DEL_H);
        DM = DL + ((DR - DL) * DEL_H);
    }
    // cout << "UM = " << UM << endl;
    // cout << "DM = " << DM << endl;

    //===================================//
    // Step4. result                     //
    //===================================//
    // UL UM UR
    //    MM
    // DL DM DR
    double result;
    double DEL_V = (DM - UM) / (input_transition_time[x2] - input_transition_time[x1]);

    if (input_transition < input_transition_time[0])
        result = UM - DEL_V * (input_transition_time[x1] - input_transition);
    else if (input_transition > input_transition_time[TABLE_SIZE-1])
        result = DM + DEL_V * (input_transition - input_transition_time[x2]);
    else
        result = UM + DEL_V * (input_transition - input_transition_time[x1]);

    // FIXME: If < 0 then equals 0
    result = (result < 0) ? 0 : result;
    return result;
}

void Cell::print_cell_info(){
    if (cell_type == CELL_NOR2X1){
        cout << setw(12) << left << instance_name;
        cout << setw(12) << left << "NOR2X1";
        cout << setw(12) << left << output_capacitance;
        cout << setw(12) << left << output_transition;
        cout << setw(12) << left << delay;
        cout << setw(12) << left << total_delay;
        string connection = ".ZN(" + ZN->wire_name + ") .A1(" + A1->wire_name + ") .A1(" + A2->wire_name + ")";
        cout << setw(25) << left << connection << endl;
    }
    else if (cell_type == CELL_INVX1) {
        cout << setw(12) << left << instance_name;
        cout << setw(12) << left << "INVX1";
        cout << setw(12) << left << output_capacitance;
        cout << setw(12) << left << output_transition;
        cout << setw(12) << left << delay;
        cout << setw(12) << left << total_delay;
        string connection = ".ZN(" + ZN->wire_name + ") .I(" + A1->wire_name + ")";
        cout << setw(25) << left << connection << endl;
    }
    else if (cell_type == CELL_NANDX1) {
        cout << setw(12) << left << instance_name;
        cout << setw(12) << left << "NANDX1";
        cout << setw(12) << left << output_capacitance;
        cout << setw(12) << left << output_transition;
        cout << setw(12) << left << delay;
        cout << setw(12) << left << total_delay;
        string connection = ".ZN(" + ZN->wire_name + ") .A1(" + A1->wire_name + ") .A1(" + A2->wire_name + ")";
        cout << setw(25) << left << connection << endl;
    }
    else {
        cout << "Type: Error (Not Defined)" << endl;
    }
}

// ##   ##    ####   ######   #######
// ##   ##    ####   #######  #######
// ##   ##     ##    ##    #  ##
// ##   ##     ##    ######   ####
// ## # ##     ##    ## ##    ##
// ### ###    ####   ##  ##   #######
// ##   ##    ####   ##   ##  #######

Wire::Wire(string name, int type){
    // cout << "Create Wire: " << name << endl;
    wire_name = name;
    wire_type = type;
    isInput  = (wire_type ==  WIRE_IN);
    isOutput = (wire_type == WIRE_OUT);
}

void Wire::print_wire_info(){
    cout << "         Name: " << wire_name << endl;
    if (wire_type == 1) {
        cout << "         Type: Input" << endl;
        cout << "Previous Cell: None" << endl;
        cout << "   Next Cells: ";
        for (auto cell: next_cells) cout << cell->instance_name << " ";
        cout << endl;
    }
    else if (wire_type == 2) {
        cout << "         Type: Output" << endl;
        cout << "Previous Cell: " << prev_cell->instance_name << endl;
        cout << "   Next Cells: None" << endl;
    }
    else if (wire_type == 3) {
        cout << "         Type: Wire" << endl;
        cout << "Previous Cell: " << prev_cell->instance_name << endl;
        cout << "   Next Cells: ";
        for (auto cell: next_cells) cout << cell->instance_name << " ";
        cout << endl;
    }
    else {
        cout << "Type: Error (Not Defined)" << endl;
    }

    cout << endl;
}

// ##         ####   ######   #######  ######    ######  ##  ##
// ##         ####   #######  #######  #######   ######  ##  ##
// ##          ##    ##    #  ##       ##    #     ##     #  #
// ##          ##    ######   ####     ######      ##     ####
// ##          ##    ##   ##  ##       ## ##       ##      ##
// #######    ####   #######  #######  ##  ##      ##      ##
// #######    ####   ######   #######  ##   ##     ##      ##



Liberty::Liberty(ifstream& INFILE_LIBERTY){
    bool range_NOR  = false;
    bool range_INV  = false;
    bool range_NAND = false;

    while(!INFILE_LIBERTY.eof()){
        //===================================//
        // 1. Get Line                       //
        //===================================//
        string line;
        string skipped_line;
        getline(INFILE_LIBERTY, line);

        //===================================//
        // 2. Filter Unwanted Informations   //
        //===================================//
        // 2.1 Remove semicolon
        // if (found_str(line, "\t"))    line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
        // if (found_str(line,  " "))    line.erase(std::remove(line.begin(), line.end(),  ' '), line.end());
        if (found_str(line,  ";"))    line = line.substr(0, line.find(';'));
        // 2.2 Empty line
        if (line.empty()) continue;


        //===================================//
        // 3. Table Indices                  //
        //===================================//
        // total_output_net_capacitance
        if (found_str(line, "index_1")) {
            if (found_str(line, "(\"")) line = line.substr(line.find("(\"") + 2);
            if (found_str(line, "\")")) line = line.substr(0, line.find("\")"));
            vector<string> str_datas = split_str_by_comma(line);
            for (const auto& data: str_datas)
                total_output_net_capacitance.push_back(stod(data));
        }

        // input_transition_time
        if (found_str(line, "index_2")) {
            if (found_str(line, "(\"")) line = line.substr(line.find("(\"") + 2);
            if (found_str(line, "\")")) line = line.substr(0, line.find("\")"));
            vector<string> str_datas = split_str_by_comma(line);
            for (const auto& data: str_datas)
                input_transition_time.push_back(stod(data));
        }

        //===================================//
        // 4-1. Define Current Parse Range   //
        //===================================//
        if (found_str(line, "cell (NOR2X1)")) {
            range_NOR  = true;
            range_INV  = false;
            range_NAND = false;
        }
        else if (found_str(line, "cell (INVX1)")) {
            range_NOR  = false;
            range_INV  = true;
            range_NAND = false;
        }
        else if (found_str(line, "cell (NANDX1)")) {
            range_NOR  = false;
            range_INV  = false;
            range_NAND = true;
        }

        //===================================//
        // 4-2. Parse Cell Datas             //
        //===================================//
        if (range_NOR && !range_INV && !range_NAND){
            if (found_str(line, "pin(A1)")){
                getline(INFILE_LIBERTY, skipped_line);
                getline(INFILE_LIBERTY, line);
                line = line.substr(line.find("capacitance : ") + 14);
                line = line.substr(0, line.find(";"));
                NOR2X1_A1_capacitance = stod(line);
            }
            else if (found_str(line, "pin(A2)")){
                getline(INFILE_LIBERTY, skipped_line);
                getline(INFILE_LIBERTY, line);
                line = line.substr(line.find("capacitance : ") + 14);
                line = line.substr(0, line.find(";"));
                NOR2X1_A2_capacitance = stod(line);
            }
            else if (found_str(line, "rise_power")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NOR2X1_rise_power.push_back(curr_row);
                }
            }
            else if (found_str(line, "fall_power")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NOR2X1_fall_power.push_back(curr_row);
                }
            }
            else if (found_str(line, "cell_rise")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NOR2X1_cell_rise.push_back(curr_row);
                }
            }
            else if (found_str(line, "cell_fall")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NOR2X1_cell_fall.push_back(curr_row);
                }
            }
            else if (found_str(line, "rise_transition")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NOR2X1_rise_transition.push_back(curr_row);
                }
            }
            else if (found_str(line, "fall_transition")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NOR2X1_fall_transition.push_back(curr_row);
                }
            }
        }
        else if (!range_NOR && range_INV && !range_NAND){
            if (found_str(line, "pin(I)")){
                getline(INFILE_LIBERTY, skipped_line);
                getline(INFILE_LIBERTY, line);
                line = line.substr(line.find("capacitance : ") + 14);
                line = line.substr(0, line.find(";"));
                INVX1_I_capacitance = stod(line);
            }
            else if (found_str(line, "rise_power")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    INVX1_rise_power.push_back(curr_row);
                }
            }
            else if (found_str(line, "fall_power")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    INVX1_fall_power.push_back(curr_row);
                }
            }
            else if (found_str(line, "cell_rise")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    INVX1_cell_rise.push_back(curr_row);
                }
            }
            else if (found_str(line, "cell_fall")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    INVX1_cell_fall.push_back(curr_row);
                }
            }
            else if (found_str(line, "rise_transition")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    INVX1_rise_transition.push_back(curr_row);
                }
            }
            else if (found_str(line, "fall_transition")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    INVX1_fall_transition.push_back(curr_row);
                }
            }
        }
        else if (!range_NOR && !range_INV && range_NAND){
            if (found_str(line, "pin(A1)")){
                getline(INFILE_LIBERTY, skipped_line);
                getline(INFILE_LIBERTY, line);
                line = line.substr(line.find("capacitance : ") + 14);
                line = line.substr(0, line.find(";"));
                NANDX1_A1_capacitance = stod(line);
            }
            else if (found_str(line, "pin(A2)")){
                getline(INFILE_LIBERTY, skipped_line);
                getline(INFILE_LIBERTY, line);
                line = line.substr(line.find("capacitance : ") + 14);
                line = line.substr(0, line.find(";"));
                NANDX1_A2_capacitance = stod(line);
            }
            else if (found_str(line, "rise_power")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NANDX1_rise_power.push_back(curr_row);
                }
            }
            else if (found_str(line, "fall_power")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NANDX1_fall_power.push_back(curr_row);
                }
            }
            else if (found_str(line, "cell_rise")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NANDX1_cell_rise.push_back(curr_row);
                }
            }
            else if (found_str(line, "cell_fall")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NANDX1_cell_fall.push_back(curr_row);
                }
            }
            else if (found_str(line, "rise_transition")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NANDX1_rise_transition.push_back(curr_row);
                }
            }
            else if (found_str(line, "fall_transition")){
                for (int i = 0; i < TABLE_SIZE; i++){
                    getline(INFILE_LIBERTY, line);
                    line = line.substr(line.find("\"") + 1);
                    line = line.substr(0, line.find("\""));
                    vector<string> str_datas = split_str_by_comma(line);
                    vector<double> curr_row;
                    for (const auto& data: str_datas)
                        curr_row.push_back(stod(data));
                    NANDX1_fall_transition.push_back(curr_row);
                }
            }
        }

    }
}



// ##   ##  #######   ######  ##         ####    #####    ######
// ##   ##  #######   ######  ##         ####   #######   ######
// ###  ##  ##          ##    ##          ##    ##          ##
// ## # ##  ####        ##    ##          ##    ######      ##
// ##  ###  ##          ##    ##          ##         ##     ##
// ##   ##  #######     ##    #######    ####   #######     ##
// ##   ##  #######     ##    #######    ####    #####      ##


Netlist::Netlist(ifstream& INFILE_NETLIST){
    while(!INFILE_NETLIST.eof()){
        //===================================//
        // 1. Get Line                       //
        //===================================//
        string line;
        getline(INFILE_NETLIST, line);

        //===================================//
        // 2. Filter Unwanted Informations   //
        //===================================//
        // 2.1 Remove tab and semicolon
        if (found_str(line, "\t"))    line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
        if (found_str(line,  " "))    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        if (found_str(line,  ";"))    line = line.substr(0, line.find(';'));
        // 2.2 Word "endmodule"
        if (line == "endmodule") break;
        // 2.3 Double Slash Comments
        if (found_str(line, "//")){
            int idx = line.find("//");
            line = line.substr(0, idx);
        }
        // 2.4.1 Slash Asterisk Comments - same line (may have multiple comments in one line)
        while (found_str(line, "/*") && found_str(line, "*/")){
            int idx1 = line.find("/*");
            int idx2 = line.find("*/");
            int str_len = idx2 + 2 - idx1;
            line.erase(idx1, str_len);
        }
        // 2.4.2 Slash Asterisk Comments - different line
        if (found_str(line, "/*")){
            while(true){
                getline(INFILE_NETLIST, line);
                if (found_str(line, "*/"))
                    break;
            }
            continue;
        }
        // 2.5 Empty line
        if (line.empty()) continue;


        //===================================//
        // 3. Fetch Data                     //
        //===================================//
        // 3.1 Parse Wires
        if (found_str(line, "input") || found_str(line, "output") || found_str(line, "wire"))
            parse_wire(line);
            // cout << "\033[1;31mPARSE WIRE\033[0m" << endl;
        // 3.2 Parse Cells
        if (found_str(line, "NOR2X1") || found_str(line, "INVX1") || found_str(line, "NANDX1"))
            parse_cell(line);
            // cout << "\033[1;31mPARSE CELL\033[0m" << endl;


        //===================================//
        // X. Print Parsed Line              //
        //===================================//
        // cout << line << endl;
        // print_PI_name();
        // print_PO_name();
    }
}

void Netlist::parse_wire(string line){
    if (found_str(line, "input")){
        string nets = line.erase(0, 5);
        PI_name = split_str_by_comma(nets);
        for (const auto& wire_name: PI_name){
            Wire *w = new Wire(wire_name, WIRE_IN);
            wire_list.push_back(w);
            wire_lut[wire_name] = w;
        }
    }
    if (found_str(line, "output")){
        string nets = line.erase(0, 6);
        PO_name = split_str_by_comma(nets);
        for (const auto& wire_name: PO_name){
            Wire *w = new Wire(wire_name, WIRE_OUT);
            wire_list.push_back(w);
            wire_lut[wire_name] = w;
        }
    }
    if (found_str(line, "wire")){
        string nets = line.erase(0, 4);
        vector<string> W_name = split_str_by_comma(nets);
        for (const auto& wire_name: W_name){
            Wire *w = new Wire(wire_name, WIRE_W);
            wire_list.push_back(w);
            wire_lut[wire_name] = w;
        }
    }
}

void Netlist::parse_cell(string line){
    string substring;
    int idx = 0;

    // print_all_cell();
    if (found_str(line, "NOR2X1")){
        // Instance name
        substring = line.erase(0, 6);
        idx = substring.find("(.");
        string instance_name = substring.substr(0, idx);
        // cout << "\033[1;31mNOR2X1\033[0m " << instance_name << endl;

        // PIN ZN
        idx = line.find(".ZN(");
        substring = line.substr(idx + 4);
        idx = substring.find(")");
        substring = substring.substr(0, idx);
        string PIN_ZN = substring;
        Wire *Wire_ZN = wire_lut[PIN_ZN];
        // cout << "PIN ZN: " << PIN_ZN << endl;

        // PIN_A1
        idx = line.find(".A1(");
        substring = line.substr(idx + 4);
        idx = substring.find(")");
        substring = substring.substr(0, idx);
        string PIN_A1 = substring;
        Wire *Wire_A1 = wire_lut[PIN_A1];
        // cout << "PIN_A1: " << PIN_A1  << endl;

        // PIN_A2
        idx = line.find(".A2(");
        substring = line.substr(idx + 4);
        idx = substring.find(")");
        substring = substring.substr(0, idx);
        string PIN_A2 = substring;
        Wire *Wire_A2 = wire_lut[PIN_A2];
        // cout << "PIN_A2: " << PIN_A2 << endl;

        // Create new cell
        Cell *new_cell = new Cell(instance_name, CELL_NOR2X1, Wire_ZN, Wire_A1, Wire_A2);
        cell_list.push_back(new_cell);
        Wire_A1->next_cells.push_back(new_cell);
        Wire_A2->next_cells.push_back(new_cell);
        Wire_ZN->prev_cell = new_cell;
    }
    else if (found_str(line, "INVX1")){
        // Instance name
        substring = line.erase(0, 5);
        idx = substring.find("(.");
        string instance_name = substring.substr(0, idx);
        // cout << "\033[1;31mINVX1\033[0m " << instance_name << endl;

        // PIN ZN
        idx = line.find(".ZN(");
        substring = line.substr(idx + 4);
        idx = substring.find(")");
        substring = substring.substr(0, idx);
        string PIN_ZN = substring;
        Wire *Wire_ZN = wire_lut[PIN_ZN];
        // cout << "PIN ZN: " << PIN_ZN << endl;

        // PIN_I
        idx = line.find(".I(");
        substring = line.substr(idx + 3);
        idx = substring.find(")");
        substring = substring.substr(0, idx);
        string PIN_I = substring;
        Wire *Wire_I = wire_lut[PIN_I];
        // cout << "PIN_I:  " << PIN_I << endl;

        // Create New Cell and Update Wire Connections
        Cell *new_cell = new Cell(instance_name, CELL_INVX1, Wire_ZN, Wire_I, nullptr);
        cell_list.push_back(new_cell);
        Wire_I->next_cells.push_back(new_cell);
        Wire_ZN->prev_cell = new_cell;
    }
    else if (found_str(line, "NANDX1")){
        // Instance name
        substring = line.erase(0, 6);
        idx = substring.find("(.");
        string instance_name = substring.substr(0, idx);
        // cout << "\033[1;31mNANDX1\033[0m " << instance_name << endl;

        // PIN ZN
        idx = line.find(".ZN(");
        substring = line.substr(idx + 4);
        idx = substring.find(")");
        substring = substring.substr(0, idx);
        string PIN_ZN = substring;
        Wire *Wire_ZN = wire_lut[PIN_ZN];
        // cout << "PIN ZN: " << PIN_ZN << endl;

        // PIN_A1
        idx = line.find(".A1(");
        substring = line.substr(idx + 4);
        idx = substring.find(")");
        substring = substring.substr(0, idx);
        string PIN_A1 = substring;
        Wire *Wire_A1 = wire_lut[PIN_A1];
        // cout << "PIN_A1: " << PIN_A1 << endl;

        // PIN_A2
        idx = line.find(".A2(");
        substring = line.substr(idx + 4);
        idx = substring.find(")");
        substring = substring.substr(0, idx);
        string PIN_A2 = substring;
        Wire *Wire_A2 = wire_lut[PIN_A2];
        // cout << "PIN_A2: " << PIN_A2 << endl;

        // Create new cell
        Cell *new_cell = new Cell(instance_name, CELL_NANDX1, Wire_ZN, Wire_A1, Wire_A2);
        cell_list.push_back(new_cell);
        Wire_A1->next_cells.push_back(new_cell);
        Wire_A2->next_cells.push_back(new_cell);
        Wire_ZN->prev_cell = new_cell;
    }
}

void Netlist::calculate_output_capacitance(){
    for (const auto& curr_cell: cell_list){
        if (curr_cell->ZN->isOutput)
            curr_cell->output_capacitance = OUTPUT_CAPACITANCE;

        for (const auto& next_cell: curr_cell->ZN->next_cells){
            if (next_cell->cell_type == CELL_NOR2X1){
                if      (curr_cell->ZN == next_cell->A1)  curr_cell->output_capacitance += NOR2X1_A1_capacitance;
                else if (curr_cell->ZN == next_cell->A2)  curr_cell->output_capacitance += NOR2X1_A2_capacitance;
                else                                      cerr << "Error Message from calculate_output_capacitance()" << endl;
            }
            else if (next_cell->cell_type == CELL_INVX1){
                curr_cell->output_capacitance += INVX1_I_capacitance;
            }
            else if (next_cell->cell_type == CELL_NANDX1){
                if      (curr_cell->ZN == next_cell->A1)  curr_cell->output_capacitance += NANDX1_A1_capacitance;
                else if (curr_cell->ZN == next_cell->A2)  curr_cell->output_capacitance += NANDX1_A2_capacitance;
                else                                      cerr << "Error Message from calculate_output_capacitance()" << endl;
            }
            else {
                cerr << "Error Message from Netlist::calculate_output_capacitance()" << endl;
            }
        }
    }
}

void Netlist::calculate_delay(int pat){
    queue<Cell*> cell_queue;

    //===================================//
    // 1. Reset at every iteration       //
    //===================================//
    // Reset total power
    total_power = 0;
    // Reset Cells, and then add all cells whose A1s and A2s are all connected to input
    for (const auto& cell: cell_list){
        // Reset every cell delay information
        cell->reset_cell();

        if (cell->cell_type == CELL_NANDX1 || cell->cell_type == CELL_NOR2X1){
            if (cell->A1->isInput && cell->A2->isInput)
                cell_queue.push(cell);
        }
        else if (cell->cell_type == CELL_INVX1){
            if (cell->A1->isInput)
                cell_queue.push(cell);
        }
    }

    // Reset wire logic values
    // for (const auto& wire: wire_list)
    //     wire->logic_value = false;



    //===================================//
    // 2. Initialize new pattern         //
    //===================================//
    unordered_map<string, bool> curr_pattern;
    for (auto& name: PI_name){
        curr_pattern[name] = input_patterns[name][pat];
    }


    //===================================//
    // 3. Update Delay of Every Cell     //
    //===================================//
    while (!cell_queue.empty()){
        Cell *curr_cell = cell_queue.front();
        cell_queue.pop();

        // Check if all previous gates are updated. If not, push back to queue again
        if (curr_cell->cell_type != CELL_INVX1){
            if (!curr_cell->A1->isInput){
                if (!curr_cell->A1->prev_cell->updated){
                    cell_queue.push(curr_cell);
                    continue;
                }
            }
            if (!curr_cell->A2->isInput){
                if (!curr_cell->A2->prev_cell->updated){
                    cell_queue.push(curr_cell);
                    continue;
                }
            }
        }
        else {
            if (!curr_cell->A1->isInput){
                if (!curr_cell->A1->prev_cell->updated){
                    cell_queue.push(curr_cell);
                    continue;
                }
            }
        }


        // Skip if updated
        if (curr_cell->updated)
            continue;


        curr_cell->update_cell_by_logic_value(curr_pattern, total_power);
        curr_cell->updated = true;

        // Push next cells to queue
        if (!curr_cell->ZN->next_cells.empty())
            for (const auto& next_cell: curr_cell->ZN->next_cells)
                cell_queue.push(next_cell);

    }
}

void Netlist::find_longest_path(Wire*& longest_output){
    Wire *curr_wire = longest_output;

    while (!curr_wire->isInput){
        longest_path.push_back(curr_wire);

        // NOR2X1 & NANDX1
        if (curr_wire->prev_cell->cell_type != CELL_INVX1){
            Wire *wire_candidate_A1 = curr_wire->prev_cell->A1;
            Wire *wire_candidate_A2 = curr_wire->prev_cell->A2;

            double candidate_A1_total_delay = (wire_candidate_A1->prev_cell) ? wire_candidate_A1->prev_cell->total_delay : 0;
            double candidate_A2_total_delay = (wire_candidate_A2->prev_cell) ? wire_candidate_A2->prev_cell->total_delay : 0;

            if (candidate_A1_total_delay > candidate_A2_total_delay)
                curr_wire = wire_candidate_A1;
            else
                curr_wire = wire_candidate_A2;
        }
        else {
            curr_wire = curr_wire->prev_cell->A1;
        }

        // Final Condition
        if (curr_wire->isInput) longest_path.push_back(curr_wire);

        // Print
        // for (const auto& wire: longest_path) cout << wire->wire_name << " ";
        // cout << endl;
    }
    reverse(longest_path.begin(), longest_path.end());
}

void Netlist::find_shortest_path(Wire*& shortest_output){
    Wire *curr_wire = shortest_output;

    while (!curr_wire->isInput){
        shortest_path.push_back(curr_wire);

        // NOR2X1 & NANDX1
        if (curr_wire->prev_cell->cell_type != CELL_INVX1){
            Wire *wire_candidate_A1 = curr_wire->prev_cell->A1;
            Wire *wire_candidate_A2 = curr_wire->prev_cell->A2;

            double candidate_A1_total_delay = (wire_candidate_A1->prev_cell) ? wire_candidate_A1->prev_cell->total_delay : 0;
            double candidate_A2_total_delay = (wire_candidate_A2->prev_cell) ? wire_candidate_A2->prev_cell->total_delay : 0;

            if (candidate_A1_total_delay > candidate_A2_total_delay)
                curr_wire = wire_candidate_A1;
            else
                curr_wire = wire_candidate_A2;
        }
        else {
            curr_wire = curr_wire->prev_cell->A1;
        }

        // Final Condition
        if (curr_wire->isInput) shortest_path.push_back(curr_wire);

        // Print
        // for (const auto& wire: shortest_path) cout << wire->wire_name << " ";
        // cout << endl;
    }
    reverse(shortest_path.begin(), shortest_path.end());
}



void Netlist::read_input_pattern(ifstream& INFILE_PAT){
    vector<string> input_names;
    while (!INFILE_PAT.eof()){
        string line;
        getline(INFILE_PAT, line);

        // Break when eof
        if (found_str(line, ".end"))
            break;

        if (line.empty())
            continue;

        // Filter unwanted characters
        if (found_str(line, "\t"))    line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
        if (found_str(line,  " "))    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        // Read Input Ports Order
        if (found_str(line, "input")){
            line = line.substr(line.find("input") + 5);
            input_names = split_str_by_comma(line);
            for (auto& name: input_names){
                vector<bool> pattern = {};
                input_patterns[name] = pattern;
            }
        }
        else {
            int size = input_names.size();
            for (int i = 0; i < size; i++){
                string name = input_names[i];
                bool value = line[i] == '1';
                input_patterns[name].push_back(value);
            }
            PAT_NUM++;
        }
    }
}

void Netlist::write_result_load(){
    sort(cell_list.begin(), cell_list.end(), sort_by_instance_name);
    for (auto& cell: cell_list){
        // OUTFILE_LOAD << cell->instance_name << " " << fixed << setprecision(6) << cell->output_capacitance  << endl;
        load_txt += (cell->instance_name + " " + to_string(cell->output_capacitance) + '\n');
    }
}

void Netlist::write_gate_info(){
    sort(cell_list.begin(), cell_list.end(), sort_by_instance_name);
    for (auto& cell: cell_list){
        // OUTFILE_GATE_INFO << cell->instance_name << " ";
        // OUTFILE_GATE_INFO << cell->ZN->logic_value << " ";
        // OUTFILE_GATE_INFO << fixed << setprecision(6) << cell->delay << " ";
        // OUTFILE_GATE_INFO << fixed << setprecision(6) << cell->output_transition << endl;
        gate_info_txt += (cell->instance_name + " ");
        gate_info_txt += (to_string(cell->ZN->logic_value) + " ");
        gate_info_txt += (to_string(cell->delay) + " ");
        gate_info_txt += (to_string(cell->output_transition) + "\n");
    }
    // OUTFILE_GATE_INFO << endl;
    gate_info_txt += "\n";
}

void Netlist::write_gate_power(){
    sort(cell_list.begin(), cell_list.end(), sort_by_instance_name);
    for (auto& cell: cell_list){
        // OUTFILE_GATE_POWER << cell->instance_name << " ";
        // OUTFILE_GATE_POWER << fixed << setprecision(6) << cell->internel_power << " ";
        // OUTFILE_GATE_POWER << fixed << setprecision(6) << cell->switching_power   << " " << endl;
        gate_power_txt += (cell->instance_name + " ");
        gate_power_txt += (to_string(cell->internel_power) + " ");
        gate_power_txt += (to_string(cell->switching_power) + " " + "\n");
    }
    // OUTFILE_GATE_POWER << endl;
    gate_power_txt += "\n";
}

void Netlist::write_coverage(int pat){
    double toggle_count = 0, total_toggle_count = 0;
    for (auto &cell: cell_list){
        total_toggle_count += 40;
        toggle_count += (cell->toggle_0to1 <= 20) ? cell->toggle_0to1 : 20;
        toggle_count += (cell->toggle_1to0 <= 20) ? cell->toggle_1to0 : 20;
    }
    double coverage = toggle_count / total_toggle_count * 100;
    double coverage_rounded = round(coverage * 100) / 100;
    string coverage_str = to_string(coverage_rounded);
    coverage_str = coverage_str.substr(0, coverage_str.size()-4);


    // OUTFILE_COVERAGE << pat+1 << " ";
    // OUTFILE_COVERAGE << fixed << setprecision(6) << total_power << " ";
    // OUTFILE_COVERAGE << fixed << setprecision(2) << coverage    << "%" << endl << endl;
    converage_txt += (to_string(pat+1) + " ");
    converage_txt += (to_string(total_power) + " ");
    converage_txt += (coverage_str + "%\n\n");
}

void Netlist::write_output(ofstream& OUTFILE_LOAD, ofstream& OUTFILE_GATE_INFO, ofstream& OUTFILE_GATE_POWER, ofstream& OUTFILE_COVERAGE){
    OUTFILE_LOAD << load_txt;
    OUTFILE_GATE_INFO << gate_info_txt;
    OUTFILE_GATE_POWER << gate_power_txt;
    OUTFILE_COVERAGE << converage_txt;
}

/* Previous HW */
void Netlist::write_result_delay(ofstream& OUTFILE_DELAY){
    sort(cell_list.begin(), cell_list.end(), sort_by_instance_name);
    for (auto& cell: cell_list){
        // cout << cell->instance_name << " " << fixed << setprecision(6) << cell->output_capacitance  << endl;
        OUTFILE_DELAY << cell->instance_name << " ";
        OUTFILE_DELAY << cell->rise_or_fall << " ";
        OUTFILE_DELAY << fixed << setprecision(6) << cell->delay << " ";
        OUTFILE_DELAY << fixed << setprecision(6) << cell->output_transition << endl;
    }
    OUTFILE_DELAY << endl;
}
/* Previous HW */
void Netlist::write_result_path(ofstream& OUTFILE_PATH){
    Wire *longest_output;
    Wire *shortest_output;
    string longest_output_name, shortest_output_name;
    double longest_delay = 0, shortest_delay = INT_MAX;

    // Get longest delay and shortest delay outputs
    for (const auto& output_name: PO_name){
        if (wire_lut[output_name]->prev_cell->total_delay > longest_delay){
            longest_output      = wire_lut[output_name];
            longest_output_name = wire_lut[output_name]->wire_name;
            longest_delay       = wire_lut[output_name]->prev_cell->total_delay;
        }
        if (wire_lut[output_name]->prev_cell->total_delay < shortest_delay){
            shortest_output      = wire_lut[output_name];
            shortest_output_name = wire_lut[output_name]->wire_name;
            shortest_delay       = wire_lut[output_name]->prev_cell->total_delay;
        }
    }

    find_longest_path(longest_output);
    find_shortest_path(shortest_output);

    OUTFILE_PATH << "Longest delay = " << longest_delay - WIRE_DELAY << ", the path is: ";

    int path_size1 = longest_path.size();
    for (int i = 0; i < path_size1; i++) {
        OUTFILE_PATH << longest_path[i]->wire_name;
        if (i + 1 < path_size1)   OUTFILE_PATH << " -> ";
        else                      OUTFILE_PATH << endl;
    }

    OUTFILE_PATH << "Shortest delay = " << shortest_delay - WIRE_DELAY << ", the path is: ";

    int path_size2 = shortest_path.size();
    for (int i = 0; i < path_size2; i++) {
        OUTFILE_PATH << shortest_path[i]->wire_name;
        if (i + 1 < path_size2)   OUTFILE_PATH << " -> ";
        else                      OUTFILE_PATH << endl;
    }
}






void Netlist::print_wire_lut(){
    ofstream sss("wirelut.log");
    for (auto it = wire_lut.begin(); it != wire_lut.end(); ++it) {
        sss << "Key: " << it->first << ",        Value: " << it->second << std::endl;
    }
    sss << endl << endl << endl;
    sss.close();
}

void Netlist::print_PI_name(){
    cout << "PIs: " ;
    for (auto &name: PI_name)
        cout << name << " ";
    cout << endl;
}

void Netlist::print_PO_name(){
    cout << "POs: " ;
    for (auto &name: PO_name)
        cout << name << " ";
    cout << endl;
}

void Netlist::print_all_wire(){
    cout << "\033[1;31m";
    cout << setw(12) << left << "NAME";
    cout << setw(12) << left << "TYPE";
    cout << setw(12) << left << "OUT_LOAD";
    cout << setw(12) << left << "OUT_TRANS";
    cout << setw(12) << left << "PG_DELAY";
    cout << setw(12) << left << "TT_DELAY";
    cout << setw(25) << left << "CONNECTION" << endl;
    cout << "\033[0m";

    for (auto wire_ptr: wire_list){
        wire_ptr->print_wire_info();
    }
}

void Netlist::print_all_cell(){
    cout << "\033[1;31m";
    cout << setw(12) << left << "NAME";
    cout << setw(12) << left << "TYPE";
    cout << setw(12) << left << "OUT_LOAD";
    cout << setw(12) << left << "OUT_TRANS";
    cout << setw(12) << left << "PG_DELAY";
    cout << setw(12) << left << "TT_DELAY";
    cout << setw(25) << left << "CONNECTION" << endl;
    cout << "\033[0m";

    for (auto cell_ptr: cell_list){
        cell_ptr->print_cell_info();
    }

    cout << endl;
}

void Netlist::print_all_patterns(){
    cout << "PAT_NUM = "<< PAT_NUM << endl;
    for (auto &name: PI_name){
        cout << setw(5) << name;
    }
    cout << endl;

    for (int i = 0; i < PAT_NUM; i++){
        for (auto &name: PI_name){
            cout << setw(5) << input_patterns[name][i];
        }
        cout << endl;
    }
}


// ##   ##       ##    ####   ##   ##
// ### ###      ###    ####   ##   ##
// ##   ##      # #     ##    ###  ##
// ## # ##     ####     ##    ## # ##
// ##   ##    #####     ##    ##  ###
// ##   ##   ##  ##    ####   ##   ##
// ##   ##  ##   ##    ####   ##   ##

int main(int argc, char *argv[]){
    ifstream INFILE_NETLIST;
    ifstream INFILE_LIBETRY;
    ifstream INFILE_PAT;
    ofstream OUTFILE_LOAD;
    ofstream OUTFILE_GATE_INFO;
    ofstream OUTFILE_GATE_POWER;
    ofstream OUTFILE_COVERAGE;

    // Arguments format assert
    if (argc != 4){
        cerr << "Wrong number of arguments. Please execute as follow: " << endl;
        cerr << "./<student_id> netlist_file.v netlist_file.pat test_lib.lib" << endl;
        exit(-1);
    }

    string netlist_file_name = argv[1];
    string case_name;

    // Netlist file assert
    if (netlist_file_name.find(".v") == string::npos){
        cerr << "Wrong file type: " << netlist_file_name << endl;
        exit(-1);
    }
    else{
        int idx = netlist_file_name.find(".v");
        case_name = netlist_file_name.substr(0, idx);
    }

    // File Assertion
    INFILE_NETLIST.open(argv[1]);
    INFILE_PAT.open(argv[2]);
    INFILE_LIBETRY.open(argv[3]);
    if (INFILE_NETLIST.fail()) { cerr << "Error:  " << argv[1] << " not found !!!" << endl; exit(1); }
    if (INFILE_PAT.fail())     { cerr << "Error:  " << argv[2] << " not found !!!" << endl; exit(1); }
    if (INFILE_LIBETRY.fail()) { cerr << "Error:  " << argv[3] << " not found !!!" << endl; exit(1); }

    OUTFILE_LOAD.open("312510158_" + case_name + "_load.txt");
    OUTFILE_GATE_INFO.open("312510158_" + case_name + "_gate_info.txt");
    OUTFILE_GATE_POWER.open("312510158_" + case_name + "_gate_power.txt");
    OUTFILE_COVERAGE.open("312510158_" + case_name + "_coverage.txt");

    // Step 0: Read netlist, liberty , and pat file
    Netlist NET(INFILE_NETLIST);
    Liberty LIB(INFILE_LIBETRY);
    NET.read_input_pattern(INFILE_PAT);

    // Step 1: Calculate output loading of each instance
    NET.calculate_output_capacitance();
    NET.write_result_load();

    for (int pat = 0; pat < NET.PAT_NUM; pat++){
        // Step 2: Calculate logic value, propagation delay, and output transition time of each instance
        // Step 3: Calculate the power consumption of each gate.
        // cout << "PATTERN NO." << pat + 1 << endl;
        NET.calculate_delay(pat);
        NET.write_gate_info();
        NET.write_gate_power();
        NET.write_coverage(pat);
    }

    NET.write_output(OUTFILE_LOAD, OUTFILE_GATE_INFO, OUTFILE_GATE_POWER, OUTFILE_COVERAGE);





    INFILE_NETLIST.close();
    INFILE_LIBETRY.close();
    INFILE_PAT.close();
    OUTFILE_LOAD.close();
    OUTFILE_GATE_INFO.close();
    OUTFILE_GATE_POWER.close();
    OUTFILE_COVERAGE.close();
    return 0;
}
