[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6164439&assignment_repo_type=AssignmentRepo)
# Algoritmos y Estructura de Datos
## Proyecto sobre Grafos
--------

## Integrantes
- Alejandro Bojorquez Samame 
- Jose Bojorquez Samame
- Diego Galván Rodriguez 

----

El proyecto del curso consiste en implementar una estructura de datos de grafo y un file parser. La estructura debe soportar los métodos y algoritmos descritos a continuacion:  


## Graph data structure

* El grafo debe ser dinámico (inserciones. eliminaciones, búsquedas, ...)
* Se debe implementar los dos tipos de grafos: dirigidos y no-dirigidos.
* No considerar loops ni multi-arista. 

----
## Basic Methods:

Métodos que se encuentran en las cabeceras correspondientes a los dos tipos de grafos. Los métodos están implementados para ambos tipos de grafos(dirigidos y no dirigidos):


----
```cpp
bool insertVertex(string id, TV data):   
```
  * #### Descripción: 
    Inserta un vértice en el unordered_map "vertexes" de la clase "graph". Para ello utiliza la función nsert_or_assign() del unordered_map en cuestión, función que se encuentra en la librería correspondiente al unordered_map STL usado. En caso de que se tenga una versión inferior a C++17, se puede reemplazar por la función find y con ayuda de una condicional, decidir si insertar o actualizar el valor.

  * #### Parámetros: 
    * string id: Valor de la key correspondiente al vértice. Con esta key se realizará la busqueda en el unordered_map de vértices.
    * TV data: Valor del dato que tendrá el vértice a insertar. 
  * #### Return: 
    * bool: Retorna un valor booleano que indica si se logró insertar el nodo con éxito con un "true", en caso de que no retorna un "false".

  * #### Consideraciones: Ninguna
##

```cpp
bool createEdge(string start, string end, TE data):
```

  * #### Descripción:
    Crea una arista entre los dos vértices que se indiquen en los parámetros. Al introducir las correspondiente keys como parametros, con ayuda de la función find() del unordered_map STL, buscarán los vértices que se unirán mediante una arista. Después se indica el peso que también será ingresado como parámetro. 

  * #### Parámetros:
    * string start: Indicar las key correspondiente al vértice que será el origen de la arista.

    * string end: Indicar las key correspondiente al vértice que será el destino de la arista.

    * TE data: Valor númerico que indicará el peso de la arista creada. 

  * #### Return: 
    * bool: Indica si se logró crear la arista con éxito retornando un "true". En caso de que no lo logre, retorna un "false".

  * #### Consideraciones: 
  Tener en cuenta el orden en que se insertan los parametros string start y string end para grafos dirigidos. Para grafos no dirigidos, no importa el orden. 
##
```cpp
 bool deleteVertex(string id):
```
  * #### Descripcion: 
    Elimina un vértice del grafo buscándolo con la key ingresada como parámetro. Las aristas vinculadas a este vértice también serán eliminadas. 

  * #### Parámetros:
    * string id: Se indica la key del vértice que se desea eliminar del grafo.

  * #### Return: 
    * bool: Indica si se logró eliminar el vértice con éxito retornando un "true". En caso de que no lo logre, retorna un "false".

  * #### Consideraciones: Ninguna
##
```cpp
bool deleteEdge(string start, string end):
```
  * #### Descripcion: 
    Elimina una arista del grafo buscándolo con las keys ingresadas como parámetros.

  * #### Parámetros:
    * string start: Indicar las key correspondiente al vértice que actúa como origen de la arista.

    * string end: Indicar las key correspondiente al vértice que actúa como destino de la arista.

  * #### Return: 
    * bool: Indica si se logró eliminar la arista con éxito retornando un "true". En caso de que no lo logre, retorna un "false".

  * #### Consideraciones: Ninguna
##
```cpp
TE &operator()(string start, string end):
```
  * #### Descripcion: 
    Indica el valor de la arista que une los vértices correspondientes a las keys ingresadas como parámetros

  * #### Parámetros:
    * string start: Indicar las key correspondiente al vértice que actúa como origen de la arista.

    * string end: Indicar las key correspondiente al vértice que actúa como destino de la arista.

  * #### Return: 
    * TE: Valor numérico que representa el peso de la arista.

  * #### Consideraciones: Tener en cuenta el orden en que se insertan los parametros string start y string end para grafos dirigidos. Para grafos no dirigidos, no importa el orden. 
##
```cpp
float density():
```
  * #### Descripcion: 
    Método que permite calcular la densidad del grafo. 

  * #### Parámetros: Ninguno
  * #### Return: 
    * float: Valor numérico que representa la densidad del grafo.

  * #### Consideraciones: Ninguna. 
##
```cpp
bool isDense(float threshold = 0.5):
```
  * #### Descripcion: 
    Indica si el grafo es denso o no dependiendo del umbral ingresado como parámetro (por defecto es 0.5). 

  * #### Parámetros: 
    * float threshold: Indica el umbral para considerar al grafo denso o no denso. 
  * #### Return:
    * bool: Indica si se el grafo es denso retornando un "true". En caso contrario, retorna un "false".

  * #### Consideraciones: Ninguna 
  ##
```cpp
bool isConnected():
```
  * #### Descripcion: 
    Indica si el grafo es conexo. Para ello emplea una cola que irá eliminando los vértices visitados de esta y un unordered_map de vértices recorridos. Si dicho unordered_map tiene la misma cantidad de elementos que la cantidad de vértices del grafo, se tratará de un grafo conexo.

  * #### Parámetros:  Ninguno 
  * #### Return:
    * bool: Indica si se el grafo es conexo retornando un "true". En caso contrario, retorna un "false".

  * #### Consideraciones: Ninguna 
  ##
```cpp
bool isStronglyConnected() throw():
```
  * #### Descripcion: 
    Indica si el grafo es fuertemente conexo. Para ello emplea una cola que irá eliminando los vértices visitados de esta y un unordered_map de vértices recorridos. Si dicho unordered_map tiene la misma cantidad de elementos que la cantidad de vértices del grafo, se tratará de un grafo conexo.

  * #### Parámetros:  Ninguno 
  * #### Return:
    * bool: Indica si se el grafo es conexo retornando un "true". En caso contrario, retorna un "false".

  * #### Consideraciones: Ninguna 
##
```cpp
bool empty():
```
  * #### Descripcion: 
    Indica si el grafo se encuentra vacío. Para ello simplemente compara el tamaño del unordered_map vertexes con el cero. 

  * #### Parámetros:  Ninguno 
  * #### Return:
    * bool: Indica si se el grafo está vacío retornando un "true". En caso contrario, retorna un "false".

  * #### Consideraciones: Ninguna 
##
```cpp
void clear():
```
  * #### Descripcion: 
    Elimina todos los vértices y aristas del grafo, para ello, con ayuda de un iterador se recorre todo el unordered_map de vertexes eliminando en cada paso.

  * #### Parámetros:  Ninguno 
  * #### Return: Ninguno

  * #### Consideraciones: No elimina el grafo, solo los vértices y aristas que lo conforman.

----------
## Algorithms:

En este apartado se detalla la información de los algoritmos relacionados con los grafos. Entre ellos se encuentran algoritmos que permiten hallar el MST (árbol de expansión mínima) o el camino más corto a otros vértices (Shortest path). 

----------
### Kruskal Algorithm:

Este algoritmo voraz o goloso genera el MST (árbol de expansión mínima) para un grafo. Este algoritmo solo funciona en grafos NO dirigidos. Para ello se ha creado una clase kruskal en cuyo constructor se realiza el algoritmo. Cuando se desea retornar el MST, se llama a la función apply() correspondiente a la clase kruskal el cual retornará un grafo no dirigido con el MST. Para determinar el MST, se requiere tener los vértices ordenados por peso de menor a mayor. Luego, se recorre este vector o lista de aristas y con disjoint sets, se van uniendo en el mismo set los vértices ubicados en los extremos de la arista en cuestión. Las iteraciones acaban al terminar de recorrer las aristas o cuando la cantidad de conjuntos sea igual a 1 Dicha clase y sus métodos se pueden encontrar en kruskal.h.
```cpp
Kruskal<char, int> kruskal(&graph):
```

* #### Descripcion: 
    Constructor de la clase kruskal. Es en este constructor en el cual se ejecuta el algoritmo. Dicho de otro modo, en un objeto kruskal se guardarán las aristas y vértices correspondientes al árbol de expansión mínima del grafo que se inserta como parámetro.

  * #### Parámetros:  Puntero a grafo o dirección de este. 
  * #### Return: Ninguno
  * #### Consideraciones: Realiza el algoritmo pero no retorna el MST.
##
```cpp
UndirectedGraph<TV, TE> apply():
``` 
  * #### Descripcion:   
    Constructor de la clase kruskal. Es en este constructor en el cual se ejecuta el algoritmo. Dicho de otro modo, en un objeto kruskal se guardarán las aristas y vértices correspondientes al árbol de expansión mínima del grafo que se inserta como parámetro.

  * #### Parámetros: Ninguno. 
  * #### Return: 
    * UndirectedGraph<TV,TE>: Retorna el MST dentro de un objeto de clase UndirectedGraph
  * #### Consideraciones: Retorna el MST correcto solo si ya se ha ejecutado el constructor con la dirección de memoria del grafo como parámetro. 

-----
### Prim Algorithm:
```cpp
//2- Generates a MST graph using the Prim approach (only for undirected graphs)

Prim<char, int> prim(&graph, "A");
UndirectedGraph<char, int> result = prim.apply();//return a tree
```
-----
### A* Algorithm

Es un algoritmo que permite encontrar el camino más corto entre dos vértices. Para hallar dicho camino, utiliza los pesos de las aristas y las heurísticas definidas para los vértices.
```cpp
//3- A *
AStar<TV, TE> astar(DirectedGraph<TV,TE> graph, string start, string end, vector<TE> heuristics);
DirectedGraph<TV, TE> result = astar.apply();
```
  * #### Descripcion:   
    Encuentra el camino más corto entre dos vértices. Fue implementado como una clase que posee un Grafo como atributo, al cual se insertan los vértices y las aristas del camino más corto según los pesos y las heurísticas. Para obtener dicho grafo se utiliza el método apply().

  * #### Parámetros:
    * DirectedGraph<TV,TE> graph: Grafo base sobre el cual se aplicará el algoritmo.
    * string start: id del vértice origen desde el que se empezará el camino.
    * string end: id del vértice destino al cual se desea llegar.
    * vector<TE> heuristics: vector que contiene las heurísticas definidas para aplicar el algoritmo.  
  * #### Return: 
    * DirectedGraph<TV, TE> : Cuando se utiliza el método apply, retorna el grafo que contiene los vértices y las aristas del camino definido en el constructor de la clase AStar. 
  * #### Consideraciones: Solo se implementó el algoritmo para grafos dirigidos. El algoritmo no funcionará si no existe un camino entre ambos vértices.
-----
### Dijkstra Algorithm

Es un algoritmo que permite encontrar el camino más corto desde un vértice origen hacia el resto de vértices del grafo. Para calcular el camino más corto, inicia en un vértice escogido y recorre los vértices adyacentes, luego marca el vértice origen como visitado y ahora se dirige al vértice que tiene menos distancia con respecto al origen. Esto se repite con todos los vértices hasta que todos los vértices sean marcados como visitados. Solo funciona en grafos cuyas aristas no tengan pesos negativos.

```cpp
TE* Dijkstra(string id):
```
  * #### Descripcion:   
    Encuentra el camino más corto hacia todos los vértices recorriendo cada uno y deteniéndose al terminar de visitar a todos. Se encuentra como método dentro de las clases UndirectedGraph y DirecteGraph.

  * #### Parámetros:
    * string id: Se ingresa la key del vértice que se ha escogido como origen.   
  * #### Return: 
    * TE* : Retorna un arreglo dinámico con las distancias desde el vértice de origen hacia los demás. 
  * #### Consideraciones: Ninguna


-----
### Bellman-Ford Algorithm

Es un algoritmo que permite encontrar el camino más corto de un vértice de origen hacia el resto de vértices de un grafo. Este algoritmo se usa en grafos dirigidos. Hay formas de representarlo para grafos no dirigidos y es representar cada arista del grafo no dirigido como 2 aristas, una para cada sentido, sin embargo, no es recomendable hacer esto y se prefiere dejarlo solo para grafos dirigidos. Admite aristas con pesos negativos pero no funciona con ciclos negativos. Este algoritmo se ha implementado como un método dentro de la clase DirectedGraph. 
```cpp
TE* BellmanFord(string id):
```
  * #### Descripcion:   
    Método que se encuentra dentro de la clase DirectedGraph y calcula la ruta más corta desde un vértice de origen. Para lograrlo, realiza una cantidad de iteraciones igual a  la cantidad de vértices en el grafo menos 1 (V-1). En cada iteración se recorren todas las aristas actualizando en cada paso la distancia desde el vértice de origen en caso de que sea menor a la distancia almacenada. Al terminar las iteraciones, retorna un array con las distancias mínimas. 

  * #### Parámetros:
    * string id: Se ingresa la key del vértice que se ha escogido como origen.   
  * #### Return: 
    * TE* : Retorna un arreglo dinámico con las distancias desde el vértice de origen hacia los demás. 
  * #### Consideraciones: 
  Complejidad de O(VE) cuando V es la cantidad de vértices y E la cantidad de aristas.


-----
### Floyd-Warshall Algorithm

Es un algoritmo que en una única ejecución encuentra el camino más corto entre todos los vértices del grafo. Para ello, inicializa una matriz donde almacena las distancias. Luego procede a llenar la matriz con las distancias entre vértices adyacentes. Finalmente, con un triple bucle anidado, recorre cada elemento de la matriz y actualiza la distancia en caso de que la distancias tentativa a insertar sea menor que la que estaba ya almacenada en la matriz. Funciona solo en grafos dirigidos.

```cpp
TE** FloydWarshall():
```
  * #### Descripcion:   
    Método que se encuentra dentro de la clase DirectedGraph y calcula la ruta más corta desde un vértice de origen. Para lograrlo, realiza una cantidad de iteraciones igual a  la cantidad de vértices en el grafo menos 1 (V-1). En cada iteración se recorren todas las aristas actualizando en cada paso la distancia desde el vértice de origen en caso de que sea menor a la distancia almacenada. Al terminar las iteraciones, retorna un array con las distancias mínimas. 

  * #### Parámetros: Ninguno
  * #### Return: 
    * TE** : Retorna una matriz dinámica con todas las distancias mínimas entre los vértices del grafo. 
  * #### Consideraciones: Ninguna.
  
-----
### BFS
 
 Es un algoritmo que recorre todos los vértices partiendo desde uno definido. Empieza recorriendo los adyacentes al inicial, luego los adyacentes de estos y así sucesivamente.

```cpp
BFS<TV, TE> bfs(DirectedGraph<TV,TE> graph, string start);
DirectedGraph<TV, TE> result = bfs.apply();
```
  * #### Descripcion:   
    Recorre todos los vértices del grafo empezando desde un vértice en específico. Fue implementado como una clase que posee un Grafo como atributo, al cual se insertan todos los vértices del grafo original y las aristas que se utilizaron para recorrerlos. Para obtener dicho grafo se utiliza el método apply().

  * #### Parámetros:
    * DirectedGraph<TV,TE> graph: Grafo base sobre el cual se aplicará el algoritmo.
    * string start: id del vértice origen desde el que se empezará el recorrido.
  * #### Return: 
    * DirectedGraph<TV, TE> : Cuando se utiliza el método apply, retorna el grafo que contiene los vértices y las aristas insertadas en el constructor de la clase BFS. 
  * #### Consideraciones: Solo se implementó el algoritmo para grafos dirigidos. El algoritmo no recorrerá todos los vértices si no existe un camino entre el inicial y alguno de los demás.


-----
## JSON file parser
* Construye un grafo a partir de una archivo JSON de aereopuertos del mundo. 
Para la lectura de datos de un archivo .json, se utilizo la libreria jsoncpp, se creo una clase parser que almacenaria los datos cargados del archivo .json y podran ser introducidos a un grafo vacio, sea directo o indirecto.  


### Methods:
```cpp
void clear(); // Clears parser saved atributes
```
  * #### Descripcion:   
    Funcion que elimina todos los datos guardados en la clase parser 

  * #### Parámetros:
    * none  
  * #### Return: 
    *none 
  * #### Consideraciones: 
  none

```cpp
void read_JSON_file(); // Parses JSON file and saves data into class
```
  * #### Descripcion:   
    Funcion que lee los datos del archivo json y guarda los datos dentro de la clase parser

  * #### Parámetros:
    * none  
  * #### Return: 
    *none 
  * #### Consideraciones: 
  El archivo json se puede seleccionar dentro del parser.h

```cpp
void uGraphMake(UndirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph
```
  * #### Descripcion:   
    Funcion que acepta un grafo indirecto vacio y genera todos los vertices y aristas en este con los datos del json guardados en la clase parser

  * #### Parámetros:
    * UndirectedGraph<string, double> &tempGraph : Grafo indirecto en donde se van a guardar los datos del parser.
  * #### Return: 
    *none 
  * #### Consideraciones: 
  none

```cpp
void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
```
  * #### Descripcion:   
    Funcion que acepta un grafo directo vacio y genera todos los vertices y aristas en este con los datos del json guardados en la clase parser

  * #### Parámetros:
    * DirectedGraph<string, double> &tempGraph : Grafo directo en donde se van a guardar los datos del parser.
  * #### Return: 
    *none 
  * #### Consideraciones: 
  none

## [Git Karma Guidelines](http://karma-runner.github.io/5.2/dev/git-commit-msg.html)

```
<type>(<scope>): <subject>

<body>
```

### Allowed ```<type>``` values

* feat (new feature for the user, not a new feature for build script)
* fix (bug fix for the user, not a fix to a build script)
* docs (changes to the documentation)
* style (formatting, missing semi colons, etc)
* refactor (refactoring production code, eg. renaming a variable)
* test (adding missing tests, refactoring tests)
* chore (updating grunt tasks etc)

### Allowed ```<scope>``` values

* graph
* directedGraph
* undirectedGraph
* parser
* main
* tester





