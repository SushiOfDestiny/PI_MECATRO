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

% Pour sorties
alphaalpha = 2/rho;


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
isbar = irbar + ilbar;
idbar = irbar - ilbar;
xbar = pbar;
ybar = 0;

%% sous système 1 (sum)
sumstatebar = [pbar; ubar; xbar; isbar];
difstatebar = [psibar; vbar; ybar; idbar];



%% Linéarisation en MRU (système complet)

% base sum, diff
% Sous système 1: Sum, sans x ni is
a = -2*k^2/beta/rho^2/R;
b = -2*k*rho/L;
c = -R/L;
dds = k*beta/rho/R;
ees = 1/L;

f = (-k^2*l^2/2/gamma/rho^2/R + mb*d*ubar/gamma);
g = l*k*rho/L;
ddd = l*k/2/gamma/R/rho;
eed = 1/L;

As = [0 1;
    0 a];
Bs = [0;
    dds];

% Sous système 2: Dif, sans i-
Ad = [0 1 0;
    0 f 0;
    ubar 0 0];
Bd = [0;
    ddd;
    0];

sys = augstate(ss(As,Bs,eye(2),zeros(2,1)));
set(sys,'InputName',{'dUs'},'OutputName',{'dp', 'du'})
figure(1), step(sys), grid
eig(As)

sys = ss(Ad,Bd,eye(3),0);
set(sys,'InputName',{'dUd'},'OutputName',{'dpsi', 'dv','dy','did'})
figure(2), step(sys), grid
eig(Ad)

% Dans les 2 cas on a bien une valeur propre très négative, et 2
% approximativement nulles.
