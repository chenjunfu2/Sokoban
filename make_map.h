#pragma once

#ifndef _make_map
#define _make_map

#include <fstream>
#include <iostream>

#include "error.h"

#define MAX_MAP 20
#define MAP_X 16
#define MAP_Y 15

//地图表现形式	0：空地"  "		1：墙壁■		2：人♀		3：箱子□		4：目的地☆○		5：箱子在目的地★●		6：人在目的地♀

//示范地图
static const int map[MAX_MAP][MAP_Y][MAP_X] = {
{
	{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},//1
	{0,0,0,1,4,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,3,1,1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,0,0,3,0,4,1,0,0,0,0,0,0},
	{1,4,0,3,0,2,1,1,1,1,0,0,0,0,0,0},
	{1,1,1,1,1,3,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,4,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0},//10
	{0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0},
	{1,1,1,3,3,3,0,1,0,0,0,0,0,0,0,0},
	{1,2,0,3,4,4,0,1,0,0,0,0,0,0,0,0},
	{1,0,3,4,4,4,1,1,0,0,0,0,0,0,0,0},
	{1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},//15
	{1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
	{1,0,3,0,3,3,0,1,0,0,0,0,0,0,0,0},
	{1,4,4,4,4,4,4,1,0,0,0,0,0,0,0,0},
	{1,0,3,3,0,3,0,1,0,0,0,0,0,0,0,0},
	{1,1,1,0,2,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},//20
	{1,4,4,3,4,4,1,0,0,0,0,0,0,0,0,0},
	{1,4,4,1,4,4,1,0,0,0,0,0,0,0,0,0},
	{1,0,3,3,3,0,1,0,0,0,0,0,0,0,0,0},
	{1,0,0,3,0,0,1,0,0,0,0,0,0,0,0,0},
	{1,0,3,3,3,0,1,0,0,0,0,0,0,0,0,0},
	{1,0,0,1,2,0,1,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},//25
	{0,1,1,1,1,1,4,0,0,0,1,0,0,0,0,0},
	{0,1,0,0,1,4,4,1,1,0,1,0,0,0,0,0},
	{0,1,0,0,3,4,4,0,0,0,1,0,0,0,0,0},
	{0,1,0,0,1,0,4,1,0,1,1,0,0,0,0,0},
	{1,1,1,0,1,1,3,1,0,0,1,0,0,0,0,0},
	{1,0,3,0,0,0,0,3,3,0,1,0,0,0,0,0},
	{1,0,1,3,1,0,0,1,0,0,1,0,0,0,0,0},
	{1,2,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
	{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0},//30
	{1,1,1,0,0,0,4,0,0,0,0,1,0,0,0,0},
	{1,0,0,0,1,1,3,1,1,0,0,1,0,0,0,0},
	{1,0,2,3,4,0,4,0,4,3,1,1,0,0,0,0},
	{1,1,0,3,1,1,3,1,1,0,1,0,0,0,0,0},
	{0,1,0,0,0,0,4,0,0,0,1,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},//35
	{1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
	{1,0,1,0,3,0,3,0,1,0,0,0,0,0,0,0},
	{1,0,0,5,4,1,0,0,1,0,0,0,0,0,0,0},
	{1,1,0,1,4,2,4,1,1,0,0,0,0,0,0,0},
	{1,1,3,1,1,1,5,1,1,1,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{1,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0},//40
	{1,0,2,0,1,1,1,1,1,1,1,1,0,0,1,0},
	{1,1,0,3,0,0,0,0,0,0,0,3,0,0,1,0},
	{0,1,0,1,0,1,0,0,1,1,1,1,0,0,1,0},
	{0,1,0,0,3,0,0,0,1,1,1,1,3,1,1,0},
	{0,1,3,0,1,1,0,1,0,3,0,3,0,1,0,0},
	{1,1,0,3,0,0,3,1,0,0,0,0,0,1,0,0},
	{1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0},
	{1,0,0,0,1,1,1,1,1,3,1,1,1,1,0,0},
	{1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0},
	{0,0,0,0,1,4,4,4,0,0,3,0,1,0,0,0},
	{0,0,0,0,1,4,4,4,4,1,0,0,1,0,0,0},
	{0,0,0,0,1,4,4,4,4,1,1,1,1,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},//45
	{0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0},
	{0,0,0,0,0,0,1,0,3,3,0,0,0,0,1,0},
	{1,1,1,1,1,1,1,3,1,0,0,1,0,0,1,0},
	{1,0,0,1,4,0,4,4,0,1,1,1,3,1,1,0},
	{1,0,0,1,4,1,5,4,3,0,0,0,0,0,1,0},
	{1,0,0,1,4,1,4,5,1,0,1,0,0,0,1,0},
	{1,0,3,3,4,4,4,4,1,0,1,1,1,1,1,0},
	{1,0,2,3,0,1,0,1,1,0,1,0,0,0,0,0},
	{1,0,3,3,3,1,0,0,0,0,1,0,0,0,0,0},
	{1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0},//50
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0},
	{1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0},
	{1,0,3,0,3,0,3,0,3,0,0,0,1,0,0,0},
	{1,0,1,4,1,4,1,4,1,0,3,1,1,0,0,0},
	{1,4,4,4,4,4,4,4,0,2,0,1,0,0,0,0},
	{1,0,1,0,1,0,1,0,1,3,1,1,1,0,0,0},
	{1,0,3,0,3,0,3,0,3,0,0,0,1,0,0,0},
	{1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},//55
	{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
	{1,0,3,2,3,3,3,3,3,0,1,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
	{1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,1,4,0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,1,4,0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,1,4,4,4,1,0,0,0,0,0,0,0,0},
	{0,0,0,1,4,0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0},//60
	{1,4,4,1,1,1,1,1,1,1,1,4,4,1,0,0},
	{1,5,4,5,4,4,4,4,4,5,4,5,4,1,0,0},
	{1,0,3,0,3,0,3,0,3,0,3,0,3,1,0,0},
	{1,3,0,3,0,3,2,3,0,3,0,3,0,1,0,0},
	{1,0,3,0,3,0,3,0,3,0,3,0,3,1,0,0},
	{1,3,0,3,0,3,0,3,0,3,0,3,0,1,0,0},
	{1,4,5,4,5,4,4,4,4,4,5,4,5,1,0,0},
	{1,4,4,1,1,1,1,1,1,1,1,4,4,1,0,0},
	{1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},//65
	{1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{1,0,0,0,1,3,1,3,0,1,0,0,0,0,0,0},
	{1,0,3,3,0,0,4,3,4,1,0,0,0,0,0,0},
	{1,0,2,1,1,1,4,4,4,1,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},//70
	{0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0},
	{1,1,1,1,1,5,1,1,0,0,1,1,0,0,0,0},
	{1,0,0,0,4,4,4,0,0,0,1,0,0,0,0,0},
	{1,0,1,0,1,5,1,1,1,3,1,1,0,0,0,0},
	{1,0,3,0,0,0,0,3,0,0,0,1,0,0,0,0},
	{1,1,1,1,1,2,0,1,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},//75
	{1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0},
	{1,0,0,0,0,3,0,0,0,3,0,1,0,0,0,0},
	{1,0,0,3,1,3,1,1,0,0,0,1,0,0,0,0},
	{1,1,1,0,1,4,5,4,0,1,1,1,0,0,0,0},
	{0,0,1,0,4,4,4,0,2,1,0,0,0,0,0,0},
	{0,0,1,1,0,1,3,1,1,1,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},//80
	{0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0},
	{0,0,0,0,0,1,0,0,3,3,0,1,0,0,0,0},
	{1,1,1,1,1,1,0,3,1,0,0,1,0,0,0,0},
	{1,4,4,4,1,1,1,0,1,0,0,1,1,0,0,0},
	{1,4,0,0,1,0,0,3,0,1,0,0,1,0,0,0},
	{1,4,0,0,0,0,3,0,3,0,3,0,1,0,0,0},
	{1,4,0,0,1,0,0,3,0,1,0,0,1,0,0,0},
	{1,4,4,4,1,1,1,0,1,0,0,1,1,0,0,0},
	{1,1,1,1,1,1,0,3,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,1,0,2,1,0,0,1,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0},//85
	{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,1,0,0,3,1,3,1,0,1,0,0},
	{0,1,1,1,1,1,1,0,0,1,0,3,0,1,0,0},
	{0,1,0,0,0,1,0,3,0,0,3,0,0,1,0,0},
	{1,1,0,3,0,0,0,0,0,1,1,1,0,1,0,0},
	{1,0,0,0,1,3,1,1,1,1,0,0,0,1,0,0},
	{1,0,0,0,0,3,0,1,1,1,0,1,1,1,0,0},
	{1,1,1,1,1,4,4,0,2,1,0,1,1,0,0,0},
	{0,0,0,1,4,4,4,3,0,3,3,0,1,0,0,0},
	{0,0,0,1,4,4,4,1,0,0,0,0,1,0,0,0},
	{0,0,0,1,4,4,4,1,1,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0},//90
	{0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,1,0,3,0,3,0,1,1,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,4,4,1,1,1,1,1,0},
	{1,1,1,1,1,1,4,4,5,4,0,0,3,0,1,0},
	{1,0,0,3,2,3,4,4,4,4,1,3,3,0,1,0},
	{1,0,0,0,3,0,1,3,1,1,1,0,0,0,1,0},
	{1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0},//95
	{0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0},
	{1,1,1,0,1,3,0,0,3,0,1,1,1,1,0,0},
	{1,0,0,3,0,0,1,1,4,4,1,0,0,1,1,1},
	{1,0,1,0,0,3,0,1,4,4,3,0,3,0,0,1},
	{1,0,3,3,0,0,3,1,4,4,0,0,1,0,0,1},
	{1,1,0,0,1,0,0,4,4,4,1,3,0,0,0,1},
	{0,1,3,0,2,0,1,4,4,4,1,0,3,0,0,1},
	{0,1,0,0,0,0,1,4,4,4,3,0,0,0,1,1},
	{0,1,0,1,1,3,0,1,1,1,0,0,0,1,1,0},
	{0,1,0,0,0,3,0,0,0,0,0,1,1,1,0,0},
	{0,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0},//100
	{0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0},
	{0,0,0,0,1,1,0,0,3,1,1,0,0,1,0,0},
	{0,0,0,0,1,0,0,1,0,0,0,3,0,1,0,0},
	{0,0,0,0,1,0,1,0,0,1,0,1,0,1,0,0},
	{0,0,0,0,1,0,3,0,3,0,0,3,0,1,0,0},
	{1,1,1,1,1,1,1,0,1,3,1,0,0,1,0,0},
	{1,0,0,3,0,3,0,0,0,0,0,0,1,1,0,0},
	{1,2,4,4,3,0,5,5,4,1,1,1,1,0,0,0},
	{1,1,4,4,4,4,4,4,1,1,1,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
}
};
//示范地图对应地图符号
static const char map_f[MAX_MAP][7][3] =
{
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
	{ "  ","■","♀","□","○","●","♀" },
	{ "  ","■","♂","□","☆","★","♂" },
};
/*
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
},
*/

extern inline bool open_map_m(std::fstream& fout_a);
extern inline void close_map_fout(std::fstream& fout_a);
extern inline bool description(std::fstream& fout_a);
extern inline bool checkpoint(std::fstream& fout_a);



extern inline ERR make_map(void);

#endif