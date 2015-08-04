#ifndef _BERRETACODE_TEMPLATE		//ESTO EVITA QUE SE INCLUYA EL MISMO HEADER VARIAS VECES 

#define _BERRETACODE_TEMPLATE

#include "stdafx.h"
#include <stdlib.h> //PARA CALLOC, REALLOC Y FREE
#include <iostream>
#ifndef NULL
#define NULL ((void *)0)
#endif

template <class T>
class BerretaClass
{
private:
T* memPtr; //aca estara almacenado tu arreglo
int count; //cantidad de elementos

public:

BerretaClass(); //constructor por defecto

virtual ~BerretaClass(); // destructor

BerretaClass(const BerretaClass& value); //constructor copia

bool Agregar(T objeto); //aca deberias determinar si queres usar calloc/free o new[] delete[] (yo uso calloc/free)
bool RemoveAt (int index); //eliminamos (si existe) el elemento en el indice index del array
bool Limpiar(void); //eliminamos todos los elementos
bool ElementAt (int index, T& retVal); //devolvemos el elemento en index (si existe claro esta)
T ElementAt (int index); //tambien devolvemos el elemento en index, creo que ambas sobrecargas se explican solas

//redefinimos el operador de asignacion
BerretaClass &operator= (const BerretaClass &val);

int Cantidad(void); //devuelve la cantidad actual de elementos
};

template <class T>
BerretaClass<T>& BerretaClass<T>::operator=(const BerretaClass<T> &val)
{
	for (int i = 0; i < val.count-1; i++)
		this->Agregar(*(val.memPtr+i));

	return *(this)
}

template <class T>
BerretaClass<T>::BerretaClass(const BerretaClass& value)
{
	this->count = 0;
	this->memPtr = NULL;

	for (int i = 0; i <= value.count-1; i++)
		this->Agregar(*(value.memPtr+i));
}

template <class T>
BerretaClass<T>::BerretaClass()
{
	this->memPtr = NULL;
	this->count = 0;
}

template <class T>
BerretaClass<T>::~BerretaClass()
{
	if (this->memPtr != NULL) 
		free ( (void *) this->memPtr);
	this->memPtr = NULL;
}

template <class T>
bool BerretaClass<T>::Agregar(T objeto)
{
	if (this->memPtr == NULL) 
	{
		//PRIMER OBJETO
		this->memPtr = (T*) calloc(1, sizeof(T));
		if (this->memPtr == NULL) //no hay suf memoria
			return false;

		*(this->memPtr) = objeto;
	}
	else
	{
		//HAY QUE HACER REALLOC
		//PUNTERO TEMPORAL
		T* tempPointer = NULL;
		tempPointer = this->memPtr;

		this->memPtr = (T*) realloc ((void *) this->memPtr, (this->count+1) * sizeof(T));

		if (this->memPtr == NULL)
		{
			//FALLO EL REDIM PERO EL CONTENIDO SIGUE SIN MODIFICACION ;)
			this->memPtr = tempPointer;
			return false;
		}

		//agregamos el objeto al final del array
		*(this->memPtr+this->count) = objeto;
	}
	//SI LLEGAMOS HASTA ACA, TODO FUE OK
	//incrementamos la variable de cantidad (ya que se agrego un nuevo elemento)
	this->count++;
	return true;
}

template <class T>
bool BerretaClass<T>::RemoveAt (int index)
{
	if ( this->memPtr == NULL ) //no hay elementos
		return false;

	if (index < 0 || index >= this->count) //fuera de los limites
		return false;

	//arreglo que contendra los valores del arreglo principal restando el que deseamos eliminar
	T* newPointer = NULL;

	newPointer = (T *) calloc (this->count - 1, sizeof(T));

	if (newPointer == NULL) //NO SE PUDO RESERVAR MEMORIA AUXILIAR
		return false;

	int j = 0;

	for (int i = 0; i < this->count; i++)
	{
		if ( i != index )
		{
			*(newPointer+j) = *(this->memPtr+i);
			j++;
		}
	}

	//ya tenemos en el segundo arreglo los valores correctos, basicamente haremos un swap
	//liberamos la ram utilizada por el primer arreglo y lo hacemos apuntar a la direccion del segundo
	free ( (void *) this->memPtr);
	this->memPtr = newPointer;

	//si llegamos hasta aca, todo esta ok
	//decrementamos la variable de cantidad total, ya que se elimino un elemento
	this->count--;
	return true;
}

template <class T>
bool BerretaClass<T>::Limpiar(void)
{
	if (this->memPtr == NULL)
	{
		//NO HAY ELEMENTOS PARA LIMPIAR
		return false;
	}

	free ( (void *) this->memPtr);
	this->memPtr = NULL;

	this->count = 0;
	return true;
}

template <class T>
bool BerretaClass<T>::ElementAt (int index, T& retVal)
{
	if ( this->memPtr == NULL ) //no hay elementos
		return false;

	if ( index < 1 || index > this->count ) //fuera de los limites
		return false;

	//traemos el elemento deseado
	retVal = *(this->memPtr+index-1);
	return true;
}

template <class T>
T BerretaClass<T>::ElementAt(int index)
{
	
	if ( this->memPtr == NULL ) //no hay elementos, se puede controlar la excepcion en el objeto que implementa la clase
		throw;

	if ( index < 1 || index > this->count ) //fuera de los limites, se puede controlar la excepcion en el objeto que implementa la clase
		throw;

	//traemos el elemento deseado
	T ret =  *(this->memPtr+index-1);
	return ret;
}

template <class T>
int BerretaClass<T>::Cantidad(void)
{
	return (this->count);
}

#endif