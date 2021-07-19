## Diseño de la Aplicación Distribuida

### Descomposición y Mapeo
Para MPI, se piensa que la mejor forma de descomponer el trabajo es pasándole mapas completos, para que estos procesos se encarguen de modificarlos, a su vez en cada proceso, haciendo uso de OpenMP estos mapas están descompuestos en celdas dentro de una matriz aplanada.
El mapeo pensado para MPI es dinámico por lo que que le piensa pasar un solo mapa a cada proceso si este lo solicita. Para el mapeo de OMP se piensa que el mapeo estático es el adecuado, ya que conocemos el tamaño de la matriz y su contenido, además, el procesamiento de cada celda casi no varia.

Las ventajas respecto los demás mapeos es que para casos de prueba medianos y grandes, esta descomposición y mapeo es la mejor respecto las otras opciones.
En casos de prueba pequeños y muy pequeños, las dos tecnologías pueden tener un peor desempeño a una versión serial.

Por como está diseñado MPI, el proceso encargado de leer del archivo de datos es el proceso raíz, este proceso es el encargado de enviarle la información a los demás, en este caso los mapas. Los demás procesos reciben el mapa enviado por el proceso raíz y se encargan de procesarlo, este proceso se encarga de crear el nuevo mapa ya con el hechizo.
