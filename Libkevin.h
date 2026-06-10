// Materia: Programación I, Paralelo 4
// Grupo: 6
// Autor: Kevin Sucaticona 
// Fecha creación: 10-06-2026
// Nombre del miniproyecto: Libreria Farmacia - Opcion 3

#ifndef LIBKEVIN_H
#define LIBKEVIN_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "libJuan.h"

using namespace std;

void BuscarProductoPorCodigo(string nombreArchivo);

void BuscarProductoPorCodigo(string nombreArchivo) {
    ifstream archivoBin;
    structProducto producto;
    int codigoBuscar;
    bool encontrado = false;

    system("cls");
    cout << "==================== BUSCAR PRODUCTO POR CODIGO ====================" << endl;
    cout << "Ingrese el codigo del producto a buscar: ";
    cin >> codigoBuscar;
    cin.ignore();

    archivoBin.open(nombreArchivo, ios::binary);
    if (!archivoBin.is_open()) {
        cout << "Error: No se pudo abrir el archivo o no hay productos registrados." << endl;
        system("pause");
        return;
    }

    while (archivoBin.read((char*)&producto, sizeof(structProducto))) {
        if (producto.codigo == codigoBuscar) {
            encontrado = true;
            cout << "\n PRODUCTO ENCONTRADO EXITOSAMENTE:" << endl;
            cout << "----------------------------------------------------------------" << endl;
            cout << "Codigo:         " << producto.codigo << endl;
            cout << "Nombre:         " << producto.nombre << endl;
            cout << "Stock Actual:   " << producto.cantidadInicial << " unidades" << endl;
            cout << "Precio Unitario: " << producto.precioUnitario << " Bolivianos" << endl;
            cout << "----------------------------------------------------------------" << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << " No existe ningun producto registrado con el codigo: " << codigoBuscar << endl;
    }

    archivoBin.close();
}

#endif
