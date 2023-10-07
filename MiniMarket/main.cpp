#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <mmsystem.h>
#include <ctime>
#include <time.h>
#include <fstream>
#include <CommCtrl.h>
#include "resource.h"
#include <ctype.h>
#include <string.h>
#include <string>
#pragma comment(lib, "winmm.lib")

using namespace std;

HWND hInicio;
HINSTANCE Instancia;

#pragma region ListaCategorias
//Lista de categorias
/*
0.- Libros
1.- Television
2.- DVDs
3.- CDs
4.- Celulares
5.- Software
6.- Computadoras
7.- Videojuegos
8.- Hogar
9.- Herramientas
10.- Automotriz
11.- Juguetes
12.- Mascotas
13.- Bebe
14.- Ropa
15.- Deporte
16.- Salud
17.- Belleza
*/
#pragma endregion

//Estructuras
struct usuario
{
	usuario *ant;
	long id;
	char nombre[20];
	char contrasenia[20];
	char foto[MAX_PATH];
	usuario *sig;
}*inicioU, *auxU;

struct usuarioLog
{
	long id;
	char nombre[20];
	char contrasenia[20];
	char foto[MAX_PATH];
}usuarioLog;

struct producto
{
	producto *ant;
	long id;
	long idUsuario;
	char nombre[30];
	char desc[100];
	float precio;
	bool conPromocion;
	float precioFinal;
	int categoria;
	char foto1[MAX_PATH];
	char foto2[MAX_PATH];
	char audio[MAX_PATH];
	producto *sig;
}*inicioP, *auxP, *auxPA;

struct promocion
{
	promocion *ant;
	long idProducto;
	char nombre[30];
	char descripcion[50];
	float descuento;
	char fechaIni[20];
	string diaIni;
	string mesIni;
	string anioIni;
	char horaIni[10];
	char fechaFin[20];
	string diaFin;
	string mesFin;
	string anioFin;
	char horaFin[10];
	int alarma;
	bool iniAlarma = false;
	bool finAlarma = false;
	promocion *sig;
}*inicioPro, *auxPro, *auxProA;

struct carro
{
	carro *ant;
	int idUsuario;
	producto carrito[10];
	carro *sig;
}*inicioCar, *auxCar;

//Ventana Login
#pragma region Login
HWND hPicLogo;
HWND hEditNombre;
HWND hEditContra;
#pragma endregion

//Ventana Registrar
#pragma region Registrar
HWND hPicFotoR;
HWND hEditNombreR;
HWND hEditContraR;
HWND hEditContraCR;
HWND hEditFotoR;
#pragma endregion

//Ventana Modificar
#pragma region Modificar
HWND hPicFotoM;
HWND hStNombreM;
HWND hStIdM;
HWND hEditNombreM;
HWND hEditContraM;
HWND hEditContraCM;
HWND hEditFotoM;
#pragma endregion

//Ventana Tienda
#pragma region Tienda
HWND hPicPerfilT;
HWND hStIdT;
HWND hStUsuarioT;
HWND hEditBuscarNombreT;
HWND hEditBuscarVendedorT;
HWND hCbBuscarCatT;
HWND hListaProductos;
HWND hPicProductoT;
HWND hStProductoT;
HWND hStPrecioT;
#pragma endregion

//Ventana mis productos
#pragma region MisProductos
HWND hPicPerfilMy;
HWND hStIdMy;
HWND hStUsuarioMy;
HWND hListaProductosMy;
HWND hPicProductoMy;
HWND hStProductoMy;
HWND hStPrecioMy;
#pragma endregion

//Ventana agregar productos
#pragma region AgregarProductos
HWND hPicPerfilAP;
HWND hStIdAP;
HWND hStUsuarioAP;
HWND hEditNombreAP;
HWND hEditDescAP;
HWND hEditPrecioAP;
HWND hStPrecioAP;
HWND hCbCategoAP;
HWND hEditFoto1AP;
HWND hEditFoto2AP;
HWND hRadActivarAP;
HWND hRadDesactivarAP;
HWND hPicProductoAP;

//ACTIVAR CON MUSICA
HWND hStAudioAP;
HWND hBtnAudioAP;
HWND hEditAudioAP;
HWND hBtnPlayAP;
HWND hBtnPauseAP;
HWND hBtnStopAP;

//ACTIVAR CON PROMOCION
HWND hStPromocionAP;
HWND hEditPromoNombreAP;
HWND hStDescripcionAP;
HWND hEditPromoDescAP;
HWND hStDescuentoAP;
HWND hStPorcentajeAP;
HWND hSliderPromoAP;
HWND hStFechaIniAP;
HWND hDateIniAP;
HWND hTimeIniAP;
HWND hStFechaFinAP;
HWND hDateFinAP;
HWND hTimeFinAP;
HWND hStTiempoAP;
HWND hStAlarmaAP;
HWND hCbAlarmaAP;
HWND hBtnReproducirAP;
HWND hBtnDetenerAP;
HWND hStPrecioFinAP;
HWND hStPrecioFinalAP;
#pragma endregion

//Ventana modificar productos
#pragma region ModificarProductos
HWND hPicPerfilMP;
HWND hStIdMP;
HWND hStUsuarioMP;
HWND hEditNombreMP;
HWND hEditDescMP;
HWND hEditPrecioMP;
HWND hStPrecioMP;
HWND hCbCategoMP;
HWND hEditFoto1MP;
HWND hEditFoto2MP;
HWND hRadActivarMP;
HWND hRadDesactivarMP;
HWND hPicProductoMP;

//ACTIVAR CON MUSICA
HWND hStAudioMP;
HWND hBtnAudioMP;
HWND hEditAudioMP;
HWND hBtnPlayMP;
HWND hBtnPauseMP;
HWND hBtnStopMP;

//ACTIVAR CON PROMOCION
HWND hStPromocionMP;
HWND hEditPromoNombreMP;
HWND hStDescripcionMP;
HWND hEditPromoDescMP;
HWND hStDescuentoMP;
HWND hStPorcentajeMP;
HWND hSliderPromoMP;
HWND hStFechaIniMP;
HWND hDateIniMP;
HWND hTimeIniMP;
HWND hStFechaFinMP;
HWND hDateFinMP;
HWND hTimeFinMP;
HWND hStTiempoMP;
HWND hStAlarmaMP;
HWND hCbAlarmaMP;
HWND hBtnReproducirMP;
HWND hBtnDetenerMP;
HWND hStPrecioFinMP;
HWND hStPrecioFinalMP;
#pragma endregion

//Ventana producto
#pragma region Producto
HWND hPicPerfilVP;
HWND hStIdVP;
HWND hStUsuarioVP;
HWND hPicProductoVP;
HWND hStPromoVP;
HWND hStNombreVP;
HWND hEditDescVP;
HWND hStPrecioVP;
HWND hStCatVP;
HWND hStVendedorVP;
HWND hStAudioVP;
HWND hEditAudioVP;
HWND hBtnPlayVP;
HWND hBtnPauseVP;
HWND hBtnStopVP;
#pragma endregion

//Ventana carrito
#pragma region Carrito
HWND hPicPerfilC;
HWND hStIdC;
HWND hStUsuarioC;
HWND hListaCarritoC;
HWND hPicProductoC;
HWND hStProductoC;
HWND hStPrecioC;
HWND hStAhorroC;
HWND hStTotalC;
#pragma endregion

#pragma region VentanaAlarma
HWND hStAvisoA;
HWND hStNombreA;
HWND hStPrecioA;
HWND hStCategoriaA;
HWND hStVendedorA;
HWND PicProductoA;
#pragma endregion

//CALLBACK
#pragma region CALLBACK
BOOL CALLBACK Login(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Registrar(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Modificar(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Tienda(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK MisProductos(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AgregarProducto(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ModificarProducto(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK VerProducto(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Carrito(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Alarma(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam);
#pragma endregion

//Funciones
#pragma region Funciones
bool Logear(HWND hVentana, HWND hNombre, HWND hContra);
void AgregarFoto(HWND Dialog, HWND Edit);
void AgregarAudio(HWND Dialog, HWND Edit);
int NumeroRandom();
int MsgCerrarSesion(HWND hWnd);
int MsgCerrarPrograma(HWND hWnd);
void guardarUsuarios();
void cargarUsuarios();
void guardarProductos();
void cargarProductos();
void guardarPromos();
void cargarPromos();
void guardarCarro();
void cargarCarro();
void agregarCbCategorias(HWND hCombo);
void agregarCbAlarma(HWND hCombo);
void idNombreFoto(HWND hVentana, static HBITMAP bmp, int PicControl, HWND hId, HWND hNombre);
void validarPrecio(HWND Edit, HWND Static);
void enablePromoAP();
void unablePromoAP();
void enablePromoMP();
void unablePromoMP();
void elegirAlarma(HWND hCombo, char buffmp3[MAX_PATH]);
void checarTiempo(HWND DateIni, HWND DateFin, HWND TimeIni, HWND TimeFin, HWND StAviso);
void llenarCuadro(HWND hWnd, int Picture, HWND Nombre, HWND Precio);
int MsgEliminarProducto(HWND hWnd);
int MsgEliminarCuenta(HWND hWnd);
void alarmaIni(HWND hWnd);
void alarmaFin(HWND hWnd);
#pragma endregion

#pragma region variables
//Variables archivos
char carpeta[MAX_PATH];
char archivoUsuario[MAX_PATH];
char archivoProducto[MAX_PATH];
char archivoPromo[MAX_PATH];
char archivoCarro[MAX_PATH];

//Variables productos
float val;
bool errorPrecio = false;
bool errorTiempo = false;
bool musica = false;
bool oferta = false;
#pragma endregion

#define ID_SSECONDS 100
UINT TimmerID1 = 0;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, PSTR cmdLine, int nCmdShow)
{
	hInicio = CreateDialog(hInst, MAKEINTRESOURCE(IDD_LOGIN), 0, Login);

	ShowWindow(hInicio, nCmdShow);

	GetCurrentDirectory(MAX_PATH, carpeta);
	sprintf(archivoUsuario, "%s\\data_usuarios.dat", carpeta);
	sprintf(archivoProducto, "%s\\data_productos.dat", carpeta);
	sprintf(archivoPromo, "%s\\data_promos.dat", carpeta);
	sprintf(archivoCarro, "%s\\data_carro.dat", carpeta);
	cargarUsuarios();
	cargarProductos();
	cargarPromos();
	cargarCarro();

	MSG mensaje;
	ZeroMemory(&mensaje, sizeof(MSG));
	while (GetMessage(&mensaje, 0, 0, 0))
	{
		TranslateMessage(&mensaje);
		DispatchMessage(&mensaje);
	}

	return 0;
}

BOOL CALLBACK Login(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP bmp;
	static HBRUSH pincel;
	static HFONT hFont;

	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		TimmerID1 = SetTimer(hWnd, 100, 1000, NULL);
		hPicLogo = GetDlgItem(hWnd, IDC_PicLogo);
		hEditNombre = GetDlgItem(hWnd, IDC_EditNombre);
		hEditContra = GetDlgItem(hWnd, IDC_EditContra);

		bmp = (HBITMAP)LoadImage(NULL, "Recursos\\minimarket.bmp", IMAGE_BITMAP, 426.66, 240, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);

		pincel = CreateSolidBrush(RGB(239, 186, 109));
		hFont = CreateFont(20, 0, 0, 0, 300, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Designer Block");
		SendMessage(hEditNombre, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		SendMessage(hEditContra, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		return true;
	}

	case WM_TIMER:
	{
		alarmaIni(hWnd);
		alarmaFin(hWnd);
		return true;
	}

	case WM_CTLCOLOREDIT:
		SetBkColor((HDC)wParam, RGB(51, 40, 74));
		SetTextColor((HDC)wParam, RGB(239, 186, 109));
		return (LRESULT)pincel;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BtnRegistrar:
			SetWindowText(hEditNombre, "");
			SetWindowText(hEditContra, "");
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_REGISTRAR), hInicio, Registrar);
			return true;

		case IDC_BtnModificar:
			if (Logear(hWnd, hEditNombre, hEditContra))
			{
				SetWindowText(hEditNombre, "");
				SetWindowText(hEditContra, "");
				DialogBox(Instancia, MAKEINTRESOURCE(IDD_MODIFICAR), hInicio, Modificar);
			}
			else
			{
				MessageBox(hWnd, "Nombe de usuario o contrase�a incorrectos", "Aviso", MB_OK | MB_ICONEXCLAMATION);
			}
			return true;
		case IDC_BtnIngresar:
			
			if (Logear(hWnd, hEditNombre, hEditContra))
			{
				SetWindowText(hEditNombre, "");
				SetWindowText(hEditContra, "");

				strcpy(usuarioLog.nombre, auxU->nombre);
				strcpy(usuarioLog.contrasenia, auxU->nombre);
				strcpy(usuarioLog.foto, auxU->foto);
				usuarioLog.id = auxU->id;

				auxU = inicioU;
				DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			}
			else
			{
				MessageBox(hWnd, "Nombre de usuario o contrase�a incorrectos", "Aviso", MB_OK | MB_ICONEXCLAMATION);
			}
			return true;
		}

		return true;
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
		return true;
	}

	case WM_DESTROY:
	{
		DeleteObject(hFont);
		guardarUsuarios();
		guardarProductos();
		guardarPromos();
		guardarCarro();
		PostQuitMessage(0);
		return true;
	}

	}
	return false;
}

BOOL CALLBACK Registrar(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
	char pathBmp[MAX_PATH];
	static HBITMAP bmp;

	switch (mensaje)
	{
	case WM_INITDIALOG:
		hPicFotoR = GetDlgItem(hWnd, IDC_PicFotoR);
		hEditNombreR = GetDlgItem(hWnd, IDC_EditNombreR);
		hEditContraR = GetDlgItem(hWnd, IDC_EditContraR);
		hEditContraCR = GetDlgItem(hWnd, IDC_EditContraCR);
		hEditFotoR = GetDlgItem(hWnd, IDC_EditFotoR);

		bmp = (HBITMAP)LoadImage(NULL, "Recursos\\user.bmp", IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicFotoR, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BtnRegresarR:
			EndDialog(hWnd, 0);
			return true;

		case IDC_BtnFotoR:
			AgregarFoto(hWnd, hEditFotoR);
			GetWindowText(hEditFotoR, pathBmp, MAX_PATH);
			bmp = (HBITMAP)LoadImage(NULL, pathBmp, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
			SendDlgItemMessage(hWnd, IDC_PicFotoR, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
			return true;

		case IDC_BtnRegistrarR:
		{
			usuario registrar;
			char buffContra[20];

			GetWindowText(hEditNombreR, registrar.nombre, sizeof(registrar.nombre));
			GetWindowText(hEditContraR, registrar.contrasenia, sizeof(registrar.contrasenia));
			GetWindowText(hEditContraCR, buffContra, sizeof(buffContra));
			GetWindowText(hEditFotoR, registrar.foto, sizeof(registrar.foto));

			if (strcmp(registrar.nombre, "") == 0 || strcmp(registrar.contrasenia, "") == 0 || strcmp(registrar.foto, "") == 0 || strcmp(buffContra, "") == 0)
			{
				MessageBox(hWnd, "Favor de ingresar todos los datos", "Aviso", MB_OK | MB_ICONINFORMATION);
				break;
			}
			else
			{
				if (strcmp(registrar.contrasenia, buffContra) == 0)
				{
					int id;
						if (inicioU == NULL)
						{
							int numero = 0;

							numero = NumeroRandom();
							usuario *nuevo = new usuario;

							nuevo->id = numero;
							id = nuevo->id;
							strcpy(nuevo->nombre, registrar.nombre);
							strcpy(nuevo->contrasenia, registrar.contrasenia);
							strcpy(nuevo->foto, registrar.foto);

							auxU = nuevo;
							auxU->sig = NULL;
							auxU->ant = NULL;
							inicioU = auxU;
						}
						else
						{
							int numero = 0;
							numero = NumeroRandom();
							auxU = inicioU;

							while (auxU != NULL)
							{
								if (numero == auxU->id)
								{
									while (numero == auxU->id)
									{
										numero = NumeroRandom();
									}
								}
									auxU = auxU->sig;
							}

							usuario *nuevo = new usuario;

							nuevo->id = numero;
							id = nuevo->id;
							strcpy(nuevo->nombre, registrar.nombre);
							strcpy(nuevo->contrasenia, registrar.contrasenia);
							strcpy(nuevo->foto, registrar.foto);

							auxU = inicioU;
							while (auxU->sig != NULL)
								auxU = auxU->sig;
							auxU->sig = nuevo;
							auxU->sig->ant = auxU;
							auxU = auxU->sig;
							auxU->sig = NULL;
							auxU = inicioU;
						}
						//Crear carrito
						if (inicioCar == NULL)
						{
							carro *nuevo = new carro;
							
							nuevo->idUsuario = id;	

							auxCar = nuevo;
							auxCar->sig = NULL;
							auxCar->ant = NULL;
							inicioCar = auxCar;
						}
						else
						{
							carro *nuevo = new carro;

							nuevo->idUsuario = id;
							auxCar = inicioCar;
							while (auxCar->sig != NULL)
								auxCar = auxCar->sig;
							auxCar->sig = nuevo;
							auxCar->sig->ant = auxCar;
							auxCar = auxCar->sig;
							auxCar->sig = NULL;
							auxCar = inicioCar;
						}
						MessageBox(hWnd, "Usuario registrado exitosamente", "Aviso", MB_OK);
						EndDialog(hWnd, 0);
				}
				else
				{
					MessageBox(hWnd, "Las contrase�as no coinciden", "Aviso", MB_OK | MB_ICONINFORMATION);
					break;
				}
			}
			return true;
		}
		}
		return true;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return true;
	}
	return false;
}

BOOL CALLBACK Modificar(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lP9aram)
{
	char pathBmp[MAX_PATH];
	static HBITMAP bmp;

	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		char buffId[8];
		hPicFotoM = GetDlgItem(hWnd, IDC_PicFotoM);
		hStNombreM = GetDlgItem(hWnd, IDC_StNombreM);
		hStIdM = GetDlgItem(hWnd, IDC_StIdM);
		hEditContraM = GetDlgItem(hWnd, IDC_EditContraM);
		hEditContraCM = GetDlgItem(hWnd, IDC_EditContraCM);
		hEditFotoM = GetDlgItem(hWnd, IDC_EditFotoM);

		bmp = (HBITMAP)LoadImage(NULL, auxU->foto, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicFotoM, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);

		sprintf(buffId, "#%i", auxU->id);

		SetWindowText(hStNombreM, auxU->nombre);
		SetWindowText(hStIdM, buffId);
		SetWindowText(hEditFotoM, auxU->foto);
		return true;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BtnRegresarM:
			auxU = inicioU;
			EndDialog(hWnd, 0);
			return true;

		case IDC_BtnFotoM:
			AgregarFoto(hWnd, hEditFotoM);
			GetWindowText(hEditFotoM, pathBmp, sizeof(pathBmp));
			bmp = (HBITMAP)LoadImage(NULL, pathBmp, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
			SendDlgItemMessage(hWnd, IDC_PicFotoM, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
			return true;

		case IDC_BtnModificarM:
		{
			usuario modificar;
			char buffContra[20];

			GetWindowText(hEditContraM, modificar.contrasenia, sizeof(modificar.contrasenia));
			GetWindowText(hEditFotoM, modificar.foto, sizeof(modificar.foto));
			GetWindowText(hEditContraCM, buffContra, sizeof(buffContra));

			if (strcmp(modificar.contrasenia, "") != 0 && strcmp(buffContra, "") != 0)  //Los edits de contra tienen algo
			{
				if (strcmp(modificar.contrasenia, buffContra) != 0) //Los edits de contra no coinciden
				{
					MessageBox(hWnd, "Las contrase�as no coinciden", "Aviso", MB_OK | MB_ICONEXCLAMATION);
					break;
				}
				else
				{
					if (strcmp(modificar.foto, auxU->foto) == 0) //Solo se modifica la contrase�a
					{
						strcpy(auxU->contrasenia, modificar.contrasenia);
						auxU = inicioU;
						MessageBox(hWnd, "Contrase�a modificada exitosamente", "Datos modificados", MB_OK);
						EndDialog(hWnd, 0);
						break;
					}
					else //Se modifica contra y foto
					{
						strcpy(auxU->contrasenia, modificar.contrasenia);
						strcpy(auxU->foto, modificar.foto);
						auxU = inicioU;
						MessageBox(hWnd, "Contre�a e imagen de perfil modificados exitosamente", "Datos modificados", MB_OK);
						EndDialog(hWnd, 0);
						break;
					}
				}
			}
			else //Los edits de contra estan vacios
			{
				if (strcmp(modificar.foto, auxU->foto) == 0) //La foto ni la contrase�a cambia
				{
					MessageBox(hWnd, "Asegurate de ingresar nuevos datos", "Aviso", MB_OK | MB_ICONEXCLAMATION);
					break;
				}
				else //Solo cambia la foto
				{
					strcpy(auxU->foto, modificar.foto);
					auxU = inicioU;
					MessageBox(hWnd, "Imagen de perfil modificada exitosamente", "Datos modificados", MB_OK);
					EndDialog(hWnd, 0);
					break;
				}
			}

			return true;
		}

		}
		return true;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
	}
	return false;
}

BOOL CALLBACK Tienda(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP bmp, bmp2;
	char pathBmp[MAX_PATH];
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		hPicPerfilT = GetDlgItem(hWnd, IDC_PicPerfilT);
		hStIdT = GetDlgItem(hWnd, IDC_StIdT);
		hStUsuarioT = GetDlgItem(hWnd, IDC_StUsuarioT);
		hEditBuscarNombreT = GetDlgItem(hWnd, IDC_EditBuscarNombreT);
		hEditBuscarVendedorT = GetDlgItem(hWnd, IDC_EditBuscarVendedorT);
		hCbBuscarCatT = GetDlgItem(hWnd, IDC_CbBuscarCatT);
		hListaProductos = GetDlgItem(hWnd, IDC_ListaProductos);
		hPicProductoT = GetDlgItem(hWnd, IDC_PicProductoT);
		hStProductoT = GetDlgItem(hWnd, IDC_StProductoT);
		hStPrecioT = GetDlgItem(hWnd, IDC_StPrecioT);

		agregarCbCategorias(hCbBuscarCatT);
		SendMessage(hCbBuscarCatT, CB_ADDSTRING, 0, (LPARAM)"Todos");

		idNombreFoto(hWnd, bmp, IDC_PicPerfilT, hStIdT, hStUsuarioT);

		bmp2 = (HBITMAP)LoadImage(NULL, "Recursos\\minibag.bmp", IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicProductoT, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);

		auxP = inicioP;
		while (auxP != NULL)
		{
			if (auxP->idUsuario != usuarioLog.id)
				SendMessage(hListaProductos, LB_ADDSTRING, 0, (LPARAM)auxP->nombre);
			auxP = auxP->sig;
		}
		return true;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_EditBuscarNombreT && HIWORD(wParam) == EN_CHANGE)
		{
			if (inicioP != NULL)
			{
				char buff[250];
				GetWindowText(hEditBuscarNombreT, buff, sizeof(buff));
				SendMessage(hListaProductos, LB_RESETCONTENT, 0, 0);
				if (strcmp(buff, "") == 0)
				{
					auxP = inicioP;
					while (auxP != NULL)
					{
						if (auxP->idUsuario != usuarioLog.id)
							SendMessage(hListaProductos, LB_ADDSTRING, 0, (LPARAM)auxP->nombre);
						auxP = auxP->sig;
					}
				}
				else
				{
					auxP = inicioP;
					while (auxP != NULL)
					{
						if (strcmp(buff, auxP->nombre) == 0 && auxP->idUsuario != usuarioLog.id)
						{
							SendMessage(hListaProductos, LB_RESETCONTENT, 0, 0);
							SendMessage(hListaProductos, LB_ADDSTRING, 0, (LPARAM)auxP->nombre);
							return true;
						}
						auxP = auxP->sig;
					}
				}
			}
			return true;
		}

		if (LOWORD(wParam) == IDC_EditBuscarVendedorT && HIWORD(wParam) == EN_CHANGE)
		{
			if (inicioP != NULL)
			{
				char buff[250];
				long idbuff;
				GetWindowText(hEditBuscarVendedorT, buff, sizeof(buff));
				SendMessage(hListaProductos, LB_RESETCONTENT, 0, 0);
				if (strcmp(buff, usuarioLog.nombre) == 0)
					return true;
				if (strcmp(buff, "") == 0)
				{
					auxP = inicioP;
					while (auxP != NULL)
					{
						if (auxP->idUsuario != usuarioLog.id)
							SendMessage(hListaProductos, LB_ADDSTRING, 0, (LPARAM)auxP->nombre);
						auxP = auxP->sig;
					}
				}
				else
				{
					auxU = inicioU;
					while (auxU != NULL)
					{
						if (strcmp(auxU->nombre, buff) == 0)
							break;
						auxU = auxU->sig;
					}
					auxP = inicioP;
					if (auxU != NULL)
					{
						while (auxP != NULL)
						{
							if (auxU->id == auxP->idUsuario)
								SendMessage(hListaProductos, LB_ADDSTRING, 0, (LPARAM)auxP->nombre);
							auxP = auxP->sig;
						}
					}
				}
			}
			return true;
		}

		if (LOWORD(wParam) == IDC_ListaProductos && HIWORD(wParam) == LBN_DBLCLK)
		{
			if (inicioP != NULL)
			{
				int i = 0;
				char producto[30];

				i = SendMessage(hListaProductos, LB_GETCURSEL, 0, 0);
				SendMessage(hListaProductos, LB_GETTEXT, i, (LPARAM)producto);

				auxP = inicioP;
				while (auxP != NULL)
				{
					if (strcmp(auxP->nombre, producto) == 0 && auxP->idUsuario != usuarioLog.id)
					{
						EndDialog(hWnd, 0);
						DialogBox(Instancia, MAKEINTRESOURCE(IDD_VER_PRODUCTO), hInicio, VerProducto);
						return true;
					}
					auxP = auxP->sig;
				}
			}
		}
		return true;

		switch (LOWORD(wParam))
		{
		case IDC_ListaProductos:
			if (inicioP != NULL)
			{
				int i = 0;
				char producto[30];

				i = SendMessage(hListaProductos, LB_GETCURSEL, 0, 0);
				SendMessage(hListaProductos, LB_GETTEXT, i, (LPARAM)producto);

				auxP = inicioP;
				while (auxP != NULL)
				{
					if (strcmp(auxP->nombre, producto) == 0 && auxP->idUsuario != usuarioLog.id)
					{
						llenarCuadro(hWnd, IDC_PicProductoT, hStProductoT, hStPrecioT);
						break;
					}
					auxP = auxP->sig;
				}
			}
			return true;

		case IDC_CbBuscarCatT:
		{
			if (inicioP != NULL)
			{
				int index = 0;
				index = SendMessage(hCbBuscarCatT, CB_GETCURSEL, 0, 0);
				auxP = inicioP;
				SendMessage(hListaProductos, LB_RESETCONTENT, 0, 0);
				while (auxP != NULL)
				{
					if (auxP->categoria == index && auxP->idUsuario != usuarioLog.id)
						SendMessage(hListaProductos, LB_ADDSTRING, 0, (LPARAM)auxP->nombre);
					auxP = auxP->sig;
				}
				if (index == 18)
				{
					auxP = inicioP;
					while (auxP != NULL)
					{
						if (auxP->idUsuario != usuarioLog.id)
							SendMessage(hListaProductos, LB_ADDSTRING, 0, (LPARAM)auxP->nombre);
						auxP = auxP->sig;
					}
				}
			}
			return true;
		}

		case IDC_BtnVerProducto:
		{
			if (inicioP != NULL)
			{
				int i = 0;
				char producto[30];

				i = SendMessage(hListaProductos, LB_GETCURSEL, 0, 0);
				SendMessage(hListaProductos, LB_GETTEXT, i, (LPARAM)producto);

				auxP = inicioP;
				while (auxP != NULL)
				{
					if (strcmp(auxP->nombre, producto) == 0 && auxP->idUsuario != usuarioLog.id)
					{
						EndDialog(hWnd, 0);
						DialogBox(Instancia, MAKEINTRESOURCE(IDD_VER_PRODUCTO), hInicio, VerProducto);
						return true;
					}
					auxP = auxP->sig;
				}
			}
			return true;
		}

			//MENU
#pragma region BotonesMenu
		case ID_USUARIO_MISPRODUCTOS:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
			return true;

		case ID_USUARIO_MICARRITO:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_CARRITO), hInicio, Carrito);
			return true;

		case ID_USUARIO_ELIMINARCUENTA:
			MsgEliminarCuenta(hWnd);
			return true;

		case ID_USUARIO_CERRARSESION:
			MsgCerrarSesion(hWnd);
			return true;

		case ID_TIENDA_PRINCIPAL:
			return true;

		case ID_SALIR_CERRARPROGRAMA:
			MsgCerrarPrograma(hWnd);
			return true;
#pragma endregion
		}

		return true;
	}

	case WM_CLOSE:
		MsgCerrarSesion(hWnd);
		return true;
	}
	return false;
}

BOOL CALLBACK MisProductos(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP bmp, bmp2;
	char pathBmp[MAX_PATH];
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		hPicPerfilMy = GetDlgItem(hWnd, IDC_PicPerfilMy);
		hStIdMy = GetDlgItem(hWnd, IDC_StIdMy);
		hStUsuarioMy = GetDlgItem(hWnd, IDC_StUsuarioMy);
		hListaProductosMy = GetDlgItem(hWnd, IDC_ListaProductosMy);
		hPicProductoMy = GetDlgItem(hWnd, IDC_PicProductoMy);
		hStProductoMy = GetDlgItem(hWnd, IDC_StProductoMy);
		hStPrecioMy = GetDlgItem(hWnd, IDC_StPrecioMy);

		idNombreFoto(hWnd, bmp, IDC_PicPerfilMy, hStIdMy, hStUsuarioMy);

		bmp2 = (HBITMAP)LoadImage(NULL, "Recursos\\minibag.bmp", IMAGE_BITMAP, 300, 300, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicProductoMy, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);

		if (inicioP != NULL)
		{
			auxP = inicioP;
			while (auxP != NULL)
			{
				if (auxP->idUsuario == usuarioLog.id)
				{
					SendMessage(hListaProductosMy, LB_ADDSTRING, 0, (LPARAM)auxP->nombre);
				}
				auxP = auxP->sig;
			}
		}
		return true;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_ListaProductosMy:
		{
			if (inicioP != NULL)
			{
				int i = 0;
				char producto[30];

				i = SendMessage(hListaProductosMy, LB_GETCURSEL, 0, 0);
				SendMessage(hListaProductosMy, LB_GETTEXT, i, (LPARAM)producto);

				auxP = inicioP;
				while (auxP != NULL)
				{
					if (strcmp(auxP->nombre, producto) == 0)
					{
						llenarCuadro(hWnd, IDC_PicProductoMy, hStProductoMy, hStPrecioMy);
						break;
					}
					auxP = auxP->sig;
				}
			}
			return true;
		}

		case IDC_BtnTiendaMy:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			return true;

		case IDC_BtnVerCarritoMy:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_CARRITO), hInicio, Carrito);
			return true;

		case IDC_BtnCerrarSesionMy:
			MsgCerrarSesion(hWnd);
			return true;

		case IDC_BtnAgregarProductoMy:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_AGREGAR_PRODUCTO), hInicio, AgregarProducto);
			return true;

		case IDC_BtnModificarProductoMy:
		{
			char buffer[30];
			int i = 0;
			i = SendMessage(hListaProductosMy, LB_GETCURSEL, 0, 0);
			SendMessage(hListaProductosMy, LB_GETTEXT, (WPARAM)i, (LPARAM)buffer);
			auxP = inicioP;
			while (auxP != NULL)
			{
				if (strcmp(buffer, auxP->nombre) == 0 && auxP->idUsuario == usuarioLog.id)
				{
					EndDialog(hWnd, 0);
					DialogBox(Instancia, MAKEINTRESOURCE(IDD_MODIFICAR_PRODUCTO), hInicio, ModificarProducto);
					return true;
				}
				auxP = auxP->sig;
			}
			return true;
		}

		case IDC_BtnEliminarProductoMy:
		{
			char buffer[30];
			int i = 0;
			i = SendMessage(hListaProductosMy, LB_GETCURSEL, 0, 0);
			SendMessage(hListaProductosMy, LB_GETTEXT, (WPARAM)i, (LPARAM)buffer);
			auxP = inicioP;
			while (auxP != NULL)
			{
				if (strcmp(buffer, auxP->nombre) == 0)
				{
					MsgEliminarProducto(hWnd);
					break;
				}
				auxP = auxP->sig;
			}
			return true;
		}
			return true;

			//MENU
		#pragma region BotonesMenu
		case ID_USUARIO_MISPRODUCTOS:
			return true;

		case ID_USUARIO_MICARRITO:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_CARRITO), hInicio, Carrito);
			return true;

		case ID_USUARIO_ELIMINARCUENTA:
			MsgEliminarCuenta(hWnd);
			return true;

		case ID_USUARIO_CERRARSESION:
			MsgCerrarSesion(hWnd);
			return true;

		case ID_TIENDA_PRINCIPAL:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			return true;

		case ID_SALIR_CERRARPROGRAMA:
			MsgCerrarPrograma(hWnd);
			return true;
		#pragma endregion
		}
		return true;
	}

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
		return true;
	}
	return false;
}

BOOL CALLBACK AgregarProducto(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP bmp, bmpP, bmp1, bmp2;
	char pathBmp[MAX_PATH];
	char foto1[MAX_PATH] , foto2[MAX_PATH];
	char pathmp3[MAX_PATH], comando[MAX_PATH];
	char pathAlarma[MAX_PATH], comandoA[MAX_PATH];
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
	#pragma region handles
		hPicPerfilAP = GetDlgItem(hWnd, IDC_PicPerfilAP);
		hStIdAP = GetDlgItem(hWnd, IDC_StIdAP);
		hStUsuarioAP = GetDlgItem(hWnd, IDC_StUsuarioAP);
		hEditNombreAP = GetDlgItem(hWnd, IDC_EditNombreAP);
		hEditDescAP = GetDlgItem(hWnd, IDC_EditDescAP);
		hEditPrecioAP = GetDlgItem(hWnd, IDC_EditPrecioAP);
		hStPrecioAP = GetDlgItem(hWnd, IDC_StPrecioAP);
		hCbCategoAP = GetDlgItem(hWnd, IDC_CbCategoAP);
		hEditFoto1AP = GetDlgItem(hWnd, IDC_EditFoto1AP);
		hEditFoto2AP = GetDlgItem(hWnd, IDC_EditFoto2AP);
		hRadActivarAP = GetDlgItem(hWnd, IDC_RadActivarAP);
		hRadActivarAP = GetDlgItem(hWnd, IDC_RadDesactivarAP);
		hPicProductoAP = GetDlgItem(hWnd, IDC_PicProductoAP);

		//ACTIVAR CON MUSICA
		hEditAudioAP = GetDlgItem(hWnd, IDC_EditAudioAP);
		hBtnAudioAP = GetDlgItem(hWnd, IDC_BtnAudioAP);
		hStAudioAP = GetDlgItem(hWnd, IDC_StAudioAP);
		hBtnPlayAP = GetDlgItem(hWnd, IDC_BtnPlayAP);
		hBtnPauseAP = GetDlgItem(hWnd, IDC_BtnPauseAP);
		hBtnStopAP = GetDlgItem(hWnd, IDC_BtnStopAP);

		//ACTIVAR CON PROMOCION
		hStPromocionAP = GetDlgItem(hWnd, IDC_StPromocionAP);
		hEditPromoNombreAP = GetDlgItem(hWnd, IDC_EditPromoNombreAP);
		hStDescripcionAP = GetDlgItem(hWnd, IDC_StDescripcionAP);
		hEditPromoDescAP = GetDlgItem(hWnd, IDC_EditPromoDescAP);
		hStDescuentoAP = GetDlgItem(hWnd, IDC_StDescuentoAP);
		hStPorcentajeAP = GetDlgItem(hWnd, IDC_StPorcentajeAP);
		hSliderPromoAP = GetDlgItem(hWnd, IDC_SliderPromoAP);
		hStFechaIniAP = GetDlgItem(hWnd, IDC_StFechaIniAP);
		hDateIniAP = GetDlgItem(hWnd, IDC_DateIniAP);
		hTimeIniAP = GetDlgItem(hWnd, IDC_TimeIniAP);
		hStFechaFinAP = GetDlgItem(hWnd, IDC_StFechaFinAP);
		hDateFinAP = GetDlgItem(hWnd, IDC_DateFinAP);
		hTimeFinAP = GetDlgItem(hWnd, IDC_TimeFinAP);
		hStTiempoAP = GetDlgItem(hWnd, IDC_StTiempoAP);
		hStAlarmaAP = GetDlgItem(hWnd, IDC_StAlarmaAP);
		hCbAlarmaAP = GetDlgItem(hWnd, IDC_CbAlarmaAP);
		hBtnReproducirAP = GetDlgItem(hWnd, IDC_BtnReproAP);
		hBtnDetenerAP = GetDlgItem(hWnd, IDC_BtnDetenerAP);
		hStPrecioFinAP = GetDlgItem(hWnd, IDC_StPrecioFinAP);
		hStPrecioFinalAP = GetDlgItem(hWnd, IDC_StPrecioFinalAP);
	#pragma endregion
		
		CheckDlgButton(hWnd, IDC_RadDesactivarAP, BST_CHECKED);
		unablePromoAP();

		idNombreFoto(hWnd, bmp, IDC_PicPerfilAP, hStIdAP, hStUsuarioAP);

		agregarCbCategorias(hCbCategoAP);
		agregarCbAlarma(hCbAlarmaAP);

		bmpP = (HBITMAP)LoadImage(NULL, "Recursos\\minibag.bmp", IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicProductoAP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpP);
		oferta = false;
		return true;
	}

	case WM_HSCROLL:
	{
		if (errorPrecio == true)
		{
			int val = SendMessage(hSliderPromoAP, TBM_GETPOS, 0, 100);
			char output[5] = "0";
			sprintf(output, "%i%%", val);
			SetWindowText(hStPorcentajeAP, output);
			SetWindowText(hStPrecioFinalAP, "ERROR");
		}
		else
		{
			char buff[30];
			float precio = 0;
			float precioF = 0;
			float desc = 0;
			val = SendMessage(hSliderPromoAP, TBM_GETPOS, 0, 100);
			int porc = SendMessage(hSliderPromoAP, TBM_GETPOS, 0, 100);
			char output[5] = "0";
			sprintf(output, "%i%%", porc);
			SetWindowText(hStPorcentajeAP, output);

			//Operacion precio final
			GetWindowText(hEditPrecioAP, buff, sizeof(buff));
			precio = atoi(buff);
			desc = (val) / (100);
			precioF = precio * desc;
			precioF = precio - precioF;

			sprintf(buff, "$%.2f", precioF);
			SetWindowText(hStPrecioFinalAP, buff);
		}
		return true;
	}

	case WM_COMMAND:

		if( LOWORD(wParam) == IDC_EditPrecioAP && HIWORD(wParam) == EN_CHANGE)
		{
			validarPrecio(hEditPrecioAP, hStPrecioAP);
			return true;
		}

		switch (LOWORD(wParam))
		{
		case IDC_CbCategoAP:
		{
			int index = 0;
			index = SendMessage(hCbCategoAP, CB_GETCURSEL, 0, 0);
			if (index == 3)
			{
				EnableWindow(hStAudioAP, true);
				EnableWindow(hBtnAudioAP, true);
				EnableWindow(hEditAudioAP, true);
				EnableWindow(hBtnPlayAP, true);
				EnableWindow(hBtnPauseAP, true);
				EnableWindow(hBtnStopAP, true);
				musica = true;
			}
			else
			{
				EnableWindow(hStAudioAP, false);
				EnableWindow(hBtnAudioAP, false);
				EnableWindow(hEditAudioAP, false);
				EnableWindow(hBtnPlayAP, false);
				EnableWindow(hBtnPauseAP, false);
				EnableWindow(hBtnStopAP, false);
				musica = false;
			}
			return true;
		}

		case IDC_BtnFoto1AP:
			AgregarFoto(hWnd, hEditFoto1AP);
			GetWindowText(hEditFoto1AP, foto1, sizeof(foto1));
			bmp1 = (HBITMAP)LoadImage(NULL, foto1, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
			SendDlgItemMessage(hWnd, IDC_PicProductoAP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
			return true;

		case IDC_BtnFoto2AP:
			AgregarFoto(hWnd, hEditFoto2AP);
			GetWindowText(hEditFoto2AP, foto2, sizeof(foto2));
			bmp2 = (HBITMAP)LoadImage(NULL, foto2, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
			SendDlgItemMessage(hWnd, IDC_PicProductoAP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
			return true;

		case IDC_BtnAudioAP:
			AgregarAudio(hWnd, hEditAudioAP);
			return true;

		case IDC_BtnPlayAP:
			GetWindowText(hEditAudioAP, pathmp3, MAX_PATH);
			if (strcmp(pathmp3, "") != 0)
			{
				sprintf(comando, "open \"%s\" alias MP3", pathmp3);
				mciSendString(comando, NULL, 0, 0);
				mciSendString("play MP3", NULL, 0, 0);
			}
			return true;

		case IDC_BtnPauseAP:
			mciSendString("pause MP3", NULL, 0, 0);
			return true;

		case IDC_BtnStopAP:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			return true;

		case IDC_RadActivarAP:
		{
			enablePromoAP();
			return true;
		}

		case IDC_RadDesactivarAP:
		{
			unablePromoAP();
			return true;
		}

		case IDC_BtnReproAP:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			mciSendString("close Alarma", NULL, 0, 0);
			elegirAlarma(hCbAlarmaAP, pathAlarma);
			if (strcmp(pathAlarma, "") != 0)
			{
				sprintf(comandoA, "open \"%s\" alias Alarma", pathAlarma);
				mciSendString(comandoA, NULL, 0, 0);
				mciSendString("play Alarma", NULL, 0, 0);
			}
			return true;

		case IDC_BtnDetenerAP:
			mciSendString("stop Alarma", NULL, 0, 0);
			mciSendString("close Alarma", NULL, 0, 0);
			return true;

		case IDC_BtnAntAP:
			SendDlgItemMessage(hWnd, IDC_PicProductoAP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
			return true;

		case IDC_BtnSigAP:
			SendDlgItemMessage(hWnd, IDC_PicProductoAP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
			return true;

		case IDC_BtnAgregarAP:
		{
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			mciSendString("stop Alarma", NULL, 0, 0);
			mciSendString("close Alarma", NULL, 0, 0);
			checarTiempo(hDateIniAP, hDateFinAP, hTimeIniAP, hTimeFinAP, hStTiempoAP);
			if (errorPrecio == true)
			{
				MessageBox(hWnd, "Verifica que el precio se un valor v�lido", "PRICE_ERROR", MB_OK | MB_ICONWARNING);
				break;
			}

			if (oferta == true)
			{
				if (errorTiempo == true)
				{
					MessageBox(hWnd, "Asegurate de que la fecha inicial no pase de la fecha final", "DATE_ERROR", MB_OK | MB_ICONWARNING);
					break;
				}
				else if(errorTiempo == false)
				{
					char buff[MAX_PATH];
					float desc;
					producto guardar;
					promocion promo;

					//Obtencion de datos, Caso: con Promo
					//Datos de Producto
					guardar.id = NumeroRandom();
					guardar.idUsuario = usuarioLog.id;
					GetWindowText(hEditNombreAP, guardar.nombre, sizeof(guardar.nombre));
					GetWindowText(hEditDescAP, guardar.desc, sizeof(guardar.desc));
					GetWindowText(hEditPrecioAP, buff, sizeof(buff));
					guardar.precio = atof(buff);
					guardar.conPromocion = true;
					guardar.precioFinal = guardar.precio;
					guardar.categoria = SendMessage(hCbCategoAP, CB_GETCURSEL, 0, 0);
					GetWindowText(hEditFoto1AP, guardar.foto1, sizeof(guardar.foto1));
					GetWindowText(hEditFoto2AP, guardar.foto2, sizeof(guardar.foto2));
					if (guardar.categoria == 3)
						GetWindowText(hEditAudioAP, guardar.audio, sizeof(guardar.audio));
					else
						strcpy(guardar.audio, "NADA");

					//Datos de Promocion
					promo.idProducto = guardar.id;
					GetWindowText(hEditPromoNombreAP, promo.nombre, sizeof(promo.nombre));
					GetWindowText(hEditPromoDescAP, promo.descripcion, sizeof(promo.descripcion));
					promo.descuento = val;
					GetWindowText(hDateIniAP, promo.fechaIni, sizeof(promo.fechaIni));
					string fechaIni(promo.fechaIni);
					promo.diaIni = fechaIni.substr(0, 2);
					promo.mesIni = fechaIni.substr(3, 2);
					promo.anioIni = fechaIni.substr(6, 4);
					GetWindowText(hTimeIniAP, promo.horaIni, sizeof(promo.horaIni));
					GetWindowText(hDateFinAP, promo.fechaFin, sizeof(promo.fechaFin));
					string fechaFin(promo.fechaFin);
					promo.diaFin = fechaFin.substr(0, 2);
					promo.mesFin = fechaFin.substr(3, 2);
					promo.anioFin = fechaFin.substr(6, 4);
					GetWindowText(hTimeFinAP, promo.horaFin, sizeof(promo.horaFin));
					promo.alarma = SendMessage(hCbAlarmaAP, CB_GETCURSEL, 0, 0);

					if (strcmp(guardar.nombre, "") == 0 || strcmp(guardar.desc, "") == 0 || guardar.precio <= 0 || guardar.categoria < 0 || strcmp(guardar.foto1, "") == 0 || strcmp(guardar.foto2, "") == 0 || strcmp(guardar.audio, "") == 0 ||
						strcmp(promo.nombre, "") == 0 || strcmp(promo.descripcion, "") == 0 || promo.descuento == 0 || promo.alarma < 0)
					{
						MessageBox(hWnd, "Asegurate de ingresar todos los datos", "Error", MB_OK | MB_ICONWARNING);
						return true;
					}
					else
					{
						bool encontrado = false;
						if (inicioP == NULL)
						{
							producto *nuevo = new producto;
							nuevo->id = guardar.id;
							nuevo->idUsuario = guardar.idUsuario;
							strcpy(nuevo->nombre, guardar.nombre);
							strcpy(nuevo->desc, guardar.desc);
							nuevo->precio = guardar.precio;
							nuevo->conPromocion = guardar.conPromocion;
							nuevo->precioFinal = guardar.precioFinal;
							nuevo->categoria = guardar.categoria;
							strcpy(nuevo->foto1, guardar.foto1);
							strcpy(nuevo->foto2, guardar.foto2);
							strcpy(nuevo->audio, guardar.audio);

							auxP = nuevo;
							auxP->sig = NULL;
							auxP->ant = NULL;
							inicioP = auxP;
						}
						else if (inicioP != NULL)
						{
							auxP = inicioP;
							while (auxP != NULL)
							{
								if (strcmp(auxP->nombre, guardar.nombre) == 0  && auxP->idUsuario == guardar.idUsuario)
								{
									encontrado = true;
									break;
								}
								auxP = auxP->sig;
							}
							if (encontrado == true)
							{
								MessageBox(hWnd, "Ya tienes un producto con este nombre", "Aviso", MB_OK | MB_ICONWARNING);
								return true;
							}

							producto *nuevo = new producto;
							nuevo->id = guardar.id;
							auxP = inicioP;
							while (auxP != NULL)
							{
								if (nuevo->id == auxP->id)
								{
									while (nuevo->id == auxP->id)
									{
										nuevo->id = NumeroRandom();
										guardar.id = nuevo->id;
										promo.idProducto = nuevo->id;
									}
								}
								auxP = auxP->sig;
							}
							nuevo->idUsuario = guardar.idUsuario;
							strcpy(nuevo->nombre, guardar.nombre);
							strcpy(nuevo->desc, guardar.desc);
							nuevo->precio = guardar.precio;
							nuevo->conPromocion = guardar.conPromocion;
							nuevo->precioFinal = guardar.precioFinal;
							nuevo->categoria = guardar.categoria;
							strcpy(nuevo->foto1, guardar.foto1);
							strcpy(nuevo->foto2, guardar.foto2);
							strcpy(nuevo->audio, guardar.audio);

							auxP = inicioP;
							while (auxP->sig != NULL)
								auxP = auxP->sig;
							auxP->sig = nuevo;
							auxP->sig->ant = auxP;
							auxP = auxP->sig;
							auxP->sig = NULL;
							auxP = inicioP;
						}

						if (inicioPro == NULL)
						{
							promo.idProducto = guardar.id;
							promocion *nuevo = new promocion;
							nuevo->idProducto = promo.idProducto;
							strcpy(nuevo->nombre, promo.nombre);
							strcpy(nuevo->descripcion, promo.descripcion);
							nuevo->descuento = promo.descuento;
							strcpy(nuevo->fechaIni, promo.fechaIni);
							nuevo->diaIni = promo.diaIni;
							nuevo->mesIni = promo.mesIni;
							nuevo->anioIni = promo.anioIni;
							strcpy(nuevo->horaIni, promo.horaIni);
							strcpy(nuevo->fechaFin, promo.fechaFin);
							nuevo->diaFin = promo.diaFin;
							nuevo->mesFin = promo.mesFin;
							nuevo->anioFin = promo.anioFin;
							strcpy(nuevo->horaFin, promo.horaFin);
							nuevo->alarma = promo.alarma;

							auxPro = nuevo;
							auxPro->sig = NULL;
							auxPro->ant = NULL;
							inicioPro = auxPro;
						}
						else if (inicioPro != NULL)
						{
							promo.idProducto = guardar.id;
							promocion *nuevo = new promocion;
							nuevo->idProducto = promo.idProducto;
							strcpy(nuevo->nombre, promo.nombre);
							strcpy(nuevo->descripcion, promo.descripcion);
							nuevo->descuento = promo.descuento;
							strcpy(nuevo->fechaIni, promo.fechaIni);
							nuevo->diaIni = promo.diaIni;
							nuevo->mesIni = promo.mesIni;
							nuevo->anioIni = promo.anioIni;
							strcpy(nuevo->horaIni, promo.horaIni);
							strcpy(nuevo->fechaFin, promo.fechaFin);
							//Aqui pasa el error 
							nuevo->diaFin = promo.diaFin;
							nuevo->mesFin = promo.mesFin;
							nuevo->anioFin = promo.anioFin;
							strcpy(nuevo->horaFin, promo.horaFin);
							nuevo->alarma = promo.alarma;

							auxPro = inicioPro;
							while (auxPro->sig != NULL)
								auxPro = auxPro->sig;
							auxPro->sig = nuevo;
							auxPro->sig->ant = auxPro;
							auxPro = auxPro->sig;
							auxPro->sig = NULL;
							auxPro = inicioPro;
						}
						MessageBox(hWnd, "Producto registrado correctamente", "Aviso", MB_OK);
						EndDialog(hWnd, 0);
						DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
						return true;
					}
				}
			}
			else if (oferta == false)
			{
				char buff[MAX_PATH];
				producto guardar;

				//Obtencion de datos, Caso: sin Promocion
				guardar.id = NumeroRandom();
				guardar.idUsuario = usuarioLog.id;
				GetWindowText(hEditNombreAP, guardar.nombre, sizeof(guardar.nombre));
				GetWindowText(hEditDescAP, guardar.desc, sizeof(guardar.desc));
				GetWindowText(hEditPrecioAP, buff, sizeof(buff));
				guardar.precio = atof(buff);
				guardar.conPromocion = false;
				guardar.precioFinal = guardar.precio;
				guardar.categoria = SendMessage(hCbCategoAP, CB_GETCURSEL, 0, 0);
				GetWindowText(hEditFoto1AP, guardar.foto1, sizeof(guardar.foto1));
				GetWindowText(hEditFoto2AP, guardar.foto2, sizeof(guardar.foto2));
				if (guardar.categoria == 3)
					GetWindowText(hEditAudioAP, guardar.audio, sizeof(guardar.audio));
				else
					strcpy(guardar.audio, "NADA");

				//Guardar en lista ligada
				if (strcmp(guardar.nombre, "") == 0 || strcmp(guardar.desc, "") == 0 || guardar.precio <= 0 || guardar.categoria < 0 || strcmp(guardar.foto1, "") == 0 || strcmp(guardar.foto2, "") == 0 || strcmp(guardar.audio, "") == 0)
				{
					MessageBox(hWnd, "Asegurate de ingresar todos los datos", "Error", MB_OK | MB_ICONWARNING);
					return true;
				}
				else
				{
					if (inicioP == NULL)
					{
						producto *nuevo = new producto;
						nuevo->id = guardar.id;
						nuevo->idUsuario = guardar.idUsuario;
						strcpy(nuevo->nombre, guardar.nombre);
						strcpy(nuevo->desc, guardar.desc);
						nuevo->precio = guardar.precio;
						nuevo->conPromocion = guardar.conPromocion;
						nuevo->precioFinal = guardar.precioFinal;
						nuevo->categoria = guardar.categoria;
						strcpy(nuevo->foto1, guardar.foto1);
						strcpy(nuevo->foto2, guardar.foto2);
						strcpy(nuevo->audio, guardar.audio);

						auxP = nuevo;
						auxP->sig = NULL;
						auxP->ant = NULL;
						inicioP = auxP;
					}
					else
					{
						bool encontrado = false;
						auxP = inicioP;
						while (auxP != NULL)
						{
							if (strcmp(auxP->nombre, guardar.nombre) == 0 && auxP->idUsuario == guardar.idUsuario)
							{
								encontrado = true;
								break;
							}
							auxP = auxP->sig;
						}
						if (encontrado == true)
						{
							MessageBox(hWnd, "Ya tienes un producto con este nombre", "Aviso", MB_OK | MB_ICONWARNING);
							return true;
						}

						producto *nuevo = new producto;
						nuevo->id = guardar.id;
						auxP = inicioP;
						while (auxP != NULL)
						{
							if (nuevo->id == auxP->id)
							{
								while (nuevo->id == auxP->id)
								{
									nuevo->id = NumeroRandom();
								}
							}
							auxP = auxP->sig;
						}
						nuevo->idUsuario = guardar.idUsuario;
						strcpy(nuevo->nombre, guardar.nombre);
						strcpy(nuevo->desc, guardar.desc);
						nuevo->precio = guardar.precio;
						nuevo->conPromocion = guardar.conPromocion;
						nuevo->precioFinal = guardar.precioFinal;
						nuevo->categoria = guardar.categoria;
						strcpy(nuevo->foto1, guardar.foto1);
						strcpy(nuevo->foto2, guardar.foto2);
						strcpy(nuevo->audio, guardar.audio);

						auxP = inicioP;
						while (auxP->sig != NULL)
							auxP = auxP->sig;
						auxP->sig = nuevo;
						auxP->sig->ant = auxP;
						auxP = auxP->sig;
						auxP->sig = NULL;
						auxP = inicioP;
					}
					MessageBox(hWnd, "Producto registrado correctamente", "Aviso", MB_OK);
					EndDialog(hWnd, 0);
					DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
					return true;
				}
			}
			return true;
		}

		case IDC_BtnRegresarAP:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
			return true;

		case IDC_BtnTiendaAP:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			return true;

		//MENU
		#pragma region BotonesMenu
		case ID_USUARIO_MISPRODUCTOS:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
			return true;

		case ID_USUARIO_MICARRITO:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_CARRITO), hInicio, Carrito);
			return true;

		case ID_USUARIO_ELIMINARCUENTA:
			MsgEliminarCuenta(hWnd);
			return true;

		case ID_USUARIO_CERRARSESION:
			MsgCerrarSesion(hWnd);
			return true;

		case ID_TIENDA_PRINCIPAL:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			return true;

		case ID_SALIR_CERRARPROGRAMA:
			MsgCerrarPrograma(hWnd);
			return true;
		#pragma endregion
		}
		return true;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
		return true;
	}
	return false;
}

BOOL CALLBACK ModificarProducto(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP bmp, bmp1, bmp2;
	char pathBmp[MAX_PATH];
	char foto1[MAX_PATH], foto2[MAX_PATH];
	char pathmp3[MAX_PATH], comando[MAX_PATH];
	char pathAlarma[MAX_PATH], comandoA[MAX_PATH];
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		oferta = false;
		char buff[256];
		#pragma region handles
		hPicPerfilMP = GetDlgItem(hWnd, IDC_PicPerfilMP);
		hStIdMP = GetDlgItem(hWnd, IDC_StIdMP);
		hStUsuarioMP = GetDlgItem(hWnd, IDC_StUsuarioMP);
		hEditNombreMP = GetDlgItem(hWnd, IDC_EditNombreMP);
		hEditDescMP = GetDlgItem(hWnd, IDC_EditDescMP);
		hEditPrecioMP = GetDlgItem(hWnd, IDC_EditPrecioMP);
		hStPrecioMP = GetDlgItem(hWnd, IDC_StPrecioMP);
		hCbCategoMP = GetDlgItem(hWnd, IDC_CbCategoMP);
		hEditFoto1MP = GetDlgItem(hWnd, IDC_EditFoto1MP);
		hEditFoto2MP = GetDlgItem(hWnd, IDC_EditFoto2MP);
		hRadActivarMP = GetDlgItem(hWnd, IDC_RadActivarMP);
		hRadDesactivarMP = GetDlgItem(hWnd, IDC_RadDesactivarMP);
		hPicProductoMP = GetDlgItem(hWnd, IDC_PicProductoMP);

		hStAudioMP = GetDlgItem(hWnd, IDC_StAudioMP);
		hBtnAudioMP = GetDlgItem(hWnd, IDC_BtnAudioMP);
		hEditAudioMP = GetDlgItem(hWnd, IDC_EditAudioMP);
		hBtnPlayMP = GetDlgItem(hWnd, IDC_BtnPlayMP);
		hBtnPauseMP = GetDlgItem(hWnd, IDC_BtnPauseMP);
		hBtnStopMP = GetDlgItem(hWnd, IDC_BtnStopMP);

		hStPromocionMP = GetDlgItem(hWnd, IDC_StPromocionMP);
		hEditPromoNombreMP = GetDlgItem(hWnd, IDC_EditPromoNombreMP);
		hStDescripcionMP = GetDlgItem(hWnd, IDC_StDescripcionMP);
		hEditPromoDescMP = GetDlgItem(hWnd, IDC_EditPromoDescMP);
		hStDescuentoMP = GetDlgItem(hWnd, IDC_StDescuentoMP);
		hStPorcentajeMP = GetDlgItem(hWnd, IDC_StPorcentajeMP);
		hSliderPromoMP = GetDlgItem(hWnd, IDC_SliderPromoMP);
		hStFechaIniMP = GetDlgItem(hWnd, IDC_StFechaIniMP);
		hDateIniMP = GetDlgItem(hWnd, IDC_DateIniMP);
		hTimeIniMP = GetDlgItem(hWnd, IDC_TimeIniMP);
		hStFechaFinMP = GetDlgItem(hWnd, IDC_StFechaFinMP);
		hDateFinMP = GetDlgItem(hWnd, IDC_DateFinMP);
		hTimeFinMP = GetDlgItem(hWnd, IDC_TimeFinMP);
		hStTiempoMP = GetDlgItem(hWnd, IDC_StTiempoMP);
		hStAlarmaMP = GetDlgItem(hWnd, IDC_StAlarmaMP);
		hCbAlarmaMP = GetDlgItem(hWnd, IDC_CbAlarmaMP);
		hBtnReproducirMP = GetDlgItem(hWnd, IDC_BtnReproMP);
		hBtnDetenerMP = GetDlgItem(hWnd, IDC_BtnDetenerMP);
		hStPrecioFinMP = GetDlgItem(hWnd, IDC_StPrecioFinMP);
		hStPrecioFinalMP = GetDlgItem(hWnd, IDC_StPrecioFinalMP);
		#pragma endregion

		idNombreFoto(hWnd, bmp, IDC_PicPerfilMP, hStIdMP, hStUsuarioMP);

		agregarCbCategorias(hCbCategoMP);
		agregarCbAlarma(hCbAlarmaMP);

		#pragma region llenarVentana
		bmp2 = (HBITMAP)LoadImage(NULL, auxP->foto2, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicProductoMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);

		bmp1 = (HBITMAP)LoadImage(NULL, auxP->foto1, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicProductoMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);

		SetWindowText(hEditNombreMP, auxP->nombre);
		SetWindowText(hEditDescMP, auxP->desc);
		sprintf(buff, "%.2f", auxP->precio);
		SetWindowText(hEditPrecioMP, buff);
		SendMessage(hCbCategoMP, CB_SETCURSEL, auxP->categoria, 0);
		SetWindowText(hEditFoto1MP, auxP->foto1);
		SetWindowText(hEditFoto2MP, auxP->foto2);
		if (auxP->categoria == 3)
		{
			EnableWindow(hStAudioMP, true);
			EnableWindow(hBtnAudioMP, true);
			EnableWindow(hEditAudioMP, true);
			EnableWindow(hBtnPlayMP, true);
			EnableWindow(hBtnPauseMP, true);
			EnableWindow(hBtnStopMP, true);
			SetWindowText(hEditAudioMP, auxP->audio);
			musica = true;
		}
		else
		{
			musica = false;
		}
		if (auxP->conPromocion == true)
		{
			CheckDlgButton(hWnd, IDC_RadActivarMP, BST_CHECKED);
			enablePromoMP();
			auxPro = inicioPro;
			while (auxPro != NULL)
			{
				if (auxPro->idProducto == auxP->id)
					break;
				auxPro = auxPro->sig;
			}
			SetWindowText(hEditPromoNombreMP, auxPro->nombre);
			SetWindowText(hEditPromoDescMP, auxPro->descripcion);
			SendMessage(hCbAlarmaMP, CB_SETCURSEL, auxPro->alarma, 0);
			sprintf(buff, "%.2f", auxP->precioFinal);
			SetWindowText(hStPrecioFinalMP, buff);
		}
		else if (auxP->conPromocion == false)
		{
			CheckDlgButton(hWnd, IDC_RadDesactivarMP, BST_CHECKED);
			unablePromoMP();
		}
		#pragma endregion
		return true;
	}

	case WM_HSCROLL:
	{
		if (errorPrecio == true)
		{
			int val = SendMessage(hSliderPromoMP, TBM_GETPOS, 0, 100);
			char output[5] = "0";
			sprintf(output, "%i%%", val);
			SetWindowText(hStPorcentajeMP, output);
			SetWindowText(hStPrecioFinalMP, "ERROR");
		}
		else
		{
			char buff[30];
			float precio = 0;
			float precioF = 0;
			float desc = 0;
			val = SendMessage(hSliderPromoMP, TBM_GETPOS, 0, 100);
			int porc = SendMessage(hSliderPromoMP, TBM_GETPOS, 0, 100);
			char output[5] = "0";
			sprintf(output, "%i%%", porc);
			SetWindowText(hStPorcentajeMP, output);

			//Operacion precio final
			GetWindowText(hEditPrecioMP, buff, sizeof(buff));
			precio = atoi(buff);
			desc = (val) / (100);
			precioF = precio * desc;
			precioF = precio - precioF;

			sprintf(buff, "$%.2f", precioF);
			SetWindowText(hStPrecioFinalMP, buff);
		}
		return true;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_EditPrecioMP && HIWORD(wParam) == EN_CHANGE)
		{
			validarPrecio(hEditPrecioMP, hStPrecioMP);
			return true;
		}

		switch(LOWORD(wParam))
		{
		case IDC_CbCategoMP:
		{
		int index = 0;
		index = SendMessage(hCbCategoMP, CB_GETCURSEL, 0, 0);
		if (index == 3)
		{
			EnableWindow(hStAudioMP, true);
			EnableWindow(hBtnAudioMP, true);
			EnableWindow(hEditAudioMP, true);
			EnableWindow(hBtnPlayMP, true);
			EnableWindow(hBtnPauseMP, true);
			EnableWindow(hBtnStopMP, true);
			musica = true;
		}
		else
		{
			EnableWindow(hStAudioMP, false);
			EnableWindow(hBtnAudioMP, false);
			EnableWindow(hEditAudioMP, false);
			EnableWindow(hBtnPlayMP, false);
			EnableWindow(hBtnPauseMP, false);
			EnableWindow(hBtnStopMP, false);
			musica = false;
		}
		return true;
	}
		
		case IDC_BtnFoto1MP:
			AgregarFoto(hWnd, hEditFoto1MP);
			GetWindowText(hEditFoto1MP, foto1, sizeof(foto1));
			bmp1 = (HBITMAP)LoadImage(NULL, foto1, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
			SendDlgItemMessage(hWnd, IDC_PicProductoMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
			return true;

		case IDC_BtnFoto2MP:
			AgregarFoto(hWnd, hEditFoto2MP);
			GetWindowText(hEditFoto2MP, foto2, sizeof(foto2));
			bmp2 = (HBITMAP)LoadImage(NULL, foto2, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
			SendDlgItemMessage(hWnd, IDC_PicProductoMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
			return true;

		case IDC_BtnAudioMP:
			AgregarAudio(hWnd, hEditAudioMP);
			return true;

		case IDC_BtnPlayMP:
			GetWindowText(hEditAudioMP, pathmp3, MAX_PATH);
			if (strcmp(pathmp3, "") != 0)
			{
				sprintf(comando, "open \"%s\" alias MP3", pathmp3);
				mciSendString(comando, NULL, 0, 0);
				mciSendString("play MP3", NULL, 0, 0);
			}
			return true;

		case IDC_BtnPauseMP:
			mciSendString("pause MP3", NULL, 0, 0);
			return true;

		case IDC_BtnStopMP:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			return true;

		case IDC_RadActivarMP:
		{
			enablePromoMP();
			return true;
		}

		case IDC_RadDesactivarMP:
		{
			unablePromoMP();
			return true;
		}

		case IDC_BtnReproMP:
			mciSendString("close Alarma", NULL, 0, 0);
			elegirAlarma(hCbAlarmaMP, pathAlarma);
			if (strcmp(pathAlarma, "") != 0)
			{
				sprintf(comandoA, "open \"%s\" alias Alarma", pathAlarma);
				mciSendString(comandoA, NULL, 0, 0);
				mciSendString("play Alarma", NULL, 0, 0);
			}
			return true;

		case IDC_BtnDetenerMP:
			mciSendString("stop Alarma", NULL, 0, 0);
			mciSendString("close Alarma", NULL, 0, 0);
			return true;

		case IDC_BtnAntMP:
			SendDlgItemMessage(hWnd, IDC_PicProductoMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
			return true;

		case IDC_BtnSigMP:
			SendDlgItemMessage(hWnd, IDC_PicProductoMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
			return true;

		case IDC_BtnModificarMP:
		{
			checarTiempo(hDateIniMP, hDateFinMP, hTimeIniMP, hTimeFinMP, hStTiempoMP);
			if (errorPrecio == true)
			{
				MessageBox(hWnd, "Verifica que el precio se un valor v�lido", "PRICE_ERROR", MB_OK | MB_ICONWARNING);
				return true;
			}
			if (oferta == true)
			{
				if (errorTiempo == true)
				{
					MessageBox(hWnd, "Asegurate de que la fecha inicial no pase de la fecha final", "DATE_ERROR", MB_OK | MB_ICONWARNING);
					return true;
				}
				else if (errorTiempo == false)
				{
					char buff[MAX_PATH];
					float desc;
					producto guardar;
					promocion promo;

					//Obtencion de datos, Caso: con Promo
					//Datos de Producto
					GetWindowText(hEditNombreMP, guardar.nombre, sizeof(guardar.nombre));
					GetWindowText(hEditDescMP, guardar.desc, sizeof(guardar.desc));
					GetWindowText(hEditPrecioMP, buff, sizeof(buff));
					guardar.precio = atof(buff);
					guardar.conPromocion = true;
					guardar.precioFinal = guardar.precio;
					guardar.categoria = SendMessage(hCbCategoMP, CB_GETCURSEL, 0, 0);
					GetWindowText(hEditFoto1MP, guardar.foto1, sizeof(guardar.foto1));
					GetWindowText(hEditFoto2MP, guardar.foto2, sizeof(guardar.foto2));
					if (guardar.categoria == 3)
						GetWindowText(hEditAudioMP, guardar.audio, sizeof(guardar.audio));
					else
						strcpy(guardar.audio, "NADA");

					//Datos de Promocion
					promo.idProducto = auxP->id;
					GetWindowText(hEditPromoNombreMP, promo.nombre, sizeof(promo.nombre));
					GetWindowText(hEditPromoDescMP, promo.descripcion, sizeof(promo.descripcion));
					promo.descuento = val;
					GetWindowText(hDateIniMP, promo.fechaIni, sizeof(promo.fechaIni));
					string fechaIni(promo.fechaIni);
					promo.diaIni = fechaIni.substr(0, 2);
					promo.mesIni = fechaIni.substr(3, 2);
					promo.anioIni = fechaIni.substr(6, 4);
					GetWindowText(hTimeIniMP, promo.horaIni, sizeof(promo.horaIni));
					GetWindowText(hDateFinMP, promo.fechaFin, sizeof(promo.fechaFin));
					string fechaFin(promo.fechaFin);
					promo.diaFin = fechaFin.substr(0, 2);
					promo.mesFin = fechaFin.substr(3, 2);
					promo.anioFin = fechaFin.substr(6, 4);
					GetWindowText(hTimeFinMP, promo.horaFin, sizeof(promo.horaFin));
					promo.alarma = SendMessage(hCbAlarmaMP, CB_GETCURSEL, 0, 0);
					if (strcmp(guardar.nombre, "") == 0 || strcmp(guardar.desc, "") == 0 || guardar.precio <= 0 || guardar.categoria < 0 || strcmp(guardar.foto1, "") == 0 || strcmp(guardar.foto2, "") == 0 || strcmp(guardar.audio, "") == 0 ||
						strcmp(promo.nombre, "") == 0 || strcmp(promo.descripcion, "") == 0 || promo.descuento == 0 || promo.alarma < 0)
					{
						MessageBox(hWnd, "Asegurate de ingresar todos los datos", "Error", MB_OK | MB_ICONWARNING);
						return true;
					}
					else
					{
						bool teniaPromo = auxP->conPromocion;
						strcpy(auxP->desc, guardar.desc);
						auxP->precio = guardar.precio;
						auxP->conPromocion = true;
						auxP->precioFinal = guardar.precioFinal;
						auxP->categoria = guardar.categoria;
						strcpy(auxP->foto1, guardar.foto1);
						strcpy(auxP->foto2, guardar.foto2);
						strcpy(auxP->audio, guardar.audio);
						//El producto modificado no tenia promocion
						if (teniaPromo == false)
						{
							if (inicioPro == NULL)
							{
								promocion *nuevo = new promocion;
								nuevo->idProducto = promo.idProducto;
								strcpy(nuevo->nombre, promo.nombre);
								strcpy(nuevo->descripcion, promo.descripcion);
								nuevo->descuento = promo.descuento;
								strcpy(nuevo->fechaIni, promo.fechaIni);
								nuevo->diaIni = promo.diaIni;
								nuevo->mesIni = promo.mesIni;
								nuevo->anioIni = promo.anioIni;
								strcpy(nuevo->horaIni, promo.horaIni);
								strcpy(nuevo->fechaFin, promo.fechaFin);
								nuevo->diaFin = promo.diaFin;
								nuevo->mesFin = promo.mesFin;
								nuevo->anioFin = promo.anioFin;
								strcpy(nuevo->horaFin, promo.horaFin);
								nuevo->alarma = promo.alarma;

								auxPro = nuevo;
								auxPro->sig = NULL;
								auxPro->ant = NULL;
								inicioPro = auxPro;
							}
							else if (inicioPro != NULL)
							{
								promocion *nuevo = new promocion;
								nuevo->idProducto = promo.idProducto;
								strcpy(nuevo->nombre, promo.nombre);
								strcpy(nuevo->descripcion, promo.descripcion);
								nuevo->descuento = promo.descuento;
								strcpy(nuevo->fechaIni, promo.fechaIni);
								nuevo->diaIni = promo.diaIni;
								nuevo->mesIni = promo.mesIni;
								nuevo->anioIni = promo.anioIni;
								strcpy(nuevo->horaIni, promo.horaIni);
								strcpy(nuevo->fechaFin, promo.fechaFin);
								//Aqui pasa el error
								nuevo->diaFin = promo.diaFin;
								nuevo->mesFin = promo.mesFin;
								nuevo->anioFin = promo.anioFin;
								strcpy(nuevo->horaFin, promo.horaFin);
								nuevo->alarma = promo.alarma;

								auxPro = inicioPro;
								while (auxPro->sig != NULL)
									auxPro = auxPro->sig;
								auxPro->sig = nuevo;
								auxPro->sig->ant = auxPro;
								auxPro = auxPro->sig;
								auxPro->sig = NULL;
								auxPro = inicioPro;
							}
							MessageBox(hWnd, "Producto modificado correctamente", "Aviso", MB_OK);
							EndDialog(hWnd, 0);
							DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
							return true;
						}
						//El producto modificado ya tenia promocion
						else if (teniaPromo == true)
						{
							strcpy(auxPro->nombre, promo.nombre);
							strcpy(auxPro->descripcion, promo.descripcion);
							auxPro->descuento = promo.descuento;
							strcpy(auxPro->fechaIni, promo.fechaIni);
							auxPro->diaIni = promo.diaIni;
							auxPro->mesIni = promo.mesIni;
							auxPro->anioIni = promo.anioIni;
							strcpy(auxPro->horaIni, promo.horaIni);
							strcpy(auxPro->fechaFin, promo.fechaFin);
							auxPro->diaFin = promo.diaFin;
							auxPro->mesFin = promo.mesFin;
							auxPro->anioFin = promo.anioFin;
							strcpy(auxPro->horaFin, promo.horaFin);
							auxPro->alarma = promo.alarma;
							auxPro->iniAlarma = false;
							auxPro->finAlarma = false;

							MessageBox(hWnd, "Producto modificado correctamente", "Aviso", MB_OK);
							EndDialog(hWnd, 0);
							DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
							return true;
						}
					}
				}
			}
			//El producto no tendra oferta
			else if (oferta == false)
			{
				bool teniaPromo = auxP->conPromocion;
				char buff[MAX_PATH];
				producto guardar;

				//Obtencion de datos, Caso: sin Promocion
				GetWindowText(hEditDescMP, guardar.desc, sizeof(guardar.desc));
				GetWindowText(hEditPrecioMP, buff, sizeof(buff));
				guardar.precio = atof(buff);
				guardar.conPromocion = false;
				guardar.precioFinal = guardar.precio;
				guardar.categoria = SendMessage(hCbCategoMP, CB_GETCURSEL, 0, 0);
				GetWindowText(hEditFoto1MP, guardar.foto1, sizeof(guardar.foto1));
				GetWindowText(hEditFoto2MP, guardar.foto2, sizeof(guardar.foto2));
				if (guardar.categoria == 3)
					GetWindowText(hEditAudioMP, guardar.audio, sizeof(guardar.audio));
				else
					strcpy(guardar.audio, "NADA");

				if (strcmp(guardar.nombre, "") == 0 || strcmp(guardar.desc, "") == 0 || guardar.precio <= 0 || guardar.categoria < 0 || strcmp(guardar.foto1, "") == 0 || strcmp(guardar.foto2, "") == 0 || strcmp(guardar.audio, "") == 0)
				{
					MessageBox(hWnd, "Asegurate de ingresar todos los datos", "Error", MB_OK | MB_ICONWARNING);
					return true;
				}
				else
				{
					strcpy(auxP->desc, guardar.desc);
					auxP->precio = guardar.precio;
					auxP->conPromocion = guardar.conPromocion;
					auxP->precioFinal = guardar.precioFinal;
					auxP->categoria = guardar.categoria;
					strcpy(auxP->foto1, guardar.foto1);
					strcpy(auxP->foto2, guardar.foto2);
					strcpy(auxP->audio, guardar.audio);
					if (teniaPromo == true)
					{
						//ELIMINAR UNICO
						if (auxPro->sig == NULL && auxPro->ant == NULL)
						{
							delete auxPro;
							inicioPro = auxPro = NULL;
						}
						//ULTIMO PRODUCTO
						else if (auxPro->sig == NULL)
						{
							promocion *auxPro2;
							auxPro2 = auxPro;
							auxPro = auxPro->ant;
							auxPro->sig = NULL;
							delete auxPro2;
							auxPro = inicioPro;
						}
						//EL PRIMERO
						else if (auxPro->ant == NULL) {
							promocion *auxPro2;
							auxPro2 = auxPro;
							auxPro = auxPro->sig;
							auxPro->ant = NULL;
							delete auxPro2;
							inicioPro = auxPro;
						}
						//EN MEDIO
						else
						{
							promocion *auxPro2;
							auxPro2 = auxPro;
							auxPro->sig->ant = auxPro->ant;
							auxPro->ant->sig = auxPro->sig;
							auxPro = inicioPro;
							delete auxPro2;
						}
					}
				}
				MessageBox(hWnd, "Producto modificado correctamente", "Aviso", MB_OK);
				EndDialog(hWnd, 0);
				DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
				return true;
			}
			return true;
		}

		case IDC_BtnRegresarMP:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
			return true;

		case IDC_BtnTiendaMP:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			return true;

			//MENU
#pragma region BotonesMenu
		case ID_USUARIO_MISPRODUCTOS:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
			return true;

		case ID_USUARIO_MICARRITO:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_CARRITO), hInicio, Carrito);
			return true;

		case ID_USUARIO_ELIMINARCUENTA:
			MsgEliminarCuenta(hWnd);
			return true;

		case ID_USUARIO_CERRARSESION:
			MsgCerrarSesion(hWnd);
			return true;

		case ID_TIENDA_PRINCIPAL:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			return true;

		case ID_SALIR_CERRARPROGRAMA:
			MsgCerrarPrograma(hWnd);
			return true;
#pragma endregion
		}
		return true;
	}

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hWnd, MisProductos);
		return true;

	}
	return false;
}

BOOL CALLBACK VerProducto(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP bmp, bmp1, bmp2;
	char pathBmp[MAX_PATH];
	char pathmp3[MAX_PATH], comando[MAX_PATH];
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		hPicPerfilVP = GetDlgItem(hWnd, IDC_PicPerfilVP);
		hStIdVP = GetDlgItem(hWnd, IDC_StIdVP);
		hStUsuarioVP = GetDlgItem(hWnd, IDC_StUsuarioVP);
		hPicProductoVP = GetDlgItem(hWnd, IDC_PicProductoVP);
		hStPromoVP = GetDlgItem(hWnd, IDC_StPromoVP);
		hStNombreVP = GetDlgItem(hWnd, IDC_StNombreVP);
		hEditDescVP = GetDlgItem(hWnd, IDC_EditDescVP);
		hStPrecioVP = GetDlgItem(hWnd, IDC_StPrecioVP);
		hStCatVP = GetDlgItem(hWnd, IDC_StCatVP);
		hStVendedorVP = GetDlgItem(hWnd, IDC_StVendedorVP);
		hStAudioVP = GetDlgItem(hWnd, IDC_StAudioVP);
		hEditAudioVP = GetDlgItem(hWnd, IDC_EditAudioVP);
		hBtnPlayVP = GetDlgItem(hWnd, IDC_BtnPlayVP);
		hBtnPauseVP = GetDlgItem(hWnd, IDC_BtnPauseVP);
		hBtnStopVP = GetDlgItem(hWnd, IDC_BtnStopVP);

		idNombreFoto(hWnd, bmp, IDC_PicPerfilVP, hStIdVP, hStUsuarioVP);

		char buff[256];

		bmp2 = (HBITMAP)LoadImage(NULL, auxP->foto2, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicProductoVP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);

		bmp1 = (HBITMAP)LoadImage(NULL, auxP->foto1, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicProductoVP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);

		SetWindowText(hStPromoVP, "");
		SetWindowText(hStNombreVP, auxP->nombre);
		SetWindowText(hEditDescVP, auxP->desc);
		sprintf(buff, "$%.2f", auxP->precioFinal);
		SetWindowText(hStPrecioVP, buff);
		switch (auxP->categoria)
		{
		case 0:
			SetWindowText(hStCatVP, "Libros");
			break;
		case 1:
			SetWindowText(hStCatVP, "Television");
			break;
		case 2:
			SetWindowText(hStCatVP, "DVD");
			break;
		case 3:
			SetWindowText(hStCatVP, "CD");
			break;
		case 4:
			SetWindowText(hStCatVP, "Celulares");
			break;;
		case 5:
			SetWindowText(hStCatVP, "Software");
			break;
		case 6:
			SetWindowText(hStCatVP, "Computadoras");
			break;
		case 7:
			SetWindowText(hStCatVP, "Videojuegos");
			break;
		case 8:
			SetWindowText(hStCatVP, "Hogar");
			break;
		case 9:
			SetWindowText(hStCatVP, "Herramientas");
			break;
		case 10:
			SetWindowText(hStCatVP, "Automotriz");
			break;
		case 11:
			SetWindowText(hStCatVP, "Juguetes");
			break;
		case 12:
			SetWindowText(hStCatVP, "Mascotas");
			break;
		case 13:
			SetWindowText(hStCatVP, "Bebe");
			break;
		case 14:
			SetWindowText(hStCatVP, "Ropa");
			break;
		case 15:
			SetWindowText(hStCatVP, "Deporte");
			break;
		case 16:
			SetWindowText(hStCatVP, "Salud");
			break;
		case 17:
			SetWindowText(hStCatVP, "Belleza");
			break;
		}
		auxU = inicioU;
		while (auxU != NULL)
		{
			if (auxU->id == auxP->idUsuario)
			{
				SetWindowText(hStVendedorVP, auxU->nombre);
				break;
			}
			auxU = auxU->sig;
		}
		if (auxP->categoria == 3)
		{
			EnableWindow(hStAudioVP, true);
			EnableWindow(hEditAudioVP, true);
			EnableWindow(hBtnPlayVP, true);
			EnableWindow(hBtnPauseVP, true);
			EnableWindow(hBtnStopVP, true);
			SetWindowText(hEditAudioVP, auxP->audio);
		}
		if (auxP->conPromocion == true)
		{
			auxPro = inicioPro;
			while (auxPro != NULL)
			{
				if (auxP->id == auxPro->idProducto)
				{
					sprintf(buff, "%s %s --------- %s %s", auxPro->fechaIni, auxPro->horaIni, auxPro->fechaFin, auxPro->horaFin);
					SetWindowText(hStPromoVP, buff);
				}
				auxPro = auxPro->sig;
			}
		}
		return true;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BtnRegresarVP:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			return true;

		case IDC_BtnAntVP:
			SendDlgItemMessage(hWnd, IDC_PicProductoVP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
			return true;

		case IDC_BtnSigVP:
			SendDlgItemMessage(hWnd, IDC_PicProductoVP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
			return true;

		case IDC_BtnPlayVP:
			GetWindowText(hEditAudioVP, pathmp3, MAX_PATH);
			if (strcmp(pathmp3, "") != 0)
			{
				sprintf(comando, "open \"%s\" alias MP3", pathmp3);
				mciSendString(comando, NULL, 0, 0);
				mciSendString("play MP3", NULL, 0, 0);
			}
			return true;

		case IDC_BtnPauseVP:
			mciSendString("pause MP3", NULL, 0, 0);
			return true;

		case IDC_BtnStopVP:
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			return true;

		case IDC_BtnCarritoVP:
		{
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			auxCar = inicioCar;
			while (auxCar != NULL)
			{
				if (auxCar->idUsuario == usuarioLog.id)
					break;
				auxCar = auxCar->sig;
			}
			if (auxCar == NULL)
			{
				MessageBox(hWnd, "Error en datos guardados", "Carrito", MB_OK | MB_ICONWARNING);
				return true;
			}

			int i = 0;
			while (i != 10)
			{
				if (auxCar->carrito[i].idUsuario < 0)
				{
					auxCar->carrito[i] = *auxP;
					break;
				}
				i++;
			}
			if (i == 10)
			{
				MessageBox(hWnd, "El carrito esta lleno", "Carrito", MB_OK|MB_ICONWARNING);
				return true;
			}
			MessageBox(hWnd, "El producto ha sido a�adido al carrito", "Carrito", MB_OK);
			return true;
		}

#pragma region BotonesMenu
		case ID_USUARIO_MISPRODUCTOS:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
			return true;

		case ID_USUARIO_MICARRITO:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_CARRITO), hInicio, Carrito);
			return true;

		case ID_USUARIO_ELIMINARCUENTA:
			MsgEliminarCuenta(hWnd);
			return true;

		case ID_USUARIO_CERRARSESION:
			MsgCerrarSesion(hWnd);
			return true;

		case ID_TIENDA_PRINCIPAL:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			return true;

		case ID_SALIR_CERRARPROGRAMA:
			MsgCerrarPrograma(hWnd);
			return true;
#pragma endregion
			return true;
		}
		return true;
	}

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);

		return true;
	}
	return false;
}

BOOL CALLBACK Carrito(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP bmp, bmpP;
	char pathBmp[MAX_PATH];
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		hPicPerfilC = GetDlgItem(hWnd, IDC_PicPerfilC);
		hStIdC = GetDlgItem(hWnd, IDC_StIdC);
		hStUsuarioC = GetDlgItem(hWnd, IDC_StUsuarioC);
		hListaCarritoC = GetDlgItem(hWnd, IDC_ListaCarritoC);
		hPicProductoC = GetDlgItem(hWnd, IDC_PicProductoC);
		hStProductoC = GetDlgItem(hWnd, IDC_StProductoC);
		hStPrecioC = GetDlgItem(hWnd, IDC_StPrecioC);
		hStAhorroC = GetDlgItem(hWnd, IDC_StAhorroC);
		hStTotalC = GetDlgItem(hWnd, IDC_StTotalC);

		idNombreFoto(hWnd, bmp, IDC_PicPerfilC, hStIdC, hStUsuarioC);
		float ahorro = 0;
		float total = 0;
		char buff[256];
		int i = 0;

		auxCar = inicioCar;
		while (auxCar != NULL)
		{
			if (auxCar->idUsuario == usuarioLog.id)
			break;
			auxCar = auxCar->sig;
		}

		while (i != 10)
		{
			if (auxCar->carrito[i].id > 0)
			{
				SendMessage(hListaCarritoC, LB_ADDSTRING, 0, (LPARAM)auxCar->carrito[i].nombre);
				ahorro = ahorro + auxCar->carrito[i].precio;
				total = total + auxCar->carrito[i].precioFinal;
			}
			i++;
		}

		bmpP = (HBITMAP)LoadImage(NULL, "Recursos//minibag.bmp", IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicProductoC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpP);

		sprintf(buff, "$%.2f", total);
		SetWindowText(hStTotalC, buff);
		ahorro = ahorro - total;
		sprintf(buff, "$%.2f", ahorro);
		SetWindowText(hStAhorroC, buff);
		return true;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_ListaCarritoC:
		{
			int i = 0;
			char buff[50];
			char producto[30];

			i = SendMessage(hListaCarritoC, LB_GETCURSEL, 0, 0);
			SendMessage(hListaCarritoC, LB_GETTEXT, i, (LPARAM)producto);

			i = 0;
			while (i != 10)
			{
				if (strcmp(auxCar->carrito[i].nombre, producto) == 0 && auxCar->carrito[i].id > 0)
				{
					bmpP = (HBITMAP)LoadImage(NULL, auxCar->carrito[i].foto1, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
					SendDlgItemMessage(hWnd, IDC_PicProductoC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmpP);

					SetWindowText(hStProductoC, auxCar->carrito[i].nombre);
					sprintf(buff, "$%.2f", auxCar->carrito[i].precioFinal);
					SetWindowText(hStPrecioC, buff);
					break;
				}
				i++;
			}
			return true;
		}

		case IDC_BtnEliminarC:
		{
		int i = 0;
		char buff[50];
		char producto[30];

		i = SendMessage(hListaCarritoC, LB_GETCURSEL, 0, 0);
		SendMessage(hListaCarritoC, LB_GETTEXT, i, (LPARAM)producto);

		i = 0;
		while (i != 10)
		{
			if (strcmp(auxCar->carrito[i].nombre, producto) == 0 && auxCar->carrito[i].id > 0)
			{
				auxCar->carrito[i].id = -1;
				EndDialog(hWnd, 0);
				DialogBox(Instancia, MAKEINTRESOURCE(IDD_CARRITO), hInicio, Carrito);
				break;
			}
			i++;
		}
			return true;
		}

		case IDC_BtnComprarC:
		{
			int i = 0;
			while (i != 10)
			{
				if (auxCar->carrito[i].id > 0)
					auxCar->carrito[i].id = -1;
				i++;
			}
			MessageBox(hWnd, "Su compra ha sido confirmada", "Compra", MB_OK);
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_CARRITO), hInicio, Carrito);
			return true;
		}
			
#pragma region BotonesMenu
		case ID_USUARIO_MISPRODUCTOS:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
			return true;

		case ID_USUARIO_MICARRITO:
			return true;

		case ID_USUARIO_ELIMINARCUENTA:
			MsgEliminarCuenta(hWnd);
			return true;

		case ID_USUARIO_CERRARSESION:
			MsgCerrarSesion(hWnd);
			return true;

		case ID_TIENDA_PRINCIPAL:
			EndDialog(hWnd, 0);
			DialogBox(Instancia, MAKEINTRESOURCE(IDD_TIENDA), hInicio, Tienda);
			return true;

		case ID_SALIR_CERRARPROGRAMA:
			MsgCerrarPrograma(hWnd);
			return true;
#pragma endregion
		}
		return true;
	}

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
		return true;
	}
	return false;
}

BOOL CALLBACK Alarma(HWND hWnd, UINT mensaje, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP bmp;
	char comando[256];
	switch (mensaje)
	{
	case WM_INITDIALOG:
	{
		hStAvisoA = GetDlgItem(hWnd, IDC_StAvisoA);
		hStNombreA = GetDlgItem(hWnd, IDC_StNombreA);
		hStPrecioA = GetDlgItem(hWnd, IDC_StPrecioA);
		hStCategoriaA = GetDlgItem(hWnd, IDC_StCategoriaA);
		hStVendedorA = GetDlgItem(hWnd, IDC_StVendedorA);
		PicProductoA = GetDlgItem(hWnd, IDC_PicProductoA);

		KillTimer(hWnd, TimmerID1);
		char buff[256];
		char buffmp3[256];

		//Buscar producto
		auxPA = inicioP;
		while (auxPA != NULL)
		{
			if (auxPA->id == auxProA->idProducto)
				break;
			auxPA = auxPA->sig;
		}

		//Elegir la alarma
		switch (auxProA->alarma)
		{
		case 0:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\A_real_hoot.mp3");
			break;
		case 1:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Bright_morning.mp3");
			break;
		case 2:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Cuckoo_clock.mp3");
			break;
		case 3:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Early_twilight.mp3");
			break;
		case 4:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Full_of_wonder.mp3");
			break;
		case 5:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Gentle_breeze.mp3");
			break;
		case 6:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Icicles.mp3");
			break;
		case 7:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Jump_start.mp3");
			break;
		case 8:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Loose_change.mp3");
			break;
		case 9:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Rolling_fog.mp3");
			break;
		case 10:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Spokes.mp3");
			break;
		case 11:
			strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Sunshower.mp3");
			break;
		}

		//Reproducir
		sprintf(comando, "open \"%s\" alias MP3", buffmp3);
		mciSendString(comando, NULL, 0, 0);
		mciSendString("play MP3", NULL, 0, 0);

		//Empieza la promocion
		if (auxProA->iniAlarma == true && auxProA->finAlarma == false)
		{
			float desc;
			SetWindowText(hStAvisoA, "LA PROMOCION HA EMPEZADO");
			desc = (auxProA->descuento) / (100);
			desc = auxPA->precio * desc;
			auxPA->precioFinal = auxPA->precio - desc;
		}

		//Termina la promocion
		if (auxProA->iniAlarma == true && auxProA->finAlarma == true)
		{
			SetWindowText(hStAvisoA, "LA PROMOCION HA FINALIZADO");
			auxPA->precioFinal = auxPA->precio;
			auxPA->conPromocion = false;
			//ELIMINAR UNICA PROMOCION
			if (auxProA->sig == NULL && auxProA->ant == NULL)
			{
				delete auxProA;
				inicioPro = auxProA = NULL;
			}
			//ULTIMO PROMOCION
			else if (auxProA->sig == NULL)
			{
				promocion *auxPro2;
				auxPro2 = auxProA;
				auxProA = auxProA->ant;
				auxProA->sig = NULL;
				delete auxPro2;
				auxProA = inicioPro;
			}
			//PRIMERA PROMOCION
			else if (auxProA->ant == NULL) {
				promocion *auxPro2;
				auxPro2 = auxProA;
				auxProA = auxProA->sig;
				auxProA->ant = NULL;
				delete auxPro2;
				inicioPro = auxProA;
			}
			//PROMOCION ENMEDIO
			else
			{
				promocion *auxPro2;
				auxPro2 = auxProA;
				auxProA->sig->ant = auxProA->ant;
				auxProA->ant->sig = auxProA->sig;
				auxProA = inicioPro;
				delete auxPro2;
			}
		}

		SetWindowText(hStNombreA, auxPA->nombre);
		sprintf(buff, "$%.2f", auxPA->precioFinal);
		SetWindowText(hStPrecioA, buff);
		bmp = (HBITMAP)LoadImage(NULL, auxPA->foto1, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_PicProductoA, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		
		switch (auxPA->categoria)
		{
		case 0:
			SetWindowText(hStCategoriaA, "Libros");
			break;
		case 1:
			SetWindowText(hStCategoriaA, "Television");
			break;
		case 2:
			SetWindowText(hStCategoriaA, "DVD");
			break;
		case 3:
			SetWindowText(hStCategoriaA, "CD");
			break;
		case 4:
			SetWindowText(hStCategoriaA, "Celulares");
			break;;
		case 5:
			SetWindowText(hStCategoriaA, "Software");
			break;
		case 6:
			SetWindowText(hStCategoriaA, "Computadoras");
			break;
		case 7:
			SetWindowText(hStCategoriaA, "Videojuegos");
			break;
		case 8:
			SetWindowText(hStCategoriaA, "Hogar");
			break;
		case 9:
			SetWindowText(hStCategoriaA, "Herramientas");
			break;
		case 10:
			SetWindowText(hStCategoriaA, "Automotriz");
			break;
		case 11:
			SetWindowText(hStCategoriaA, "Juguetes");
			break;
		case 12:
			SetWindowText(hStCategoriaA, "Mascotas");
			break;
		case 13:
			SetWindowText(hStCategoriaA, "Bebe");
			break;
		case 14:
			SetWindowText(hStCategoriaA, "Ropa");
			break;
		case 15:
			SetWindowText(hStCategoriaA, "Deporte");
			break;
		case 16:
			SetWindowText(hStCategoriaA, "Salud");
			break;
		case 17:
			SetWindowText(hStCategoriaA, "Belleza");
			break;
		}
		return true;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BtnOkA:
		{
			EndDialog(hWnd, 0);
			mciSendString("stop MP3", NULL, 0, 0);
			mciSendString("close MP3", NULL, 0, 0);
			return true;
		}
			return true;
		}
		return true;
	}
	}
	return false;
}

//Funciones
void AgregarFoto(HWND Dialog, HWND Edit)
{
	char szFile[MAX_PATH];
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Dialog;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Imagenes";
	ofn.lpstrFilter = "Imagen BITMAP\0*.bmp\0";
	ofn.nFilterIndex = 2;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		SetWindowText(Edit, ofn.lpstrFile);
	}
}

void AgregarAudio(HWND Dialog, HWND Edit)
{
	char szFile[MAX_PATH];
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = Dialog;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "C:\\Users\\Miini\\Music";
	ofn.lpstrFilter = "Audio MP3\0*.mp3\0";
	ofn.nFilterIndex = 2;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		SetWindowText(Edit, ofn.lpstrFile);
	}
}

int NumeroRandom()
{
	int i;
	srand(time(NULL));

	i = rand() % 999999 + 1;

	return i;
}

bool Logear(HWND hVentana,HWND hNombre, HWND hContra)
{
	char buffNombre[20];
	char buffContra[20];

	GetWindowText(hNombre, buffNombre, sizeof(buffNombre));
	GetWindowText(hContra, buffContra, sizeof(buffContra));
	
	auxU = inicioU;
	while (auxU != NULL)
	{
		if (strcmp(auxU->nombre, buffNombre) == 0)
		{
			if (strcmp(auxU->contrasenia, buffContra) == 0)
			{
				return true;
			}
		}
		auxU = auxU->sig;
	}
	return false;
}

int MsgCerrarSesion(HWND hWnd)
{
	int msgboxID = MessageBox(hWnd, "�Desea cerrar sesi�n?", "Cerrar sesi�n", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

	switch (msgboxID)
	{
	case IDYES:
		EndDialog(hWnd, 0);
		usuarioLog.id = 0;
		strcpy(usuarioLog.nombre, "");
		strcpy(usuarioLog.contrasenia, "");
		strcpy(usuarioLog.foto, "");
		break;

	case IDNO:
		break;
	}
	return msgboxID;
}

int MsgCerrarPrograma(HWND hWnd)
{
	int msgboxID = MessageBox(hWnd, "�Desea cerrar sesi�n y cerrar el programa?", "Salir", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

	switch (msgboxID)
	{
	case IDYES:
		guardarUsuarios();
		DestroyWindow(hInicio);
		break;

	case IDNO:
		break;
	}

	return msgboxID;
}

void guardarUsuarios()
{
	ofstream guardar;
	guardar.open(archivoUsuario, ios::out | ios::binary | ios::trunc);
	if (inicioU != NULL)
	{
		auxU = inicioU;
		while (auxU != NULL)
		{
			guardar.write((char*)reinterpret_cast<char*>(auxU), sizeof(usuario));
			auxU = auxU->sig;
		}
	}
}

void cargarUsuarios()
{
	ifstream cargar;
	cargar.open(archivoUsuario, ios::in | ios::binary);
	if (cargar.is_open())
	{
		usuario *nuevo = new usuario;
		cargar.read(reinterpret_cast<char*>(nuevo), sizeof(usuario));
		nuevo->sig = NULL;
		while (!cargar.eof())
		{
			if (inicioU == NULL)
			{
				inicioU = nuevo;
				auxU = nuevo;
			}
			else
			{
				auxU = inicioU;
				while (auxU->sig != NULL)
					auxU = auxU->sig;
				auxU->sig = nuevo;
				auxU->sig->ant = auxU;
				auxU = auxU->sig;
				auxU->sig = NULL;
			}
			nuevo = new usuario;
			cargar.read(reinterpret_cast<char*>(nuevo), sizeof(usuario));
			nuevo->sig = NULL;
			nuevo->ant = NULL;
		}
	}
}

void guardarProductos()
{
	ofstream guardar;
	guardar.open(archivoProducto, ios::out | ios::binary | ios::trunc);
	if (inicioP != NULL)
	{
		auxP = inicioP;
		while (auxP != NULL)
		{
			guardar.write((char*)reinterpret_cast<char*>(auxP), sizeof(producto));
			auxP = auxP->sig;
		}
	}
}

void cargarProductos()
{
	ifstream cargar;
	cargar.open(archivoProducto, ios::in | ios::binary);
	if (cargar.is_open())
	{
		producto *nuevo = new producto;
		cargar.read(reinterpret_cast<char*>(nuevo), sizeof(producto));
		nuevo->sig = NULL;
		nuevo->sig = NULL;
		while (!cargar.eof())
		{
			if (inicioP == NULL)
			{
				inicioP = nuevo;
				auxP = nuevo;
			}
			else
			{
				auxP = inicioP;
				while (auxP->sig != NULL)
					auxP = auxP->sig;
				auxP->sig = nuevo;
				auxP->sig->ant = auxP;
				auxP = auxP->sig;
				auxP->sig = NULL;
			}
			nuevo = new producto;
			cargar.read(reinterpret_cast<char*>(nuevo), sizeof(producto));
			nuevo->sig = NULL;
			nuevo->ant = NULL;
		}
	}
}

void guardarPromos()
{
	ofstream guardar;
	guardar.open(archivoPromo, ios::out | ios::binary | ios::trunc);
	if (inicioPro != NULL)
	{
		auxPro = inicioPro;
		while (auxPro != NULL)
		{
			guardar.write((char*)reinterpret_cast<char*>(auxPro), sizeof(promocion));
			auxPro = auxPro->sig;
		}
	}
}

void cargarPromos()
{
	ifstream cargar;
	cargar.open(archivoPromo, ios::in | ios::binary);
	if (cargar.is_open())
	{
		promocion *nuevo = new promocion;
		cargar.read(reinterpret_cast<char*>(nuevo), sizeof(promocion));
		nuevo->sig = NULL;
		nuevo->sig = NULL;
		while (!cargar.eof())
		{
			if (inicioPro == NULL)
			{
				inicioPro = nuevo;
				auxPro = nuevo;
			}
			else
			{
				auxPro = inicioPro;
				while (auxPro->sig != NULL)
					auxPro = auxPro->sig;
				auxPro->sig = nuevo;
				auxPro->sig->ant = auxPro;
				auxPro = auxPro->sig;
				auxPro->sig = NULL;
			}
			nuevo = new promocion;
			cargar.read(reinterpret_cast<char*>(nuevo), sizeof(promocion));
			nuevo->sig = NULL;
			nuevo->ant = NULL;
		}
	}
}

void guardarCarro()
{
	ofstream guardar;
	guardar.open(archivoCarro, ios::out | ios::binary | ios::trunc);
	if (inicioCar != NULL)
	{
		auxCar = inicioCar;
		while (auxCar != NULL)
		{
			guardar.write((char*)reinterpret_cast<char*>(auxCar), sizeof(carro));
			auxCar = auxCar->sig;
		}
	}
}

void cargarCarro()
{
	ifstream cargar;
	cargar.open(archivoCarro, ios::in | ios::binary);
	if (cargar.is_open())
	{
		carro *nuevo = new carro;
		cargar.read(reinterpret_cast<char*>(nuevo), sizeof(carro));
		nuevo->sig = NULL;
		nuevo->sig = NULL;
		while (!cargar.eof())
		{
			if (inicioCar == NULL)
			{
				inicioCar = nuevo;
				auxCar = nuevo;
			}
			else
			{
				auxCar = inicioCar;
				while (auxCar->sig != NULL)
					auxCar = auxCar->sig;
				auxCar->sig = nuevo;
				auxCar->sig->ant = auxCar;
				auxCar = auxCar->sig;
				auxCar->sig = NULL;
			}
			nuevo = new carro;
			cargar.read(reinterpret_cast<char*>(nuevo), sizeof(carro));
			nuevo->sig = NULL;
			nuevo->ant = NULL;
		}
	}
}

void agregarCbCategorias(HWND hCombo)
{
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Libros");
	SendMessage(hCombo, CB_ADDSTRING, 1, (LPARAM)"Television");
	SendMessage(hCombo, CB_ADDSTRING, 2, (LPARAM)"DVD");
	SendMessage(hCombo, CB_ADDSTRING, 3, (LPARAM)"CD");
	SendMessage(hCombo, CB_ADDSTRING, 4, (LPARAM)"Celular");
	SendMessage(hCombo, CB_ADDSTRING, 5, (LPARAM)"Software");
	SendMessage(hCombo, CB_ADDSTRING, 6, (LPARAM)"Computadora");
	SendMessage(hCombo, CB_ADDSTRING, 7, (LPARAM)"Videojuego");
	SendMessage(hCombo, CB_ADDSTRING, 8, (LPARAM)"Hogar");
	SendMessage(hCombo, CB_ADDSTRING, 9, (LPARAM)"Herramienta");
	SendMessage(hCombo, CB_ADDSTRING, 10, (LPARAM)"Automotriz");
	SendMessage(hCombo, CB_ADDSTRING, 11, (LPARAM)"Juguete");
	SendMessage(hCombo, CB_ADDSTRING, 12, (LPARAM)"Mascotas");
	SendMessage(hCombo, CB_ADDSTRING, 13, (LPARAM)"Bebe");
	SendMessage(hCombo, CB_ADDSTRING, 14, (LPARAM)"Ropa");
	SendMessage(hCombo, CB_ADDSTRING, 15, (LPARAM)"Deporte");
	SendMessage(hCombo, CB_ADDSTRING, 16, (LPARAM)"Salud");
	SendMessage(hCombo, CB_ADDSTRING, 17, (LPARAM)"Belleza");
}

void agregarCbAlarma(HWND hCombo)
{
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"A real hoot");
	SendMessage(hCombo, CB_ADDSTRING, 1, (LPARAM)"Bright morning");
	SendMessage(hCombo, CB_ADDSTRING, 2, (LPARAM)"Cuckoo clock");
	SendMessage(hCombo, CB_ADDSTRING, 3, (LPARAM)"Early twilight");
	SendMessage(hCombo, CB_ADDSTRING, 4, (LPARAM)"Full of wonder");
	SendMessage(hCombo, CB_ADDSTRING, 5, (LPARAM)"Gentle breeze");
	SendMessage(hCombo, CB_ADDSTRING, 6, (LPARAM)"Icicles");
	SendMessage(hCombo, CB_ADDSTRING, 7, (LPARAM)"Jump start");
	SendMessage(hCombo, CB_ADDSTRING, 8, (LPARAM)"Loose change");
	SendMessage(hCombo, CB_ADDSTRING, 9, (LPARAM)"Rolling fog");
	SendMessage(hCombo, CB_ADDSTRING, 10, (LPARAM)"Spokes");
	SendMessage(hCombo, CB_ADDSTRING, 11, (LPARAM)"Sunshower");
}

void idNombreFoto(HWND hVentana, static HBITMAP bmp, int PicControl, HWND hId, HWND hNombre) 
{
	bmp = (HBITMAP)LoadImage(NULL, usuarioLog.foto, IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	SendDlgItemMessage(hVentana, PicControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);

	char buffId[8];
	sprintf(buffId, "#%i", usuarioLog.id);
	SetWindowText(hId, buffId);

	SetWindowText(hNombre, usuarioLog.nombre);
}

void validarPrecio(HWND Edit, HWND Static)
{
	errorPrecio = false;
	char validacion[50];
	char buff[50];
	int punto = 0;
	int centavo = 0;
	GetWindowText(Edit, validacion, sizeof(validacion));
	for (int i = 0; i < sizeof(validacion); i++)
	{
		if (punto > 1)
		{
			errorPrecio = true;
			break;
		}
		if (centavo > 2)
		{
			errorPrecio = true;
			break;
		}
		if (validacion[i] == '\0')
		{
			break;
		}
		if (validacion[i] == '.')
		{
			punto++;
			continue;
		}
		if (punto > 0 && isdigit(validacion[i]))
		{
			centavo++;
			continue;
		}
		if (validacion[i] == '�' || validacion[i] == '�')
		{
			errorPrecio = true;
			break;
		}
		if (!isdigit(validacion[i]))
		{
			errorPrecio = true;
			break;
		}
	}

	if (errorPrecio == true)
	{
		SetWindowText(Static, "Precio invalido");
	}
	else
	{
		SetWindowText(Static, "");
	}
}

void enablePromoAP()
{
	EnableWindow(hStPromocionAP, true);
	EnableWindow(hEditPromoNombreAP, true);
	EnableWindow(hStDescripcionAP, true);
	EnableWindow(hEditPromoDescAP, true);
	EnableWindow(hStDescuentoAP, true);
	EnableWindow(hStPorcentajeAP, true);
	EnableWindow(hSliderPromoAP, true);
	EnableWindow(hStFechaIniAP, true);
	EnableWindow(hDateIniAP, true);
	EnableWindow(hTimeIniAP, true);
	EnableWindow(hStFechaFinAP, true);
	EnableWindow(hDateFinAP, true);
	EnableWindow(hTimeFinAP, true);
	EnableWindow(hStAlarmaAP, true);
	EnableWindow(hCbAlarmaAP, true);
	EnableWindow(hBtnReproducirAP, true);
	EnableWindow(hBtnDetenerAP, true);
	EnableWindow(hStPrecioFinAP, true);
	EnableWindow(hStPrecioFinalAP, true);
	oferta = true;
}

void unablePromoAP()
{
	EnableWindow(hStPromocionAP, false);
	EnableWindow(hEditPromoNombreAP, false);
	EnableWindow(hStDescripcionAP, false);
	EnableWindow(hEditPromoDescAP, false);
	EnableWindow(hStDescuentoAP, false);
	EnableWindow(hStPorcentajeAP, false);
	EnableWindow(hSliderPromoAP, false);
	EnableWindow(hStFechaIniAP, false);
	EnableWindow(hDateIniAP, false);
	EnableWindow(hTimeIniAP, false);
	EnableWindow(hStFechaFinAP, false);
	EnableWindow(hDateFinAP, false);
	EnableWindow(hTimeFinAP, false);
	EnableWindow(hStAlarmaAP, false);
	EnableWindow(hCbAlarmaAP, false);
	EnableWindow(hBtnReproducirAP, false);
	EnableWindow(hBtnDetenerAP, false);
	EnableWindow(hStPrecioFinAP, false);
	EnableWindow(hStPrecioFinalAP, false);
	oferta = false;
}

void enablePromoMP()
{
	EnableWindow(hStPromocionMP, true);
	EnableWindow(hEditPromoNombreMP, true);
	EnableWindow(hStDescripcionMP, true);
	EnableWindow(hEditPromoDescMP, true);
	EnableWindow(hStDescuentoMP, true);
	EnableWindow(hStPorcentajeMP, true);
	EnableWindow(hSliderPromoMP, true);
	EnableWindow(hStFechaIniMP, true);
	EnableWindow(hDateIniMP, true);
	EnableWindow(hTimeIniMP, true);
	EnableWindow(hStFechaFinMP, true);
	EnableWindow(hDateFinMP, true);
	EnableWindow(hTimeFinMP, true);
	EnableWindow(hStAlarmaMP, true);
	EnableWindow(hCbAlarmaMP, true);
	EnableWindow(hBtnReproducirMP, true);
	EnableWindow(hBtnDetenerMP, true);
	EnableWindow(hStPrecioFinMP, true);
	EnableWindow(hStPrecioFinalMP, true);
	oferta = true;
}

void unablePromoMP()
{
	EnableWindow(hStPromocionMP, false);
	EnableWindow(hEditPromoNombreMP, false);
	EnableWindow(hStDescripcionMP, false);
	EnableWindow(hEditPromoDescMP, false);
	EnableWindow(hStDescuentoMP, false);
	EnableWindow(hStPorcentajeMP, false);
	EnableWindow(hSliderPromoMP, false);
	EnableWindow(hStFechaIniMP, false);
	EnableWindow(hDateIniMP, false);
	EnableWindow(hTimeIniMP, false);
	EnableWindow(hStFechaFinMP, false);
	EnableWindow(hDateFinMP, false);
	EnableWindow(hTimeFinMP, false);
	EnableWindow(hStAlarmaMP, false);
	EnableWindow(hCbAlarmaMP, false);
	EnableWindow(hBtnReproducirMP, false);
	EnableWindow(hBtnDetenerMP, false);
	EnableWindow(hStPrecioFinMP, false);
	EnableWindow(hStPrecioFinalMP, false);
	oferta = false;
}

void elegirAlarma(HWND hCombo, char buffmp3[MAX_PATH])
{
	int index = 0;
	index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
	switch (index)
	{
	case 0:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\A_real_hoot.mp3");
		break;
	case 1:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Bright_morning.mp3");
		break;
	case 2:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Cuckoo_clock.mp3");
		break;
	case 3:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Early_twilight.mp3");
		break;
	case 4:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Full_of_wonder.mp3");
		break;
	case 5:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Gentle_breeze.mp3");
		break;
	case 6:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Icicles.mp3");
		break;
	case 7:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Jump_start.mp3");
		break;
	case 8:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Loose_change.mp3");
		break;
	case 9:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Rolling_fog.mp3");
		break;
	case 10:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Spokes.mp3");
		break;
	case 11:
		strcpy(buffmp3, "C:\\Users\\Miini\\Documents\\FCFM\\2do Semestre\\Programacion 3ra Op\\MiniMarket\\MiniMarket\\Alarmas\\Sunshower.mp3");
		break;
	}
}

void checarTiempo(HWND DateIni, HWND DateFin, HWND TimeIni, HWND TimeFin, HWND StAviso)
{
	errorTiempo = false;
	char fechaIni[15];
	char fechaFin[15];
	char horaIni[15];
	char horaFin[15];

	GetWindowText(TimeIni, horaIni, sizeof(horaIni));
	GetWindowText(DateIni, fechaIni, sizeof(fechaIni));
	string sfechaIni(fechaIni);
	string diaIni = sfechaIni.substr(0, 2);
	string mesIni = sfechaIni.substr(3, 2);
	string anioIni = sfechaIni.substr(6, 4);

	GetWindowText(TimeFin, horaFin, sizeof(horaFin));
	GetWindowText(DateFin, fechaFin, sizeof(fechaFin));
	string sfechaFin(fechaFin);
	string diaFin = sfechaFin.substr(0, 2);
	string mesFin = sfechaFin.substr(3, 2);
	string anioFin = sfechaFin.substr(6, 4);

	if (anioFin < anioIni)
	{
		errorTiempo = true;
		SetWindowText(StAviso, "La fecha inicial no debe pasar de la fecha final");
	}
	else if (anioFin == anioIni)
	{
		if (mesFin < mesIni)
		{
			errorTiempo = true;
			SetWindowText(StAviso, "La fecha inicial no debe pasar de la fecha final");
		}
		else if (mesFin == mesIni)
		{
			if (diaFin < diaIni)
			{
				errorTiempo = true;
				SetWindowText(StAviso, "La fecha inicial no debe pasar de la fecha final");
			}
			else if (diaFin == diaIni)
			{
				if (strncmp(horaFin, horaIni, MAX_PATH) < 0)
				{
					errorTiempo = true;
					SetWindowText(StAviso, "La fecha inicial no debe pasar de la fecha final");
				}
			}
		}
	}

	if (errorTiempo == false)
	{
		SetWindowText(StAviso, "");
	}
}

void llenarCuadro(HWND hWnd, int Picture, HWND Nombre, HWND Precio)
{
	static HBITMAP bmp;
	char buff[30];

	bmp = (HBITMAP)LoadImage(NULL, auxP->foto1, IMAGE_BITMAP, 250, 250, LR_LOADFROMFILE);
	SendDlgItemMessage(hWnd, Picture, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);

	SetWindowText(Nombre, auxP->nombre);
	
	sprintf(buff, "$%.2f", auxP->precioFinal);
	SetWindowText(Precio, buff);

	auxP = inicioP;
}

int MsgEliminarProducto(HWND hWnd)
{
	int msgboxID = MessageBox(hWnd, "�Desea eliminar el producto permanentemente?", "Elminar producto", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

	switch (msgboxID)
	{
	case IDYES:
	{
		if (auxP->conPromocion == true)
		{
			auxPro = inicioPro;
			while (auxPro != NULL)
			{
				if (auxPro->idProducto == auxP->id)
					break;
				auxPro = auxPro->sig;
			}

			//Eliminar promocion
			if (auxPro->sig == NULL &&auxPro->ant == NULL)
			{
				delete auxPro;
				inicioPro = auxPro = NULL;
			}
			else if (auxPro->sig == NULL)
			{
				promocion *auxPro2;
				auxPro2 = auxPro;
				auxPro = auxPro->ant;
				auxPro->sig = NULL;
				delete auxPro2;
				auxPro = inicioPro;
			}
			else if (auxPro->ant == NULL)
			{
				promocion *auxPro2;
				auxPro2 = auxPro;
				auxPro = auxPro->sig;
				auxPro->ant = NULL;
				delete auxPro2;
				inicioPro = auxPro;
			}
			else
			{
				promocion *auxPro2;
				auxPro2 = auxPro;
				auxPro->sig->ant = auxPro->ant;
				auxPro->ant->sig = auxPro->sig;
				auxPro = inicioPro;
				delete auxPro2;
			}
		}
#pragma region EliminarProducto
		if (auxP->sig == NULL && auxP->ant == NULL) // Es el unico
		{
			delete auxP;
			inicioP = auxP = NULL;
		}
		else if (auxP->sig == NULL) //Es el ultimo
		{
			producto *aux2;
			aux2 = auxP;
			auxP = auxP->ant;
			auxP->sig = NULL;
			delete aux2;
			auxP = inicioP;
		}
		else if (auxP->ant == NULL) //Es el primero
		{
			producto *aux2;
			aux2 = auxP;
			auxP = auxP->sig;
			auxP->ant = NULL;
			delete aux2;
			inicioP = auxP;
		}
		else //Esta en medio
		{
			producto *aux2;
			aux2 = auxP;
			auxP->sig->ant = auxP->ant;
			auxP->ant->sig = auxP->sig;
			auxP = inicioP;
			delete aux2;
		}
#pragma endregion

		MessageBox(hWnd, "Producto eliminado", "Eliminar producto", MB_OK);
		EndDialog(hWnd, 0);
		DialogBox(Instancia, MAKEINTRESOURCE(IDD_MIS_PRODUCTOS), hInicio, MisProductos);
		break;
	}

	case IDNO:
		break;
	}

	return msgboxID;
}

int MsgEliminarCuenta(HWND hWnd)
{
	int msgboxID = MessageBox(hWnd, "Eliminar su cuenta significaria la eliminacion de sus datos tambien, �Desea eliminar su cuenta?", "Eliminar cuenta", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2);

	switch (msgboxID)
	{
	case IDYES:
	{
		//Eliminar Productos
		if (inicioP != NULL)
		{
			auxP = inicioP;
			while (auxP != NULL)
			{
				if (auxP->idUsuario == usuarioLog.id)
				{
					if (auxP->sig == NULL && auxP->ant == NULL) {
						delete auxP;
						inicioP = auxP = NULL;
						break;
					}
					else if (auxP->sig == NULL)
					{
						producto *aux2P;
						aux2P = auxP;
						auxP = auxP->ant;
						auxP->sig = NULL;
						delete aux2P;
						auxP = inicioP;
						continue;
					}
					else if (auxP->ant == NULL) {
						producto *aux2P;
						aux2P = auxP;
						auxP = auxP->sig;
						auxP->ant = NULL;
						delete aux2P;
						inicioP = auxP;
						continue;
					}
					else
					{
						producto *aux2P;
						aux2P = auxP;
						auxP->sig->ant = auxP->ant;
						auxP->ant->sig = auxP->sig;
						auxP = inicioP;
						delete aux2P;
						continue;
					}
				}
				auxP = auxP->sig;
			}
		}

		//Eliminar Carrito
		auxCar = inicioCar;
		while (auxCar != NULL)
		{
			if (auxCar->idUsuario == usuarioLog.id)
				break;
			auxCar = auxCar->sig;
		}

		if (auxCar->sig == NULL && auxCar->ant == NULL) {
			delete auxCar;
			inicioCar = auxCar = NULL;
		}
		else if (auxCar->sig == NULL)
		{
			carro *aux2Car;
			aux2Car = auxCar;
			auxCar = auxCar->ant;
			auxCar->sig = NULL;
			delete aux2Car;
			auxCar = inicioCar;
		}
		else if (auxCar->ant == NULL) {
			carro *aux2Car;
			aux2Car = auxCar;
			auxCar = auxCar->sig;
			auxCar->ant = NULL;
			delete aux2Car;
			inicioCar = auxCar;
		}
		else
		{
			carro *aux2Car;
			aux2Car = auxCar;
			auxCar->sig->ant = auxCar->ant;
			auxCar->ant->sig = auxCar->sig;
			auxCar = inicioCar;
			delete aux2Car;
		}

		//Eliminar Usuario
		auxU = inicioU;
		while (auxU != NULL) //Buscar usuario
		{
			if (auxU->id == usuarioLog.id)
				break;
			auxU = auxU->sig;
		}

		if (auxU->sig == NULL && auxU->ant == NULL) { //En caso de que solo sea uno
			delete auxU;
			inicioU = auxU = NULL;
		}
		else if (auxU->sig == NULL) //En caso de que este al final de la lista
		{
			usuario *aux2U;
			aux2U = auxU;
			auxU = auxU->ant;
			auxU->sig = NULL;
			delete aux2U;
			auxU = inicioU;
		}
		else if (auxU->ant == NULL) { //En caso de que sea el primero
			usuario *aux2U;
			aux2U = auxU;
			auxU = auxU->sig;
			auxU->ant = NULL;
			delete aux2U;
			inicioU = auxU;
		}
		else //Esta en medio de la lista
		{
			usuario *aux2U;
			aux2U = auxU;
			auxU->sig->ant = auxU->ant;
			auxU->ant->sig = auxU->sig;
			auxU = inicioU;
			delete aux2U;
		}

		MessageBox(hWnd, "La cuenta y sus productos han sido eliminados", "Eliminar cuenta", MB_OK);
		EndDialog(hWnd, 0);
		break;
	}

	case IDNO:
		break;
	}

	return msgboxID;
}

void alarmaIni(HWND hWnd)
{
	char dia[10];
	char mes[10];
	char anio[10];

	char fecha[15];
	char hora[15];

	//FECHA
	int i = 0;
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(dia, sizeof(dia), "%d", timeinfo);
	strftime(mes, sizeof(mes), "%m", timeinfo);
	strftime(anio, sizeof(anio), "%Y", timeinfo);
	strftime(fecha, sizeof(fecha), "%d/%m/%Y", timeinfo);
	strftime(hora, sizeof(hora), "%T", timeinfo);

	int diaa = atoi(dia);
	int mesa = atoi(mes);
	int anioa = atoi(anio);

	auxProA = inicioPro;
	if (inicioPro != NULL)
	{
		while (auxProA != NULL)
		{
			if (strncmp(auxProA->fechaIni, fecha, MAX_PATH) == 0)
			{
				if (strncmp(auxProA->horaIni, hora, MAX_PATH) == 0)
				{
					if (auxProA->iniAlarma == false)
					{
						auxProA->iniAlarma = true;
						DialogBox(Instancia, MAKEINTRESOURCE(IDD_ALARMA), hInicio, Alarma);
						break;
					}
				}
			}

			int anio2, mes2, dia2;
			anio2 = stoi(auxProA->anioIni);
			mes2 = stoi(auxProA->mesIni);
			dia2 = stoi(auxProA->diaIni);

			if (anio2 < anioa || anio2 == anioa)
			{
				if (mes2 < mesa || mes2 == mesa)
				{
					if (dia2 < diaa || dia2 == diaa)
					{
						if (strncmp(auxProA->horaIni, hora, MAX_PATH) < 0)
						{
							if (auxProA->iniAlarma == false)
							{
								auxProA->iniAlarma = true;
								//KillTimer(window, TimmerID1);
								DialogBox(Instancia, MAKEINTRESOURCE(IDD_ALARMA), hInicio, Alarma);
								break;
							}
						}
					}
				}
			}
			auxProA = auxProA->sig;
		}
	}
	auxProA = NULL;
}

void alarmaFin(HWND hWnd)
{
	char dia[10];
	char mes[10];
	char anio[10];

	char fecha[15];
	char hora[15];

	//FECHA
	int i = 0;
	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(dia, sizeof(dia), "%d", timeinfo);
	strftime(mes, sizeof(mes), "%m", timeinfo);
	strftime(anio, sizeof(anio), "%Y", timeinfo);
	strftime(fecha, sizeof(fecha), "%d/%m/%Y", timeinfo);
	strftime(hora, sizeof(hora), "%T", timeinfo);

	int diaa = atoi(dia);
	int mesa = atoi(mes);
	int anioa = atoi(anio);
	
	auxProA = inicioPro;
	if (inicioPro != NULL)
	{
		while (auxProA != NULL)
		{
			if (strncmp(auxProA->fechaFin, fecha, MAX_PATH) == 0)
			{
				if (strncmp(auxProA->horaFin, hora, MAX_PATH) == 0)
				{
					if (auxProA->finAlarma == false)
					{
						auxProA->finAlarma = true;
						DialogBox(Instancia, MAKEINTRESOURCE(IDD_ALARMA), hInicio, Alarma);
						break;
					}
				}
			}

			int anio2, mes2, dia2;
			anio2 = stoi(auxProA->anioFin);
			mes2 = stoi(auxProA->mesFin);
			dia2 = stoi(auxProA->diaFin);

			if (anio2 < anioa || anio2 == anioa)
			{
				if (mes2 < mesa || mes2 == mesa)
				{
					if (dia2 < diaa || dia2 == diaa)
					{
						if (strncmp(auxProA->horaFin, hora, MAX_PATH) < 0)
						{
							if (auxProA->finAlarma == false)
							{
								auxProA->finAlarma = true;
								DialogBox(Instancia, MAKEINTRESOURCE(IDD_ALARMA), hInicio, Alarma);
								break;
							}
						}
					}
				}
			}
			auxProA = auxProA->sig;
		}
	}
	auxProA = NULL;
}