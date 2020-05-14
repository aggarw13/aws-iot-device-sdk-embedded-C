# Source Files
APP_SRCDIR=.
MQTT_SRCDIR=../mqtt
SHADOW_SRCDIR=../shadow

SRCS+=$(wildcard $(APP_SRCDIR)/*.c)
SRCS+=$(wildcard $(MQTT_SRCDIR)/*.c)
SRCS+=$(wildcard $(SHADOW_SRCDIR)/*.c)

INCLUDE_DIRS+=-I .
INCLUDE_DIRS+=-I ../mqtt
INCLUDE_DIRS+=-I ../mqtt/private
INCLUDE_DIRS+=-I ../shadow
INCLUDE_DIRS+=-I ../shadow/private
INCLUDE_DIRS+=-I ../logging-framework

OBJS=$(SRCS:.c=.o)
EXE = app_1

CC=gcc
CFLAGS+=-std=c99 -Wall -O0 -ggdb -DENABLE_LOGGING

.DEFAULT_GOAL:=build

build: $(EXE)

clean:
	rm -rf $(APP_SRCDIR)/*.o $(MQTT_SRCDIR)/*.o $(SHADOW_SRCDIR)/*.o *~ $(EXE)

.PHONY: build test clean

$(EXE): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $(EXE) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $<  -o $@
