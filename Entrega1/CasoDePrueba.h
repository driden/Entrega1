#pragma once

#include "ISistema.h"
#include "Prueba.h"

class CasoDePrueba : public Prueba
{
public:
	CasoDePrueba(Puntero<ISistema>(*inicializar)());

protected:
	void CorrerPruebaConcreta() override;
	Cadena GetNombre() const override;

private:
	Puntero<ISistema>(*inicializar)();
	Puntero<ISistema> InicializarSistema();

	bool ignorarOK;
	void Verificar(TipoRetorno obtenido, TipoRetorno esperado, Cadena comentario);
	template <class T>
	void Verificar(const T& obtenido, const T& esperado, Cadena comentario);
	template <class T>
	void VerificarConjuntos(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra);
	template <class T>
	void VerificarSecuencias(Iterador<T> obtenidos, Iterador<T> esperados, Cadena comentarioEncontrado, Cadena comentarioFalta, Cadena comentarioSobra);
	void VerificarOrden(Tupla<TipoRetorno, Iterador<Cadena>> obtenido, TipoRetorno tipoRetEsperado, Matriz<bool> resultadoEsperado, Iterador<Cadena> temas, Cadena comentario);
	void VerificarSiEstaDentroDeLasSolucionesPosibles(Matriz<bool> esperados, Iterador<Cadena> obtenido, Cadena comentario, Iterador<Cadena> temas);
	bool ExistePrecedencia(Cadena elementoI, Cadena elementoJ, Matriz<bool> matrizAVerificar, Iterador<Cadena> temas);

	void VerificarConjuntoAristasNoDirigidas(TipoRetorno retObtenido, TipoRetorno retEsperado, Iterador<Tupla<nat, nat>> arbolObtenido, Iterador<Tupla<nat, nat>> arbolEsperado, Cadena comentario);
	template <class T>
	bool SonIguales(Iterador<T> obtenidos, Iterador<T> esperados) const;
	bool SonIguales(const Tupla<nat, nat>& obtenido, const Tupla<nat, nat>& esperado) const;
	template <class T>
	Cadena ObtenerTexto(Iterador<T> it) const;
	Cadena ObtenerTexto(const Tupla<nat, nat>& t) const;
	Cadena ObtenerTexto(nat n) const;
	template <class T>
	bool Pertenece(const T& dato, Iterador<T> iterador, T& encontrado) const;
	void InicializarMatrizEnCero(Matriz<nat> matrizAInicializar);
	void InicializarMatriz(Matriz<bool> matrizAInicializar, int largo);
	template <class T>
	int ObtenerLargoIterador(Iterador<T> iteradorFuente);
	Matriz<bool> CrearMatrizDePrecedencias(Iterador<Tupla<Cadena, Cadena> > relacionesEntreVertices, Iterador<Cadena> verticesQueParticipan);
	int ObtenerNumeroInternoVertice(Cadena verticeABuscar, Iterador<Cadena> iteradorDeVertices);

	void PruebaOperacion1();
	void PruebaOperacion1A(Puntero<ISistema> interfazDelSistema);
	void PruebaOperacion1B(Puntero<ISistema> interfazDelSistema);
	void PruebaOperacion1C(Puntero<ISistema> interfazDelSistema);
	void PruebaOperacion1D(Puntero<ISistema> interfazDelSistema);
	void PruebaOperacion2();
	void PruebaOperacion2A(Puntero<ISistema> interfazDelSistema);
	void PruebaOperacion2B(Puntero<ISistema> interfazDelSistema);
	void PruebaOperacion3();
	void PruebaOperacion3A(Puntero<ISistema> interfazDelSistema);
	void PruebaOperacion3B(Puntero<ISistema> interfazDelSistema);
};
