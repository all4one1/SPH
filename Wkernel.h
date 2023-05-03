#pragma once


#define wP6D2(r)		4.0*pow((H2-r*r),3)/(Pi*H8)
#define wP6D3(r)		(315.0/64.0)*pow((H2-r*r),3)/(Pi*H9)
#define wP6D2Grad(r)	-24.0*pow((H2-r*r),2)*r/(Pi*H8)  //отличается только знаком минус
#define wP6D3Grad(r)	-(945.0/32.0)*pow((H2-r*r),2)*r/(Pi*H9) //отличается только знаком минус
#define wP6D2Lapl(r)	-(48.0*(H2-r*r))*(H2-3.0*r*r)/(Pi*H8)
#define wP6D3Lapl(r)	-(945.0/32.0)*(H2-r*r)*(3.0*H2-7.0*r*r)/(Pi*H9) 

#define wSpikyD2(r)		10.0*pow((H-r),3)/(Pi*H5)
#define wSpikyD3(r)		15.0*pow((H-r),3)/(Pi*H6)
#define wSpikyD2Grad(r)	-30.0*pow((H-r),2)/(Pi*H5) //отличается только знаком минус
#define wSpikyD3Grad(r)	-45.0*pow((H-r),2)/(Pi*H6) //отличается только знаком минус
#define wSpikyD2Lapl(r)	-(30.0*(H-r))*(-3.0*r+H)/(Pi*H5*r)
#define wSpikyD3Lapl(r)	-(90.0*(H-r))*(-3.0*r+H)/(r*Pi*H6) 

#define wViscD2(r)		(10.0/3.0)*(-(0.5)*r*r*r/H3+r*r/H2+(0.5)*H/r-1.0)/(H2*Pi)
#define wViscD3(r)		(15.0/2.0)*(-(0.5)*r*r*r/H3+r*r/H2+(0.5)*H/r-1.0)/(H3*Pi)
#define wViscD2Grad(r)	(-10.0/3.0)*(-(1.5)*r*r/H3+2.0*r/H2-(0.5)*H/(r*r))/(H2*Pi) //не используется, добавил знак минус
#define wViscD3Grad(r)	(-15.0/2.0)*(-(1.5)*r*r/H3+2.0*r/H2-(0.5)*H/(r*r))/(H3*Pi) //не используется, добавил знак минус
//#define wViscD2Lapl(r)	(5.0/3.0)*(H4+8.0*H*r*r*r-9.0*r*r*r*r)/(H5*r*r*r*Pi) // !мой результат не совпадает 
#define wViscD2Lapl(r)  (20*(H-r))/(Pi*H5) //мой результат
#define wViscD3Lapl(r)	(45.0*(H-r))/(Pi*H6) 