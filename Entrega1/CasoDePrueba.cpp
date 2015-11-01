#include "CasoDePrueba.h"

CasoDePrueba::CasoDePrueba(Puntero<ISistema>(*inicializar)())
{
	this->inicializar = inicializar;
}

Puntero<ISistema> CasoDePrueba::InicializarSistema()
{
	Puntero<ISistema> interfaz = inicializar();
	ignorarOK = false;
	return interfaz;
}

Cadena CasoDePrueba::GetNombre()const
{
	return "Casos de Prueba";
}

void CasoDePrueba::CorrerPruebaConcreta()
{
	PruebaOperacion1();
	PruebaOperacion2();
	PruebaOperacion3();
}

void CasoDePrueba::Verificar(TipoRetorno obtenido, TipoRetorno esperado, Cadena comentario)
{
	if (!ignorarOK || obtenido != esperado)
		Prueba::Verificar(obtenido, esperado, comentario);
}

template <class T>
void CasoDePrueba::Verificar(const T& obtenido, const T& esperado, Cadena comentario)
{
	Verificar(SonIguales(obtenido, esperado) ? OK : ERROR, OK, comentario.DarFormato(ObtenerTexto(obtenido), ObtenerTexto(esperado)));
}

template <class T>
void CasoDePrueba::VerificarConjuntos(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra)
{
	bool verificarCantidad = true;
	nat totalObtenidos = 0;
	T aux;
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	foreach(T obtenido, obtenidos)
	{
		totalObtenidos++;
		if (Pertenece(obtenido, esperados, aux))
			Verificar(OK, OK, comentarioEncontrado.DarFormato(ObtenerTexto(obtenido), ObtenerTexto(obtenido)));
		else
		{
			Verificar(ERROR, OK, comentarioSobra.DarFormato(ObtenerTexto(obtenido)));
			verificarCantidad = false;
		}
	}
	nat totalEsperados = 0;
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	foreach(T esperado, esperados)
	{
		totalEsperados++;
		if (!Pertenece(esperado, obtenidos, aux))
		{
			Verificar(ERROR, OK, comentarioFalta.DarFormato(ObtenerTexto(esperado)));
			verificarCantidad = false;
		}
	}
	if (verificarCantidad && totalObtenidos != totalEsperados)
		Verificar(ERROR, OK, "Se verifica la cantidad de elementos de los conjuntos");
}

template <class T>
void CasoDePrueba::VerificarSecuencias(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra)
{
	esperados.Reiniciar();

	foreach(T obtenido, obtenidos)
	{
		if (esperados.HayElemento())
		{
			T esperado = *esperados;
			++esperados;
			Verificar(obtenido, esperado, comentarioEncontrado);
		}
		else
			Verificar(ERROR, OK, comentarioSobra.DarFormato(ObtenerTexto(obtenido)));
	}

	while (esperados.HayElemento())
	{
		T esperado = *esperados;
		++esperados;
		Verificar(ERROR, OK, comentarioFalta.DarFormato(ObtenerTexto(esperado)));
	}
}

Matriz<bool> CasoDePrueba::CrearMatrizDePrecedencias(Iterador<Tupla<Cadena, Cadena> > relacionesEntreVertices, Iterador<Cadena> verticesQueParticipan)
{
	int cantidadDeVertices = ObtenerLargoIterador(verticesQueParticipan);
	Matriz<bool> matrizDePrecedencias = Matriz<bool>(cantidadDeVertices);
	InicializarMatriz(matrizDePrecedencias, cantidadDeVertices);
	verticesQueParticipan.Reiniciar();
	relacionesEntreVertices.Reiniciar();

	while (relacionesEntreVertices.HayElemento())
	{
		Cadena nombreVerticeI = relacionesEntreVertices.ElementoActual().Dato1;
		int numInternoVerticeI = ObtenerNumeroInternoVertice(nombreVerticeI, verticesQueParticipan);
		Cadena nombreVerticeJ = relacionesEntreVertices.ElementoActual().Dato2;
		int numInternoVerticeJ = ObtenerNumeroInternoVertice(nombreVerticeJ, verticesQueParticipan);
		matrizDePrecedencias[numInternoVerticeI][numInternoVerticeJ] = true;
		relacionesEntreVertices.Avanzar();
	}

	return matrizDePrecedencias;
}

void CasoDePrueba::InicializarMatriz(Matriz<bool> matrizAInicializar, int largo)
{
	for (int i = 0; i < largo; i++)
		for (int j = 0; j < largo; j++)
			matrizAInicializar[i][j] = false;
}

template <class T>
int CasoDePrueba::ObtenerLargoIterador(Iterador<T> iteradorFuente)
{
	iteradorFuente.Reiniciar();
	int cantidadDeElementos = 0;
	while (iteradorFuente.HayElemento())
	{
		cantidadDeElementos++;
		iteradorFuente.Avanzar();
	}
	iteradorFuente.Reiniciar();
	return cantidadDeElementos;
}

int CasoDePrueba::ObtenerNumeroInternoVertice(Cadena verticeABuscar, Iterador<Cadena> iteradorDeVertices)
{
	int numeroPosicion = 0;
	bool encontre = false;
	iteradorDeVertices.Reiniciar();
	while (iteradorDeVertices.HayElemento() && !encontre)
	{
		Cadena verticeEncontrado = iteradorDeVertices.ElementoActual();
		if (verticeEncontrado == verticeABuscar)
		{
			encontre = true;
		}
		else
		{
			numeroPosicion++;
			iteradorDeVertices.Avanzar();
		}
	}
	return numeroPosicion;
}

void CasoDePrueba::VerificarOrden(Tupla<TipoRetorno, Iterador<Cadena>> obtenido, TipoRetorno tipoRetEsperado, Matriz<bool> resultadoEsperado, Iterador<Cadena> temas, Cadena comentario)
{
	TipoRetorno tipoRetObtenido = obtenido.Dato1;
	Iterador<Cadena> iteradorObtenido = obtenido.Dato2;
	if (tipoRetObtenido == OK && tipoRetEsperado == OK)
	{
		IniciarSeccion(comentario, tipoRetEsperado);
		VerificarSiEstaDentroDeLasSolucionesPosibles(resultadoEsperado, iteradorObtenido, comentario, temas);
		CerrarSeccion();
	}
	else
		Verificar(tipoRetObtenido, tipoRetEsperado, comentario);
}

void CasoDePrueba::VerificarSiEstaDentroDeLasSolucionesPosibles(Matriz<bool> esperados, Iterador<Cadena> obtenido, Cadena comentario, Iterador<Cadena> temas)
{
	if (ObtenerLargoIterador(obtenido) < ObtenerLargoIterador(temas))
	{
		Verificar(ERROR, OK, comentario);
		return;
	}
	obtenido.Reiniciar();
	Iterador<Cadena> copiaObtenido = obtenido.Clonar();
	copiaObtenido.Reiniciar();
	while (obtenido.HayElemento())
	{
		Cadena elementoJ = obtenido.ElementoActual();
		copiaObtenido.Reiniciar();
		while (copiaObtenido.HayElemento() && copiaObtenido.ElementoActual() != elementoJ)
		{
			Cadena elementoI = copiaObtenido.ElementoActual();
			if (ExistePrecedencia(elementoJ, elementoI, esperados, temas))
			{
				Verificar(ERROR, OK, comentario);
				return;
			}
			copiaObtenido.Avanzar();
		}
		obtenido.Avanzar();
	}
	Verificar(OK, OK, comentario);
}

bool CasoDePrueba::ExistePrecedencia(Cadena elementoI, Cadena elementoJ, Matriz<bool> matrizAVerificar, Iterador<Cadena> temas)
{
	temas.Reiniciar();
	int posI = ObtenerNumeroInternoVertice(elementoI, temas);
	int posJ = ObtenerNumeroInternoVertice(elementoJ, temas);
	return matrizAVerificar[posI][posJ];
}

void CasoDePrueba::VerificarConjuntoAristasNoDirigidas(TipoRetorno retObtenido, TipoRetorno retEsperado, Iterador<Tupla<nat, nat>> arbolObtenido, Iterador<Tupla<nat, nat>> arbolEsperado, Cadena comentario)
{
	if (retEsperado == OK && retObtenido == OK)
	{
		IniciarSeccion(comentario, retEsperado);
		arbolEsperado.Reiniciar();
		arbolObtenido.Reiniciar();
		VerificarConjuntos(arbolObtenido, arbolEsperado, "Se obtuvo {0} y se esperaba {1}", "Se esperaba {0}", "No se esperaba {0}");
		CerrarSeccion();
	}
	else
		Verificar(retObtenido, retEsperado, comentario);
}

void CasoDePrueba::InicializarMatrizEnCero(Matriz<nat> matrizAInicializar)
{
	int largo = matrizAInicializar.Largo;
	for (int i = 0; i < largo; i++)
		for (int j = 0; j < largo; j++)
			matrizAInicializar[i][j] = 0;
}

template <class T>
bool CasoDePrueba::SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const
{
	obtenidos.Reiniciar();
	esperados.Reiniciar();
	while (obtenidos.HayElemento() && esperados.HayElemento())
	{
		if (!SonIguales(*obtenidos, *esperados))
			return false;
		++obtenidos;
		++esperados;
	}

	return esperados.HayElemento() == obtenidos.HayElemento();
}

template <class T>
Cadena CasoDePrueba::ObtenerTexto(Iterador<T> it) const
{
	Cadena sepVacio = "";
	Cadena sepGuion = "-";
	Cadena sep = sepVacio;
	Cadena retorno = sepVacio;
	foreach(auto t, it)
	{
		retorno += sep + ObtenerTexto(t);
		sep = sepGuion;
	}
	return retorno;
}

Cadena CasoDePrueba::ObtenerTexto(const Tupla<nat, nat>& t) const
{
	Cadena ret = " {0} - {1} ";
	return ret.DarFormato(ObtenerTexto(t.Dato1), ObtenerTexto(t.Dato2));
}

Cadena CasoDePrueba::ObtenerTexto(nat n) const
{
	switch (n)
	{
	case 0:
		return "0";
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	default:
		Cadena ret = "";
		while (n != 0)
		{
			ret = ObtenerTexto(n % 10) + ret;
			n /= 10;
		}
		return ret;
	}
}

bool CasoDePrueba::SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const
{
	return (obtenido.Dato1 == esperado.Dato1 && obtenido.Dato2 == esperado.Dato2) ||
		(obtenido.Dato2 == esperado.Dato1 && obtenido.Dato1 == esperado.Dato2);
}

template <class T>
bool CasoDePrueba::Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const
{
	iterador.Reiniciar();
	foreach(T dato2, iterador)
	{
		if (SonIguales(dato, dato2))
		{
			encontrado = dato2;
			return true;
		}
	}
	return false;
}

//Operacion 1:
void CasoDePrueba::PruebaOperacion1()
{
	IniciarSeccion("Operacion 1");
	Puntero<ISistema> interfaz = InicializarSistema();
	PruebaOperacion1A(interfaz);
	PruebaOperacion1B(interfaz);
	PruebaOperacion1C(interfaz);
	PruebaOperacion1D(interfaz);
	CerrarSeccion();
}

void CasoDePrueba::PruebaOperacion1A(Puntero<ISistema> interfazDelSistema)
{
	Array<nat> computadoras = Array<nat>(8);
	computadoras[0] = 1;
	computadoras[1] = 2;
	computadoras[2] = 3;
	computadoras[3] = 4;
	computadoras[4] = 5;
	computadoras[5] = 6;
	computadoras[6] = 7;
	computadoras[7] = 8;

	Array<Tupla<nat, nat>> cables = Array<Tupla<nat, nat>>(10);
	cables[0] = Tupla<nat, nat>(1, 2);
	cables[1] = Tupla<nat, nat>(1, 3);
	cables[2] = Tupla<nat, nat>(2, 3);
	cables[3] = Tupla<nat, nat>(2, 4);
	cables[4] = Tupla<nat, nat>(3, 4);
	cables[5] = Tupla<nat, nat>(4, 5);
	cables[6] = Tupla<nat, nat>(5, 6);
	cables[7] = Tupla<nat, nat>(5, 7);
	cables[8] = Tupla<nat, nat>(6, 7);
	cables[9] = Tupla<nat, nat>(6, 8);

	Array<Tupla<nat, nat>> cablesCriticos = Array<Tupla<nat, nat>>(2);
	cablesCriticos[0] = Tupla<nat, nat>(4, 5);
	cablesCriticos[1] = Tupla<nat, nat>(6, 8);

	Iterador<nat> iteradorComp = computadoras.ObtenerIterador();
	Iterador<Tupla<nat, nat>> iteradorCables = cables.ObtenerIterador();
	Iterador<Tupla<nat, nat>> esperado = cablesCriticos.ObtenerIterador();
	TipoRetorno retEsperado = OK;

	Tupla<TipoRetorno, Iterador<Tupla<nat, nat> > > resultadoObtenido = interfazDelSistema->EnlacesCriticos(iteradorComp, iteradorCables);
	TipoRetorno retObtenido = resultadoObtenido.Dato1;
	Iterador<Tupla<nat, nat> > obtenido = resultadoObtenido.Dato2;
	VerificarConjuntoAristasNoDirigidas(retEsperado, retObtenido, esperado, obtenido, "Se prueba la Operación 1");
}

void CasoDePrueba::PruebaOperacion1B(Puntero<ISistema> interfazDelSistema)
{
	Array<nat> computadoras = Array<nat>(4);
	computadoras[0] = 1;
	computadoras[1] = 2;
	computadoras[2] = 3;
	computadoras[3] = 4;

	Array<Tupla<nat, nat>> cables = Array<Tupla<nat, nat>>(3);
	cables[0] = Tupla<nat, nat>(1, 2);
	cables[1] = Tupla<nat, nat>(2, 3);
	cables[2] = Tupla<nat, nat>(3, 4);

	Array<Tupla<nat, nat>> cablesCriticos = Array<Tupla<nat, nat>>(3);
	cablesCriticos[0] = Tupla<nat, nat>(1, 2);
	cablesCriticos[1] = Tupla<nat, nat>(2, 3);
	cablesCriticos[2] = Tupla<nat, nat>(3, 4);

	Iterador<nat> iteradorComp = computadoras.ObtenerIterador();
	Iterador<Tupla<nat, nat>> iteradorCables = cables.ObtenerIterador();
	Iterador<Tupla<nat, nat>> esperado = cablesCriticos.ObtenerIterador();
	TipoRetorno retEsperado = OK;

	Tupla<TipoRetorno, Iterador<Tupla<nat, nat> > > resultadoObtenido = interfazDelSistema->EnlacesCriticos(iteradorComp, iteradorCables);
	TipoRetorno retObtenido = resultadoObtenido.Dato1;
	Iterador<Tupla<nat, nat> > obtenido = resultadoObtenido.Dato2;
	VerificarConjuntoAristasNoDirigidas(retEsperado, retObtenido, esperado, obtenido, "Se prueba la Operación 1");
}

void CasoDePrueba::PruebaOperacion1C(Puntero<ISistema> interfazDelSistema)
{
	Array<nat> computadoras = Array<nat>(6);
	computadoras[0] = 1;
	computadoras[1] = 2;
	computadoras[2] = 3;
	computadoras[3] = 4;
	computadoras[4] = 5;
	computadoras[5] = 6;

	Array<Tupla<nat, nat>> cables = Array<Tupla<nat, nat>>(5);
	cables[0] = Tupla<nat, nat>(1, 2);
	cables[1] = Tupla<nat, nat>(2, 3);
	cables[2] = Tupla<nat, nat>(3, 4);
	cables[3] = Tupla<nat, nat>(2, 5);
	cables[4] = Tupla<nat, nat>(2, 6);

	Array<Tupla<nat, nat>> cablesCriticos = Array<Tupla<nat, nat>>(5);
	cablesCriticos[0] = Tupla<nat, nat>(1, 2);
	cablesCriticos[1] = Tupla<nat, nat>(2, 3);
	cablesCriticos[2] = Tupla<nat, nat>(3, 4);
	cablesCriticos[3] = Tupla<nat, nat>(2, 5);
	cablesCriticos[4] = Tupla<nat, nat>(2, 6);

	Iterador<nat> iteradorComp = computadoras.ObtenerIterador();
	Iterador<Tupla<nat, nat>> iteradorCables = cables.ObtenerIterador();
	Iterador<Tupla<nat, nat>> esperado = cablesCriticos.ObtenerIterador();
	TipoRetorno retEsperado = OK;

	Tupla<TipoRetorno, Iterador<Tupla<nat, nat> > > resultadoObtenido = interfazDelSistema->EnlacesCriticos(iteradorComp, iteradorCables);
	TipoRetorno retObtenido = resultadoObtenido.Dato1;
	Iterador<Tupla<nat, nat> > obtenido = resultadoObtenido.Dato2;
	VerificarConjuntoAristasNoDirigidas(retEsperado, retObtenido, esperado, obtenido, "Se prueba la Operación 1");
}

void CasoDePrueba::PruebaOperacion1D(Puntero<ISistema> interfazDelSistema)
{
	Array<nat> computadoras = Array<nat>(5);
	computadoras[0] = 1;
	computadoras[1] = 2;
	computadoras[2] = 3;
	computadoras[3] = 4;
	computadoras[4] = 5;

	Array<Tupla<nat, nat>> cables = Array<Tupla<nat, nat>>(5);
	cables[0] = Tupla<nat, nat>(1, 2);
	cables[1] = Tupla<nat, nat>(2, 3);
	cables[2] = Tupla<nat, nat>(2, 4);
	cables[3] = Tupla<nat, nat>(2, 5);
	cables[4] = Tupla<nat, nat>(1, 5);

	Array<Tupla<nat, nat>> cablesCriticos = Array<Tupla<nat, nat>>(2);
	cablesCriticos[0] = Tupla<nat, nat>(2, 4);
	cablesCriticos[1] = Tupla<nat, nat>(2, 3);

	Iterador<nat> iteradorComp = computadoras.ObtenerIterador();
	Iterador<Tupla<nat, nat>> iteradorCables = cables.ObtenerIterador();
	Iterador<Tupla<nat, nat>> esperado = cablesCriticos.ObtenerIterador();
	TipoRetorno retEsperado = OK;

	Tupla<TipoRetorno, Iterador<Tupla<nat, nat> > > resultadoObtenido = interfazDelSistema->EnlacesCriticos(iteradorComp, iteradorCables);
	TipoRetorno retObtenido = resultadoObtenido.Dato1;
	Iterador<Tupla<nat, nat> > obtenido = resultadoObtenido.Dato2;
	VerificarConjuntoAristasNoDirigidas(retEsperado, retObtenido, esperado, obtenido, "Se prueba la Operación 1");
}

//Operacion 2:
void CasoDePrueba::PruebaOperacion2()
{
	IniciarSeccion("Operacion 2");
	Puntero<ISistema> interfaz = InicializarSistema();
	PruebaOperacion2A(interfaz);
	PruebaOperacion2B(interfaz);
	CerrarSeccion();
}

void CasoDePrueba::PruebaOperacion2A(Puntero<ISistema> interfazDelSistema)
{
	Matriz<nat> matrizDelGrafo = Matriz<nat>(6);
	InicializarMatrizEnCero(matrizDelGrafo);
	matrizDelGrafo[1][0] = 6;
	matrizDelGrafo[0][2] = 1;
	matrizDelGrafo[2][1] = 5;
	matrizDelGrafo[0][3] = 5;
	matrizDelGrafo[3][2] = 5;
	matrizDelGrafo[2][4] = 6;
	matrizDelGrafo[1][4] = 3;
	matrizDelGrafo[4][5] = 6;
	matrizDelGrafo[2][5] = 4;
	matrizDelGrafo[5][3] = 2;

	Array<Tupla<nat, nat>> cablesNecesarios = Array<Tupla<nat, nat>>(5);
	cablesNecesarios[0] = Tupla<nat, nat>(0, 2);
	cablesNecesarios[1] = Tupla<nat, nat>(2, 1);
	cablesNecesarios[2] = Tupla<nat, nat>(1, 4);
	cablesNecesarios[3] = Tupla<nat, nat>(2, 5);
	cablesNecesarios[4] = Tupla<nat, nat>(5, 3);
	Iterador<Tupla<nat, nat>> iteradorCablesNecesarios = cablesNecesarios.ObtenerIterador();
	TipoRetorno retEsperado = OK;

	Tupla<TipoRetorno, Iterador<Tupla<nat, nat> > > resultadoObtenido = interfazDelSistema->AhorroEnlaces(matrizDelGrafo);
	TipoRetorno retObtenido = resultadoObtenido.Dato1;
	Iterador<Tupla<nat, nat> > iteradorCablesNecesariosOb = resultadoObtenido.Dato2;

	VerificarConjuntoAristasNoDirigidas(retEsperado, retObtenido, iteradorCablesNecesarios, iteradorCablesNecesariosOb, "Se prueba la Operación 2");
}

void CasoDePrueba::PruebaOperacion2B(Puntero<ISistema> interfazDelSistema)
{
	Matriz<nat> matrizDelGrafo = Matriz<nat>(9);
	InicializarMatrizEnCero(matrizDelGrafo);
	matrizDelGrafo[1][0] = 4;
	matrizDelGrafo[0][7] = 8;
	matrizDelGrafo[7][1] = 11;
	matrizDelGrafo[1][2] = 10;
	matrizDelGrafo[2][8] = 2;
	matrizDelGrafo[8][7] = 14;
	matrizDelGrafo[8][6] = 6;
	matrizDelGrafo[7][6] = 1;
	matrizDelGrafo[6][5] = 2;
	matrizDelGrafo[5][2] = 4;
	matrizDelGrafo[2][3] = 7;
	matrizDelGrafo[3][5] = 14;
	matrizDelGrafo[3][4] = 9;
	matrizDelGrafo[4][5] = 10;

	Array<Tupla<nat, nat>> cablesNecesarios = Array<Tupla<nat, nat>>(8);
	cablesNecesarios[0] = Tupla<nat, nat>(7, 6); //Peso 1
	cablesNecesarios[1] = Tupla<nat, nat>(6, 5); //Primera de Peso 2
	cablesNecesarios[2] = Tupla<nat, nat>(2, 8); //Segunda de Peso 2
	cablesNecesarios[3] = Tupla<nat, nat>(1, 0); //Primera de Peso 4 (No hay de peso 3)
	cablesNecesarios[4] = Tupla<nat, nat>(5, 2); //Segunda de peso 4
	cablesNecesarios[5] = Tupla<nat, nat>(2, 3); //Peso 7 (No hay de peso 5. La de peso 6 forma ciclo)
	cablesNecesarios[6] = Tupla<nat, nat>(0, 7); //Peso 8
	cablesNecesarios[7] = Tupla<nat, nat>(3, 4); //Peso 9
	Iterador<Tupla<nat, nat>> iteradorCablesNecesarios = cablesNecesarios.ObtenerIterador();
	TipoRetorno retEsperado = OK;

	Tupla<TipoRetorno, Iterador<Tupla<nat, nat> > > resultadoObtenido = interfazDelSistema->AhorroEnlaces(matrizDelGrafo);
	TipoRetorno retObtenido = resultadoObtenido.Dato1;
	Iterador<Tupla<nat, nat> > iteradorCablesNecesariosOb = resultadoObtenido.Dato2;

	VerificarConjuntoAristasNoDirigidas(retEsperado, retObtenido, iteradorCablesNecesarios, iteradorCablesNecesariosOb, "Se prueba la operación 2");
}

//Operación 3:
void CasoDePrueba::PruebaOperacion3()
{
	IniciarSeccion("Operacion 3");
	Puntero<ISistema> interfaz = InicializarSistema();
	PruebaOperacion3A(interfaz);
	PruebaOperacion3B(interfaz);
	CerrarSeccion();
}

void CasoDePrueba::PruebaOperacion3A(Puntero<ISistema> interfazDelSistema)
{
	Array<Cadena> temas = Array<Cadena>(8);
	temas[0] = "Tarea 1";
	temas[1] = "Tarea 2";
	temas[2] = "Tarea 3";
	temas[3] = "Tarea 4";
	temas[4] = "Tarea 5";
	temas[5] = "Tarea 6";
	temas[6] = "Tarea 7";
	temas[7] = "Tarea 8";

	Array<Tupla<Cadena, Cadena>> relaciones = Array<Tupla<Cadena, Cadena>>(6);
	relaciones[0] = Tupla<Cadena, Cadena>("Tarea 3", "Tarea 8");
	relaciones[1] = Tupla<Cadena, Cadena>("Tarea 6", "Tarea 5");
	relaciones[2] = Tupla<Cadena, Cadena>("Tarea 8", "Tarea 7");
	relaciones[3] = Tupla<Cadena, Cadena>("Tarea 4", "Tarea 6");
	relaciones[4] = Tupla<Cadena, Cadena>("Tarea 4", "Tarea 7");
	relaciones[5] = Tupla<Cadena, Cadena>("Tarea 3", "Tarea 2");

	Iterador<Cadena> iteradorTareas = temas.ObtenerIterador();
	Iterador<Tupla<Cadena, Cadena>> iteradorRelaciones = relaciones.ObtenerIterador();
	Matriz<bool> precedenciasEntreLasTareas = CrearMatrizDePrecedencias(iteradorRelaciones, iteradorTareas);
	Tupla<TipoRetorno, Iterador<Cadena> > ordenDeTareasObtenido = interfazDelSistema->GerenteProyecto(iteradorTareas, iteradorRelaciones);

	VerificarOrden(ordenDeTareasObtenido, OK, precedenciasEntreLasTareas, iteradorTareas, "Se prueba la operación 3");
}

void CasoDePrueba::PruebaOperacion3B(Puntero<ISistema> interfazDelSistema)
{
	Array<Cadena> tareas = Array<Cadena>(13);
	tareas[0] = "Tarea1";
	tareas[1] = "Tarea2";
	tareas[2] = "Tarea3";
	tareas[3] = "Tarea4";
	tareas[4] = "Tarea5";
	tareas[5] = "Tarea6";
	tareas[6] = "Tarea7";
	tareas[7] = "Tarea8";
	tareas[8] = "Tarea9";
	tareas[9] = "Tarea10";
	tareas[10] = "Tarea11";
	tareas[11] = "Tarea12";
	tareas[12] = "Tarea13";

	Array<Tupla<Cadena, Cadena>> relaciones = Array<Tupla<Cadena, Cadena>>(16);
	relaciones[0] = Tupla<Cadena, Cadena>("Tarea1", "Tarea2");
	relaciones[1] = Tupla<Cadena, Cadena>("Tarea1", "Tarea3");
	relaciones[2] = Tupla<Cadena, Cadena>("Tarea2", "Tarea4");
	relaciones[3] = Tupla<Cadena, Cadena>("Tarea2", "Tarea5");
	relaciones[9] = Tupla<Cadena, Cadena>("Tarea3", "Tarea6");
	relaciones[10] = Tupla<Cadena, Cadena>("Tarea3", "Tarea7");
	relaciones[4] = Tupla<Cadena, Cadena>("Tarea4", "Tarea8");
	relaciones[6] = Tupla<Cadena, Cadena>("Tarea5", "Tarea9");
	relaciones[7] = Tupla<Cadena, Cadena>("Tarea5", "Tarea10");
	relaciones[11] = Tupla<Cadena, Cadena>("Tarea6", "Tarea10");
	relaciones[13] = Tupla<Cadena, Cadena>("Tarea7", "Tarea12");
	relaciones[5] = Tupla<Cadena, Cadena>("Tarea8", "Tarea11");
	relaciones[8] = Tupla<Cadena, Cadena>("Tarea9", "Tarea11");
	relaciones[12] = Tupla<Cadena, Cadena>("Tarea10", "Tarea12");
	relaciones[15] = Tupla<Cadena, Cadena>("Tarea11", "Tarea13");
	relaciones[14] = Tupla<Cadena, Cadena>("Tarea12", "Tarea13");

	Iterador<Cadena> iteradorTareas = tareas.ObtenerIterador();
	Iterador<Tupla<Cadena, Cadena>> iteradorRelaciones = relaciones.ObtenerIterador();
	Matriz<bool> precedenciasEntreLasTareas = CrearMatrizDePrecedencias(iteradorRelaciones, iteradorTareas);
	Tupla<TipoRetorno, Iterador<Cadena> > ordenDeTareasObtenido = interfazDelSistema->GerenteProyecto(iteradorTareas, iteradorRelaciones);

	VerificarOrden(ordenDeTareasObtenido, OK, precedenciasEntreLasTareas, iteradorTareas, Cadena("Se prueba la operación 3"));
}
