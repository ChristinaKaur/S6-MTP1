#include <iostream>
#include <iomanip>

using namespace std;

const string EOS = "0";

struct Pacient {
    string DNI;
    string cognom;
    string nom;
    int gravetat;
};

const int MAX = 1000;
typedef Pacient Taula_pacients[MAX];

void omplir_taula(Taula_pacients& pacients, int& n)
{
    n = 0;
    string DNI;
    cin >> DNI;
    while (DNI != EOS and n < MAX)
    {
        pacients[n].DNI = DNI;
        cin >> pacients[n].cognom;
        cin >> pacients[n].nom;
        cin >> pacients[n].gravetat;
        n++;
        cin >> DNI;
    }
}

int posicio_del_maxim_des_de(const Taula_pacients vec, int n, int inici) {
    //Pre: 0 <= inici < n <= MAX
    //Post: retorna la posició del pacient amb gravetat maxima de vec[inici..n - 1] i si n'hi ha dos amb la mateixa gravetat, amb DNI màxim
    int pos_max = inici;
    for (int i = inici + 1; i < n; i++)
    {
        if (vec[i].gravetat > vec[pos_max].gravetat) pos_max = i;
        else if (vec[i].gravetat == vec[pos_max].gravetat)
        {
            if (vec[i].DNI < vec[pos_max].DNI) pos_max = i;
        }
    }
    return pos_max;
}

void intercanvia(Pacient& a, Pacient& b)
{
    //Pre: a=A i b=B
    //Post: a=B i b=A
    Pacient aux = a;
    a = b;
    b = aux;
}

void ordenar_per_gravetat_decreixent(Taula_pacients& vec, const int n)
{
    //Pre: 0<=n<=MAX, vec=VEC
    //Post: vec[0..n-1] conté el elements de VEC[0..n-1] ordenats per gravetat decreixent
    for (int i = 0; i < n; i++) 
    {
        int pos_max = posicio_del_maxim_des_de(vec, n, i);
        intercanvia(vec[i], vec[pos_max]);
    }
}

void mostrar_pacients(Taula_pacients vec, const int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << vec[i].DNI << " " << vec[i].cognom << " " << vec[i].nom << " " << vec[i].gravetat << endl;
    }
}

int nombre_de_pacients_greus(Taula_pacients vec, const int n, const int llindar)
{
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        if (vec[i].gravetat >= llindar) num++;
    }
    return num;
}

int main() {
    Taula_pacients pacients;
    int n;
    cout << "Informacio dels pacients (" << EOS << " per acabar):" << endl;
    omplir_taula(pacients, n);
    ordenar_per_gravetat_decreixent(pacients, n);

    cout << "Ordre segons gravetat:" << endl;
    mostrar_pacients(pacients, n);

    cout << "Nivell de gravetat: ";
    int llindar;
    cin >> llindar;
    cout << "Nombre de pacients: " << nombre_de_pacients_greus(pacients, n, llindar) << endl;

    return 0;
}
