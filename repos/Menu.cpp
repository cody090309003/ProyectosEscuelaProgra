#include "Menu.h"
#include <iostream>
using namespace std;

void Menu::MostrarMenu() const
{
    int opcionMenu;
    do {
        system("cls");
        cout << "        Menu\n"
            << "1 - Reservar vuelo\n"
            << "2 - Pagar boleto\n"
            << "3 - Salir" << endl;
        cin >> opcionMenu;

        switch (opcionMenu)
        {
        case 1:
            cout << "Reservar vuelo" << endl;
            break;
        default:
            break;
        }
    } while (opcionMenu != 3);
}
