Siguelineas
===========

Robot de bajo coste seguidor de l�neas basado en Arduino. Al disponer de m�dulo bluetooth, tambi�n es posible controlarlo de forma remota con un ordenador o dispositivo m�vil.

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

En la carpeta ``documentacion`` encontrar�s multitud de informaci�n sobre el proyecto, los datasheets de las partes utilizadas, la memoria o una presentaci�n resumiendo los puntos principales.

C�digo
------

La programaci�n est� realizada en C++ de la forma m�s modular posible para facilitar la modificaci�n de las funcionalidades. Los archivos se almacenan en la carpeta ``codigo``.

El sketch principal es el llamado ``robot`` y se apoya en el uso de las librer�as dispuestas en la carpeta ``librerias``, que facilitan en gran medida la programaci�n y el acceso a todas las capacidades de las que se ha dotado el robot.

La carpeta ``test`` incluye sketches para la comprobaci�n individual de cada uno de los m�dulos utilizado y comprobar el correcto funcioamiento de la electr�nica y montaje.

Esquem�ticos
------------

En la carpeta ``esquematicos`` se encuentran los diagramas electr�nicos y las PCBs, dise�adas en DipTrace.

El robot est� formado por las siguientes placas:

- Principal: distribuci�n de los pines del Arduino a las placas modulares
- Encoder de rueda: se instala pegado a las ruedas para con un detector de reflexi�n infrarroja detectar el movimiento de la rueda
- Driver de motores: aloja toda la electr�nica de potencia para el movimiento de los motores
- Comunicaciones: sirve de base para el m�dulo bluetooth utilizado con la electr�nica de adaptaci�n de se�ales
- Detecci�n de l�nea: integra los seis sensores de detecci�n de l�nea que permite detectar su posici�n