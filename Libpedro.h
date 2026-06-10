// Materia: Programación I, Paralelo 4
// Grupo: 6
// Autor: Pedro Enrique Méndez Verdástegui
// Fecha creación: 05-06-2026
// Nombre del miniproyecto: Librería Farmacia - Opciones 2 y 5

#ifndef LIBPEDRO_H
#define LIBPEDRO_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "libJuan.h"

using namespace std;

void ProcesarVentas(string nombreArchivo);
void AdicionarVentaManual();

void ProcesarVentas(string nombreArchivo) {
    fstream archivoBin;
    structProducto producto;

    archivoBin.open(nombreArchivo, ios::in | ios::out | ios::binary);
    if (!archivoBin.is_open()) {
        cout << "No hay productos registrados." << endl;
        return;
    }

    system("cls");
    cout << "==================================== REPORTE DE VENTAS ====================================" << endl;
    cout << left << setw(8) << "CODIGO" 
         << setw(20) << "NOMBRE PRODUCTO" 
         << setw(15) << "CANT.INICIAL" 
         << setw(10) << "PRECIO" 
         << setw(15) << "CANT.VENDIDA" 
         << setw(12) << "TOTAL (Bs)" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;

    struct Venta {
        int codProd;
        int cant;
    };
    Venta listaVentas[1000];
    int totalVentas = 0;

    ifstream archivoTxt;
    archivoTxt.open("VENTAS.txt", ios::in);
    if (archivoTxt.is_open()) {
        int ci;
        char nombreCli[50];
        int cod;
        int cantidad;
        char separador;

        while (archivoTxt >> ci >> separador) {
            archivoTxt.getline(nombreCli, 50, ';');
            archivoTxt >> cod >> separador >> cantidad;
            listaVentas[totalVentas].codProd = cod;
            listaVentas[totalVentas].cant = cantidad;
            totalVentas++;
        }
        archivoTxt.close();
    }

    while (archivoBin.read((char*)&producto, sizeof(structProducto))) {
        int vendido = 0;

        for (int i = 0; i < totalVentas; i++) {
            if (listaVentas[i].codProd == producto.codigo) {
                vendido += listaVentas[i].cant;
            }
        }

        double totalBs = vendido * producto.precioUnitario;
        int stockAnterior = producto.cantidadInicial;

        if (vendido > 0) {
            producto.cantidadInicial -= vendido;
            archivoBin.seekp(-sizeof(structProducto), ios::cur);
            archivoBin.write((char*)&producto, sizeof(structProducto));
        }

        cout << left << setw(8) << producto.codigo
             << setw(20) << producto.nombre
             << setw(15) << stockAnterior
             << setw(10) << producto.precioUnitario
             << setw(15) << vendido
             << setw(12) << totalBs << endl;
    }

    archivoBin.close();
    cout << "===========================================================================================" << endl;
}

void AdicionarVentaManual() {
    ofstream archivo;
    char ci[20];
    char nombre[50];
    int codigo;
    int cantidad;

    system("cls");
    cout << "==================== ADICIONAR VENTA MANUAL ====================" << endl;

    archivo.open("VENTAS.txt", ios::app);
    if (archivo.is_open()) {
        cout << "Ingrese CI del cliente: ";
        cin.ignore();
        cin.getline(ci, 20);

        cout << "Ingrese Nombre del Cliente: ";
        cin.getline(nombre, 50);

        cout << "Ingrese Codigo del Producto: ";
        cin >> codigo;

        cout << "Ingrese Cantidad Comprada: ";
        cin >> cantidad;

        archivo << ci << ";" << nombre << ";" << codigo << ";" << cantidad << endl;
        archivo.close();

        cout << "\nVenta registrada exitosamente en VENTAS.txt" << endl;
    } else {
        cout << "Error: No se pudo abrir el archivo VENTAS.txt" << endl;
    }
}

#endif
