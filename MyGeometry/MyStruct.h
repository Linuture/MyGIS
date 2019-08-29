#pragma once
#ifndef _MYSTRUCT_H_
#define _MYSTRUCT_H_

//点坐标
typedef struct
{
	double x;//x坐标
	double y;//y坐标
}GPoint;

//点属性
typedef struct
{
	long  pointId;    //点序号
	int   pointRadius; //点半径
	int   pointType; //点类型
	COLORREF  pointColor; //点的颜色
}GPointProperty;

#endif