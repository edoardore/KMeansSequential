# KMeansSequential
Progetto mid-term di Parallel Computing 

## Utilizzo
Eseguire il modulo main.cpp, cambiare i valori delle variabili globali per diversi risultati:
```c++
double Range = 99999;
const int nPoint = 5000;
int nCluster = 5;
int itr = 20;
```
È possibile modificare i due booleani per eseguire il codice con i punti in Array of Structures (AoS) oppure in Structure of Arrays (SoA):
```c++
bool AoS = TRUE;
bool SoA = TRUE;
```

## Esecuzione
Il programma genererà sulla base dei valori impostati in nPoint e nCluster, in questo esempio 5000 punti casuali e 5 cluster casuali nei quali successivamente aggiornerà i centroidi e le appartenenze dei punti ai clusters.



## Esempio di output del file ```main.cpp```
```
**********************Points in AoS************************
Creazione di 5000 punti casuali
Creazione di 5 Clusters
Punti e Clusters generati in: 0.00300002s
Aggiornamento dei Clusters con 20 iterazioni in: 0.0930002s
**********************Points in SoA************************
Creazione di 5000 punti casuali
Creazione di 5 Clusters
Punti e Clusters generati in: 0.00200009s
Aggiornamento dei Clusters con 20 iterazioni in: 0.0569999s

Process finished with exit code 0
```

![gnuplot results](https://github.com/edoardore/KMeansSequential/blob/master/gnuplot.PNG)


## Librerie utilizzate
```c++
#include <iostream>
#include <chrono>
#include <omp.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <windef.h>
#include "Cluster.h"
```
Attenzione: solitamente sugli IDE più comuni sono quasi tutte presenti tranne per [gnuplot](http://www.gnuplot.info/download.html).

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
Please make sure to update tests as appropriate.


## License
[Edoardo Re](https://github.com/edoardore), 2020
