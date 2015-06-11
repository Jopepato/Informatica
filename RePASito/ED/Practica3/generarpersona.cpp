/*!
  \file   generarpersona.cpp
  \brief  Codificación de las funciones auxiliares para generar aleatoriamente personas
  \author Name
  \date   16/03/2015
*/

#include <cstdlib>
#include <cassert>
#include <fstream>
#include "generarpersona.hpp"
#include "persona.hpp"

static const  std::string _apellidos[] = {
"GARCIA",
"FERNANDEZ",
"GONZALEZ",
"RODRIGUEZ",
"LOPEZ",
"MARTINEZ",
"SANCHEZ",
"PEREZ",
"MARTIN",
"GOMEZ",
"RUIZ",
"DIAZ",
"HERNANDEZ",
"JIMENEZ",
"ALVAREZ",
"MORENO",
"MUNOZ",
"ALONSO",
"GUTIERREZ",
"ROMERO",
"NAVARRO",
"DOMINGUEZ",
"TORRES",
"VAZQUEZ",
"GIL",
"RAMOS",
"BLANCO",
"SERRANO",
"SUAREZ",
"RAMIREZ",
"MOLINA",
"DELGADO",
"ORTEGA",
"RUBIO",
"CASTRO",
"MORALES",
"SANZ",
"IGLESIAS",
"ORTIZ",
"MARIN",
"NÚNEZ",
"GARRIDO",
"SANTOS",
"PRIETO",
"MEDINA",
"CANO",
"LOZANO",
"DIEZ",
"CALVO",
"CASTILLO",
"GALLEGO",
"MENDEZ",
"VIDAL",
"GUERRERO",
"CRUZ",
"VEGA",
"PASCUAL",
"HERRERO",
"PENA",
"NIETO",
"CAMPOS",
"MARQUEZ",
"FUENTES",
"CORTES",
"IBANEZ",
"LEON",
"CABALLERO",
"CARRASCO",
"LORENZO",
"HERRERAS",
"FERRER",
"CABRERA",
"GIMENEZ",
"VICENTE",
"SAEZ",
"SANTANA",
"MONTERO",
"CRESPO",
"HIDALGO",
"ARIAS",
"AGUILAR",
"FLORES",
"DURAN",
"PASTOR",
"ESTEBAN",
"MORA",
"VELASCO",
"CARMONA",
"REYES",
"BRAVO",
"SOTO",
"SOLER",
"MENENDEZ",
"MERINO",
"PARDO",
"BENITEZ",
"MOYA",
"REDONDO",
"REY",
"ROMAN"
};

static const  std::string _nombres[] = {
"MARIA_CARMEN",
"MARIA",
"CARMEN",
"JOSEFA",
"ISABEL",
"ANA_MARIA",
"MARIA_DOLORES",
"MARIA_PILAR",
"MARIA_TERESA",
"ANA",
"FRANCISCA",
"LAURA",
"ANTONIA",
"DOLORES",
"MARIA_ANGELES",
"CRISTINA",
"MARTA",
"MARIA_JOSE",
"MARIA_ISABEL",
"PILAR",
"MARIA_LUISA",
"CONCEPCION",
"LUCIA",
"MERCEDES",
"MANUELA",
"ELENA",
"ROSA_MARIA",
"RAQUEL",
"MARIA_JESUS",
"SARA",
"JUANA",
"TERESA",
"ROSARIO",
"PAULA",
"ENCARNACION",
"BEATRIZ",
"ROSA",
"NURIA",
"SILVIA",
"MONTSERRAT",
"PATRICIA",
"JULIA",
"MONICA",
"IRENE",
"MARGARITA",
"ANDREA",
"MARIA_MAR",
"ANGELA",
"ROCIO",
"SONIA",
"ANTONIO",
"JOSE",
"MANUEL",
"FRANCISCO",
"JUAN",
"DAVID",
"JOSE_ANTONIO",
"JOSE_LUIS",
"JESUS",
"JAVIER",
"FRANCISCO_JAVIER",
"CARLOS",
"DANIEL",
"MIGUEL",
"RAFAEL",
"PEDRO",
"JOSE_MANUEL",
"ANGEL",
"ALEJANDRO",
"MIGUEL_ANGEL",
"JOSE_MARIA",
"FERNANDO",
"LUIS",
"SERGIO",
"PABLO",
"JORGE",
"ALBERTO",
"JUAN_CARLOS",
"JUAN_JOSE",
"RAMON",
"ENRIQUE",
"VICENTE",
"JUAN_ANTONIO",
"DIEGO",
"RAUL",
"ALVARO",
"JOAQUIN",
"ADRIAN",
"ANDRES",
"IVAN",
"OSCAR",
"RUBEN",
"SANTIAGO",
"JUAN_MANUEL",
"EDUARDO",
"VICTOR",
"ROBERTO",
"JAIME",
"FRANCISCO_JOSE",
"ALFONSO"
};

static const int NUMERONOMBRES = 100;
static const int NUMEROAPELLIDOS = 100;

static inline int generarEnteroAleatorio (const int &min, const int &max)
{
  return min + rand() % (max - min + 1);
}

const edi::Persona generarPersona()
{
	edi::Persona persona;

	persona.dni(generarEnteroAleatorio(20000000, 70000000));
  persona.apellido(_apellidos[generarEnteroAleatorio(0, NUMEROAPELLIDOS - 1)]);
	persona.nombre(_nombres[generarEnteroAleatorio(0, NUMERONOMBRES - 1)]);
	persona.borrado('n');

  return persona;
}

//Selecciona personas aleatorias del fichero de personas 
std::vector <edi::Persona> generarPersonas(const  std::string &fichero, const int &numeroPersonas)
{
	std::vector <edi::Persona> v;
	std::vector <edi::Persona> personasSeleccionadas;
	edi::Persona p;
	std::string nombre, apellido;
	int dni;
	
	std::ifstream f(fichero.c_str());
	while (f >> nombre >> apellido >> dni)
	{
		p.nombre(nombre);
		p.apellido(apellido);
		p.dni(dni);
		v.push_back(p);
	}
	
	assert((unsigned int)numeroPersonas <= v.size());
	bool seleccionado[v.size() - 1];
	for(unsigned int i = 0; i < v.size(); i++)
		seleccionado[i] = false;
	
	int indice;
	
	for(unsigned int i = 0; i < (unsigned int)numeroPersonas; )
	{
		indice = generarEnteroAleatorio(0, v.size() - 1);
		if (not seleccionado[indice])
		{
			seleccionado[indice] = true;
			personasSeleccionadas.push_back(v[(unsigned int)indice]);
			i++;
		}
	}
	
  return personasSeleccionadas;
}

