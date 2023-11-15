% Système boucle ouverte et linéarisation

clear, clc
format short g

%% True Parameters
% Masses
mw=0.1;
mb=1;
M=1.2;

% Distances
rho=0.07;
l=0.02;
d=0.015; % distance A-C

% Electriques
L=0.05;
R=1e6;
% r;

% Couples
k=2.63e4;
% alpha=34.6;
% beta=2.06e5;

% Moments inertie
Iwy=2.45e-4;
Ipsi=1.53e-2;

% Utilitaire
beta = (M + 2*Iwy/rho^2);
gamma = Ipsi + mb*d^2; 

%% Nominal Equilibrium Point
Ubar = 12;

ubar = rho/2/k*Ubar; % m/s
psibar = 0;
vbar = 0;

% base right, left
irbar = 0;
ilbar = 0;
statebar = [ubar; psibar; vbar; irbar; ilbar];

% base sum, diff
isbar = 0;
idbar = 0;
statebar = [ubar; psibar; vbar; isbar; idbar];



%% Linéarisation (système complet)

% base sum, diff
A = [0 0 0 k/beta/rho 0;
    0 0 1 0 0;
    0 0 mb*d*rho*Ubar/2/gamma/k l*k/2/gamma/rho 0;
    -2*k/L/rho 0 0 -R/L 0;
    0 0 -k*l/L/rho 0 -R/L];

B = [0 0;
    0 0;
    0 0;
    1/L 0;
    0 1/L];

% Coefficients
alpha1 = -A(1,4)
alpha2 = -A(2,3)
alpha3 = -A(3,3)
alpha4 = -A(3,4)
alpha5 = A(4,1)
alpha6 = A(4,4)
alpha7 = A(5,3)

% Bd = 0;

sys = ss(A,B,eye(5),0);
set(sys,'InputName',{'dUs','dUd'},'OutputName',{'du','dpsi','dv','dis','did'})

figure(1), step(sys), grid

sort(eig(A)) % 3 vp très négatives, 1 vp nulle, 1 vp > 0 faible donc non stable

%% Optionnel: vérification du linéarisé avec SCD linearizer

