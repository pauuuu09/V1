//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char ID[10];
	char fecha[10];
	char hora[10];
	int duracion;
	char winner[20];
	char consulta [80];
	int NPartidas = 0;
	//Creamos una conexion al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexi\u1162\u1108n: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "proyecto",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexi\u1162\u1108n: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	err=mysql_query (conn, "SELECT duracion FROM partida WHERE duracion>15;");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta. El resultado de la
	//consulta se devuelve en una variable del tipo puntero a
	//MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia
	//de la tabla real en disco.
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial en memoria
	// en la que cada fila contiene los datos de una persona.
	// Ahora obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	row = mysql_fetch_row (resultado);
	// En una fila hay tantas columnas como datos tiene una
	// persona. En nuestro caso hay tres columnas: dni(row[0]),
	// nombre(row[1]) y edad (row[2]).
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL) {
			NPartidas = NPartidas + 1;
			row = mysql_fetch_row (resultado);
			
	}
		mysql_close (conn);
		exit(0);

	printf("Hi ha %d partides que duren més de 15 minuts\n",NPartidas);
}
