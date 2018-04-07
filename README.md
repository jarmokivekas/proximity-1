
# Proximity-1

This repository contains notes for implementing a proximity-1 stack. They are mostly in the form of almost syntactically correct c++ source files and mixed snippets of working code in Jupyter notebooks. Most, if not all, information in this repository is based on the 2013 releases of the CCSDS blue books on proximity-1.

## Rationale

This project is the result of going too far off on a tangent during a literature review, which was supposed to be on topics related to geodesy. The thought process went from geodesy to planetary science, to mars research, to Mars landers, to lander communication system. Still almost on topic.

## Proximity-1 protocol



Proximity-1 is a communications protocol that used my mars orbiter, landers, and satellites. The recommendations standard for the protocol is published by CCSDS, The Consultative Committee for Space Data Systems.

The standard defines a complete stack, including directives on modulation types on the physical layer, a coding and synchronization layer, data link layer. As far a complete communications systems go, proximity-1 is more complicated than for example most amateur radio systems, giving it robustness, but also simple enough to be implemented on resource-constrained microcontroller platforms.

# Radio layer

Bits are encoded as NRZ (no return to zero natural binary) or "Bi-phase-L," aka. Manchester encoding.
Manchester requires typically 2x the bandwidth given the same data rate.


# Common implementation methodology for bit field data structures

The Proximity-1 protocol stack utilizes a lot of data structures made up of bit fields at a fixed offset. At least in:

- SPDU
- transfer fame header
- PULT


## Non-mutability

The is little reason to mutate messages on any level of the communication stack. Objects representing various parts of a data packet can be declared with constant data members. This is to say, that the messages are only either read from when receiving a message or built from the ground up when transmitting a new one. Therefore all classes have two constructors, one that expects a buffer as the argument, and one that either initialize all field values to reasonable defaults, or requires the user to supply initialization values.

A basic pattern would look something like this:

```
class Some_protocol_element{

public:
    /
    Some_protocol_element(uint8_t *buffer):
    Some_protocol_element(uint8_t fieldA, uint8_t fieldB)
    uint8_t *as_buffer()

}
```


## Naming conventions

The naming conventions used in the source code should match the names referred to in the specification of the protocol; in this case the CCSDS Blue Book. The object-oriented interfaces to various data structures have been designed in a way to keep a balance between readability and similarity between names in code and the specification.
