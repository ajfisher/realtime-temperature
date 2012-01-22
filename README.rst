Introduction
============

Realtime Temperature is a BSD Licensed set of applications that utilises web sockets to interact with an Arduino microcontroller.

This project was originally designed for a talk At Linux Conferance Australia, 2012 on how to communicate between Arduino and the Web in real time so was a good example.

Installation
=============

You'll need the following dependencies (please see individual installation process for each project):

    * An arduino microcontroller (see http://arduino.cc ) - note Arduino 1.0 is required
    * Django (see http://www.djangoproject.com )
    * django-socketio (see https://github.com/stephenmcd/django-socketio)
    * websocket client (https://github.com/krohling/ArduinoWebsocketClient)
    
Assuming you have all of these set up, you can download and extract these project files to a directory or else just grab the latest from github::

    $ git git://github.com/ajfisher/realtime-temperature.git
    

General usage
===============

Django
------

You need to run the django socketio server. Please see django docs and django-socketio for specifics but here's the gist::

    $ python manage.py runserver_socketio addr:port
    
You'll then be able to browse to addr:port via your web browser of choice and you should see the server up and running. From the home page at / you'll be able to follow the demos and interactions.

Local Settings
..............

To make it easy to configure, you can edit the local_settings.py folder in the root. Each of the config settings is explained in the file and it should be pretty straight forward to change (it's just serial device paths etc).


Realtime temperature graphing
=============================

Arduino
--------

Build your temperature measuring circuit with ethernet capable Arduinos and load the sketch from rt_temperature_sensor.ino 

Note that you'll need to set the network settings appropriately in the header section of the sketch for your own needs.

Web
----

Run the django server as notes above, then browse to your server address. Once you see the graph starting then turn on / restart your sensors and you should start to see data being plotted.



