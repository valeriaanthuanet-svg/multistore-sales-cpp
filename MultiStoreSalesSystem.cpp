#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <fstream>


using namespace std;
using namespace System;

struct Producto
{
    string codigo;
    string nombre;
    string area;
    float precio;
    int stock;
    char estado;
};

struct Tienda
{
    string codigo;
    string nombre;
    string distrito;
};

struct Venta
{
    string codigoVenta;
    int dia;
    int mes;
    int anio;
    Tienda tienda;
    Producto producto;
    int cantidad;
    float total;
};

void presentacion()
{
    cout << "\n --------------------------------------------------\n";
    cout << "|         SISTEMA DE CONTROL MULTITIENDA           |\n";
    cout << "|           S A G A  F A L A B E L L A             |\n";
    cout << " --------------------------------------------------\n";
    cout << "\n";
    cout << "        Curso : Lenguaje de Programacion  \n";
    cout << "     Profesor : Ramirez Espinoza, Juan Alfonso\n";
    cout << "\n";
    cout << " INTEGRANTES DEL GRUPO\n";
    cout << " Integrante 1 : Flores Cancino, Nadia Cristal\n";
    cout << " Integrante 2 : Quispe Mendoza, Valeria Anthuane\n";
    cout << " Integrante 3 : Saravia, Andrea Fernanda\n";
    cout << " Integrante 4 : Salcedo Meza, Cristofer Juan\n";
    cout << "\n";
    cout << "---- Conectando tiendas, potenciando decisiones ----";
    _getch();
    Console::Clear();
}

void menu()
{
    cout << "\n=========================================\n";
    cout << " SISTEMA INTELIGENTE DE VENTAS MULTITIENDA\n";
    cout << "=========================================\n";
    cout << "[1] Cargar datos\n";
    cout << "[2] Registrar venta\n";
    cout << "[3] Generar ventas aleatorias\n";
    cout << "[4] Mostrar ventas\n";
    cout << "[5] Mostrar tiendas\n";
    cout << "[6] Reportes\n";
    cout << "[7] Salir\n";
}




void cargarProductos(Producto* productos, int& nProductos, string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    nProductos = 0;

    while (getline(archivo, productos[nProductos].codigo, '|'))
    {
        getline(archivo, productos[nProductos].nombre, '|');
        getline(archivo, productos[nProductos].area, '|');

        archivo >> productos[nProductos].precio;
        archivo.ignore();

        archivo >> productos[nProductos].stock;
        archivo.ignore();

        archivo >> productos[nProductos].estado;
        archivo.ignore();

        nProductos++;
    }

    archivo.close();
}

void cargarTiendas(Tienda* tiendas, int& nTiendas)
{
    ifstream archivo("tiendas.txt");
    nTiendas = 0;

    while (getline(archivo, tiendas[nTiendas].codigo, '|'))
    {
        getline(archivo, tiendas[nTiendas].nombre, '|');
        getline(archivo, tiendas[nTiendas].distrito);

        nTiendas++;
    }

    archivo.close();
}

int codigoTiendaExiste(Tienda* vtiendas, int nTiendas, string codTienda)
{
    for (int i = 0; i < nTiendas; i++)
    {
        if (vtiendas[i].codigo == codTienda)
        {
            return i;
        }
    }
    return -1;
}


int codigoProductoExiste(Producto* vproductos, int nProductos, string codProducto)
{
    for (int i = 0; i < nProductos; i++)
    {
        if (vproductos[i].codigo == codProducto)
        {
            return i;
        }
    }
    return -1;
}

int validarStock(Producto* vproductos, int posProducto, int cantidad)
{
    if (cantidad <= vproductos[posProducto].stock)
    {
        return 1;
    }

    return 0;
}

int validarCodigoVenta(Venta* vventas, int nVentas, string codigoVen)
{
    if (codigoVen.length() != 4) {
        return 1;
    }

    if (codigoVen[0] != 'V') {
        return 1;
    }

    for (int i = 0; i < nVentas; i++) {
        if (vventas[i].codigoVenta == codigoVen) {
            return 1;
        }
    }

    return 0;
}
int hayProductosDisponibles(Producto* vproductos, int nProductos)
{
    for (int i = 0; i < nProductos; i++)
    {
        if (vproductos[i].estado == 'S')
        {
            return 1;
        }
    }

    return 0;
}
int hayTiendasDisponibles(Producto* productosF01, int nF01, Producto* productosF02, int nF02, Producto* productosF03, int nF03, Producto* productosF04, int nF04, Producto* productosF05, int nF05)
{
    if (hayProductosDisponibles(productosF01, nF01) == 1)
        return 1;

    if (hayProductosDisponibles(productosF02, nF02) == 1)
        return 1;

    if (hayProductosDisponibles(productosF03, nF03) == 1)
        return 1;

    if (hayProductosDisponibles(productosF04, nF04) == 1)
        return 1;

    if (hayProductosDisponibles(productosF05, nF05) == 1)
        return 1;

    return 0;
}
void siguienteFecha(int& dia, int& mes)
{
    int diasMes;

    if (mes == 2)
        diasMes = 28;
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        diasMes = 30;
    else
        diasMes = 31;

    dia++;

    if (dia > diasMes)
    {
        dia = 1;
        mes++;
    }
}
void registrarVenta(Venta* vventas, int& nVentas, Tienda* vtiendas, int nTiendas, Producto* productosF01, int nF01, Producto* productosF02, int nF02, Producto* productosF03, int nF03, Producto* productosF04, int nF04, Producto* productosF05, int nF05) {
    string codTienda, codProducto, codventa;
    int posTienda, posProducto;
    int stocks, contador;
    int dia, mes, anio;
    Producto* vproductos;
    int nProductos;
    cout << "\n========== REGISTRAR VENTA ==========\n";
    do
    {
        cout << "Codigo de venta (ejm. V001): ";
        cin >> codventa;

        if (validarCodigoVenta(vventas, nVentas, codventa) == 1) {
            cout << "Error: el codigo debe empezar con V, tener 4 caracteres y no repetirse.\n";
        }

    } while (validarCodigoVenta(vventas, nVentas, codventa) == 1);
    vventas[nVentas].codigoVenta = codventa;
    cout << "\n========== FECHA ==========\n";

    do
    {
        cout << "Mes (1-12): ";
        cin >> mes;

        if (mes < 1 || mes > 12)
        {
            cout << "Mes invalido.\n";
        }

    } while (mes < 1 || mes > 12);

    do
    {
        cout << "Dia: ";
        cin >> dia;

        contador = 1;

        if (mes == 2)
        {
            if (dia < 1 || dia > 28)
                contador = 0;
        }
        else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        {
            if (dia < 1 || dia > 30)
                contador = 0;
        }
        else
        {
            if (dia < 1 || dia > 31)
                contador = 0;
        }

        if (contador == 0)
        {
            cout << "Dia invalido para ese mes.\n";
        }

    } while (contador == 0);

    vventas[nVentas].dia = dia;
    vventas[nVentas].mes = mes;
    vventas[nVentas].anio = 2026;

    do
    {
        cout << left << setw(15) << "COD. TIENDA" << setw(15) << "DISTRITO" << endl;
        cout << left << setw(15) << "F01" << setw(15) << "Chorrillos" << endl;
        cout << left << setw(15) << "F02" << setw(15) << "San Isidro" << endl;
        cout << left << setw(15) << "F03" << setw(15) << "Miraflores" << endl;
        cout << left << setw(15) << "F04" << setw(15) << "Barranco" << endl;
        cout << left << setw(15) << "F05" << setw(15) << "San Borja" << endl;
        cout << "INGRESE EL CODIGO DE TIENDA: ";
        cin >> codTienda;
        posTienda = codigoTiendaExiste(vtiendas, nTiendas, codTienda);

        if (posTienda == -1) {
            cout << "tienda no encontrada, vuelva a intentarlo" << endl;
        }
    } while (posTienda == -1);
    vventas[nVentas].tienda = vtiendas[posTienda];

    if (codTienda == "F01")
    {
        vproductos = productosF01;
        nProductos = nF01;
    }
    else if (codTienda == "F02")
    {
        vproductos = productosF02;
        nProductos = nF02;
    }
    else if (codTienda == "F03")
    {
        vproductos = productosF03;
        nProductos = nF03;
    }
    else if (codTienda == "F04")
    {
        vproductos = productosF04;
        nProductos = nF04;
    }
    else
    {
        vproductos = productosF05;
        nProductos = nF05;
    }

    do
    {
        cout << "Codigo producto (ejm. P00X, donde ""X"" es un numero entero): ";
        cin >> codProducto;
        posProducto = codigoProductoExiste(vproductos, nProductos, codProducto);

        if (posProducto == -1) {
            cout << "producto no encontrado, vuelva a intentarlo" << endl;
        }
    } while (posProducto == -1);
    vventas[nVentas].producto = vproductos[posProducto];

    if (vproductos[posProducto].estado == 'S')
    {
        do
        {
            cout << "Para el producto " << codProducto << " se tiene un stock de: " << vproductos[posProducto].stock << endl;
            cout << "Ingrese la cantidad: ";
            cin >> stocks;

            contador = validarStock(vproductos, posProducto, stocks);

            if (contador == 0)
            {
                cout << "Stock insuficiente, vuelva a intentarlo." << endl;
            }

        } while (contador == 0);
        vproductos[posProducto].stock -= stocks;

        if (vproductos[posProducto].stock == 0)
        {
            vproductos[posProducto].estado = 'N';
        }

        vventas[nVentas].producto = vproductos[posProducto];
        vventas[nVentas].cantidad = stocks;
        vventas[nVentas].total = vventas[nVentas].producto.precio * stocks;

        nVentas++;

        cout << "\nVenta registrada correctamente.\n";
    }
    else
    {
        cout << "\nProducto no disponible." << endl;
    }
}
void generarVentas(Venta* vventas, int& nVentas, Tienda* vtiendas, Producto* productosF01, int nF01, Producto* productosF02, int nF02, Producto* productosF03, int nF03, Producto* productosF04, int nF04, Producto* productosF05, int nF05)
{
    int mesInicio, mesFin;

    cout << "\n========== GENERAR VENTAS ==========\n";

    do
    {
        cout << "Mes inicial (1-12): ";
        cin >> mesInicio;

    } while (mesInicio < 1 || mesInicio > 12);

    do
    {
        cout << "Mes final (" << mesInicio << "-12): ";
        cin >> mesFin;

    } while (mesFin < mesInicio || mesFin > 12);

    int dia = 1;
    int mes = mesInicio;
    int anio = 2026;

    Producto* vproductos;
    int nProductos;

    while (mes <= mesFin)
    {
        if (hayTiendasDisponibles(productosF01, nF01, productosF02, nF02, productosF03, nF03, productosF04, nF04, productosF05, nF05) == 0)
        {
            cout << "\nTodos los productos se agotaron." << endl;
            break;
        }

        int ventasDia = rand() % 8 + 3;

        for (int i = 0; i < ventasDia; i++)
        {
            int tienda;

            do
            {
                tienda = rand() % 5;

                switch (tienda)
                {
                case 0:
                    vproductos = productosF01;
                    nProductos = nF01;
                    break;

                case 1:
                    vproductos = productosF02;
                    nProductos = nF02;
                    break;

                case 2:
                    vproductos = productosF03;
                    nProductos = nF03;
                    break;

                case 3:
                    vproductos = productosF04;
                    nProductos = nF04;
                    break;

                default:
                    vproductos = productosF05;
                    nProductos = nF05;
                    break;
                }

            } while (hayProductosDisponibles(vproductos, nProductos) == 0);

            int posProducto;

            do
            {
                posProducto = rand() % nProductos;

            } while (vproductos[posProducto].estado == 'N');

            int cantidad = rand() % 5 + 1;

            if (cantidad > vproductos[posProducto].stock)
            {
                cantidad = vproductos[posProducto].stock;
            }

            if (nVentas < 9)
                vventas[nVentas].codigoVenta = "V00" + to_string(nVentas + 1);
            else if (nVentas < 99)
                vventas[nVentas].codigoVenta = "V0" + to_string(nVentas + 1);
            else
                vventas[nVentas].codigoVenta = "V" + to_string(nVentas + 1);

            vventas[nVentas].dia = dia;
            vventas[nVentas].mes = mes;
            vventas[nVentas].anio = anio;

            vventas[nVentas].tienda = vtiendas[tienda];
            vventas[nVentas].producto = vproductos[posProducto];
            vventas[nVentas].cantidad = cantidad;
            vventas[nVentas].total =
                cantidad * vproductos[posProducto].precio;

            vproductos[posProducto].stock -= cantidad;

            if (vproductos[posProducto].stock == 0)
            {
                vproductos[posProducto].estado = 'N';
            }

            vventas[nVentas].producto = vproductos[posProducto];

            nVentas++;
        }

        siguienteFecha(dia, mes);
    }

    cout << "\nSe generaron " << nVentas << " ventas correctamente.\n";
}

void mostrarVentas(Venta* vventas, int nVentas)
{
    string fecha;
    float suma = 0;
    if (nVentas == 0) {
        cout << "\nERROR, AUN NO HAY VENTAS REGISTRADAS..." << endl;
    }

    if (nVentas > 0) {
        cout << endl;
        cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "AREA" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;

        for (int i = 0; i < nVentas; i++)
        {
            fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
            cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.area << setw(15) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << vventas[i].total << endl;
            suma += vventas[i].total;
        }
        float promedio = suma / nVentas;
        cout << endl;
        cout << "VENTA TOTAL: " << suma << endl;
        cout << "PROMEDIO DE VENTAS TOTALES: " << promedio << endl;
        cout << endl;
    }
}

void mostrarTiendas(Tienda* vtiendas, int nTiendas)
{
    cout << endl;
    cout << left << setw(20) << "CODIGO" << setw(20) << "NOMBRE" << setw(20) << "DISTRITO" << endl;

    for (int i = 0; i < nTiendas; i++)
    {
        cout << left << setw(20) << vtiendas[i].codigo << setw(20) << vtiendas[i].nombre << setw(20) << vtiendas[i].distrito << endl;
    }
}

void mostrarVentasDistrito(Venta* vventas, int nVentas, string distrito)
{
    string fecha;
    cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "AREA" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;

    for (int i = 0; i < nVentas; i++)
    {
        fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
        if (vventas[i].tienda.distrito == distrito)
        {
            cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.nombre << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.area << setw(15) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << vventas[i].total << endl;
        }
    }
}

void ventasArea(Venta* vventas, int nVentas)
{
    int opc;
    int conta;
    float suma;
    string fecha;
    do
    {
        cout << endl;
        cout << "======= VENTAS POR AREA =======" << endl;
        cout << "[1] Tecnologia" << endl;
        cout << "[2] Electrohogar" << endl;
        cout << "[3] Belleza" << endl;
        cout << "[4] Calzado" << endl;
        cout << "[5] Juguetes" << endl;
        cout << "[6] Volver al menu principal" << endl;
        cout << "ingrese una opcion: ";
        cin >> opc;
        switch (opc) {
        case 1:
            suma = 0;
            conta = 0;
            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].producto.area == "Tecnologia") {
                    conta++;
                }
            }
            if (conta > 0)
            {
                cout << "=========================================\n";
                cout << "AREA: " << "Tecnologia" << endl;
                cout << "=========================================\n";
                cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;
                for (int i = 0; i < nVentas; i++)
                {
                    fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
                    if (vventas[i].producto.area == "Tecnologia") {
                        cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << vventas[i].total << endl;
                        suma += vventas[i].total;
                    }
                }
                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
            }
            else
            {
                cout << "\nNo hay ventas en esta area." << endl;
            }
            cout << endl;
            break;
        case 2:
            suma = 0;
            conta = 0;
            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].producto.area == "Electrohogar") {
                    conta++;
                }
            }
            if (conta > 0)
            {
                cout << "=========================================\n";
                cout << "AREA: " << "Electrohogar" << endl;
                cout << "=========================================\n";
                cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;
                for (int i = 0; i < nVentas; i++)
                {
                    fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
                    if (vventas[i].producto.area == "Electrohogar") {
                        cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << vventas[i].total << endl;
                        suma += vventas[i].total;
                    }
                }
                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
            }
            else
            {
                cout << "\nNo hay ventas en esta area." << endl;
            }
            cout << endl;
            break;
        case 3:
            suma = 0;
            conta = 0;
            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].producto.area == "Belleza") {
                    conta++;
                }
            }
            if (conta > 0)
            {
                cout << "=========================================\n";
                cout << "AREA: " << "Belleza" << endl;
                cout << "=========================================\n";
                cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;
                for (int i = 0; i < nVentas; i++)
                {
                    fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
                    if (vventas[i].producto.area == "Belleza") {
                        cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << vventas[i].total << endl;
                        suma += vventas[i].total;
                    }
                }
                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
            }
            else
            {
                cout << "\nNo hay ventas en esta area." << endl;
            }
            cout << endl;
            break;
        case 4:
            suma = 0;
            conta = 0;
            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].producto.area == "Calzado") {
                    conta++;
                }
            }
            if (conta > 0)
            {
                cout << "=========================================\n";
                cout << "AREA: " << "Calzado" << endl;
                cout << "=========================================\n";
                cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;
                for (int i = 0; i < nVentas; i++)
                {
                    fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
                    if (vventas[i].producto.area == "Calzado") {
                        cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << vventas[i].total << endl;
                        suma += vventas[i].total;
                    }
                }
                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
            }
            else
            {
                cout << "\nNo hay ventas en esta area." << endl;
            }
            cout << endl;
            break;
        case 5:
            suma = 0;
            conta = 0;
            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].producto.area == "Juguetes") {
                    conta++;
                }
            }
            if (conta > 0)
            {
                cout << "=========================================\n";
                cout << "AREA: " << "Juguetes" << endl;
                cout << "=========================================\n";
                cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;
                for (int i = 0; i < nVentas; i++)
                {
                    if (vventas[i].producto.area == "Juguetes") {
                        cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << vventas[i].total << endl;
                        suma += vventas[i].total;
                    }
                }
                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
            }
            else
            {
                cout << "\nNo hay ventas en esta area." << endl;
            }
            cout << endl;
            break;
        case 6:
            cout << "volviendo al menu principal..." << endl;
            break;
        default:
            cout << "opcion invalida, vuelva a intentarlo..." << endl;
            break;
        }

    } while (opc != 6);

}

void ventarXtienda(Venta* vventas, int nVentas) {
    int opc;
    int conta;
    float suma;
    do
    {
        cout << " \n====== VENTAS POR DISTRITOS =======" << endl;
        cout << "[1] Chorrillos" << endl;
        cout << "[2] San isidro" << endl;
        cout << "[3] Miraflores" << endl;
        cout << "[4] Barranco" << endl;
        cout << "[5] San Borja" << endl;
        cout << "[6] Regresar al menu principal" << endl;
        cout << "ingrese una opcion: ";
        cin >> opc;
        switch (opc)
        {
        case 1:
            conta = 0;
            suma = 0;
            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].tienda.distrito == "Chorrillos") {
                    suma += vventas[i].total;
                    conta++;
                }
            }
            if (conta > 0)
            {
                cout << "\nVENTAS DEL DISTRITO DE CHORRILLOS" << endl;

                mostrarVentasDistrito(vventas, nVentas, "Chorrillos");

                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
                cout << endl;
            }
            else
            {
                cout << "No hay ventas en ese distrito." << endl;
            }
            break;
        case 2:
            conta = 0;
            suma = 0;

            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].tienda.distrito == "San Isidro")
                {
                    suma += vventas[i].total;
                    conta++;
                }
            }

            if (conta > 0)
            {
                cout << "\nVENTAS DEL DISTRITO DE SAN ISIDRO" << endl;

                mostrarVentasDistrito(vventas, nVentas, "San Isidro");

                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
                cout << endl;
            }
            else
            {
                cout << "No hay ventas en ese distrito." << endl;
            }
            break;
        case 3:
            conta = 0;
            suma = 0;

            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].tienda.distrito == "Miraflores")
                {
                    suma += vventas[i].total;
                    conta++;
                }
            }

            if (conta > 0)
            {
                cout << "\nVENTAS DEL DISTRITO DE MIRAFLORES" << endl;

                mostrarVentasDistrito(vventas, nVentas, "Miraflores");

                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
                cout << endl;
            }
            else
            {
                cout << "No hay ventas en ese distrito." << endl;
            }
            break;
        case 4:
            conta = 0;
            suma = 0;

            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].tienda.distrito == "Barranco")
                {
                    suma += vventas[i].total;
                    conta++;
                }
            }

            if (conta > 0)
            {
                cout << "\nVENTAS DEL DISTRITO DE BARRANCO" << endl;

                mostrarVentasDistrito(vventas, nVentas, "Barranco");

                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
                cout << endl;
            }
            else
            {
                cout << "No hay ventas en ese distrito." << endl;
            }
            break;
        case 5:
            conta = 0;
            suma = 0;

            for (int i = 0; i < nVentas; i++)
            {
                if (vventas[i].tienda.distrito == "San Borja")
                {
                    suma += vventas[i].total;
                    conta++;
                }
            }

            if (conta > 0)
            {
                cout << "\nVENTAS DEL DISTRITO DE SAN BORJA" << endl;

                mostrarVentasDistrito(vventas, nVentas, "San Borja");

                cout << "\nVENTA TOTAL: " << suma << endl;
                cout << "PROMEDIO DE VENTAS: " << suma / conta << endl;
                cout << endl;
            }
            else
            {
                cout << "No hay ventas en ese distrito." << endl;
            }
            break;
        case 6:
            cout << "regresando al menu principal..." << endl;
            break;
        default:
            cout << "opcion invalido, vuelva a intentarlo" << endl;
            break;
        }

    } while (opc != 6);
}

void areaMayorVenta(Venta* vventas, int nVentas) {
    float* vsumas = new float[5];
    string fecha;

    vsumas[0] = 0;
    vsumas[1] = 0;
    vsumas[2] = 0;
    vsumas[3] = 0;
    vsumas[4] = 0;

    string areas[5] = { "Tecnologia", "Electrohogar", "Belleza", "Calzado", "Juguetes" };

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].producto.area == "Tecnologia")
            vsumas[0] += vventas[i].total;

        else if (vventas[i].producto.area == "Electrohogar")
            vsumas[1] += vventas[i].total;

        else if (vventas[i].producto.area == "Belleza")
            vsumas[2] += vventas[i].total;

        else if (vventas[i].producto.area == "Calzado")
            vsumas[3] += vventas[i].total;

        else if (vventas[i].producto.area == "Juguetes")
            vsumas[4] += vventas[i].total;
    }

    float mayor = vsumas[0];
    int indice = 0;

    for (int i = 1; i < 5; i++)
    {
        if (vsumas[i] > mayor)
        {
            mayor = vsumas[i];
            indice = i;
        }
    }

    cout << "\nAREA CON MAYOR VENTA: " << areas[indice] << endl;

    cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "AREA" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;

    int contador = 0;

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].producto.area == areas[indice])
        {
            fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
            cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.area << setw(15) << fixed << setprecision(2) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << fixed << setprecision(2) << vventas[i].total << endl;
            contador++;
        }
    }

    float promedio = mayor / contador;

    cout << "\nVENTA TOTAL: " << mayor << endl;
    cout << "PROMEDIO DE VENTAS: " << promedio << endl;

    delete[] vsumas;
}

void areaMenorVenta(Venta* vventas, int nVentas) {
    float* vsumas = new float[5];
    string fecha;

    vsumas[0] = 0;
    vsumas[1] = 0;
    vsumas[2] = 0;
    vsumas[3] = 0;
    vsumas[4] = 0;

    string areas[5] = { "Tecnologia", "Electrohogar", "Belleza", "Calzado", "Juguetes" };

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].producto.area == "Tecnologia")
            vsumas[0] += vventas[i].total;

        else if (vventas[i].producto.area == "Electrohogar")
            vsumas[1] += vventas[i].total;

        else if (vventas[i].producto.area == "Belleza")
            vsumas[2] += vventas[i].total;

        else if (vventas[i].producto.area == "Calzado")
            vsumas[3] += vventas[i].total;

        else if (vventas[i].producto.area == "Juguetes")
            vsumas[4] += vventas[i].total;
    }

    float menor = vsumas[0];
    int indice = 0;

    for (int i = 1; i < 5; i++)
    {
        if (vsumas[i] < menor)
        {
            menor = vsumas[i];
            indice = i;
        }
    }

    cout << "\nAREA CON MENOR VENTA: " << areas[indice] << endl;

    cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "AREA" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;

    int contador = 0;

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].producto.area == areas[indice])
        {
            fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
            cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.area << setw(15) << fixed << setprecision(2) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << fixed << setprecision(2) << vventas[i].total << endl;
            contador++;
        }
    }

    float promedio = menor / contador;

    cout << "\nVENTA TOTAL: " << menor << endl;
    cout << "PROMEDIO DE VENTAS: " << promedio << endl;

    delete[] vsumas;
}

void top3tiendas(Venta* vventas, int nVentas)
{
    float* vsumas = new float[5];

    vsumas[0] = 0;
    vsumas[1] = 0;
    vsumas[2] = 0;
    vsumas[3] = 0;
    vsumas[4] = 0;

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].tienda.codigo == "F01")
            vsumas[0] += vventas[i].total;

        else if (vventas[i].tienda.codigo == "F02")
            vsumas[1] += vventas[i].total;

        else if (vventas[i].tienda.codigo == "F03")
            vsumas[2] += vventas[i].total;

        else if (vventas[i].tienda.codigo == "F04")
            vsumas[3] += vventas[i].total;

        else if (vventas[i].tienda.codigo == "F05")
            vsumas[4] += vventas[i].total;
    }

    string tiendas[5] = { "Chorrillos", "San Isidro", "Miraflores", "Barranco", "San Borja" };
    cout << "\n========== TOP 3 TIENDAS FALABELLA ==========\n";
    for (int k = 1; k <= 3; k++)
    {
        float mayor = vsumas[0];
        int indice = 0;

        for (int i = 1; i < 5; i++)
        {
            if (vsumas[i] > mayor)
            {
                mayor = vsumas[i];
                indice = i;
            }
        }

        cout << "TOP " << k << ": " << tiendas[indice] << "   S/. " << mayor << endl;
        vsumas[indice] = 0;
    }
}
void top3Area(Venta* vventas, int nVentas)
{
    float* vsumas = new float[5];

    vsumas[0] = 0;
    vsumas[1] = 0;
    vsumas[2] = 0;
    vsumas[3] = 0;
    vsumas[4] = 0;

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].producto.area == "Tecnologia")
            vsumas[0] += vventas[i].total;

        else if (vventas[i].producto.area == "Electrohogar")
            vsumas[1] += vventas[i].total;

        else if (vventas[i].producto.area == "Belleza")
            vsumas[2] += vventas[i].total;

        else if (vventas[i].producto.area == "Calzado")
            vsumas[3] += vventas[i].total;

        else if (vventas[i].producto.area == "Juguetes")
            vsumas[4] += vventas[i].total;
    }
    string areas[5] = { "Tecnologia", "Electrohogar", "Belleza", "Calzado", "Juguetes" };

    cout << "\n========== TOP 3 AREAS ==========\n";

    for (int k = 1; k <= 3; k++)
    {
        float mayor = vsumas[0];
        int indice = 0;

        for (int i = 1; i < 5; i++)
        {
            if (vsumas[i] > mayor)
            {
                mayor = vsumas[i];
                indice = i;
            }
        }

        cout << "TOP " << k << ": " << areas[indice] << "   S/. " << mayor << endl;

        vsumas[indice] = 0;
    }

    delete[] vsumas;
}

void tiendaRentable(Venta* vventas, int nVentas)
{
    float* vsumas = new float[5];
    string fecha;

    vsumas[0] = 0;
    vsumas[1] = 0;
    vsumas[2] = 0;
    vsumas[3] = 0;
    vsumas[4] = 0;

    string tiendas[5] = { "Chorrillos", "San Isidro", "Miraflores", "Barranco", "San Borja" };

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].tienda.codigo == "F01")
        {
            vsumas[0] += vventas[i].total;
        }
        else if (vventas[i].tienda.codigo == "F02")
        {
            vsumas[1] += vventas[i].total;
        }
        else if (vventas[i].tienda.codigo == "F03")
        {
            vsumas[2] += vventas[i].total;
        }
        else if (vventas[i].tienda.codigo == "F04")
        {
            vsumas[3] += vventas[i].total;
        }
        else if (vventas[i].tienda.codigo == "F05")
        {
            vsumas[4] += vventas[i].total;
        }
    }

    float mayor = vsumas[0];
    int indice = 0;

    for (int i = 1; i < 5; i++)
    {
        if (vsumas[i] > mayor)
        {
            mayor = vsumas[i];
            indice = i;
        }
    }

    cout << "\n========== TIENDA MAS RENTABLE ==========\n";
    cout << "TIENDA: " << tiendas[indice] << endl << endl;

    cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "AREA" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;

    int contador = 0;

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].tienda.distrito == tiendas[indice])
        {
            fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
            cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.area << setw(15) << fixed << setprecision(2) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << fixed << setprecision(2) << vventas[i].total << endl;
            contador++;
        }
    }

    cout << "\nVENTA TOTAL: S/. " << mayor << endl;
    cout << "PROMEDIO DE VENTAS: S/. " << mayor / contador << endl;

    delete[] vsumas;
}

void tiendaMenosRentable(Venta* vventas, int nVentas)
{
    float* vsumas = new float[5];
    string fecha;

    vsumas[0] = 0;
    vsumas[1] = 0;
    vsumas[2] = 0;
    vsumas[3] = 0;
    vsumas[4] = 0;

    string tiendas[5] = { "Chorrillos", "San Isidro", "Miraflores", "Barranco", "San Borja" };

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].tienda.codigo == "F01")
        {
            vsumas[0] += vventas[i].total;
        }
        else if (vventas[i].tienda.codigo == "F02")
        {
            vsumas[1] += vventas[i].total;
        }
        else if (vventas[i].tienda.codigo == "F03")
        {
            vsumas[2] += vventas[i].total;
        }
        else if (vventas[i].tienda.codigo == "F04")
        {
            vsumas[3] += vventas[i].total;
        }
        else if (vventas[i].tienda.codigo == "F05")
        {
            vsumas[4] += vventas[i].total;
        }
    }

    float menor = vsumas[0];
    int indice = 0;

    for (int i = 1; i < 5; i++)
    {
        if (vsumas[i] < menor)
        {
            menor = vsumas[i];
            indice = i;
        }
    }

    cout << "\n========== TIENDA MENOS RENTABLE ==========\n";
    cout << "TIENDA: " << tiendas[indice] << endl << endl;

    cout << left << setw(10) << "CODIGO" << setw(12) << "FECHA" << setw(20) << "TIENDA" << setw(40) << "PRODUCTO" << setw(15) << "AREA" << setw(15) << "PRECIO S/." << setw(10) << "CANT." << setw(10) << "TOTAL" << endl;

    int contador = 0;

    for (int i = 0; i < nVentas; i++)
    {
        if (vventas[i].tienda.distrito == tiendas[indice])
        {
            fecha = to_string(vventas[i].dia) + "/" + to_string(vventas[i].mes) + "/" + to_string(vventas[i].anio);
            cout << left << setw(10) << vventas[i].codigoVenta << setw(12) << fecha << setw(20) << vventas[i].tienda.distrito << setw(40) << vventas[i].producto.nombre << setw(15) << vventas[i].producto.area << setw(15) << fixed << setprecision(2) << vventas[i].producto.precio << setw(10) << vventas[i].cantidad << setw(10) << fixed << setprecision(2) << vventas[i].total << endl;
            contador++;
        }
    }

    cout << "\nVENTA TOTAL: S/. " << menor << endl;
    cout << "PROMEDIO DE VENTAS: S/. " << menor / contador << endl;

    delete[] vsumas;
}

void menuReportes(Venta* vventas, int nVentas)
{
    int opc;
    do
    {
        cout << "\n=========== REPORTES ===========\n";
        cout << "[1] Area con mayor venta\n";
        cout << "[2] Area con menor venta\n";
        cout << "[3] Top 3 tiendas con mas ventas\n";
        cout << "[4] Top 3 de areas con mas ventas\n";
        cout << "[5] Tienda mas rentable\n";
        cout << "[6] Tienda menos rentable\n";
        cout << "[7] Ventas por distrito\n";
        cout << "[8] Ventas por area\n";
        cout << "[9] Volver\n";
        cout << "INGRESE UNA OPCION: ";
        cin >> opc;
        switch (opc)
        {
        case 1:
            areaMayorVenta(vventas, nVentas);
            break;
        case 2:
            areaMenorVenta(vventas, nVentas);
            break;
        case 3:
            top3tiendas(vventas, nVentas);
            break;
        case 4:
            top3Area(vventas, nVentas);
            break;
        case 5:
            tiendaRentable(vventas, nVentas);
            break;
        case 6:
            tiendaMenosRentable(vventas, nVentas);
            break;
        case 7:
            ventarXtienda(vventas, nVentas);
            break;
        case 8:
            ventasArea(vventas, nVentas);
            break;
        case 9:
            cout << "REGRESANDO AL MENU PRINCIPAL...." << endl;
            break;
        default:
            cout << "dato invalido, vuelva a intentarlo..." << endl;
            break;
        }

    } while (opc != 9);
}
int main()
{
    srand(time(NULL));
    int opc;
    int validar = 0;
    int validar2 = 0;
    int validar3 = 0;

    Tienda* vtiendas = new Tienda[10];

    Producto* productosF01 = new Producto[100];
    Producto* productosF02 = new Producto[100];
    Producto* productosF03 = new Producto[100];
    Producto* productosF04 = new Producto[100];
    Producto* productosF05 = new Producto[100];

    Venta* vventas = new Venta[100000];

    int nF01 = 0;
    int nF02 = 0;
    int nF03 = 0;
    int nF04 = 0;
    int nF05 = 0;

    int nTiendas = 0;
    int nVentas = 0;

    presentacion();
    do
    {
        menu();
        cout << "ingrese una opcion: ";
        cin >> opc;
        switch (opc) {
        case 1:
            cargarTiendas(vtiendas, nTiendas);

            cargarProductos(productosF01, nF01, "productos_F01.txt");
            cargarProductos(productosF02, nF02, "productos_F02.txt");
            cargarProductos(productosF03, nF03, "productos_F03.txt");
            cargarProductos(productosF04, nF04, "productos_F04.txt");
            cargarProductos(productosF05, nF05, "productos_F05.txt");
            cout << "Datos cargados correctamente." << endl;
            validar = 1;
            break;
        case 2:
            if (validar == 0) {
                cout << "\nprimero carga los archivos..." << endl;
                break;
            }
            registrarVenta(vventas, nVentas, vtiendas, nTiendas, productosF01, nF01, productosF02, nF02, productosF03, nF03, productosF04, nF04, productosF05, nF05);
            validar2 = 1;
            break;
        case 3:
            if (validar == 0) {
                cout << "\nprimero carga los archivos..." << endl;
                break;
            }
            generarVentas(vventas, nVentas, vtiendas, productosF01, nF01, productosF02, nF02, productosF03, nF03, productosF04, nF04, productosF05, nF05);
            validar3 = 1;
            break;
        case 4:
            if (validar == 0) {
                cout << "\nprimero carga los archivos..." << endl;
                break;
            }
            if (validar2 == 0 && validar3 == 0)
            {
                cout << "\nPrimero registre o genere ventas." << endl;
                break;
            }
            mostrarVentas(vventas, nVentas);
            break;

        case 5:
            if (validar == 0) {
                cout << "\nprimero carga los archivos..." << endl;
                break;
            }
            mostrarTiendas(vtiendas, nTiendas);
            break;
        case 6:
            if (validar == 0)
            {
                cout << "\nPrimero cargue los archivos." << endl;
                break;
            }

            if (validar2 == 0 && validar3 == 0)
            {
                cout << "\nPrimero registre o genere ventas." << endl;
                break;
            }
            menuReportes(vventas, nVentas);
            break;
        case 7:
            cout << "HASTA PRONTO..." << endl;
            break;

        default:
            cout << "opcion invalida, vuelva a intentarlo" << endl;
            break;
        }
    } while (opc != 7);

    _getch();
}

