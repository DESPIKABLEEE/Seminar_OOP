#include "class.hpp"

bool jePotopljen(const vector<vector<char>>& ploca, int x, int y) {
    for (int i = x; i >= 0 && ploca[i][y] != '~'; i--) {
        if (ploca[i][y] == 'S') return false;
    }
    for (int i = x + 1; i < velicina && ploca[i][y] != '~'; i++) {
        if (ploca[i][y] == 'S') return false;
    }

    for (int j = y; j >= 0 && ploca[x][j] != '~'; j--) {
        if (ploca[x][j] == 'S') return false;
    }
    for (int j = y + 1; j < velicina && ploca[x][j] != '~'; j++) {
        if (ploca[x][j] == 'S') return false;
    }

    return true;
}

void printPloca(const vector<vector<char>>& ploca, const vector<vector<char>>& pogodci, bool prikaziBrodove) {
    cout << "  ";
    for (int i = 0; i < velicina; i++) cout << i << " ";
    cout << endl;

    for (int i = 0; i < velicina; i++) {
        cout << i << " ";
        for (int j = 0; j < velicina; j++) {
            if (pogodci[i][j] == 'X') {
                cout << GREEN << pogodci[i][j] << RESET << " ";
            }
            else if (pogodci[i][j] == 'O') {
                cout << RED << pogodci[i][j] << RESET << " ";
            }
            else if (prikaziBrodove && ploca[i][j] == 'S') {
                if (pogodci[i][j] == 'X') {
                    cout << YELLOW << 'S' << RESET << " ";
                }
                else {
                    cout << 'S' << " ";
                }
            }
            else if (ploca[i][j] == 'X') {
                cout << YELLOW << 'S' << RESET << " ";
            }
            else {
                cout << '~' << " ";
            }
        }
        cout << endl;
    }
}




bool Igrac::provjeraPozicije(int x, int y, int brod, int smjer) const {
    if (smjer == 0 && x + brod > velicina) {
        return false;
    }
    if (smjer == 1 && y + brod > velicina) {
        return false;
    }
    int i;
    for (i = 0; i < brod; i++) {
        int bx = x + (smjer == 0 ? i : 0);
        int by = y + (smjer == 1 ? i : 0);
        if (getPloca()[bx][by] != '~') {
            return false;
        }
        // susjedne
        int susjedneX, susjedneY, drugiX, drugiY;
        for (susjedneX = -1; susjedneX <= 1; susjedneX++) {
            for (susjedneY = -1; susjedneY <= 1; susjedneY++) {
                drugiX = bx + susjedneX;
                drugiY = by + susjedneY;
                if (drugiX >= 0 && drugiX < velicina && drugiY >= 0 && drugiY < velicina) {
                    if (getPloca()[drugiX][drugiY] != '~') {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void Igrac::postaviBrod(int x, int y, int brod, int smjer) {
    for (int i = 0; i < brod; i++) {
        int ix = x + (smjer == 0 ? i : 0);
        int iy = y + (smjer == 1 ? i : 0);
        getPloca()[ix][iy] = 'S';
    }
}
pair<int, int> Ai::napadAi() {
    if (!(pogodciAi.empty())) {
        pair<int, int> koordinata = pogodciAi.back();
        pogodciAi.pop_back();
        return koordinata;
    }
    int x, y;
    do {
        x = rand() % velicina;
        y = rand() % velicina;
    } while (getPogodci()[x][y] != '~');
    return { x, y };
}

bool napad(Igrac& igrac, int x, int y) {
    if (igrac.getPloca()[x][y] == 'S') {
        igrac.getPloca()[x][y] = 'X';
        return true;
    }
    else if (igrac.getPloca()[x][y] == '~') {
        igrac.getPloca()[x][y] = 'O';
    }
    return false;
}

void igraPloca(Igrac& igrac, bool ai) {
    for (int brod : brodovi) {
        bool pos = false;
        while (!pos) {
            int x, y, smjer;
            if (ai) {
                x = rand() % velicina;
                y = rand() % velicina;
                smjer = rand() % 2;
            }
            else {
                printPloca(igrac.getPloca(), igrac.getPogodci(), true);
                cout << "Postavljate brod velicine " << brod << " : " << endl;
                cout << "Unesite x, y i smjer (0 za horizontalno, 1 za vertikalno): ";
                cin >> x >> y >> smjer;

                while (x < 0 || x >= velicina || y < 0 || y >= velicina || (smjer != 0 && smjer != 1)) {
                    cout << "Nevalidan unos, probaj ponovo." << endl;
                    cout << "Unesite x, y i smjer (0 za horizontalno, 1 za vertikalno): ";
                    cin >> x >> y >> smjer;
                }
            }
            if (igrac.provjeraPozicije(x, y, brod, smjer)) {
                igrac.postaviBrod(x, y, brod, smjer);
                pos = true;
            }
            else if (!ai) {
                cout << "Netocna pozicija, pokusaj ponovno" << endl;
            }
        }
    }
}

void igra(bool ai) {
    Igrac prviIgrac;
    Ai drugiIgrac;

    igraPloca(prviIgrac, false);
    igraPloca(drugiIgrac, ai);

    bool prviNaRedu = true;

    while (true) {

        if (prviNaRedu) {
            printPloca(prviIgrac.getPloca(), prviIgrac.getPogodci(), true);
        }
        else if (ai) {
            printPloca(drugiIgrac.getPloca(), drugiIgrac.getPogodci(), false);
        }
        else {
            printPloca(drugiIgrac.getPloca(), drugiIgrac.getPogodci(), true);
        }


        int x, y;
        if (prviNaRedu || !ai) {
            cout << "Unesite koordinate napada (x,y): ";
            cin >> x >> y;

            while (x < 0 || x >= velicina || y < 0 || y >= velicina ||
                (prviNaRedu ? prviIgrac.getPogodci()[x][y] : drugiIgrac.getPogodci()[x][y]) != '~') {
                cout << "Nevalidan unos, probaj ponovo." << endl;
                cout << "Unesite koordinate napada (x,y): ";
                cin >> x >> y;
            }
        }
        else {
            tie(x, y) = drugiIgrac.napadAi();
            cout << "Bot napada: (" << x << ", " << y << ")" << endl;
        }

        bool pogodak = napad(prviNaRedu ? drugiIgrac : prviIgrac, x, y);


        if (prviNaRedu) {
            prviIgrac.getPogodci()[x][y] = pogodak ? 'X' : 'O';
        }
        else {
            drugiIgrac.getPogodci()[x][y] = pogodak ? 'X' : 'O';
        }

        if (pogodak) {
            cout << GREEN << "Pogodak!!" << RESET << endl;
            if (jePotopljen(prviNaRedu ? drugiIgrac.getPloca() : prviIgrac.getPloca(), x, y)) {
                cout << GREEN << "Potopili ste brod!" << RESET << endl;
            }
        }
        else {
            cout << RED << "Promasaj!!" << RESET << endl;
        }

        cout << "--------------------------" << endl;

        if (all_of(drugiIgrac.getPloca().begin(), drugiIgrac.getPloca().end(), [](const vector<char>& red) {
            return all_of(red.begin(), red.end(), [](char c) { return c != 'S'; });
            })) {
            cout << "Igrac 1 je pobijedio!" << endl;
            break;
        }
        else if (all_of(prviIgrac.getPloca().begin(), prviIgrac.getPloca().end(), [](const vector<char>& red) {
            return all_of(red.begin(), red.end(), [](char c) { return c != 'S'; });
            })) {
            cout << (ai ? "AI" : "Igrac 2") << " je pobijedio!" << endl;
            break;
        }
        prviNaRedu = !prviNaRedu;
    }
}


int main() {
    srand(time(0));
    cout << "Dobrodosli u battleship igru" << endl;
    cout << "Unesite 1 za igru protiv Ai-a ili 2 za igru protiv drugog igraca: " << endl;
    int n;
    cin >> n;
    if (n == 1) {
        igra(true);
    }
    else if (n == 2) {
        igra(false);
    }
    else {
        cout << "Nevalidan unos";
    }
    return 0;
}