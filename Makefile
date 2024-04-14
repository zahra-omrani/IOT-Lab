CONTIKI_PROJECT = hello-world
TARGET ?= nrf52840

all: $(CONTIKI_PROJECT)

CONTIKI = ../..
include $(CONTIKI)/Makefile.include

run: $(CONTIKI_PROJECT).$(TARGET)
	$(RUNNER) $(TARGET)$(EXTENSION)

