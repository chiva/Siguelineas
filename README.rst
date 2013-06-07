Siguelineas
===========

Robot de bajo coste seguidor de líneas basado en Arduino. Al disponer de módulo bluetooth, también es posible controlarlo de forma remota con un ordenador o dispositivo móvil.

.. image:: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/primerplano.jpg
   :align: left
   :target: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/big/primerplano.jpg
.. image:: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/seguidor.jpg
   :target: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/big/seguidor.jpg
.. image:: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/detectores.jpg
   :align: right
   :target: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/big/detectores.jpg
   
.. image:: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/bluetooth.jpg
   :align: left
   :target: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/big/bluetooth.jpg
.. image:: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/driver.jpg
   :target: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/big/driver.jpg
.. image:: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/encoder.jpg
   :align: right
   :target: https://raw.github.com/chiva/Siguelineas/master/documentacion/imagenes/big/encoder.jpg

En la carpeta ``documentacion`` encontrarás multitud de información sobre el proyecto, los datasheets de las partes utilizadas, la memoria o una presentación resumiendo los puntos principales.

Código
------

La programación está realizada en C++ de la forma más modular posible para facilitar la modificación de las funcionalidades. Los archivos se almacenan en la carpeta ``codigo``.

El sketch principal es el llamado ``robot`` y se apoya en el uso de las librerías dispuestas en la carpeta ``librerias``, que facilitan en gran medida la programación y el acceso a todas las capacidades de las que se ha dotado el robot.

La carpeta ``test`` incluye sketches para la comprobación individual de cada uno de los módulos utilizado y comprobar el correcto funcioamiento de la electrónica y montaje.

Esquemáticos
------------

En la carpeta ``esquematicos`` se encuentran los diagramas electrónicos y las PCBs, diseñadas en DipTrace.

El robot está formado por las siguientes placas:

- Principal: distribución de los pines del Arduino a las placas modulares
- Encoder de rueda: se instala pegado a las ruedas para con un detector de reflexión infrarroja detectar el movimiento de la rueda
- Driver de motores: aloja toda la electrónica de potencia para el movimiento de los motores
- Comunicaciones: sirve de base para el módulo bluetooth utilizado con la electrónica de adaptación de señales
- Detección de línea: integra los seis sensores de detección de línea que permite detectar su posición