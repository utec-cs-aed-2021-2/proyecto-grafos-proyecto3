#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
#include <string>
#include <iostream>
#include <vector>
#include <json\json.h>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <math.h>

using namespace std;

template<typename TV, typename TE>
class parser {

public:

    vector<string> City;
    vector<string> DBTZ;
    vector<string> Name;
    vector<string> Country;
    vector<string> IATA;
    vector<double> Longitude;
    vector<string> ICAO;
    vector<string> id;
    vector<double> Latitude;
    vector<int> Timezone;
    vector<int> DST;
    vector<vector<string>> destinations;
    vector<bool> visitado;



    std::unordered_map<string, int> indexes;


public:

    parser() {};

    void clear() {
        City.clear();
        DBTZ.clear();
        Name.clear();
        Country.clear();
        IATA.clear();
        Longitude.clear();
        ICAO.clear();
        id.clear();
        Latitude.clear();
        Timezone.clear();
        DST.clear();
        destinations.clear();
    }

    void read_file_Json() {
        Json::Reader reader;
        Json::Value root;

        ifstream in("Parser/Data/prueba.json");

        reader.parse(in, root);

        //Preparar los datos
        string dato_City;
        string dato_DBTZ;
        string dato_Name;
        string dato_Country;
        string dato_IATA;
        string dato_Longitude;
        double dato_Lon_double;
        string dato_ICAO;
        string dato_Airport_id;
        int dato_Air_id_entero;
        string dato_Latitude;
        double dato_La_double;
        string dato_Timezone;
        int dato_Time_entero;
        string dato_DST;
        int dato_DST_entero;
        string dato_Destinations;
        int dato_Dest_entero;

        vector<string> datos;

        //cout << "Prueba ";
        //cout << root.size() << " \n";

        for (unsigned int i = 0; i < root.size(); i++)
        {
            dato_City = root[i]["City"].asString();
            dato_DBTZ = root[i]["DBTZ"].asString();
            dato_Name = root[i]["Name"].asString();
            dato_Country = root[i]["Country"].asString();
            dato_IATA = root[i]["IATA/FAA"].asString();
            dato_Longitude = root[i]["Longitude"].asString();
            dato_Lon_double = stod(dato_Longitude);
            dato_ICAO = root[i]["ICAO"].asString();
            dato_Airport_id = root[i]["Airport ID"].asString();
            dato_Air_id_entero = atoi(dato_Airport_id.c_str());
            dato_Latitude = root[i]["Latitude"].asString();
            dato_La_double = stod(dato_Latitude);
            dato_Timezone = root[i]["Timezone"].asString();
            dato_Time_entero = atoi(dato_Timezone.c_str());
            dato_DST = root[i]["DST"].asString();
            dato_DST_entero = atoi(dato_DST.c_str());

            datos.clear();
            //cout << i << " " << dato_City << " " << dato_DBTZ << " " << dato_Name << " " << dato_Country << " " << dato_IATA << " " << dato_Lon_double << " " << dato_ICAO << " " << dato_Air_id_entero << " " << dato_La_double << " " << dato_Time_entero << " " << dato_DST_entero << " " << "[";
            for (unsigned int k = 0; k < root[i]["destinations"].size(); k++)
            {
                //vector de destinos
                dato_Destinations = root[i]["destinations"][k].asString();   //dato a guardar
                dato_Dest_entero = atoi(dato_Destinations.c_str());
                if (k == 0) {
                    //cout << dato_Dest_entero;
                }
                else {
                    //cout << "," << dato_Dest_entero;
                }
                datos.push_back(dato_Destinations);
                //datos = dato_datos;
            }
            //cout << "] \n";


            //Guardar los datos
            City.push_back(dato_City);
            DBTZ.push_back(dato_DBTZ);
            Name.push_back(dato_Name);
            Country.push_back(dato_Country);
            IATA.push_back(dato_IATA);
            Longitude.push_back(dato_Lon_double);
            id.push_back(dato_Airport_id);
            Latitude.push_back(dato_La_double);
            Timezone.push_back(dato_Time_entero);
            DST.push_back(dato_DST_entero);
            destinations.push_back(datos);
            visitado.push_back(false);
        }
        in.close();
        for (int i = 0; i < Longitude.size(); i++) {
            //cout << Name[i] << " ";
            for (int k = 0; k < destinations[i].size(); k++) {
                //cout << destinations[i][k] << " ";
            }
            //cout << "\n";
        }

    }

    void uGraphMake(UnDirectedGraph<string, double>& tempGraph) {
        //cout << "Prueba 2\n";
        string id_vertice;
        string airport;
        string id_vertice_origen;
        string id_vertice_destino;
        double longitud_vertice_origen;
        double latitud_vertice_origen;
        double longitud_vertice_destino;
        double latitud_vertice_destino;

        double distancia = 0;

        //insertar vertices
        for (int i = 0; i < id.size(); i++) {
            id_vertice = this->id[i];
            airport = this->City[i];
            this->indexes.insert_or_assign(this->id[i], i);
            //cout << this->indexes.find("1")->second << "\n";
            //cout << id_vertice << " ";
            //cout << airport << " ";
            tempGraph.insertVertex(id_vertice, airport);
            //cout << tempGraph.findById(id[i]) << "\n";
        }

        //poenr a false todos los puntos
        for (int i = 0; i < id.size(); i++) {
            visitado[i] = false;
        }

        //insertar aristas
        //cout << "\nPRUEBA ARISTAS\n";
        for (int i = 0; i < id.size(); i++) {
            id_vertice_origen = id[i];
            longitud_vertice_origen = Longitude[i];
            latitud_vertice_origen = Latitude[i];
            visitado[i] = true;
            //cout << City[i] << "\n";
            for (int k = 0; k < destinations[i].size(); k++) {
                id_vertice_destino = destinations[i][k];
                //cout << this->indexes.find(id_vertice_destino)->second << " ";
                if (visitado[this->indexes.find(id_vertice_destino)->second] == false) {
                    longitud_vertice_destino = Longitude[this->indexes.find(id_vertice_destino)->second];
                    latitud_vertice_destino = Latitude[this->indexes.find(id_vertice_destino)->second];
                    distancia = sqrt(pow(longitud_vertice_origen - longitud_vertice_destino, 2) + pow(latitud_vertice_origen - latitud_vertice_destino, 2));
                    //cout << id_vertice_origen << " " << id_vertice_destino << " " << distancia << endl;
                    tempGraph.createEdge(id_vertice_origen, id_vertice_destino, round(distancia));
                }

            }
            //cout << endl;
        }

    }

    void dGraphMake(DirectedGraph<string, double>& tempGraph) {
        //cout << "Prueba 2\n";
        string id_vertice;
        string airport;
        string id_vertice_origen;
        string id_vertice_destino;
        double longitud_vertice_origen;
        double latitud_vertice_origen;
        double longitud_vertice_destino;
        double latitud_vertice_destino;

        double distancia = 0;

        //insertar vertices
        for (int i = 0; i < id.size(); i++) {
            id_vertice = id[i];
            airport = City[i];
            this->indexes.insert_or_assign(id[i], i);
            //cout << id_vertice << " ";
            //cout << airport << " ";
            tempGraph.insertVertex(id_vertice, airport);
            //cout << tempGraph.findById(id[i]) << "\n";
        }

        //insertar aristas
        for (int i = 0; i < id.size(); i++) {
            id_vertice_origen = id[i];
            longitud_vertice_origen = Longitude[i];
            latitud_vertice_origen = Latitude[i];
            for (int k = 0; k < destinations[i].size(); k++) {
                id_vertice_destino = destinations[i][k];
                longitud_vertice_destino = Longitude[this->indexes.find(id_vertice_destino)->second];
                latitud_vertice_destino = Latitude[this->indexes.find(id_vertice_destino)->second];
                distancia = sqrt(pow(longitud_vertice_origen - longitud_vertice_destino, 2) + pow(latitud_vertice_origen - latitud_vertice_destino, 2));
                tempGraph.createEdge(id_vertice_origen, id_vertice_destino, round(distancia));

            }
        }
    }

};