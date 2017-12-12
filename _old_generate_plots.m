%
%   Generate Some Nice Plots for my transpalette
%
clear all
close all
clc

FontSize= 18;


%
% CSV formatted as follows:
%  
%         NCC,NSC2,NSC3,NSC5,NN,P-BP,P-MSE
% line1:  scores on original  data
% line2:  execution times on original data
% line3:  scores on pca data
% line4:  execution times on pca data
%
performance_MNIST = dlmread('scores_and_times_MNIST.csv', ',');
performance_ORL = dlmread('scores_and_times_ORL.csv', ',');

%
% CSV formatted as follows:
%  
% line1: Labels
% line2: Dimension 1
% line3: Dimension 2

data_pca_MNIST = dlmread('/path/to/pca_data_MNIST',',');
data_pca_ORL = dlmread('/path/to/pca_data_ORL',',');


%% Performance Bar Plots
% Original Data
fig_MNIST = figure('units','normalized','outerposition',[0 0 1 1]);
c = {'NC','NSC2','NSC3','NSC5','NN','P-BP','P-MSE'};
bar(performance_MNIST(1,:))
barvalues;
ylim([0 120]);
set(gca,'xticklabel',c)
set(gca,'FontSize',FontSize);
ylabel('Success Rate [%]','FontSize',FontSize)
grid on


fig_ORL = figure('units','normalized','outerposition',[0 0 1 1]);
c = {'NC','NSC2','NSC3','NSC5','NN','P-BP','P-MSE'};
bar(performance_ORL(1,:))
barvalues;
ylim([0 120]);
set(gca,'xticklabel',c)
set(gca,'FontSize',FontSize);
ylabel('Success Rate [%]','FontSize',FontSize)
grid on

% PCA Data
fig_MNIST_pca = figure('units','normalized','outerposition',[0 0 1 1]);
c = {'NC','NSC2','NSC3','NSC5','NN','P-BP','P-MSE'};
bar(performance_MNIST(3,:))
barvalues;
ylim([0 120]);
set(gca,'xticklabel',c)
set(gca,'FontSize',FontSize);
ylabel('Success Rate [%]','FontSize',FontSize)
grid on


fig_ORL_pca = figure('units','normalized','outerposition',[0 0 1 1]);
c = {'NC','NSC2','NSC3','NSC5','NN','P-BP','P-MSE'};
bar(performance_ORL(3,:))
barvalues;
ylim([0 120]);
set(gca,'xticklabel',c)
set(gca,'FontSize',FontSize);
ylabel('Success Rate [%]','FontSize',FontSize)
grid on







%% Performance  Plots
fig_performance = figure('units','normalized','outerposition',[0 0 1 1]);

h=semilogy(performance_MNIST(1,:),performance_MNIST(2,:),'x',...
         performance_ORL(1,:),performance_ORL(2,:),'o');
lgd = legend('MNIST','ORL','Location','NW');
lgd.FontSize = FontSize;
l = {'NC','NSC2','NSC3','NSC5','NN','P-BP','P-MSE'};
labelpoints(performance_MNIST(1,:),performance_MNIST(2,:),l,'N','FontSize',FontSize);
labelpoints(performance_ORL(1,:),performance_ORL(2,:),'N','FontSize',FontSize);
set(h(1),'MarkerSize',12,'Linewidth',3);
set(h(2),'MarkerSize',12,'Linewidth',3);
set(gca,'FontSize',FontSize);
ylabel('Execution Time [ms]','FontSize',FontSize)
xlabel('Success Rate [%]','Fontsize',FontSize)
grid on

fig_performance_pca = figure('units','normalized','outerposition',[0 0 1 1]);

h=semilogy(performance_MNIST(3,:),performance_MNIST(4,:),'x',...
         performance_ORL(3,:),performance_ORL(4,:),'o');
lgd = legend('MNIST','ORL','Location','NW');
lgd.FontSize = FontSize;
l = {'NC','NSC2','NSC3','NSC5','NN','P-BP','P-MSE'};
labelpoints(performance_MNIST(3,:),performance_MNIST(4,:),l,'N','FontSize',FontSize);
labelpoints(performance_ORL(3,:),performance_ORL(4,:),'N','FontSize',FontSize);
set(h(1),'MarkerSize',12,'Linewidth',3);
set(h(2),'MarkerSize',12,'Linewidth',3);
set(gca,'FontSize',FontSize);
ylabel('Execution Time [ms]','FontSize',FontSize)
xlabel('Success Rate [%]','Fontsize',FontSize)
grid on

%% PCA Data Plots

% MNIST
for i =1:10
    % Split data into classes
    idx = find(data_pca_MNIST(1,:) == i-1);
    s{i} = data_pca_MNIST(2:3,idx);
end
fig_mnist_pca = figure('units','normalized','outerposition',[0 0 1 1]);
plot(s{1}(1,:),s{1}(2,:),'+',...
    s{2}(1,:),s{2}(2,:),'o',...
    s{3}(1,:),s{3}(2,:),'*',...
    s{4}(1,:),s{4}(2,:),'.',...
    s{5}(1,:),s{5}(2,:),'x',...
    s{6}(1,:),s{6}(2,:),'s',...
    s{7}(1,:),s{7}(2,:),'d',...
    s{8}(1,:),s{8}(2,:),'^',...
    s{9}(1,:),s{9}(2,:),'v',...
    s{10}(1,:),s{10}(2,:),'>');
grid on

% ORL
for i =1:40
    idx = find(data_pca_ORL(1,:) == i);
    s{i} = data_pca_ORL(2:3,idx);
end
fig_orl_pca = figure('units','normalized','outerposition',[0 0 1 1]);

plot(s{1}(1,:),s{1}(2,:),'+',...
    s{2}(1,:),s{2}(2,:),'o',...
    s{3}(1,:),s{3}(2,:),'*',...
    s{4}(1,:),s{4}(2,:),'.',...
    s{5}(1,:),s{5}(2,:),'x',...
    s{6}(1,:),s{6}(2,:),'s',...
    s{7}(1,:),s{7}(2,:),'d',...
    s{8}(1,:),s{8}(2,:),'^',...
    s{9}(1,:),s{9}(2,:),'v',...
    s{10}(1,:),s{10}(2,:),'<',...
    s{11}(1,:),s{11}(2,:),'>',...
    s{12}(1,:),s{12}(2,:),'p',...
    s{13}(1,:),s{13}(2,:),'h',...
    s{14}(1,:),s{14}(2,:),'+',...
    s{15}(1,:),s{15}(2,:),'o',...
    s{16}(1,:),s{16}(2,:),'*',...
    s{17}(1,:),s{17}(2,:),'.',...
    s{18}(1,:),s{18}(2,:),'x',...
    s{19}(1,:),s{19}(2,:),'s',...
    s{20}(1,:),s{20}(2,:),'d',...
    s{21}(1,:),s{21}(2,:),'^',...
    s{22}(1,:),s{22}(2,:),'v',...
    s{23}(1,:),s{23}(2,:),'>',...
    s{24}(1,:),s{24}(2,:),'<',...
    s{25}(1,:),s{25}(2,:),'p',...
    s{26}(1,:),s{26}(2,:),'h',...
    s{27}(1,:),s{27}(2,:),'+',...
    s{28}(1,:),s{28}(2,:),'o',...
    s{29}(1,:),s{29}(2,:),'*',...
    s{30}(1,:),s{30}(2,:),'.',...
    s{31}(1,:),s{31}(2,:),'x',...
    s{32}(1,:),s{32}(2,:),'s',...
    s{33}(1,:),s{33}(2,:),'d',...
    s{34}(1,:),s{34}(2,:),'^',...
    s{35}(1,:),s{35}(2,:),'v',...
    s{36}(1,:),s{36}(2,:),'>',...
    s{37}(1,:),s{37}(2,:),'<',...
    s{38}(1,:),s{38}(2,:),'p',...
    s{39}(1,:),s{39}(2,:),'h',...
    s{40}(1,:),s{40}(2,:),'+');
grid on


%% Save
mkdir('plots')
% Print to .eps file for nice latex integration
print(fig_performance, 'plots/comparison_performance','-depsc');
print(fig_performance_pca, 'plots/comparison_performance_pca','-depsc');
print(fig_mnist_pca, 'plots/mnist_pca_plot','-depsc');
print(fig_orl_pca, 'plots/orl_pca_plot','-depsc');
