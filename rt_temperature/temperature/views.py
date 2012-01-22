from django.shortcuts import get_object_or_404, render, redirect
from django_socketio import events, broadcast, broadcast_channel

@events.on_subscribe(channel="tempvalues")
def subscribe_to_tempvalues(request, socket, context, channel):
    print "Subscribed to tempvalues"

@events.on_subscribe(channel="tempsensor")
def subscribe_to_tempsensor(request, socket, context, channel):
    print "Subscribed to tempsensor"
    
@events.on_message(channel="^tempsensor")
def get_temperature(request, socket, context, message):
    message = message[0]
    value = message["value"]
    sensor_id = message["sensor"]
    socket.send_and_broadcast_channel({"sensor": sensor_id, "value":value}, channel="tempvalues")
    

def home (request, template="index.html"):
    context = {}
    return render(request, template, context)
    
    
events.on_message.__call__()
