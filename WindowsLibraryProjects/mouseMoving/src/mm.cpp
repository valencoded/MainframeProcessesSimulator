#include <windows.h>
#include <iostream>
using namespace std;
int main() {

    POINT pAnterior, pActual;

    while (true) {
        // Obtener la posición actual del mouse
        if (GetCursorPos(&pActual)) {
            // Comparar con la posición anterior
            if (pActual.x > pAnterior.x)
                cout << "Movimiento hacia la derecha." << endl;
            else if (pActual.x < pAnterior.x)
                cout << "Movimiento hacia la izquierda." << endl;
            //para arriba y abajo seria lo mismo pero con y
        }
        pAnterior = pActual;
        Sleep(100); // Evitar sobrecargar el CPU
    }
    return 0;
}