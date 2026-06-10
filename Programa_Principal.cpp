// Materia: Programación I, Paralelo 4
// Grupo: 1
// Autor: Juan
// Fecha creación: 27-05-2026
// Nombre del miniproyecto: Menú de Inventario - Farmacias Chávez

#include <iostream>
#include "libjuan.h" 

using namespace std;

void MenuOpciones(string nombreArchivo);

int main() {
    string nombreArchivo = "PRODUCTOS.BIN";
    system("chcp 65001"); 
    MenuOpciones(nombreArchivo);
    return 0;
}

void MenuOpciones(string nombreArchivo) {
    int opcion = 0;
    do {
        system("cls");
        cout << "SISTEMA DE INVENTARIO - FARMACIAS CHÁVEZ" << endl;
        cout << "========================================" << endl;
        cout << "1. Opción 1: Adicionar Producto" << endl;
        cout << "4. Opción 4: Modificar Atributos de Producto" << endl;
        cout << "0. Salir" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); 

        system("cls");

        switch (opcion) {
            case 1:
                AdicionarProducto(nombreArchivo);
                system("pause");
                break;
            case 4: 
                ModificarProducto(nombreArchivo);
                system("pause");
                break;
            case 0:
                cout << "Saliendo del módulo de inventario..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
                system("pause");
                break;
        } 
    } while (opcion != 0); 

    system("cls");
    cout << "SE HA SALIDO DEL MENÚ PRINCIPAL" << endl; 
}