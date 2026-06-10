// Materia: Programación I, Paralelo 4
// Grupo: 6
// Autor: Juan, Pedro
// Fecha creación: 05-06-2026
// Nombre del miniproyecto: Menú de Inventario - Farmacias Chávez
#include <iostream>
#include "libJuan.h"
#include "libKevin.h"
#include "Libpedro.h"

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

        cout << "        SISTEMA DE INVENTARIO - FARMACIAS CHAVEZ" << endl;
        cout << "=========================================================" << endl;
        cout << "1. Opcion 1: Adicionar Producto           " << endl;
        cout << "2. Opcion 2: Procesar Ventas y Listar     " << endl;
        cout << "3. Opcion 3: Buscar Producto por Codigo   " << endl;
        cout << "4. Opcion 4: Modificar Atributos          " << endl;
        cout << "5. Opcion 5: Adicionar Ventas Manuales    " << endl;
        cout << "0. Salir" << endl;
        cout << "=========================================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        system("cls");

        switch (opcion) {
        case 1:
            AdicionarProducto(nombreArchivo);
            system("pause");
            break;
        case 2:
            ProcesarVentas(nombreArchivo);
            system("pause");
            break;
        case 3:
            BuscarProductoPorCodigo(nombreArchivo);
            system("pause");
            break;
        case 4:
            ModificarProducto(nombreArchivo);
            system("pause");
            break;
        case 5:
            AdicionarVentaManual();
            system("pause");
            break;
        case 0:
            cout << "Saliendo del modulo de inventario..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            system("pause");
            break;
        }

    } while (opcion != 0);

    system("cls");
    cout << "SE HA SALIDO DEL MENU PRINCIPAL" << endl;
}
