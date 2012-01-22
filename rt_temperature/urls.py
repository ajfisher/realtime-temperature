from django.conf.urls.defaults import patterns, include, url

urlpatterns = patterns('',
    url("^$", "temperature.views.home"),
    url("", include("django_socketio.urls")),
)
