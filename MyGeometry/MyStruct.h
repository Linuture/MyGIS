#pragma once
#ifndef _MYSTRUCT_H_
#define _MYSTRUCT_H_

//������
typedef struct
{
	double x;//x����
	double y;//y����
}GPoint;

//������
typedef struct
{
	long  pointId;    //�����
	int   pointRadius; //��뾶
	int   pointType; //������
	COLORREF  pointColor; //�����ɫ
}GPointProperty;

#endif