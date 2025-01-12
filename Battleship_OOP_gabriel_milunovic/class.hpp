#ifndef CLASS_HPP
#define CLASS_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <tuple>

using namespace std;

const int velicina = 10;
const vector<int> brodovi = {5, 4, 3, 3, 2}; // carrier, battleship, submarine, cruiser, destroyer
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string RESET = "\033[0m";
const string YELLOW = "\033[33m";



class Igrac{
private:
    vector<vector<char>> ploca;
    vector<vector<char>> pogodci;
public:
    Igrac() : ploca(velicina, vector<char>(velicina, '~')),
                pogodci(velicina, vector<char>(velicina, '~')) {}
    vector<vector<char>>& getPloca() {return ploca;}
    const vector<vector<char>>& getPloca() const {return ploca;}

    vector<vector<char>>& getPogodci() {return pogodci;}
    const vector<vector<char>>& getPogodci() const {return pogodci;}

    
    bool provjeraPozicije(int x, int y, int brod, int smjer) const;
    void postaviBrod(int x, int y, int brod, int smjer);
    
};
class Ai : public Igrac {
public:
    vector<pair<int,int>> pogodciAi;
    
    pair<int, int> napadAi();
};

#endif
