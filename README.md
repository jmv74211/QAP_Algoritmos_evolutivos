# Problemas de optimización combinatoria (QAP)
## Algoritmos evolutivos
### Autor: Jonathan Martín Valera

---

# QAP

El objetivo de esta práctica es resolver un problema de optimización tı́pico utilizando
técnicas de computación evolutiva. Deberá implementar varias variantes de algoritmos
evolutivos para resolver el problema de la asignación cuadrática, incluyendo como mı́nimo
las variantes que se describen en este guión de prácticas.

# 1 El problema de la asignación cuadrática

El problema de la asignación cuadrática o QAP [Quadratic Assignment Problem] es
un problema fundamental de optimización combinatoria con numerosas aplicaciones. El
problema se puede describir de la siguiente forma:

Supongamos que queremos decidir dónde construir n instalaciones (p.ej. fábricas) y
tenemos n posibles localizaciones en las que podemos construir dichas instalaciones. Conocemos las distancias que hay entre cada par de instalaciones y también el flujo de materiales que ha de existir entre las distintas instalaciones (p.ej. la cantidad de suministros que deben transportarse de una fábrica a otra). El problema consiste en decidir dónde construir cada instalación de forma que se minimize el coste de transporte de materiales.

Formalmente, si llamamos d(i, j) a la distancia de la localización i a la localización j y w(i, j) al peso asociado al flujo de materiales que ha de transportarse de la instalación i
a la instalación j, hemos de encontrar la asignación de instalaciones a localizaciones que minimice la función de coste:

![img]()

donde p() define una permutación sobre el conjunto de instalaciones.
Igual que en el problema del viajante de comercio, que se puede considerar un caso
particular del QAP, una solución para el problema es una permutación del conjunto de
instalaciones que indica dónde se debe construir cada una.

El problema de la asignación cuadrática es un problema habitual en Investigación
Operativa y, además de utilizarse para decidir la ubicación de plantas de producción,
también se puede utilizar como modelo para colocar los componentes electrónicos de un
circuito sobre una placa impresa o los módulos de un circuito integrado en la superficie de un microchip.

Por su interés teórico y práctico, existe una variedad muy amplia de algoritmos que
abordan la resolución del problema de la asignación cuadrática. Al ser un problema NP-completo, el diseño y aplicación de algoritmos exactos para su resolución no es viable cuando n es grande. Nos centraremos, por tanto, en el diseño de algoritmos evolutivos y evaluaremos su rendimiento sobre instancias concretas del problema.

# 2. Implementación y análisis de resultados

- **Implemente un algoritmo genético estándar** que resuelva el problema de la asignación cuadrática. Además de su implementación y una descripción del algoritmo genético utilizado (técnica de representación, mecanismo de selección, operadores de cruce y mutación...), debe proporcionar la permutación obtenida y el coste asociado a la misma para los distintos conjuntos de datos proporcionados. No olvide incluir los parámetros concretos utilizados en la ejecución de su algoritmo genético (tamaño de la población, número de generaciones necesario para obtener la solución encontrada, probabilidades de cruce y mutación, etc.).

- **Implemente una variante baldwiniana** de su algoritmo genético estándar, que in-
corpore técnicas de optimización local (p.ej. heurı́sticas greedy) para dotar a los
individuos de su población de capacidad de “aprendizaje”. Compare los resultados
obtenidos con respecto a los que obtuvo el algoritmo genético estándar.

  *NOTA:* En la variante baldwiniana del algoritmo genético, para evaluar el fitness de
cada individuo, se utiliza dicho individuo como punto inicial de una búsqueda local
(p.ej. ascensión de colinas por la máxima pendiente) hasta que se alcanza un óptimo
local. El valor de ese óptimo local determina el fitness del individuo. Sin embargo, a la hora de formar descendientes, se utiliza el material genético del individuo original (sin incluir las mejoras “aprendidas” al aplicar la técnica de búsqueda local).

- **Implemente una variante lamarckiana de su algoritmo genético estándar**, que in-
corpore técnicas de optimización local (p.ej. heurı́sticas greedy) para dotar a los
individuos de su población de capacidad de “aprendizaje” y permita que lo “apren-
dido” se pueda heredar directamente de padres a hijos. Compare los resultados
obtenidos con respecto a los que obtuvo con las variantes anteriores.

  *NOTA:* En la variante lamarckiana del algoritmo genético, el fitness de los individuos
se evalúa igual que en la variante baldwiniana, si bien ahora los descendientes de
un individuo se forman a partir de la solución mejorada que se consigue utilizando
técnicas de búsqueda local (esto es, los descendientes heredan los rasgos adquiridos
por sus padres en su proceso de “aprendizaje”).

  Realice un estudio comparativo de las tres variantes implementadas utilizando para
ello los conjuntos de datos de prueba que se proporcionan con este guión. Visualice
gráficamente los resultados de las distintas ejecuciones mostrando la evolución del
fitness de la mejor solución encontrada en cada generación. ¿Cómo se comportan
las distintas variantes en cuanto a la calidad de las soluciones obtenidas y al tiempo
necesario para obtenerlas?
