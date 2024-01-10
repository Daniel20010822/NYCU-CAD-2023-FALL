#include <bits/stdc++.h>
using namespace std;

/* ================== Quine McCluskey ================== */
void QM_init(ifstream&, int&, vector<int>&, vector<int>&);
void QM_dec2bin(int&, vector<int>&, vector<string>&);
void print_implicant(vector<string>&);
void QM_get_prime_implicant(vector<string>&, vector<string>&);
void convert_to_alphabetic_format(vector<string>&, vector<string>&);
/* ================== Petrick ==================*/
void Petrick_get_POS(vector<vector<string>>&, vector<string>&, vector<string>&);
void Petrick_print_POS(vector<vector<string>>&);
void Petrick_remove_redundant_terms(vector<vector<string>>&);

void Petrick_solve_for_SOP(vector<vector<string>>&, vector<set<string>>&);
void Petrick_expand(vector<set<string>>&, vector<string>);
void Petrick_print_SOP(vector<set<string>>&);
bool prime_is_on_onset(string, string);
/* ================== Small Functions ================== */
bool sort_by_num_of_ones(string, string);
bool sort_by_alphabet(string, string);
bool sort_by_SOP(set<string>, set<string>);
int  count_num_of_one(string);
bool isGrayCode(string, string);
string merge_implicant(string, string);
void write_result(ofstream&, vector<string>, vector<string>);



int main(int argc, char *argv[]){
    //---------------------------------------------------------------------
    //   DECLARATION
    //---------------------------------------------------------------------
    int nVar;
    vector<int> on_set;
    vector<int> dc_set;
    vector<string> on_set_bin;
    vector<string> dc_set_bin;
    vector<string> implicant, primeImplicant;

    // Open input and output files
    ifstream FILEIN(argv[1]);
    ofstream FILEOUT(argv[2]);

    //---------------------------------------------------------------------
    //   QUINE MCCULSKEY METHOD
    //---------------------------------------------------------------------
    QM_init(FILEIN, nVar, on_set, dc_set);
    QM_dec2bin(nVar, on_set, on_set_bin);
    QM_dec2bin(nVar, dc_set, dc_set_bin);
    implicant.insert(implicant.end(), on_set_bin.begin(), on_set_bin.end());
    implicant.insert(implicant.end(), dc_set_bin.begin(), dc_set_bin.end());
    sort(implicant.begin(), implicant.end(), sort_by_num_of_ones);

    // Solve for prime implicants
    while (!implicant.empty()){
        // print_implicant(implicant);
        QM_get_prime_implicant(implicant, primeImplicant);
    }

    //---------------------------------------------------------------------
    //   PETRICK'S METHOD (POS -> SOP)
    //---------------------------------------------------------------------
    vector<vector<string>> product_of_sum;
    vector<set<string>>    sum_of_product;
    Petrick_get_POS(product_of_sum, on_set_bin, primeImplicant);

    Petrick_remove_redundant_terms(product_of_sum);

    // Solve Petrick's Method
    Petrick_solve_for_SOP(product_of_sum, sum_of_product);
    sort(sum_of_product.begin(), sum_of_product.end(), sort_by_SOP);
    // cout << endl << "SOP Result: " << endl;
    // Petrick_print_SOP(sum_of_product);

    // Minimum covering is the on the top of sum_of_product
    vector<string> minimum_cover(sum_of_product[0].begin(), sum_of_product[0].end());

    // Write result
    write_result(FILEOUT, primeImplicant, minimum_cover);

    // Close files
    FILEIN.close();
    FILEOUT.close();
    return 0;
}



/* ================== Quine McCluskey ================== */
void QM_init(ifstream& FILEIN, int& nVar, vector<int>& on_set, vector<int>& dc_set){
    string cmd;
    string inputs;

    for (int i = 0; i < 3; i++){
        getline(FILEIN, cmd);
        if (cmd == ".i") {
            getline(FILEIN, inputs);
            stringstream ss(inputs);
            ss >> nVar;
        }
        else if (cmd == ".m") {
            getline(FILEIN, inputs);
            stringstream ss(inputs);
            int num;
            while(ss >> num) on_set.push_back(num);
        }
        else if (cmd == ".d") {
            getline(FILEIN, inputs);
            stringstream ss(inputs);
            int num;
            while(ss >> num) dc_set.push_back(num);
        }
    }
}

void QM_dec2bin(int& nVar, vector<int>& set_dec, vector<string>& set_bin){
    int size = set_dec.size();
    for (int element = 0; element < size; element++){
        string binary, leading_zero;
        int num = set_dec[element];
        for (int i = 0; i < nVar; i++){
            binary += (num % 2) ? '1' : '0';
            num /= 2;
        }
        reverse(binary.begin(), binary.end());
        set_bin.push_back(binary);
    }
}

void QM_get_prime_implicant(vector<string>& implicant, vector<string>& primeImplicant){
    vector<string> temp;
    int size = implicant.size();
    vector<bool> mergable(size, false);
    for(int i = 0; i < size; i++){
        for (int j = i + 1; j < size; j++){
            if (count_num_of_one(implicant[i]) + 1 != count_num_of_one(implicant[j]))
                continue;

            // cout << i << " " << j << endl; //!
            if (isGrayCode(implicant[i], implicant[j])){
                mergable[i] = true;
                mergable[j] = true;
                string new_Implicant = merge_implicant(implicant[i], implicant[j]);
                if (find(temp.begin(), temp.end(), new_Implicant) == temp.end())
                    temp.push_back(new_Implicant);
            }
        }
    }

    for (int i = 0; i < size; i++){
        if (!mergable[i]) primeImplicant.push_back(implicant[i]);
    }
    implicant.clear();
    implicant.insert(implicant.end(), temp.begin(), temp.end());
}

void print_implicant(vector<string>& implicant){
    int size = implicant.size();
    for (int i = 0; i < size; i++){
        cout << implicant[i] << " ";
    }
    cout << endl;
}

void convert_to_alphabetic_format(vector<string>& primeImplicant, vector<string>& primeImplicant_alpha){
    int size = primeImplicant.size();
    for (int i = 0; i < size; i++){
        string implicant_alpha;
        int char_size = primeImplicant[i].size();
        for (int j = 0; j < char_size; j++){
            if (primeImplicant[i][j] != '-')
                implicant_alpha += ('A' + j);
            if (primeImplicant[i][j] == '0')
                implicant_alpha += "'";
        }
        primeImplicant_alpha.push_back(implicant_alpha);
    }
}

void write_result(ofstream& FILEOUT ,vector<string> primeImplicant, vector<string> minimum_cover){
    // Prime Implicants
    vector<string> primeImplicant_alpha;
    sort(primeImplicant.begin(), primeImplicant.end(), sort_by_alphabet);
    convert_to_alphabetic_format(primeImplicant, primeImplicant_alpha);

    int p_size = primeImplicant.size();
    FILEOUT << ".p " << p_size << endl;
    for (int i = 0; i < min(p_size, 15); i++){
        FILEOUT << primeImplicant_alpha[i] << endl;
    }

    // Minimum covering
    vector<string> minimum_cover_alpha;
    reverse(minimum_cover.begin(), minimum_cover.end());
    convert_to_alphabetic_format(minimum_cover, minimum_cover_alpha);

    int literal = 0;
    int mc_size = minimum_cover.size();
    FILEOUT << endl << ".mc " << mc_size << endl;
    for (int i = 0; i < mc_size; i++){
        literal += count(minimum_cover[i].begin(), minimum_cover[i].end(), '0');
        literal += count(minimum_cover[i].begin(), minimum_cover[i].end(), '1');
        FILEOUT << minimum_cover_alpha[i] << endl;
    }
    FILEOUT << "literal=" << literal;


}

/* ================== Petrick ==================*/
void Petrick_get_POS(vector<vector<string>>& product_of_sum, vector<string>& on_set_bin, vector<string>& primeImplicant){
    int on_size = on_set_bin.size();
    int prime_size = primeImplicant.size();
    for (int i = 0; i < on_size; i++){
        vector<string> col;
        for (int j = 0; j < prime_size; j++){
            // Check whether the prime implicant is in the on-set
            if (prime_is_on_onset(on_set_bin[i], primeImplicant[j])){
                col.push_back(primeImplicant[j]);
            }
        }
        product_of_sum.push_back(col);
    }
}

bool prime_is_on_onset(string on_set, string primeImplicant){
    int size = on_set.size();
    int diff = 0;
    for (int i = 0; i < size; i++){
        if (on_set[i] == '0' && primeImplicant[i] == '1') diff++;
        if (primeImplicant[i] == '0' && on_set[i] == '1') diff++;
    }
    return (diff == 0);
}

void Petrick_remove_redundant_terms(vector<vector<string>>& product_of_sum){
    vector<string> essential_primeImplicant;
    int POS_size = product_of_sum.size();
    for (int i = 0; i < POS_size; i++){
        int size = product_of_sum[i].size();
        if (size == 1){
            essential_primeImplicant.push_back(product_of_sum[i][0]);
        }
    }
    // cout << endl << "\033[1;31mBefore simplification:\033[0m" << endl;
    // Petrick_print_POS(product_of_sum);

    // cout << endl << "\033[1;31mEssential Prime Implicants:\033[0m" << endl;
    // print_implicant(essential_primeImplicant);
    // cout << endl;

    int size = essential_primeImplicant.size();
    for (int i = 0; i < size; i++){
        // cout << "\033[92m" << "Target: " << "\033[0m" << essential_primeImplicant[i] << endl;
        for (auto itr = product_of_sum.begin(); itr != product_of_sum.end(); itr++){
            // cout << "\033[94mCurrent iteration:\033[0m ";
            // print_implicant(*itr);
            if (find((*itr).begin(), (*itr).end(), essential_primeImplicant[i]) != (*itr).end()  &&  (*itr).size() != 1){
                // cout << "\033[94mDelete: \033[0m ";
                // print_implicant(*itr);
                product_of_sum.erase(itr);
                itr--;
            }
        }
        // Petrick_print_POS(product_of_sum);
    }
    // cout << endl << "\033[1;31mAfter simplification:\033[0m" << endl;
    // Petrick_print_POS(product_of_sum);

}


void Petrick_solve_for_SOP(vector<vector<string>>& product_of_sum, vector<set<string>>& sum_of_product){
    // Initialize sum_of_product
    int size = product_of_sum[0].size();
    for (int i = 0; i < size; i++){
        set<string> product({product_of_sum[0][i]});
        sum_of_product.push_back(product);
    }

    // cout << endl << "Round: " << "0" << endl;
    // Petrick_print_SOP(sum_of_product);
    // cout << "========================================================" << endl;

    // Start Expansion
    int nTerm = product_of_sum.size();
    for (int i = 1; i < nTerm; i++){

        Petrick_expand(sum_of_product, product_of_sum[i]);



        // cout << endl << "Round: " << i << endl;
        // cout << "New Term: "; print_implicant(product_of_sum[i]);
        // Petrick_print_SOP(sum_of_product);
        // cout << "========================================================" << endl;
    }
}

void Petrick_expand(vector<set<string>>& current_sop, vector<string> newTerm){
    vector<set<string>> tmp_sop;
    vector<set<string>> new_sop;


    int sop_size = current_sop.size();
    int nTerm = newTerm.size();
    int minTerm = INT_MAX;
    for (int i = 0; i < sop_size; i++){
        for (int j = 0; j < nTerm; j++){
            set<string> product = current_sop[i];
            product.insert(newTerm[j]);
            int product_size = product.size();
            minTerm = (product_size < minTerm) ? product_size : minTerm;
            tmp_sop.push_back(product);
        }
    }

    for (auto &sop: tmp_sop){
        int size = sop.size();
        if (size == minTerm)
            new_sop.push_back(sop);
    }

    current_sop = new_sop;
}

void Petrick_print_SOP(vector<set<string>>& sum_of_product){
    for (auto &term: sum_of_product){
        for (auto &primeImplicant: term){
            cout << primeImplicant << " ";
        }
        cout << endl;
    }
}

void Petrick_print_POS(vector<vector<string>>& product_of_sum){
    for (auto &col: product_of_sum){
        for (auto &primeImplicant: col){
            cout << primeImplicant << " ";
        }
        cout << endl;
    }
}
/* ================== Small Functions ================== */
bool sort_by_num_of_ones(string a, string b){
    assert(a.size() == b.size());
    int ones_a = count_num_of_one(a);
    int ones_b = count_num_of_one(b);
    return ones_a < ones_b;
}

bool sort_by_alphabet(string a, string b){
    return a > b;
}

bool sort_by_SOP(set<string> a, set<string> b){
    int literal_a = 0, literal_b = 0;
    for (auto itr = a.begin(); itr != a.end(); itr++){
        string implicant = *itr;
        literal_a += count(implicant.begin(), implicant.end(), '0');
        literal_a += count(implicant.begin(), implicant.end(), '1');
    }
    for (auto itr = b.begin(); itr != b.end(); itr++){
        string implicant = *itr;
        literal_b += count(implicant.begin(), implicant.end(), '0');
        literal_b += count(implicant.begin(), implicant.end(), '1');
    }

    return literal_a < literal_b;
    // return a.size() < b.size();
}

int count_num_of_one(string a){
    int count = 0;
    int size = a.size();
    for (int i = 0; i < size; i++){
        if (a[i] == '1')  count++;
    }
    return count;
}

bool isGrayCode(string a, string b){
    assert(a.size() == b.size());
    int diff = 0;
    int size = a.size();
    for (int i = 0; i < size; i++){
        diff += (a[i] != b[i]);
    }
    return (diff == 1);
}

string merge_implicant(string a, string b){
    assert(a.size() == b.size());
    int size = a.size();
    string merged_implicant;
    for (int i = 0; i < size; i++){
        merged_implicant += (a[i] != b[i]) ? '-' : a[i];
    }
    return merged_implicant;
}