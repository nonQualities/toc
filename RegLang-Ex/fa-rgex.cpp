#include <iostream>
#include <string>
#include <vector>

enum Q{
  STATE1, STATE2, STATE3, HEAD, END  
};

struct Trans{
  char in;
  Q fs;
  Q ts;
};

Q delta(const std::vector<Trans>&table, Q curr_s, char in){

    for ( auto t : table) {
        if(t.fs == curr_s && t.in == in) return t.ts;
    }
    return END;
}

std::string print_state_name(Q q){
switch (q) {
    case STATE1: return "STATE1";
    case STATE2: return "STATE2";
    case STATE3: return "STATE3";
    case    END: return "END";
    case   HEAD: return "HEAD";
    default    : return "INVALID";
}
}

int main(){
    std::vector<Trans>trn_map{
    {'a', STATE1, STATE3},
    {'b', STATE3, STATE2},
    {'a', STATE2, STATE1 }
    };

    Q F = STATE3;
    Q Q0 = STATE1;
    std::string str_in= "abaabaa";
    std::cout <<"STATE: "<<print_state_name(Q0) << "\n" ;

    for(char c : str_in){
        Q0 = delta(trn_map, Q0, c);
        std::cout << "Read: "<< c <<"--->" << print_state_name(Q0) <<"\n";
        if(Q0==END) break;
    
    }

    if(Q0 == F) std::cout<<"String Accepted\n";
    else std::cout << "String Rejected\n";
    return 0;
}
