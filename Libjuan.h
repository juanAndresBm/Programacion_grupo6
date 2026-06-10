// Materia: Programación I, Paralelo 4
// Grupo: 1
// Autor: Juan
// Fecha creación: 27-05-2026
// Nombre del miniproyecto: Libreria Farmacia - Ejercicio 2

#ifndef LIBJUAN_H
#define LIBJUAN_H

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct structProducto {
    int codigo;
    char nombre[30];
    int cantidadInicial;
    double precioUnitario;
};

void AdicionarProducto(string nombreArchivo);
void ModificarProducto(string nombreArchivo);
bool ExisteCodigo(string nombreArchivo, int codigoBuscar);
bool ExisteNombre(string nombreArchivo, const char* nombreBuscar);

bool ExisteCodigo(string nombreArchivo, int codigoBuscar) {
    ifstream archivo;
    structProducto producto;
    bool encontrado = false;

    archivo.open(nombreArchivo, ios::binary);
    
    if (!archivo.is_open()) {
        return false; 
    }

    while (archivo.read((char*)&producto, sizeof(structProducto))) {
        if (producto.codigo == codigoBuscar) {
            encontrado = true;
            break;
        }
    }
    
    archivo.close();
    return encontrado;
}

bool ExisteNombre(string nombreArchivo, const char* nombreBuscar) {
    ifstream archivo;
    structProducto producto;
    bool encontrado = false;

    archivo.open(nombreArchivo, ios::binary);
    
    if (!archivo.is_open()) {
        return false;
    }

    while (archivo.read((char*)&producto, sizeof(structProducto))) {
        if (strcmp(producto.nombre, nombreBuscar) == 0) {
            encontrado = true;
            break;
        }
    }
    
    archivo.close();
    return encontrado;
}

void AdicionarProducto(string nombreArchivo) {
    ofstream archivo;
    structProducto nuevoProducto;

    cout << "ADICIONAR PRODUCTO" << endl;
    cout << "==================" << endl;
    
    cout << "Ingrese el código del producto: ";
    cin >> nuevoProducto.codigo;
    cin.ignore(); 

    if (ExisteCodigo(nombreArchivo, nuevoProducto.codigo)) {
        cout << "Error: El código " << nuevoProducto.codigo << " ya se encuentra registrado." << endl;
        return;
    }

    cout << "Ingrese el nombre del producto: ";
    cin.getline(nuevoProducto.nombre, 30);

    if (ExisteNombre(nombreArchivo, nuevoProducto.nombre)) {
        cout << "Error: El producto con nombre '" << nuevoProducto.nombre << "' ya existe." << endl;
        return;
    }

    cout << "Ingrese la cantidad inicial (Stock): ";
    cin >> nuevoProducto.cantidadInicial;
    
    cout << "Ingrese el precio unitario: ";
    cin >> nuevoProducto.precioUnitario;
    cin.ignore(); 

    archivo.open(nombreArchivo, ios::binary | ios::app);
    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo para guardar." << endl;
    } else {
        archivo.write((char*)&nuevoProducto, sizeof(structProducto));
        cout << "Producto adicionado correctamente en PRODUCTOS.BIN." << endl;
    }
    archivo.close();
}

void ModificarProducto(string nombreArchivo) {
    fstream archivo;
    structProducto producto;
    int codigoBuscar;
    bool encontrado = false;
    int seleccion = 0;

    cout << "MODIFICAR ATRIBUTOS DE PRODUCTO" << endl;
    cout << "===============================" << endl;
    cout << "Ingrese el código del producto a modificar: ";
    cin >> codigoBuscar;
    cin.ignore(); 

    archivo.open(nombreArchivo, ios::in | ios::out | ios::binary);

    if (archivo.fail()) {
        cout << "Error: El archivo PRODUCTOS.BIN no existe o no tiene registros." << endl;
        return;
    }

    while (archivo.read((char*)&producto, sizeof(structProducto))) {
        if (producto.codigo == codigoBuscar) {
            encontrado = true;
            
            cout << "\nProducto Encontrado:" << endl;
            cout << "\tNombre Actual: " << producto.nombre << endl;
            cout << "\tPrecio Actual: " << producto.precioUnitario << endl;
            cout << "-----------------------------------" << endl;
            cout << "1. Modificar Nombre" << endl;
            cout << "2. Modificar Precio Unitario" << endl;
            cout << "Seleccione una opción: ";
            cin >> seleccion;
            cin.ignore(); 

            if (seleccion == 1) {
                char nuevoNombre[30];
                cout << "Ingrese el nuevo nombre: ";
                cin.getline(nuevoNombre, 30);
                
                if (ExisteNombre(nombreArchivo, nuevoNombre)) {
                    cout << "Error: Ese nombre ya está en uso por otro producto." << endl;
                } else {
                    strcpy(producto.nombre, nuevoNombre);
                }
            } else if (seleccion == 2) {
                cout << "Ingrese el nuevo precio unitario: ";
                cin >> producto.precioUnitario;
                cin.ignore(); 
            } else {
                cout << "Opción inválida. No se realizaron cambios." << endl;
                break;
            }

            archivo.seekp(-sizeof(structProducto), ios::cur);
            archivo.write((char*)&producto, sizeof(structProducto));
            cout << "Registro actualizado físicamente en disco con éxito." << endl;
            break; 
        }
    }

    if (!encontrado) {
        cout << "El producto con el código " << codigoBuscar << " no existe en el inventario." << endl;
    }

    archivo.close();
}

#endif