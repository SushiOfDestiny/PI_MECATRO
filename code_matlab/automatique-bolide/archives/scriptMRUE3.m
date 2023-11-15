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
L=1e-3;
R=1e6;
% r;

% Couples
k=1e-2;
% alpha=34.6;
% beta=2.06e5;

% Moments inertie
Iwy=2.45e-4;
Ipsi=1.53e-2;

% Utilitaire
beta = (M + 2*Iwy/rho^2);
gamma = Ipsi + mb*d^2; 

%% Nominal Equilibrium Point

% We command speed and angle
uref = 1; %m/s
psiref = 0;

Usbar = min([2*k/rho*uref; 12]); % should not be >12V

Urbar = Usbar/2; %right
Ulbar = Usbar/2;

pbar = 0; % is not in state function, any value fits
% normally, should equals ubar*t.
ubar = uref;
psibar = psiref;
vbar = 0;
irbar = 0;
ilbar = 0;
xbar = pbar;
ybar = 0;

statebar = [pbar; ubar; psibar; vbar; irbar; ilbar; xbar; ybar];




%% Linéarisation en MRU (système complet)

% base sum, diff
% Coefficients
a = [1
    k/beta/rho
    l*k/2/gamma/rho
    mb*d*ubar/gamma
    1/L
    -R/L
    -2*k/L/rho
    -k*l/L/rho
    -sin(psibar)*ubar
    cos(psibar)
    cos(psibar)*ubar
    sin(psibar)];

A = [0 a(1) 0 0 0 0 0 0;
    0 0 0 0 a(2) 0 0 0;
    0 0 0 a(1) 0 0 0 0;
    0 0 0 a(4) a(3) 0 0 0;
    0 a(7) 0 0 a(6) 0 0 0;
    0 0 0 a(8) 0 a(6) 0 0;
    0 a(10) a(9) 0 0 0 0 0;
    0 a(12) a(11) 0 0 0 0 0];


Bsd = [0 0; % for Us, Ud
    0 0;
    0 0;
    0 0;
    a(5) 0;
    0 a(5);
    0 0;
    0 0];

% Base changing matrix sum diff -> right left
Prd = [1 1;
        1 -1];

Brd = mtimes(Bsd, Prd); % Entries in base r,d

% Bd = 0;

sys = ss(A,Brd,eye(8),0);
set(sys,'InputName',{'dUr','dUl'},'OutputName',{'dp', 'du','dpsi','dv','dis','did', 'dx', 'dy'})

figure(1), step(sys), grid

eig(A) % eig in sum diff base, hard to interpretate

% Passage matrix s,d -> r,l for intensity
Pird = blkdiag(eye(4),Prd,eye(2));
Ard = mtimes(A,Pird);

eig(Ard)
% eigenvalues for intensities are high -> simplifiable
% some eigenvalues are null, because there is redonduncy with
% p,psi and x,y

