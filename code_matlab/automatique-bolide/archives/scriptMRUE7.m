% Design du contrôleur sur le système de commande

%% Système boucle ouverte et linéarisation
run('scriptMRUE6.m')
close all

% bonne réponse "standard" en poursuite et en rejet
omega0 = 60;
ksi = 1/sqrt(2);
goodPoursuite = tf(1,[1 ksi*omega0 omega0^2]);

% comparaison des réponses temporelles
figure(1), step(goodPoursuite,goodPoursuite), grid, legend('Location','best')
% Stabilisation en 0.25s, dépassement de peu

%% contrôleur PD sur système Sum pour "bonne poursuite"

K1 = omega0^2/dds/alphaalpha;
K2 = (-a - ksi*omega0)/dds/alphaalpha;
K3 = K1;
