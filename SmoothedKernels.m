clear all, close all, clc
pkg load symbolic;
syms r h;
Wpoly6=(h^2-r^2)^3;
Wspily=(h-r)^3;
Wvicosity=-r^3/(2*h^3)+r^2/h^2+h/(2*r)-1;

hold on;

#Kpoly6=1/(2*pi*int(r*Wpoly6,r, 0, h)); #case 2d
#Kspily = 1/(2*pi*int(r*Wspily,r,0,h)); #case 2d
#Kviscosity = 1/(2*pi*int(r*Wvicosity,r, 0, h)); #case 2d

Kpoly6=1/(2*pi*2*int(r^2*Wpoly6, r, 0, h)); #case 3d
Kspily = 1/(2*pi*2*int(r^2*Wspily,r,0,h)); #case 3d
Kviscosity = 1/(2*pi*2*int(r^2*Wvicosity,r, 0, h)); #case 3d

W = Kpoly6*Wpoly6
Grad_W = -gradient(W, r)
#Laplac_W = (laplacian(W, r)); не правильно вычисляет, хз
#Laplac_W = simplify((diff(r*diff(W,r),r))/r) #2d
Laplac_W = simplify((diff(r^2*diff(W,r),r))/r^2) #3d


W_spily = Kspily*Wspily
Grad_W_spily = -gradient(W_spily, r)
#Laplac_W_spily = simplify(laplacian(W_spily, r)); не правильно вычисляет, хз
#Laplac_W_spily = simplify((diff(r*diff(W_spily,r),r))/r) #2d
Laplac_W_spily = simplify((diff(r^2*diff(W_spily,r),r))/r^2) #3d

W_viscosity = (Kviscosity*Wvicosity)
W_viscosity_h=subs(W_viscosity,r,h)==0; #true
Grad_W_viscosity = -gradient(W_viscosity, r)
Grad_W_viscosity_h=subs(Grad_W_viscosity, r,h)==0; #true
#Laplac_W_viscosity = simplify(laplacian(W_viscosity, r)) не правильно вычисляет, хз
#Laplac_W_viscosity = simplify((diff(r*diff(W_viscosity,r),r))/r) #2d
Laplac_W_viscosity = simplify((diff(r^2*diff(W_viscosity,r),r))/r^2) #3d



h = double(1);
#ezplot(subs(W), [-1,1])
ezplot(subs(subs(W_spily), r, abs(r)), [-1,1])
#ezplot(subs(subs(W_viscosity),r,abs(r)), [-1,1])


#Grad_W_h1 = subs(Grad_W);
Grad_W_spily_h1 = subs(Grad_W_spily);
#Grad_W_visc_h1 = subs(Grad_W_viscosity);

#ezplot(subs(Grad_W_h1, r, abs(r)), [-1,1])
ezplot(subs(Grad_W_spily_h1, r, abs(r)), [-1,1])
#ezplot(subs(Grad_W_visc_h1, r, abs(r)), [-1,1])


#Laplac_W_h1 = simplify(subs(Laplac_W));
Laplac_W_spily_h1 = simplify(subs(Laplac_W_spily));
#Laplac_W_visc_h1 = simplify(subs(Laplac_W_viscosity));

#ezplot(Laplac_W_h1, [-1, 1])
ezplot(subs(Laplac_W_spily_h1, r,abs(r)), [-1, 1])
#ezplot(subs(subs(Laplac_W_visc_h1), r,abs(r)), [-1, 1])


leg = legend( {'W', 'GradientW', 'LaplacianW'} );
set(leg, 'location', 'eastoutside' );      % set the location
set( leg, 'fontsize', 16 );  % set the font size
set( leg, 'orientation', 'vertical' );     % set the orientation
title( '' );
grid on;
axis([-1 1 -5 5]);

