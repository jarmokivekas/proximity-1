
# Proximity-1

This repository contains notes for implementing a proximity-1 stack. They are mostly in the form of almost syntactically correct c++ source files and mixed snippets of working code in Jupyter notebooks. Most, if not all, information in this repository is based on the 2013 releases of the CCSDS blue books on proximity-1.

## Rationale

This project is the result of going too far off on a tangent during a literature review, which was supposed to be on topics related to geodesy. The thought process went from geodesy to planetary science, to mars research, to Mars landers, to lander communication system. Still almost on topic.

## Proximity-1 protocol



Proximity-1 is a communications protocol that used my mars orbiter, landers, and satellites. The recommendations standard for the protocol is published by CCSDS, The Consultative Committee for Space Data Systems.

The standard defines a complete stack, including directives on modulation types on the physical layer, a coding and synchronization layer, data link layer. As far a complete communications systems go, proximity-1 is more complicated than for example most amateur radio systems, giving it robustness, but also simple enough to be implemented on resource-constrained microcontroller platforms.



# REQUIREMENTS LIST

Item	|Description	| Reference 					| Status | Support
--------|---------------|-------------------------------|--------|--------
1		|PLTU structure: ASM, V3 Transfer Frame, CRC	| 3.2 	| M |
2		|Idle data										| 3.3	| M |
3		|Coding option: uncoded data					| 3.4 	| O.1 |
4		|Coding option: convolutional					| 3.4.3 | O.1 |
5		|Coding option: LDPC							| 3.4.4, 3.4.5 | O.1 |
6		|Time tag support								| 3.5.6, 3.6.8 | O |
7		|Handling of invalid received frames			| 3.6.6 | M  |
