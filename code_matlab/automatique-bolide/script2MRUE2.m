% Deuxième Version du Script Bolide

%% Système boucle ouverte et linéarisation

clear, clc
format short g

%% Paramètres du Système
% Masses
mw=0.1;
mb=1;
Ms=1.2;

% Distances
rho=0.07;
l=0.02;
d=0.015; % distance A-C

% Electriques
L=2.3e-3;
R=2.2;
% r;

% Couples
k=0.342;
% alpha=34.6;
% beta=2.06e5;

% Moments inertie A TROUVER
Iwy=2.45e-4;
Ipsi=1.53e-2;

% Constantes utilitaires
beta = (Ms + 2*Iwy/rho^2);
gamma = Ipsi + mb*d^2; 
alpha = 2/rho;
eta = l/rho;

%% Trajectoire d'équilibre
% Mouvement Rectiligne Uniforme selon axe x du laboratoire.
% On néglige les perturbations sur les entrées et les mesures.

% Références
ur = 1; %m/s
psir = 0;

% On fait le changement right,left (r,l) -> sum,dif (s,d)
% Somme des tensions gauche et droite
% Le "s" signifie "sum", on trouvera aussi "d"
% pour "difference"
Usbar = min([2*k/rho*ur; 12]); % should not be >12V

pbar = 0; % normally, should equals ubar*t, 
% but is not in state function, so any value fits.
ubar = ur;
psibar = psir;
vbar = 0;
Isbar = 0;
Idbar = 0;
ybar = 0;

statebar = [pbar; ubar; psibar; vbar; Isbar; Idbar; ybar];

%% Système de simulation en Simulink

%% Linéarisation (système complet)
% Entrées et sorties en sum,diff
% Etat=[p; u; psi; v; Isbar; Idbar; y], Entrée=[Us; Ud], 
% Sortie mesurée=[phis; phid; cLF]

% Fonction d'état
A = [0 1 0 0 0 0 0;
    0 0 0 0 1/beta*k/rho 0 0;
    0 0 0 1 0 0 0;
    0 0 0 1/gamma*mb*d*ubar 0 1/gamma*l*k/2/rho 0;
    0 -2*k/L/rho 0 0 -R/L 0 0;
    0 0 0 -k*l/L/rho 0 -R/L 0;
    0 0 ubar 0 0 0 0;];

% Entrée de commande
B = [0 0;
    0 0;
    0 0;
    0 0;
    1/L 0;
    0 1/L;
    0 0;];

% Entrée de perturbation

% Sortie mesurées
% phis (sum), phid (dif), cLF (capteur Line Follower)
C = [alpha 0 0 0 0 0 0;
    0 0 eta 0 0 0 0;
    0 0 0 0 0 0 1;];

% Influence des commandes
D = zeros(3,2);

% Influence des perturbations -> Dans Simulink
% Dd = zeros(3,2);

sys = ss(A,B,C,D);
set(sys,'InputName',{'dUs','dUd'},'OutputName',{'dphis','dphid','dcLF'});

figure(1), step(sys), grid
% phis augmente exponentiellement

sort(eig(A)) % 2 vp très rapides => simplification par perturbations singulières
fastEig = -R/L % ce sont les vp des courants

%% Optionnel: vérification du linéarisé avec SCD linearizer

%% Sous-système Lent Somme
% On a négligé Is par perturbation
% Etat=[p; u], Entrée=[Us], Sortie mesurée=[phis]

Qs = k/beta/rho/R;

ASum = [0 1;
    0 Qs*(-2*k/rho)];

BSum = [0;
    Qs];

CSum = [alpha 0];

DSum = [0];

sysSum = augstate(ss(ASum,BSum,CSum,DSum)); % Ajout de l'état à la sortie
set(sysSum,'InputName',{'dUs'},'OutputName',{'dphis','dp','du'});

figure(2), step(sysSum), grid
% Vitesse constante, p est une droite

%% Sous-système Lent Différence
% On a négligé Id par perturbation
% Etat=[psi; v; y], Entrée=[Ud], Sortie mesurée=[phid; cLF]

b1 = 1/gamma*mb*d*ubar;
b2 = 1/gamma*l*k/2/rho/R;

ADif = [0 1 0;
    0 (b1 + b2*(-k*l/rho)) 0;
    ubar 0 0];

BDif = [0;
    b2;
    0];

CDif = [eta 0 0;
    0 0 1];

DDif = [0;
    0];

sysDif = augstate(ss(ADif,BDif,CDif,DDif)); % Ajout de l'état à la sortie
set(sysDif,'InputName',{'dUd'},'OutputName',{'dphid','dcLF','dpsi','dv', ...
    'dy'});

figure(3), step(sysDif), grid
% Divergence au bout de t=65s

%% Les vp des sous-systèmes sont les vp du système lent complet
eigSys=sort(eig(A)) 
fastEig
eigSysSumOl = sort(eig(ASum))
eigSysDifOl = sort(eig(ADif))

%% Modèle de commande somme
sumEig = sort(eig(ASum));

% réglage PD idéal
w0 = 2*abs(sumEig(1)); % accélération facteur 2000
xi = 1/sqrt(2);
% Gains
h1 = w0^2/Qs/alpha;
h2 = 1/alpha*(-2*xi*w0/Qs + 2*k/rho);
h3 = h1;
sumEigDesired = roots([1 2*xi*w0 w0^2]);

% PD idéal
PDsum = [tf([-h2 h3],1) tf([h2 -h1], 1)];
set(PDsum,'InputName',{'dphisr','dphis'},'OutputName',{'dUs'})

%figure(4), bode(PDsum), grid


% PD approximé
Tds = h2/h1;
ns = 50; % à régler, augmente la sensibilité au bruit.

Ms = -ns;
Ns = [ns -ns];
Ps = h1*Tds*ns;
Qs = [h1*(1-Tds*ns) -h1*(1-Tds*ns)];

PDsumApprox = ss(Ms,Ns,Ps,Qs);
set(PDsumApprox,'InputName',{'dphisr','dphis'},'OutputName',{'dUs'})

% comparaison PD idéal/PD approximé
figure(41), bode(PDsum,PDsumApprox), grid, legend('ideal','approx')
% Espérons que notre approximation soit assez précise dans le domaine de
% fréquence de fonctionnement

% Vérification BF avec PDs idéal et approximés
% sys bouclé par PDsum a les valeurs propres désirées
sysSumBF = lft(PDsum,sysSum,1,1); % on boucle phis sur Us
eigSysSumBF = eig(sysSumBF) % ce qu'on a
sysSumBFApprox = lft(PDsumApprox,sysSum,1,1);
eigSysSumBFApprox = eig(sysSumBFApprox)
sumEigDesired % ce qu'on voulait
fastEig
% Les 2 sont << vp de Is donc hypothèse des perturbations singulières
% respectée


% Réponses des système Sum (Idéal et Approx) en Boucle Fermée
% Temporelle 
figure(5), step(sysSumBF), grid, title('RépTemp de sysSumBF')
figure(51), step(sysSumBF,sysSumBFApprox), grid, title('RépTemp de sysSumBF et sysSumBFApprox'), legend('ideal','approx')
figure(52), step(sysSumBFApprox), grid, title('RépTemp de sysSumBFApprox')
% Fréquentielle
figure(6), bode(sysSumBF), grid, title('RépFréq de sysSumBF')
% On regarde le transfert p/phisr
% Marge de phase=+inf° (Gain dans [-110,-60] donc jamais nul), 
% Marge de gain=+infdB (Phase dans [0.,90] donc jamais =-180° mod 360)
% Marges trop grandes -> robuste mais performances médiocres
figure(61), bode(sysSumBF,sysSumBFApprox), grid, title('RépFréq de sysSumBF et sysSumBFApprox'), legend('ideal','approx')


%% Modèle de commande diff

% réglage Contrôleur Idéal, PD sur phid, P sur cLF
sigma = 3; % à régler, réponse très lente.
% Gains
k1 = 1/b2/eta*sigma^2*sqrt(6);
k2 = 1/b2/eta*(-sigma*sqrt(6) - b1 + b2*k*l/rho);
k3 = k1;
k4 = sigma^3/ubar/b2;
k5 = k4;
difEigDesired = roots([1 sigma*sqrt(6) sigma^2*sqrt(6) sigma^3]);

% PD+D idéal
PDdif = [tf([-k2 k3],1) tf([k5],1) tf([k2 -k1],1) tf([-k4],1)];
set(PDdif,'InputName',{'dphidr','dcLFr','dphid','dcLF'},'OutputName', ...
    {'dUd'})

%figure(7), bode(PDdif), grid


% PD+P approximé
Tdd = k2/k1;
nd = 50;

Md = -nd;
Nd = [nd 0 -nd 0];
Pd = k1*Tdd*nd;
Qd = [k1*(1-Tdd*nd) k5 -k1*(1-Tdd*nd) -k5];

PDdifApprox = ss(Md,Nd,Pd,Qd);
set(PDdifApprox,'InputName',{'dphidr','dcLFr','dphid','dcLF'},'OutputName',{'dUd'})

% comparaison PD idéal/PD approximé
figure(71), bode(PDsum,PDdifApprox), grid, legend('ideal','approx')

% Vérification BF avec PD idéal
% sys bouclé par PDdif a les valeurs propres désirées
sysDifBF = lft(PDdif,sysDif,2,1); % on boucle phis sur Us
eigSysDifBF = eig(sysDifBF) % ce qu'on a
sysDifBFApprox = lft(PDdifApprox,sysDif,2,1);
eigSysDifBFApprox = eig(sysDifBFApprox)
difEigDesired % ce qu'on voulait
fastEig
% Les vp sont << vp de Id donc hypothèse des perturbations singulières
% respectée

% Réponses des systèmes Dif (Idéal et Approx) en Boucle Fermée
% Temporelle 
figure(8), step(sysDifBF), grid, title('RépTemp de sysDifBF')
figure(81), step(sysDifBF,sysDifBFApprox), grid, title('RépTemp de sysDifBF et sysDifBFApprox'), legend('ideal','approx')
% Fréquentielle
figure(9), bode(sysDifBF), grid, title('RépFréq de sysDifBF')
% On regarde le transfert y/cLF
% Marge de phase = entre 180° et 90°, grand -> robuste mais peu précis
% Marge de gain = 13dB confortable
figure(91), bode(sysDifBF,sysDifBFApprox), grid, title('RépFréq de sysDifBF et sysDifBFApprox'), legend('ideal','approx')




